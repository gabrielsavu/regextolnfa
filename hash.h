//
// Created by htpzn on 29.03.2019.
//

#ifndef DFA_HASH_H
#define DFA_HASH_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class Hash {
private:
    static const unsigned hashSize = 100;
    struct bucket {
        bool empty;
        std::string Q;
        std::string word;
        std::string out;
        bucket *next;
    };
    bucket **hashTable;

public:
    Hash();

    ~Hash();

    Hash(const Hash &);

    static unsigned createHash(std::string);

    void pushBucket(const std::string&, const std::string&, const std::string&);

    std::vector<std::string> getBucket(std::string, std::string);

    bool checkBucket(const std::string&, const std::string&);

    Hash* concatenate(Hash*);

    friend std::ostream &operator << (std::ostream&, Hash&);

};

#endif //DFA_HASH_H
