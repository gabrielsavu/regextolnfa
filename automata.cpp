//
// Created by htpzn on 29.03.2019.
//

#include "automata.h"



Automata::~Automata() {
    delete Delta;
}

Automata::Automata() {
    this->nQ = 0;
    this->nF = 0;
    this->nSigma = 0;
    this->nDelta = 0;
    this->Delta = nullptr;
}

Automata::Automata(const Automata &obj) {
    this->Q = obj.Q;
    this->F = obj.F;
    this->Sigma = obj.Sigma;
    this->q0 = obj.q0;
    this->nQ = obj.nQ;
    this->nF = obj.nF;
    this->nSigma = obj.nSigma;
    this->nDelta = obj.nDelta;
    this->Delta = new Hash(*obj.Delta);
}

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

void Automata::pushQ (const std::string& s) {
    this->Q.push_back(s);
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

void Automata::concatenateSigma (const std::vector<std::string> &s) {
    this->Sigma.insert(this->Sigma.end(), s.begin(), s.end());

    sort(this->Sigma.begin(), this->Sigma.end());
    auto last = std::unique(this->Sigma.begin(), this->Sigma.end());
    this->Sigma.erase(last, this->Sigma.end());
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

Hash* Automata::getDelta () {
    return Delta;
}

void Automata::setDelta (Hash* Delta) {
    this->Delta = Delta;
}


std::istream &operator >> (std::istream &input, Automata &obj) {
    std::string temp, temp2, temp3;
    Automata::read(input, obj.Q, obj.nQ);
    Automata::read(input, obj.Sigma, obj.nSigma);
    input >> obj.q0;
    Automata::read(input, obj.F, obj.nF);
    input >> obj.nDelta;
    obj.Delta = new Hash();
    for(unsigned i = 0; i < obj.nDelta; i ++) {
        input >> temp >> temp2 >> temp3;
        obj.Delta->pushBucket(temp, temp2, temp3);
    }
    return input;
}

std::ostream &operator << (std::ostream &output, Automata &obj) {
    //unsigned index;
    output << obj.nQ << std::endl;
    for (const auto& i : obj.Q) {
        output << i << " ";
    }
    output << std::endl;
    output << obj.nSigma << std::endl;
    for (const auto& i : obj.Sigma) {
        output << i << " ";
    }
    output << std::endl << obj.q0 << std::endl << obj.nF << std::endl;
    for (const auto& i : obj.F) {
        output << i << " ";
    }
    output << std::endl << obj.nDelta << std::endl;
    output << (Hash&)*obj.Delta;
    return output;
}