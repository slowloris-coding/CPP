#include <bits/stdc++.h>
#include <thread>
#include <regex>

using namespace std;

std::string exec(string _cmd) {
    const char* cmd = _cmd.c_str();

    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw std::runtime_error("_popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}

bool pingHost(string ip){
        int x = 0;

        stringstream cmd_ss;
        cmd_ss << "ping " << ip << " -n 1 >nul 2>&1";

        string cmd_st = cmd_ss.str();
        const char* cmd_str = cmd_st.c_str();

        x = system(cmd_str);

        return (x == 0);
}

vector<string> split_str(string str, char del){
    vector<string> str_v;
    string tmp_str = "";

    for(int i = 0; i < str.size(); i++){
        if(str[i] == del){
            if(tmp_str.size() > 0){
                str_v.push_back(tmp_str);
            }

            tmp_str = "";
        }
        else {
            tmp_str += str[i];
        }
    }

    if(tmp_str.size() > 0){
        str_v.push_back(tmp_str);
        tmp_str = "";
    }

    return str_v;
}

int two_power(int p){
    int r = 1;

    for(int i = 0; i < p; i++){
        r *= 2;
    }

    return r;
}

namespace IPv4 {
    class IP_ADDR {
    private:
    public:
        int value[4] = {0,0,0,0};
        bitset<32> bit_value;
        string str = "";

        IP_ADDR(){}
        IP_ADDR(int oct0, int oct1, int oct2, int oct3){
            this->value[0] = oct0;
            this->value[1] = oct1;
            this->value[2] = oct2;
            this->value[3] = oct3;

            stringstream ss;
            ss << this->value[0] << "." << this->value[1] << "." << this->value[2] << "." << this->value[3];
            this->str = ss.str();

            int bi = 0;

            for(int i = 0; i < 4; i++){
                bitset<8> oct_bs(this->value[i]);

                for(int j = 0; j < 8; j++, bi+=1){
                    this->bit_value[bi] = oct_bs[j];
                }
            }
        }
    };

    class SN_MASK {
    private:
    public:
        int value[4] = {0,0,0,0};
        int cidr = 0;
        bitset<32> bit_value;
        string str = "";

        SN_MASK(){}
        SN_MASK(int oct0, int oct1, int oct2, int oct3){
            this->value[0] = oct0;
            this->value[1] = oct1;
            this->value[2] = oct2;
            this->value[3] = oct3;

            stringstream ss;
            ss << this->value[0] << "." << this->value[1] << "." << this->value[2] << "." << this->value[3];
            this->str = ss.str();

            int bi = 0;

            for(int i = 0; i < 4; i++){
                bitset<8> oct_bs(this->value[i]);

                for(int j = 7; j >= 0; j--, bi+=1){
                    this->bit_value[bi] = oct_bs[j];
                }
            }

            for(int i=0; i < 32 && this->bit_value[i] == true; i++){
                this->cidr += 1;
            }
        }
    };

    class Host {
    private:
    public:
        IP_ADDR ip;
        SN_MASK subnet_mask;
        bool reachable = false;

        Host(){}
        Host(IP_ADDR ip, SN_MASK sm): ip(ip), subnet_mask(sm){}

        bool ping(int time_out = 1500 /* ms */){
            string cmd_ret;

            stringstream cmd_ss;
            cmd_ss << "ping " << this->ip.str << " -n 1 -w " << time_out; //<< " >nul 2>&1";

            string cmd_st = cmd_ss.str();

            cmd_ret = exec(cmd_ss.str());

            string ip_reg_str = string(to_string(this->ip.value[0]) + "\\." + to_string(this->ip.value[1]) + "\\." + to_string(this->ip.value[2]) + "\\." + to_string(this->ip.value[3]));

            std::regex reg(string(".*" + ip_reg_str + ": Bytes\\=" + ".*\\(0\\%.*"), std::regex::extended);

            if(regex_match(cmd_ret, reg)){
                this->reachable = true;
            }
            else{
                this->reachable = false;
                //cout << cmd_ret << endl;
            }

            return this->reachable;
        }
    };
}


void scan_thread(IPv4::Host *host){
    host->ping();
}

class Subnet{
private:
    int calc_host_addr_count(){
        int free_bits = 32 - this->subnet_mask.cidr;
        int addr_count = 0;

        for(int i = 0; i < free_bits; i++){
            if(addr_count == 0){
                addr_count = 2;
            }else{
                addr_count *= 2;
            }
        }

        return addr_count;
    }

    IPv4::IP_ADDR convert_bin_to_obj(bitset<32> &b_addr){
        vector<bitset<8>> bs_v;
        vector<int> i_oct_v;

        for(int i = 0; i < 32; i += 8){
            bitset<8> oct(0);

            for(int j = 0; j < 8; j++){
                oct[j] = b_addr[(i + j)];
            }

            bs_v.push_back(oct);
        }

        for(auto &bs : bs_v){
            i_oct_v.push_back((int)(bs.to_ulong()));
        }

        IPv4::IP_ADDR ip = IPv4::IP_ADDR(i_oct_v[0], i_oct_v[1], i_oct_v[2], i_oct_v[3]);

        return ip;
    }

    IPv4::IP_ADDR gen_host_addr(int no){
        bitset<32> h_addr = this->net_addr.bit_value;
        bitset<32> h_bits(no);

        // reorder h_bits
        h_bits = h_bits << this->subnet_mask.cidr;

        //cout << h_bits << " --> ";
        h_addr = h_addr | h_bits;
        //cout << h_addr << endl;

        return this->convert_bin_to_obj(h_addr);
    }

    vector<IPv4::IP_ADDR> gen_host_ips(){
        vector<IPv4::IP_ADDR> h_ips;
        int addr_count = this->calc_host_addr_count();

        // var i starts from 1 bc 0 would be the network address
        for(int i=1; i < addr_count; i++){
            if(i == addr_count - 1){
                this->broadcast_addr = this->gen_host_addr(i);
            }else{
                h_ips.push_back(this->gen_host_addr(i));
            }
        }

        return h_ips;
    }

    void create_hosts(){
        vector<IPv4::IP_ADDR> host_ips = this->gen_host_ips();

        for(auto &hi : host_ips){
            IPv4::Host host = IPv4::Host(hi, this->subnet_mask);
            this->hosts.push_back(host);
        }
    }

public:
    IPv4::IP_ADDR net_addr;
    IPv4::IP_ADDR broadcast_addr;

    IPv4::SN_MASK subnet_mask;

    vector<IPv4::Host> hosts;
    vector<IPv4::Host*> reachable_hosts;
    vector<IPv4::Host*> un_reachable_hosts;

    Subnet(){}
    Subnet(IPv4::IP_ADDR addr, IPv4::SN_MASK sm): net_addr(addr), subnet_mask(sm){
        this->create_hosts();
    }

    void scan(){
        vector<thread> scan_threads;

        for(auto &host : this->hosts){
            scan_threads.emplace_back(scan_thread, &host);
        }

        for(auto &th : scan_threads){
            th.join();
        }

        for(auto &host : this->hosts){
            if(host.reachable){
                this->reachable_hosts.push_back(&host);
            }
            else{
                this->un_reachable_hosts.push_back(&host);
            }
        }
    }

    void print_scan_results(bool show_unreachable = false){
        system("cls");
        cout << "[SCAN]" << endl;
        cout << "Subnet:  " << this->net_addr.str << " - " << this->broadcast_addr.str << endl;
        cout << "Mask:    " << this->subnet_mask.str << endl;
        cout << "CIDR:    " << this->subnet_mask.cidr << endl;

        cout << "\n\n[RESULTS]" << endl;

        if(show_unreachable){
            for(auto &host : this->hosts){
                cout << ((host.reachable) ? "\x1b[38;2;0;255;0m[+]\x1b[0m  ": "\x1b[38;2;255;0;0m[x]\x1b[0m  ") << host.ip.str << endl;
            }
        }else{
            for(auto host : this->reachable_hosts){
                cout << "\x1b[38;2;0;255;0m[+]\x1b[0m  " << host->ip.str  << endl;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    int arg_addr[4] = {192,168,0,0};
    int arg_sm[4] = {255,255,255,0};
    bool show_unreachable = false;

    for(int i = 1; i < argc; i++){
        if(regex_match(argv[i], regex("^(\\~n|\\~s|\\~sn|\\~\\~(net|subnet))$"))){
            i += 1;
            vector<string> addr_parts = split_str(string(argv[i]), '.');

            for(int j = 0; j < 4; j++){
                arg_addr[j] = stoi(string(addr_parts[j]));
            }
        }
        else if(regex_match(argv[i], regex("^(\\~c|\\~sm|\\~\\~(cidr|subnetmask|mask))$"))){
            i += 1;

            vector<string> sm_parts = split_str(string(argv[i]), '.');

            for(int j = 0; j < 4; j++){
                arg_sm[j] = stoi(string(sm_parts[j]));
            }
        }
        else if(regex_match(argv[i], regex("^(\\~su|\\~\\~show_unreachable|\\~\\~show_all)$"))){
            i += 1;
            show_unreachable = (regex_match(argv[i], regex("^[Tt]rue$")) || stoi(argv[i]) == 1);
        }
    }

    IPv4::IP_ADDR sn_addr = IPv4::IP_ADDR(arg_addr[0],arg_addr[1],arg_addr[2],arg_addr[3]);
    IPv4::SN_MASK sn_mask = IPv4::SN_MASK(arg_sm[0],arg_sm[1],arg_sm[2],arg_sm[3]);
    Subnet sn = Subnet(sn_addr, sn_mask);

    cout << sn_addr.bit_value << endl;
    cout << sn_addr.str << endl;
    cout << sn_mask.bit_value << endl;
    cout << sn_mask.str << endl;
    cout << sn_mask.cidr << endl;

    cin.get();

    sn.scan();
    sn.print_scan_results(show_unreachable);

    cout << "\n\nPress Enter to continue....";
    cin.get();
    return 0;
}