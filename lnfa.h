//
// Created by htpzn on 29.03.2019.
//

#ifndef DFA_LNFA_H
#define DFA_LNFA_H
#include <iostream>
#include <queue>
#include <utility>
#include "hash.h"
#include "automata.h"

class LNFA: public Automata {
private:

public:
    friend std::istream &operator >> (std::istream&, LNFA&);

    friend std::ostream &operator << (std::ostream &, LNFA&);

    bool checkWord(std::string);

    std::vector<std::string> lambdaClosure (const std::string&);
};


#endif //DFA_LNFA_H
