//
// Created by htpzn on 29.03.2019.
//

#include "hash.h"

std::ostream &operator << (std::ostream &output, Hash &obj) {
    for (unsigned i = 0; i < Hash::hashSize; i ++) {
        if (!obj.hashTable[i]->empty) {
            std::cout << obj.hashTable[i]->Q << " " << obj.hashTable[i]->word << " " << obj.hashTable[i]->out << std::endl;
            Hash::bucket *p = obj.hashTable[i]->next;
            while(p != nullptr) {
                std::cout << p->Q << " " << p->word << " " << p->out << std::endl;
                p = p->next;
            }
        }
    }

    return output;
}


Hash* Hash::concatenate(Hash* second) {
    Hash *out = new Hash(*this);

    for (unsigned i = 0; i < Hash::hashSize; i ++) {
        if (!second->hashTable[i]->empty) {
            out->pushBucket(second->hashTable[i]->Q, second->hashTable[i]->word,second->hashTable[i]->out);
            Hash::bucket *p = second->hashTable[i]->next;
            while(p != nullptr) {
                out->pushBucket(p->Q, p->word, p->out);
                p = p->next;
            }
        }
    }
    return out;
}

Hash::Hash() {
    hashTable = new bucket*[hashSize];
    for (unsigned i = 0; i < hashSize; i ++) {
        hashTable[i] = new bucket;
        hashTable[i]->empty = true;
        hashTable[i]->next = nullptr;
    }
}

Hash::~Hash() {
    for (unsigned i = 0; i < hashSize; i ++) {
        delete hashTable[i];
        hashTable[i] = nullptr;
    }
    delete[] hashTable;
    hashTable = nullptr;
}

Hash::Hash(const Hash &h) {
    this->hashTable = new bucket*[hashSize];
    for (unsigned i = 0; i < hashSize; i ++) {
        this->hashTable[i] = new bucket;
        this->hashTable[i]->empty = true;
        this->hashTable[i]->next = nullptr;
    }

    for (unsigned i = 0; i < hashSize; i ++) {
        if (!h.hashTable[i]->empty) {
            pushBucket(h.hashTable[i]->Q, h.hashTable[i]->word, h.hashTable[i]->out);
            bucket *p = h.hashTable[i]->next;
            while(p != nullptr) {
                pushBucket(p->Q, p->word, p->out);
                p = p->next;
            }
        }
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
        hashTable[index]->next = nullptr;
    }
    else {
        bucket *p = hashTable[index];
        auto *new_bucket = new bucket;
        new_bucket->empty = false;
        new_bucket->Q = Q;
        new_bucket->word = word;
        new_bucket->out = in;
        new_bucket->next = nullptr;

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