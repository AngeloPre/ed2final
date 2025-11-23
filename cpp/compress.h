#ifndef COMPRESS_H
#define COMPRESS_H

#include <cstdint>

// Cabeçalho mínimo do arquivo compactado.
// tamanho_original -> número de bytes do arquivo original (original_size)
// tamanho_bloco    -> implementar (e utilizar) depois para descompressão + busca
// numero_blocos    -> num_blocks
struct Cabecalho {
    std::uint64_t tamanho_original;
    std::uint32_t tamanho_bloco;
    std::uint32_t numero_blocos;
};

int compactar(const char* nome_arquivo_entrada,
              const char* nome_arquivo_saida);

#endif
