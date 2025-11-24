#include "bitwriter.h"

BitWriter::BitWriter(std::ostream &o)
    : out(o), buffer(0), bit_count(0) {}

void BitWriter::writeBit(int bit) {
    // Pega o buffer ex: 0011 faz shift com "<<"
    // 0000 0011 << 1 = 0000 0110 e o bitwise or coloca o bit no final
    // 0000 0110 | 0000 0001 = 0111
    buffer = static_cast<unsigned char>((buffer << 1) | (bit & 1));
    bit_count++;
    if (bit_count == 8) {
        out.put(static_cast<char>(buffer));
        buffer = 0;
        bit_count = 0;
    }
}

void BitWriter::writeByte(unsigned char b) {
    if (bit_count == 0) {
        out.put(static_cast<char>(b));
    } else {
       for (int i = 7; i >= 0; --i) {
            writeBit((b >> i) & 1);
        }
    }
}

void BitWriter::flush() {
    if (bit_count > 0) {
        buffer = static_cast<unsigned char>(buffer << (8 - bit_count));
        out.put(static_cast<char>(buffer));
        buffer = 0;
        bit_count = 0;
    }
}
