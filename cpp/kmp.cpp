#include "kmp.h"
#include <list>
#include <vector>

KMP::KMP() : emptyArr(nullptr) {
    state = 0;
    pos = 0;
    DFA.reserve(256);
}

KMP::~KMP() {
    resetDFA();
}

void KMP::initializeDFA(std::string substring) {
    int M = substring.length();

    emptyArr = new std::vector<int>(M + 1, 0);
    
    for (int i = 0; i < 256; i++) {
        DFA.push_back(emptyArr);
    }
    
    for (char c : substring) {
        int charCode = static_cast<int>(static_cast<unsigned char>(c));
        if (DFA.at(charCode) == emptyArr) {
            DFA.at(charCode) = new std::vector<int>(M + 1, 0);
            dict.push_back(charCode);
        }
    }

    DFA.at(static_cast<int>(static_cast<unsigned char>(substring.at(0))))->at(0) = 1;

    int X = 0; 
    for (int j = 1; j < substring.length(); j++) {
        for (int c : dict) 
            DFA.at(c)->at(j) = DFA.at(c)->at(X);
        
        DFA.at(static_cast<int>(static_cast<unsigned char>(substring.at(j))))->at(j) = j+1;
        X = DFA.at(static_cast<int>(static_cast<unsigned char>(substring.at(j))))->at(X);
    }

    for (int c : dict) {
        DFA.at(c)->at(M) = DFA.at(c)->at(X);
    }
}

void KMP::resetDFA() {
    for (int c : dict) {
        if (DFA.at(c) != emptyArr && DFA.at(c) != nullptr) {
            delete DFA.at(c);
            DFA.at(c) = nullptr;
        }
    }
    
    if (emptyArr != nullptr) {
        delete emptyArr;
        emptyArr = nullptr;
    }
    
    DFA.clear();
    dict.clear();
}

int KMP::stepDFA(unsigned char c) {
    state = DFA.at(static_cast<int>(c))->at(state);
    pos++;
    
    int M = emptyArr->size() - 1;
    
    if (state == M) {
        return pos - M;
    }
    
    return -1;
}

