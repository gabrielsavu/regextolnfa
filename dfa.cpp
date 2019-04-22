//
// Created by htpzn on 29.03.2019.
//

#include "dfa.h"


std::istream &operator >> (std::istream &input, DFA &obj ) {
    input >> (Automata&)obj;
    return input;
}

bool DFA::checkWord (std::string word) {
    std::string q = q0;
    unsigned i;
    i = 0;
    bool incomplete = false;
    while (i < word.length()) {
        if(!Delta->checkBucket(q, std::string(1, word[i]))) {
            q = Delta->getBucket(q, std::string(1, word[i])).back();
            i++;
        }
        else {
            incomplete = true;
            break;
        }
    }
    if (incomplete)
        return false;
    else {
        return std::find(F.begin(), F.end(), q) != F.end();
    }
}