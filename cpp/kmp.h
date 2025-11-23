#ifndef KMP_H
#define KMP_H

#include <list>
#include <string>
#include <vector>

class KMP {
    public:
        KMP();
        ~KMP();

        void initializeDFA(std::string substring);

        void resetDFA();

        int stepDFA(unsigned char c);

    private:
        int state;
        unsigned long pos;
        std::vector<std::vector<int>*> DFA;
        std::list<int> dict;
        std::vector<int>* emptyArr;
};

#endif