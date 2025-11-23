#include "kmp.h"
#include <iostream>
#include <ostream>

int main(void) {
    std::string pattern = "AAB";
    std::string text = "AAABCAABA";

    KMP kmp = KMP();
    kmp.initializeDFA(pattern);

    for (char c : text) {
        int pos = kmp.stepDFA(c);
        std::cout << (pos == -1 ? "R " : "A ");
    }

    std::cout << std::endl;
}