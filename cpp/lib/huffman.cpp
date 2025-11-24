#include "huffman.h"

//Construtor da classe
HuffmanNode::HuffmanNode(Arvore* a, size_t t) : arvore(a), tam(t) {};

bool comparaPorTamanho(const HuffmanNode& a, const HuffmanNode& b) {
    return a.tam < b.tam;
}

void preencheArvoreInicial(std::list<HuffmanNode>& huff, size_t freq[]) {
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            Arvore* newArvore = arv_constroi(static_cast<char>(i), nullptr, nullptr);
            huff.push_back(HuffmanNode(newArvore, freq[i]));
        }
    }
}

Arvore* gerarTrieHuffman(std::list<HuffmanNode>& huff) {
    huff.sort(comparaPorTamanho);
    while (huff.size() > 1) {
        HuffmanNode n1 = huff.front(); huff.pop_front();
        HuffmanNode n2 = huff.front(); huff.pop_front();
        Arvore* newArvore = arv_constroi('\0', n1.arvore, n2.arvore);
        huff.emplace_back(newArvore, n1.tam + n2.tam);
        huff.sort(comparaPorTamanho);
    }
    if (huff.empty()) return nullptr;
    return huff.front().arvore;
}