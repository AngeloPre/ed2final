#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include "arvore.h"

using std::size_t;

class HuffmanNode {
    public:
        Arvore* arvore;
        size_t tam;

        HuffmanNode(Arvore* a, size_t t) : arvore(a), tam(t) {}
};

bool comparaPorTamanho(const HuffmanNode& a, const HuffmanNode& b) {
    return a.tam < b.tam;
}

size_t frequencias[256];
std::list<HuffmanNode> arvoreHuffman;
std::string codigos[256];

void contaFrequencia(size_t freq[], const char buffer[], size_t length) {
    for (size_t i = 0; i < length; i++) {
        unsigned char byteVal = static_cast<unsigned char>(buffer[i]);
        freq[byteVal]++;
    }
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

void printTreeHorizontal(Arvore* node, std::string prefix = "", bool isLeft = true, bool isRoot = true) {
    if (node == nullptr) {
        return;
    }

    // Print right subtree first (top part of display)
    if (node->dir != nullptr) {
        printTreeHorizontal(node->dir, prefix + (isRoot ? "" : (isLeft ? "│   " : "    ")), false, false);
    }

    // Print current node
    std::cout << prefix;
    if (!isRoot) {
        std::cout << (isLeft ? "└── " : "┌── ");
    }
    std::cout << node->info << std::endl;

    // Print left subtree (bottom part of display)
    if (node->esq != nullptr) {
        printTreeHorizontal(node->esq, prefix + (isRoot ? "" : (isLeft ? "    " : "│   ")), true, false);
    }
}

void printTree(Arvore* root) {
    if (root == nullptr) {
        std::cout << "(empty tree)" << std::endl;
        return;
    }
    printTreeHorizontal(root);
}

void gerarCodigos(Arvore* arv, std::string codigos[], std::string codAnterior) {
    if (arv != nullptr) {
        gerarCodigos(arv->esq, codigos,codAnterior + "0");
        gerarCodigos(arv->dir, codigos,codAnterior + "1");
    }
    else return;

    //Apenas nós folhas
    if (arv->dir == nullptr && arv->esq == nullptr) {
        unsigned char byteVal = static_cast<unsigned char>(arv->info);
        codigos[byteVal] = codAnterior;
    }

}

int main(int argc, char** argv) {
    const size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    if (argc != 2) {
        std::cerr << "Passe o nome do arquivo a ser lido!\n";
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Erro: não foi possível abrir arquivo!\n";
        return 1;
    }

    while (true) {
        // Read up to BUFFER_SIZE bytes
        file.read(buffer, BUFFER_SIZE);
        std::streamsize bytesRead = file.gcount();

        if (bytesRead <= 0) {
            // No more data to read (EOF or error)
            break;
        }

        // Process this chunk of data (here we just write it to stdout)
        contaFrequencia(frequencias, buffer, bytesRead);

        // If EOF reached, stop
        if (file.eof()) {
            break;
        }

        // If some other error occurred, handle it
        if (!file && !file.eof()) {
            std::cerr << "\nError while reading file.\n";
            return 1;
        }
    }

    preencheArvoreInicial(arvoreHuffman, frequencias);

    arvore* final = gerarTrieHuffman(arvoreHuffman);

    printTreeHorizontal(final);

    gerarCodigos(final, codigos, "");

    for (int i = 0; i < 256; i++) {
        if (codigos[i].size() != 0){
            std::cout << static_cast<char>(i) << ", " << "Codigo :" << codigos[i] << '\n';
        }
    }

    

    return 0;
}