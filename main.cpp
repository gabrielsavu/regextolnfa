#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

class Hash {
private:
    static const unsigned hashSize = 40;
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
    unsigned createHash(std::string);
    void pushBucket(const std::string&, const std::string&, const std::string&);
    std::string getBucket(std::string, std::string);
    inline bool checkBucket(const std::string&, const std::string&);

};

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
        hash += character;
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

inline bool Hash::checkBucket(const std::string& Q, const std::string& word) {
    unsigned index = createHash(Q + word);
    return hashTable[index]->empty;
}

std::string Hash::getBucket(std::string Q, std::string word) {
    unsigned index = createHash(Q + word);
    if (hashTable[index]->empty) return "";
    bucket *p = hashTable[index];
    while(p != nullptr) {
        if(p->word == word && p->Q == Q)
            return p->out;
        p = p->next;
    }
    return "";
}

void read(std::vector<std::string>& v, unsigned& n) {
    std::string temp;
    std::cin >> n;
    for(unsigned i = 0; i < n; i ++) {
        std::cin >> temp;
        v.push_back(temp);
    }
}


int main() {


    std::ifstream f("in.in");
    if(f.is_open()){
        std::cin.rdbuf(f.rdbuf());
    }
    Hash Delta;
    std::vector<std::string> Q, F, Sigma;
    unsigned nQ, nF, nSigma, nDelta , i;
    std::string q0, temp, word, temp2, temp3;


    read(Q, nQ);
    read(Sigma, nSigma);
    std::cin >> q0;
    read(F, nF);

    std::cin >> nDelta;

    for(i = 0; i < nDelta; i ++) {
        std::cin >> temp >> temp2 >> temp3;
        Delta.pushBucket(temp, temp2, temp3);
    }

    std::cin >> word;
    std::string q = q0;
    i = 0;
    bool incomplete = false;
    while (i < word.length()) {
        if(!Delta.checkBucket(q, std::string(1, word[i]))) {
            q = Delta.getBucket(q, std::string(1, word[i]));
            i++;
        }
        else {
            incomplete = true;
            break;
        }
    }
    if (incomplete)
        std::cout << "NU";
    else {
        if (std::find(F.begin(), F.end(), q) != F.end())
            std::cout << "DA";
        else
            std::cout << "NU";
    }

    return 0;
}