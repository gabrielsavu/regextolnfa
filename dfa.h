//
// Created by htpzn on 29.03.2019.
//

#ifndef DFA_DFA_H
#define DFA_DFA_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "hash.h"
#include "automata.h"

class DFA: private Automata {
private:
public:
    friend std::istream &operator >>(std::istream&, DFA&);

    bool checkWord(std::string);

};

#endif //DFA_DFA_H
