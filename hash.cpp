//
// Created by htpzn on 29.03.2019.
//

#include "hash.h"

Hash::Hash() {
    hashTable = new bucket*[hashSize];
    for (unsigned i = 0; i < hashSize; i ++) {
        hashTable[i] = new bucket;
        hashTable[i]->empty = true;
        hashTable[i]->next = nullptr;
    }
}

unsigned Hash::createHash(std::string key) {
    unsigned hash = 0, index, i;
    for(char& character : key) {
        hash += character * 17;
    }
    index = hash % hashSize;
    return index;
}

void Hash::pushBucket(const std::string& Q, const std::string& word, const std::string& in) {
    unsigned index = createHash(Q + word);
    if (hashTable[index]->empty) {
        hashTable[index]->empty = false;
        hashTable[index]->Q = Q;
        hashTable[index]->word = word;
        hashTable[index]->out = in;
    }
    else {
        bucket *p = hashTable[index];
        auto *new_bucket = new bucket;
        new_bucket->empty = false;
        new_bucket->Q = Q;
        new_bucket->word = word;
        new_bucket->out = in;

        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = new_bucket;
    }

}

bool Hash::checkBucket(const std::string& Q, const std::string& word) {
    unsigned index = createHash(Q + word);
    bucket *p = hashTable[index];
    while(p != nullptr) {
        if(p->word == word && p->Q == Q)
            return false;
        p = p->next;
    }
    return true;
}

std::vector<std::string> Hash::getBucket(std::string Q, std::string word) {
    unsigned index = createHash(Q + word);
    std::vector<std::string> ret;
    if (checkBucket(Q, word)) return ret;
    bucket *p = hashTable[index];
    while(p != nullptr) {
        if((p->word == word && p->Q == Q) || (p->word == "." && p->Q == Q))
            ret.push_back(p->out);
        p = p->next;
    }
    return ret;
}