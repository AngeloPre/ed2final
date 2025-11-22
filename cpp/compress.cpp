#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <ostream>
#include <string>
#include "arvore.h"
#include "huffman.h"

using std::size_t;

size_t frequencias[256];
std::list<HuffmanNode> arvoreHuffman;
std::string codigos[256];

void contaFrequencia(size_t freq[], const char buffer[], size_t length) {
    for (size_t i = 0; i < length; i++) {
        unsigned char byteVal = static_cast<unsigned char>(buffer[i]);
        freq[byteVal]++;
    }
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

class BitWriter{
    public:
        std::ostream &out;
        unsigned char buffer = 0;
        int bit_count = 0;

        BitWriter(std::ostream &o) : out(o) {}

        void writeBit(int bit) {
            // Pega o buffer ex: 0011 faz shift com "<<"
            // 0000 0011 << 1 = 0000 0110 e o bitwise or coloca o bit no final
            // 0000 0110 | 0000 0001 = 0111
            buffer = (buffer << 1) | bit;
            bit_count++;
            if (bit_count == 8) {
                out.put(buffer);
                buffer = 0;
                bit_count = 0;
            }
        }

        void writeByte(unsigned char b) {
            if (bit_count == 0) {
                out.put(b);
            } else {
                //Extrai os bits usando shifts e bitwise and
                //ex: 1100 0000 >> 7 = 0000 0001 & 1 = 1
                //    1100 0000 >> 5 = 0000 0110 & 1 = 0
                for (int i = 7; i >=0; i--) {
                    writeBit((b >> i) & 1);
                }
            }
        }

        void flush() {
            if (bit_count > 0) {
                buffer <<= (8 - bit_count);
                out.put(buffer);
                buffer = 0;
                bit_count = 0;
            }
        }

};

void escreverTrie(arvore *arv, BitWriter &bw) {
    if (!arv) return;

    if (!arv->esq && !arv->dir) {
        //Armazena 1 se nó folha
        bw.writeBit(1);
        bw.writeByte((unsigned char) arv->info);
    } else {
        //Armazenza 0 caso contrário e percorre a árvore
        bw.writeBit(0);
        escreverTrie(arv->esq, bw);
        escreverTrie(arv->dir, bw);
    }
};

void escreverTexto(std::string codigos[], BitWriter &bw, const char buffer[], size_t length) {
    for (size_t i = 0; i < length; i++) {
        unsigned char byteVal = static_cast<unsigned char>(buffer[i]);
        std::string &cod = codigos[byteVal];
        for (char bitChar : cod) {
            int bit = (bitChar == '1') ? 1 : 0;
            bw.writeBit(bit);
        }
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

    //printTreeHorizontal(final);

    gerarCodigos(final, codigos, "");

    /*for (int i = 0; i < 256; i++) {
        if (codigos[i].size() != 0){
            std::cout << static_cast<char>(i) << ", " << "Codigo :" << codigos[i] << '\n';
        }
    }*/

    std::ofstream outputFile("output");

    BitWriter bw(outputFile);

    escreverTrie(final, bw);

    bw.flush();

    std::ifstream file2(argv[1], std::ios::binary);
    if (!file2) {
        std::cerr << "Erro: não foi possível abrir arquivo!\n";
        return 1;
    }

    while (true) {
        // Read up to BUFFER_SIZE bytes
        file2.read(buffer, BUFFER_SIZE);
        std::streamsize bytesRead = file2.gcount();

        if (bytesRead <= 0) {
            // No more data to read (EOF or error)
            break;
        }

        // Process this chunk of data (here we just write it to stdout)
        escreverTexto(codigos, bw, buffer, bytesRead);

        // If EOF reached, stop
        if (file2.eof()) {
            break;
        }

        // If some other error occurred, handle it
        if (!file2 && !file2.eof()) {
            std::cerr << "\nError while reading file.\n";
            return 1;
        }
    }

    bw.flush();

    return 0;
}