//
// Created by htpzn on 31.03.2019.
//

#include "regex.h"

bool Regex::isOperator (char character) {
    return character == '*' || character == '+' || character == '.' || character == '|' || character == '(' || character == ')';
}

LNFA* new_symbol (unsigned &index, char character) {
    LNFA* symbol = new LNFA;
    unsigned start;

    symbol->setnQ(2);
    start = index;
    index ++;
    symbol->setQ((std::vector<std::string>){std::to_string(start), std::to_string(index)});

    symbol->setnSigma(1);
    symbol->setSigma((std::vector<std::string>){std::string(1, character)});

    symbol->setq0(std::to_string(start));

    symbol->setnF(1);
    symbol->setF((std::vector<std::string>){std::to_string(index)});

    symbol->setnDelta(1);
    Hash *h = new Hash();
    h->pushBucket(std::to_string(start), std::string(1, character), std::to_string(index));
    symbol->setDelta(h);

    index ++;
    return symbol;
}

LNFA* kleene (LNFA* symbol, unsigned &index) {
    LNFA* out = new LNFA;
    unsigned new_start;
    std::string initial_start, initial_final;
    std::vector<std::string> a, b;

    out->setnQ(symbol->getnQ() + 2);
    a = symbol->getQ();
    index ++;
    new_start = index;
    b = {std::to_string(new_start), std::to_string(++index)};
    a.insert(a.end(), b.begin(), b.end());
    out->setQ(a);

    out->setnSigma(symbol->getnSigma());
    out->setSigma(symbol->getSigma());

    initial_start = symbol->getq0();
    out->setq0(std::to_string(new_start));

    out->setnF(symbol->getnF());
    initial_final = symbol->getF()[0];
    out->setF((std::vector<std::string>){std::to_string(index)});

    out->setnDelta(symbol->getnDelta() + 4);

    Hash *h = new Hash(*symbol->getDelta());

    h->pushBucket(std::to_string(new_start), ".", initial_start);
    h->pushBucket(std::to_string(new_start), ".", std::to_string(index));
    h->pushBucket(initial_final, ".", std::to_string(index));
    h->pushBucket(std::to_string(index), ".", std::to_string(new_start));

    out->setDelta(h);
    delete symbol;
    return out;
}

LNFA* concatenate(LNFA* first, LNFA* second, unsigned &index) {
    LNFA* out = new LNFA(*first);

    for (const auto& it : second->getQ()) {
        out->pushQ(it);
    }

    out->setnQ(out->getQ().size());
    out->concatenateSigma(second->getSigma());
    out->setnSigma(out->getSigma().size());

    out->setnDelta(out->getnDelta()+second->getnDelta()+1);
    Hash *Delta = out->getDelta()->concatenate(second->getDelta());
    Delta->pushBucket(first->getF()[0], ".", second->getq0());
    out->setDelta(Delta);
    out->setF((std::vector<std::string>){second->getF()[0]});


    delete first;
    delete second;
    return out;
}

LNFA* or_selection(LNFA* first, LNFA* second, unsigned &index) {
    LNFA* out = new LNFA(*first);
    unsigned start, final;

    for (auto it : second->getQ()) {
        out->pushQ(it);
    }
    index ++;
    start = index;
    out->pushQ(std::to_string(start));
    index ++ ;
    out->pushQ(std::to_string(index));
    final = index;
    out->setnQ(out->getQ().size());

    out->concatenateSigma(second->getSigma());
    out->setnSigma(out->getSigma().size());

    out->setnDelta(out->getnDelta()+second->getnDelta()+4);
    Hash *Delta = out->getDelta()->concatenate(second->getDelta());

    Delta->pushBucket(std::to_string(start), ".", first->getq0());
    Delta->pushBucket(std::to_string(start), ".", second->getq0());
    Delta->pushBucket(first->getF()[0], ".", std::to_string(final));
    Delta->pushBucket(second->getF()[0], ".", std::to_string(final));

    out->setDelta(Delta);


    out->setF((std::vector<std::string>){std::to_string(final)});

    out->setq0(std::to_string(start));

    delete first;
    delete second;
    return out;
}

LNFA* Regex::regexToLNFA (const std::string &word) {

    std::stack<char> operators;
    std::stack<LNFA*> operands;
    std::stack<LNFA*> concatenate_stack;
    unsigned index = 0, count = 0;
    bool expect = false;
    char sym;
    LNFA *symbol, *op1, *op2;
    for (auto it : word) {
        if (!isOperator(it)) {
            symbol = new_symbol(index, it);
            operands.push(symbol);
            if (expect) operators.push('.');
            else expect = true;
        }
        else {
            if (it == '*') {
                LNFA *star_symbol = operands.top();
                operands.pop();
                operands.push(kleene(star_symbol, index));
                expect = true;
            }
            else if (it == '+') {
                LNFA *current_symbol = operands.top();
                operands.pop();

            }
            else if(it == '.') {
                operators.push(it);
                expect = false;
            }
            else if (it == '|') {
                operators.push(it);
                expect = false;
            }
            else if (it == '(') {
                operators.push(it);
                count ++ ;
            }
            else {
                expect = false;
                if (count == 0) {
                    return nullptr;
                }
                else count -- ;
                while (!operators.empty() && operators.top() != '(') {
                    sym = operators.top();
                    operators.pop();

                    if (sym == '.') {
                        op2 = operands.top();
                        operands.pop();
                        op1 = operands.top();
                        operands.pop();
                        operands.push(concatenate(op1, op2, index));
                    }
                    if (sym == '|') {
                        op2 = operands.top();
                        operands.pop();
                        if (!operators.empty() && operators.top() == '.'){

                            concatenate_stack.push(operands.top());
                            operands.pop();
                            while (!operators.empty() && operators.top() == '.'){

                                concatenate_stack.push(operands.top());
                                operands.pop();
                                operators.pop();
                            }
                            LNFA *temp = concatenate_stack.top();
                            concatenate_stack.pop();

                            op1 = concatenate(temp, concatenate_stack.top(), index);
                            concatenate_stack.pop();
                            while (concatenate_stack.size() > 0){
                                op1 = concatenate(op1, concatenate_stack.top(), index);
                                concatenate_stack.pop();
                            }
                        }
                        else {
                            op1 = operands.top();
                            operands.pop();
                        }
                        operands.push(or_selection(op1, op2, index));
                    }
                }
            }
        }
    }
    while (operators.size() > 0){
        if (operands.empty()) {
            return nullptr;
        }
        sym = operators.top();
        operators.pop();
        if (sym == '.'){
            op2 = operands.top();
            operands.pop();
            op1 = operands.top();
            operands.pop();
            operands.push(concatenate(op1, op2, index));
        }
        else if (sym == '|') {
            op2 = operands.top();
            operands.pop();
            if (!operators.empty() && operators.top() == '.'){
                concatenate_stack.push(operands.top());
                operands.pop();
                while (!operators.empty() && operators.top() == '.'){
                    concatenate_stack.push(operands.top());
                    operands.pop();
                    operators.pop();
                }
                LNFA *temp = concatenate_stack.top();
                concatenate_stack.pop();

                op1 = concatenate(temp, concatenate_stack.top(), index);
                concatenate_stack.pop();
                while (concatenate_stack.size() > 0) {
                    op1 = concatenate(op1, concatenate_stack.top(), index);
                    concatenate_stack.pop();
                }
            }
            else{
                op1 = operands.top();
                operands.pop();
            }
            operands.push(or_selection(op1, op2, index));
        }
    }
    return operands.top();
}