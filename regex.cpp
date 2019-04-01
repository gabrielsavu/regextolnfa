//
// Created by htpzn on 31.03.2019.
//

#include "regex.h"

bool Regex::isOperator (char character) {
    return character == '*' || character == '|' || character == '(' || character == ')';
}

LNFA kleene (LNFA symbol) {
    LNFA out;
 


    return out;
}

LNFA Regex::regexToLNFA (const std::string &word) {


    std::stack<char> operators;
    std::stack<LNFA> operands;
    LNFA *symbol;
    for (auto it : word) {
        if (!isOperator(it)){

            symbol = new LNFA;

            symbol->setnQ(2);
            symbol->setQ((std::vector<std::string>){"q0", "q1"});

            symbol->setnSigma(1);
            symbol->setSigma((std::vector<std::string>){std::string(1, it)});

            symbol->setq0("q0");

            symbol->setnF(1);
            symbol->setF((std::vector<std::string>){"q1"});

            symbol->setnDelta(1);
            Hash h;
            h.pushBucket("q0", std::string(1, it), "q1");
            symbol->setDelta(h);

            operands.push(*symbol);

            delete symbol;


        }
        else {
            if (it == '*') {
                LNFA star_symbol = operands.top();
                operands.pop();
                operands.push(kleene(star_symbol));
            }
            else if (it == '.') {
                operators.push(it);
            }
            else if (it == '|') {
                operators.push(it);
            }
            else if (it == '(') {
                operators.push(it);
            }
            else {

            }

        }


    }
    return operands.top();
}