//
// Created by htpzn on 29.03.2019.
//

#ifndef DFA_AUTOMATA_H
#define DFA_AUTOMATA_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
    Hash *Delta;
public:
    Automata();

    Automata(const Automata &obj);

    ~Automata();

    std::vector<std::string> getQ ();

    void setQ (const std::vector<std::string> &);

    void pushQ (const std::string&);

    std::vector<std::string> getF ();

    void setF (const std::vector<std::string> &);

    std::vector<std::string> getSigma ();

    void setSigma (const std::vector<std::string> &);

    void concatenateSigma (const std::vector<std::string> &);

    std::string getq0 ();

    void setq0 (const std::string &);

    unsigned getnQ ();

    void setnQ (const unsigned &);

    unsigned getnF ();

    void setnF (const unsigned &);

    unsigned getnSigma ();

    void setnSigma (const unsigned &);

    unsigned getnDelta ();

    void setnDelta (const unsigned &);

    Hash* getDelta ();

    void setDelta (Hash*);

    static void read (std::istream &input, std::vector<std::string>&, unsigned&);

    friend std::istream &operator >> (std::istream&, Automata&);

    friend std::ostream &operator << (std::ostream&, Automata&);
};

#endif //DFA_AUTOMATA_H
