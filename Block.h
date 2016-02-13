#ifndef A1_BLOCK_H
#define A1_BLOCK_H

#include <iosfwd>
#include <iostream>
#include <ostream>
#include <vector>

using std::cout;
using std::endl;
using std::cerr;
using std::istream;
using std::ostream;
using std::string;
using std::vector;

class Block {

public:
    Block (): char_count(0), blocks_count(0), bytes_count(8), pad_size(0) {}

    bool xor_encrypt();
    bool xor_decrypt();

    bool read_input_file(istream& input_file);
    bool read_keyfile(istream& keyfile);
    bool write_output(ostream& file);

    bool swap();
    bool unpad();

    string to_string_padded();
    string to_string_unpadded();

private:
    vector<string> blocks;
    string key;
    int char_count;
    int blocks_count;
    int bytes_count;
    int pad_size;
};


#endif //A1_BLOCK_H
