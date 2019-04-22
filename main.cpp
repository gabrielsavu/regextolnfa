#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "hash.h"
#include "dfa.h"
#include "lnfa.h"
#include "regex.h"

int main() {

    Regex r;
    LNFA *l = r.regexToLNFA("ab*");
    if (l != nullptr) std::cout << *l;
    else std::cout << "Invalid expression.";
    //std::cout << l->checkWord("a");

    return 0;
}