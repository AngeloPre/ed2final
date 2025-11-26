#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include "lib/arvore.h"
#include "lib/huffman.h"
#include "lib/bitwriter.h"
#include "lib/bitreader.h"
#include "lib/kmp.h"
#include "compress.h"

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

Arvore* lerTrie(BitReader &br) {
    int bit = br.lerBit();
    if (bit == -1) {
        // EOF inesperado
        return nullptr;
    }

    if (bit == 1) {
        // Nó folha: lê 1 byte com o símbolo
        unsigned char c;
        if (!br.lerByte(c)) {
            return nullptr;
        }
        return arv_constroi(static_cast<char>(c), nullptr, nullptr);
    } else {
        // Nó interno: bit == 0
        Arvore* esq = lerTrie(br);
        Arvore* dir = lerTrie(br);
        return arv_constroi('\0', esq, dir);
    }
}

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

int compactar(const char* nome_arquivo_entrada,
              const char* nome_arquivo_saida) {
    const size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    // Zera vetor de frequências
    std::memset(frequencias, 0, sizeof(frequencias));

    std::ifstream file(nome_arquivo_entrada, std::ios::binary);
    if (!file) {
        std::cerr << "Erro: nao foi possivel abrir arquivo de entrada!\n";
        return 1;
    }

    std::uint64_t tamanho_original = 0;

    // 1ª PASSAGEM: conta frequências e tamanho_original
    while (true) {
        file.read(buffer, BUFFER_SIZE);
        std::streamsize bytesRead = file.gcount();

        if (bytesRead <= 0) {
            break;
        }

        contaFrequencia(frequencias, buffer,
                        static_cast<size_t>(bytesRead));
        tamanho_original += static_cast<std::uint64_t>(bytesRead);

        if (file.eof()) {
            break;
        }
        if (!file && !file.eof()) {
            std::cerr << "\nErro de leitura no arquivo de entrada.\n";
            return 1;
        }
    }
    file.close();

    // Arquivo vazio: grava só o cabeçalho mínimo
    if (tamanho_original == 0) {
        std::ofstream saida_vazia(nome_arquivo_saida, std::ios::binary);
        if (!saida_vazia) {
            std::cerr << "Erro: nao foi possivel abrir arquivo de saida!\n";
            return 1;
        }

        Cabecalho cabecalho{};
        cabecalho.tamanho_original = 0;
        cabecalho.tamanho_bloco    = 0;
        cabecalho.numero_blocos    = 0;

        saida_vazia.write(reinterpret_cast<const char*>(&cabecalho),
                          sizeof(Cabecalho));
        return 0;
    }

    // Constrói árvore de Huffman e códigos
    arvoreHuffman.clear();
    preencheArvoreInicial(arvoreHuffman, frequencias);

    Arvore* final = gerarTrieHuffman(arvoreHuffman);
    if (!final) {
        std::cerr << "Erro ao construir arvore de Huffman.\n";
        return 1;
    }

    for (int i = 0; i < 256; ++i) {
        codigos[i].clear();
    }
    gerarCodigos(final, codigos, "");

    // Abre arquivo de saída e grava cabeçalho (header mínimo)
    std::ofstream outputFile(nome_arquivo_saida, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Erro: nao foi possivel abrir arquivo de saida!\n";
        return 1;
    }

    Cabecalho cabecalho{};
    cabecalho.tamanho_original = tamanho_original;                     // original_size
    cabecalho.tamanho_bloco    = static_cast<std::uint32_t>(tamanho_original); // block_size (1 bloco = arquivo)
    cabecalho.numero_blocos    = 1;                                   // num_blocks
    //std::cout << "tamanho original: " << (double)tamanho_original/1024/1024;
    outputFile.write(reinterpret_cast<const char*>(&cabecalho),
                     sizeof(Cabecalho));

    // Grava a trie em pré-ordem logo após o cabeçalho
    BitWriter bw(outputFile);
    escreverTrie(final, bw);
    // bw.flush(); // alinha bits que podem sobrar no fianl

    // 2ª PASSAGEM: relê arquivo e escreve o texto compactado
    file.open(nome_arquivo_entrada, std::ios::binary);
    if (!file) {
        std::cerr << "Erro: nao foi possivel reabrir arquivo de entrada!\n";
        return 1;
    }

    while (true) {
        file.read(buffer, BUFFER_SIZE);
        std::streamsize bytesRead = file.gcount();

        if (bytesRead <= 0) {
            break;
        }

        escreverTexto(codigos, bw, buffer,
                      static_cast<size_t>(bytesRead));

        if (file.eof()) {
            break;
        }
        if (!file && !file.eof()) {
            std::cerr << "\nErro de leitura durante compressao.\n";
            return 1;
        }
    }

    bw.flush();
    file.close();
    outputFile.close();

    arv_libera(final);

    return 0;
}

int descompactar(const char* nome_arquivo_compactado,
                 const char* nome_arquivo_saida) {
    std::ifstream entrada(nome_arquivo_compactado, std::ios::binary);
    if (!entrada) {
        std::cerr << "Erro: nao foi possivel abrir arquivo compactado!\n";
        return 1;
    }

    // Lê o cabeçalho para saber o tamanho_original
    Cabecalho cabecalho{};
    if (!entrada.read(reinterpret_cast<char*>(&cabecalho),
                      sizeof(Cabecalho))) {
        std::cerr << "Erro ao ler cabeçalho do arquivo compactado.\n";
        return 1;
    }

    std::uint64_t tamanho_original = cabecalho.tamanho_original;
    if (tamanho_original == 0) {
        // Arquivo original vazio -> cria saída vazia e encerra
        std::ofstream saida_vazia(nome_arquivo_saida, std::ios::binary);
        if (!saida_vazia) {
            std::cerr << "Erro: nao foi possivel criar arquivo de saida.\n";
            return 1;
        }
        return 0;
    }

    // Configura o BitReader a partir da posição atual do arquivo (logo após o cabeçalho)
    BitReader br(entrada);

    // Reconstrói a árvore de Huffman a partir da trie serializada
    Arvore* raiz = lerTrie(br);
    if (!raiz) {
        std::cerr << "Erro ao reconstruir a arvore de Huffman.\n";
        return 1;
    }

    std::ofstream saida(nome_arquivo_saida, std::ios::binary);
    if (!saida) {
        std::cerr << "Erro: nao foi possivel criar arquivo de saida.\n";
        arv_libera(raiz);
        return 1;
    }

    // Agora lê bits do arquivo comprimido e navega na árvore até reconstruir
    // exatamente tamanho_original bytes.
    std::uint64_t bytes_escritos = 0;
    Arvore* atual = raiz;

    while (bytes_escritos < tamanho_original) {
        int bit = br.lerBit();
        if (bit == -1) {
            std::cerr << "Fim inesperado de arquivo durante descompactacao.\n";
            arv_libera(raiz);
            return 1;
        }

        // Caminha na árvore: 0 -> esq, 1 -> dir
        if (bit == 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }

        if (!atual) {
            std::cerr << "Caminho invalido na arvore de Huffman.\n";
            arv_libera(raiz);
            return 1;
        }

        // Se chegou em folha, temos um símbolo completo
        if (!atual->esq && !atual->dir) {
            saida.put(atual->info);
            ++bytes_escritos;
            atual = raiz; // volta para a raiz para decodificar o próximo símbolo
        }
    }

    entrada.close();
    saida.close();
    arv_libera(raiz);
    return 0;
}

int buscar_simples(const char* nome_arquivo, const char* substring) {
    // Validação
    if (!substring || strlen(substring) == 0) {
        std::cerr << "Substring vazia!\n";
        return 1;
    }
    
    std::string pattern(substring);
    
    // Abre o arquivo
    std::ifstream file(nome_arquivo, std::ios::binary);
    if (!file) {
        std::cerr << "Erro: nao foi possivel abrir arquivo!\n";
        return 1;
    }
    
    // Inicializa o KMP e as vars
    KMP kmp;
    kmp.initializeDFA(pattern);
    int count = 0;
    
    const size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    
    while (file.read(buffer, BUFFER_SIZE) || file.gcount() > 0) {
        std::streamsize bytesRead = file.gcount();
        
        // Processa cada caractere do chunk
        std::string chunk = std::string(buffer, bytesRead);
        for (size_t i = 0; i < chunk.length(); i++) {
            int match_pos = kmp.stepDFA(static_cast<unsigned char>(chunk[i]));
            
            if (match_pos != -1) {
                std::cout << "Posicao (byte): " << match_pos << "\n";
                count++; 
            }
        }
    }
    
    file.close();
    
    if (count == 0) 
        std::cout << "Substring nao encontrada.\n";
    else {
        std::cout << "Substring encontrada em " << count
        << " posicao(oes):\n";
    }
    
    return 0;
}

int buscar_compactado(const char* nome_arquivo_compactado, const char* substring) {
    std::ifstream entrada(nome_arquivo_compactado, std::ios::binary);
    if (!entrada) {
        std::cerr << "Erro: nao foi possivel abrir arquivo compactado!\n";
        return 1;
    }

    // Lê o cabeçalho para saber o tamanho_original
    Cabecalho cabecalho{};
    if (!entrada.read(reinterpret_cast<char*>(&cabecalho),
                      sizeof(Cabecalho))) {
        std::cerr << "Erro ao ler cabeçalho do arquivo compactado.\n";
        return 1;
    }

    std::uint64_t tamanho_original = cabecalho.tamanho_original;
    if (tamanho_original == 0) {
        std::cout << "Arquivo vazio" << std::endl;
        return 0;
    }

    // Configura o BitReader a partir da posição atual do arquivo (logo após o cabeçalho)
    BitReader br(entrada);

    // Reconstrói a árvore de Huffman a partir da trie serializada
    Arvore* raiz = lerTrie(br);
    if (!raiz) {
        std::cerr << "Erro ao reconstruir a arvore de Huffman.\n";
        return 1;
    }

    //Inicializa KMP para o processamento
    KMP kmp = KMP();
    kmp.initializeDFA(substring);
    int count = 0;

    // Agora lê bits do arquivo comprimido e navega na árvore até reconstruir
    // exatamente tamanho_original bytes.
    std::uint64_t bytes_analizados = 0;
    Arvore* atual = raiz;

    while (bytes_analizados < tamanho_original) {
        int bit = br.lerBit();
        if (bit == -1) {
            std::cerr << "Fim inesperado de arquivo durante descompactacao.\n";
            arv_libera(raiz);
            return 1;
        }

        // Caminha na árvore: 0 -> esq, 1 -> dir
        if (bit == 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }

        if (!atual) {
            std::cerr << "Caminho invalido na arvore de Huffman.\n";
            arv_libera(raiz);
            return 1;
        }

        // Se chegou em folha, temos um símbolo completo
        if (!atual->esq && !atual->dir) {
            int match_pos = kmp.stepDFA(static_cast<unsigned char>(atual->info));

            if (match_pos != -1) {
                std::cout << "Posicao (byte): " << match_pos << "\n";
                count++; 
            }
            ++bytes_analizados;
            atual = raiz; // volta para a raiz para decodificar o próximo símbolo
        }
    }

    if (count == 0) 
        std::cout << "Substring nao encontrada.\n";
    else {
        std::cout << "Substring encontrada em " << count
        << " posicao(oes):\n";
    }

    entrada.close();
    arv_libera(raiz);
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Uso:\n"
                  << "  " << argv[0]
                  << " compactar <arquivo_original> <arquivo_compactado>\n"
                  << "  " << argv[0]
                  << " descompactar <arquivo_compactado> <arquivo_saida>\n"
                  << "  " << argv[0]
                  << " buscar_simples <arquivo_original> \"<substring>\"\n";
        return 1;
    }

    std::string comando = argv[1];

    if (comando == "compactar" && argc == 4) {
        return compactar(argv[2], argv[3]);
    } else if (comando == "descompactar" && argc == 4) {
        return descompactar(argv[2], argv[3]);
    } else if (comando == "buscar_simples" && argc == 4) {
        return buscar_simples(argv[2], argv[3]);
    } else if (comando == "buscar_compactado") {
        return buscar_compactado(argv[2], argv[3]);
    } else {
        std::cerr << "Comando inválido ou argumentos incorretos.\n";
        return 1;
    }
}
