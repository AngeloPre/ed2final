#include "bitreader.h"

BitReader::BitReader(std::istream &in)
    : entrada(in), buffer(0), bits_restantes(0) {}

int BitReader::lerBit() {
    if (bits_restantes == 0) {
        char c;
        if (!entrada.get(c)) {
            return -1; // EOF ou erro
        }
        buffer = static_cast<unsigned char>(c);
        bits_restantes = 8;
    }

    int bit = (buffer & 0x80) ? 1 : 0;      // lê o bit mais significativo(https://stackoverflow.com/questions/45362872/whats-the-meaning-of-this-condition-if-buffer0-0x80)
    buffer <<= 1;                           // avança
    --bits_restantes;
    return bit;
}

bool BitReader::lerByte(unsigned char &b) {
    int bit;
    unsigned char valor = 0;
    for (int i = 0; i < 8; ++i) {
        bit = lerBit();
        if (bit == -1) {
            return false;
        }
        valor = static_cast<unsigned char>((valor << 1) | (bit & 1));
    }
    b = valor;
    return true;
}
