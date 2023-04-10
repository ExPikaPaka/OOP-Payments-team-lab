#include "Auth.h"

Auth::Auth() {
	hash = "";
	state = false;
}

Auth::Auth(std::string stringToHash) {
	this->hash = hash256(stringToHash);
    this->state = false;
}

bool Auth::checkHash(std::string stringToHash) {
    state = hash == hash256(stringToHash);
    return state;
}

bool Auth::getState() {
    return state;
}

std::string Auth::hash256() {
    return hash;
}

void Auth::setHash(std::string hash) {
    this->hash = hash;
}

std::string Auth::hash256(std::string stringToHash) {
                  // 18446744073709551615ull - ULLMAX
    uint64_t PRIME_1 = 1099511628211ull;
    uint64_t PRIME_2 = 457182368124ull;
    uint64_t PRIME_3 = 76238736776ull;
    uint64_t PRIME_4 = 66233324132ull;
    uint64_t hash_1 = 12385762189ull;
    uint64_t hash_2 = 487121412ull;
    uint64_t hash_3 = 7423851ull;
    uint64_t hash_4 = 82673524ull;

    for (int i = 0; i < stringToHash.size(); i++) {
        hash_1 *= PRIME_1;
        hash_1 += (int)stringToHash.c_str()[i];

        hash_2 *= PRIME_2;
        hash_2 += (int)stringToHash.c_str()[i];

        hash_3 *= PRIME_3;
        hash_3 += (int)stringToHash.c_str()[i];

        hash_4 *= PRIME_4;
        hash_4 += (int)stringToHash.c_str()[i];

        // hash_1 ^= hash_2;
        // hash_3 ^= hash_4;
    }

    char hashPart_1[17] = { 0 };
    char hashPart_2[17] = { 0 };
    char hashPart_3[17] = { 0 };
    char hashPart_4[17] = { 0 };

    sprintf_s(hashPart_1, "%016llx", hash_1);
    sprintf_s(hashPart_2, "%016llx", hash_2);
    sprintf_s(hashPart_3, "%016llx", hash_3);
    sprintf_s(hashPart_4, "%016llx", hash_4);

    std::string hash256;
    for (int i = 0; i < 16; i++) {
        hash256 += hashPart_1[i];
        hash256 += hashPart_2[i];
        hash256 += hashPart_3[i];
        hash256 += hashPart_4[i];
    }

    return hash256;
}
