#ifndef BITREADER_H
#define BITREADER_H

#include <istream>

class BitReader {
public:
    explicit BitReader(std::istream &in);

    // Lê 1 bit: retorna 0 ou 1; retorna -1 em EOF/erro.
    int lerBit();

    // Lê 1 byte completo a partir da stream de bits.
    // Retorna true se conseguiu ler 8 bits; false em EOF/erro.
    bool lerByte(unsigned char &b);

private:
    std::istream &entrada;
    unsigned char buffer;
    int bits_restantes;
};

#endif
