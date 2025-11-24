#ifndef BITWRITER_H
#define BITWRITER_H

#include <ostream>

class BitWriter {
public:
    explicit BitWriter(std::ostream &o);

    void writeBit(int bit);
    void writeByte(unsigned char b);
    void flush();

private:
    std::ostream &out;
    unsigned char buffer;
    int bit_count;
};

#endif
