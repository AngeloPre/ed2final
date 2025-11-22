#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "arvore.h"
#include <list>

class HuffmanNode {
    public:
        Arvore* arvore;
        size_t tam;

        HuffmanNode(Arvore* a, size_t t);
};

bool comparaPorTamanho(const HuffmanNode& a, const HuffmanNode& b);

void preencheArvoreInicial(std::list<HuffmanNode>& huff, size_t freq[]);

Arvore* gerarTrieHuffman(std::list<HuffmanNode>& huff);

#endif