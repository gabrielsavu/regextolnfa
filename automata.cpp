//
// Created by htpzn on 29.03.2019.
//

#include "automata.h"

void Automata::read(std::istream &input, std::vector<std::string>& v, unsigned& n) {
    std::string temp;
    input >> n;
    for(unsigned i = 0; i < n; i ++) {
        input >> temp;
        v.push_back(temp);
    }
}


std::istream &operator >> (std::istream &input, Automata &obj ) {
    std::string temp, temp2, temp3;
    Automata::read(input, obj.Q, obj.nQ);
    Automata::read(input, obj.Sigma, obj.nSigma);
    input >> obj.q0;
    Automata::read(input, obj.F, obj.nF);
    input >> obj.nDelta;
    for(unsigned i = 0; i < obj.nDelta; i ++) {
        input >> temp >> temp2 >> temp3;
        obj.Delta.pushBucket(temp, temp2, temp3);
    }
    return input;
}