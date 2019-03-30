//
// Created by htpzn on 29.03.2019.
//

#ifndef DFA_AUTOMATA_H
#define DFA_AUTOMATA_H
#include <iostream>
#include <vector>
#include <string>
#include "hash.h"

class Automata {
protected:
    std::vector<std::string> Q;
    std::vector<std::string> F;
    std::vector<std::string> Sigma;
    std::string q0;
    unsigned nQ;
    unsigned nF;
    unsigned nSigma;
    unsigned nDelta;
    Hash Delta;
public:
    static void read(std::istream &input, std::vector<std::string>&, unsigned&);

    friend std::istream &operator >>(std::istream&, Automata&);
};

#endif //DFA_AUTOMATA_H
