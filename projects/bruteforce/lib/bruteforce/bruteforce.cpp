//
// Created by loris on 07.12.2022.
//

#include "bruteforce.h"
#include <bits/stdc++.h>
#include <regex>

using namespace std;

void BF::HASH::set_curr_hash_t(const string &ht_name) {
    if(regex_match(ht_name, regex("^[Mm][Dd]\\-?5$"))){
        BF::HASH::CURR_HASH_T = BF::HASH::HashType::md5;
    }
    else if(regex_match(ht_name, regex("^[Ss][Hh][Aa]\\-?1$"))){
        BF::HASH::CURR_HASH_T = BF::HASH::HashType::sha1;
    }
    else if(regex_match(ht_name, regex("^[Ss][Hh][Aa]\\-?2$"))){
        BF::HASH::CURR_HASH_T = BF::HASH::HashType::sha2;
    }
    else if(regex_match(ht_name, regex("^[Ss][Hh][Aa]\\-?224$"))){
        BF::HASH::CURR_HASH_T = BF::HASH::HashType::sha224;
    }
    else if(regex_match(ht_name, regex("^[Ss][Hh][Aa]\\-?256$"))){
        BF::HASH::CURR_HASH_T = BF::HASH::HashType::sha256;
    }
    else if(regex_match(ht_name, regex("^[Ss][Hh][Aa]\\-?348$"))){
        BF::HASH::CURR_HASH_T = BF::HASH::HashType::sha384;
    }
    else if(regex_match(ht_name, regex("^[Ss][Hh][Aa]\\-?512$"))){
        BF::HASH::CURR_HASH_T = BF::HASH::HashType::sha512;
    }
}

string BF::HASH::hash_string(const string &secret_str) {
    switch(BF::HASH::CURR_HASH_T){
        case BF::HASH::HashType::md5 :
            break;

        case BF::HASH::HashType::sha1 :
            break;

        case BF::HASH::HashType::sha2 :
            break;

        case BF::HASH::HashType::sha224 :
            break;

        case BF::HASH::HashType::sha256 :
            break;

        case BF::HASH::HashType::sha384 :
            break;

        case BF::HASH::HashType::sha512 :
            break;

        default:
            return secret_str;
            break;
    }
}


void BF::brute_force(const string &secret, void (*callback_func)(string)){

}