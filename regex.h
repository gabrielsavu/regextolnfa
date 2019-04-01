//
// Created by htpzn on 31.03.2019.
//

#ifndef DFA_REGEX_H
#define DFA_REGEX_H

#include "lnfa.h"
#include <stack>

class Regex {
private:

public:
    bool isOperator (char);

    LNFA regexToLNFA (const std::string &);

};

#endif //DFA_REGEX_H
