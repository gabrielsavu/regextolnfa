#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "hash.h"
#include "dfa.h"
#include "lnfa.h"

int main() {


    std::ifstream in("in.in");
    std::ofstream out("out.out");
    LNFA d;
    std::string word;
    in >> d;
    unsigned n;
    in >> n;
    for (unsigned j = 0; j < n ; j ++) {
        in >> word;
        out << (d.checkWord(word) ? "DA" : "NU") << std::endl;
    }
    return 0;
}