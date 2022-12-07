//
// Created by loris on 07.12.2022.
//

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <bits/stdc++.h>
#include <regex>

using namespace std;

namespace BF {
    namespace HASH { // HSH => HASH
        enum HashType {
            md5 = 0 << 0,
            sha1 = 1 << 0,
            sha2 = 1 << 1,
            sha256 = 1 << 2,
            sha512 = 1 << 3,
            sha224 = 1 << 4,
            sha384 = 1 << 5
        };

        BF::HASH::HashType CURR_HASH_T = BF::HASH::HashType::sha1;

        void set_curr_hash_t(const string &ht_name);
        string hash_string(const string &secret_str);
    }

    namespace CS { // CS => CHAR_SET
        const vector<char> CHAR_SET{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R','S', 'T', 'U','V','W','X', 'Y', 'Z',' ','+','"','@','*','#','%','&','/','|','(',')','=','?','\'','^','`','~','[',']','!','{','}','$','-','_','.',':',',',';','<','>','\\'};
        const int LAST_INDEX = (BF::CS::CHAR_SET.size() - 1);
    }

    void brute_force(const string &secret, void (*callback_func)(string));
}

#endif //BRUTEFORCE_BRUTEFORCE_H
