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

std::vector<std::string> Automata::getQ () {
    return this->Q;
}

void Automata::setQ (const std::vector<std::string> &Q) {
    this->Q = Q;
}

std::vector<std::string> Automata::getF () {
    return this->F;
}

void Automata::setF (const std::vector<std::string> &F) {
    this->F = F;
}

std::vector<std::string> Automata::getSigma () {
    return this->Sigma;
}

void Automata::setSigma (const std::vector<std::string> &Sigma) {
    this->Sigma = Sigma;
}

std::string Automata::getq0 () {
    return this->q0;
}

void Automata::setq0 (const std::string &q0) {
    this->q0 = q0;
}

unsigned Automata::getnQ () {
    return this->nQ;
}

void Automata::setnQ (const unsigned & nQ) {
    this->nQ = nQ;
}

unsigned Automata::getnF () {
    return this->nF;
}

void Automata::setnF (const unsigned & nF) {
    this->nF = nF;
}

unsigned Automata::getnSigma () {
    return this->nSigma;
}

void Automata::setnSigma (const unsigned &nSigma) {
    this->nSigma = nSigma;
}

unsigned Automata::getnDelta () {
    return this->nDelta;
}

void Automata::setnDelta (const unsigned &nDelta) {
    this->nDelta = nDelta;
}

Hash Automata::getDelta () {
    return Delta;
}

void Automata::setDelta (const Hash &Delta) {
    this->Delta = Delta;
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