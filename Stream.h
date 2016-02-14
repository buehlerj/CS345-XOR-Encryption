#ifndef A1_STREAM_H
#define A1_STREAM_H

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

class Stream {

public:
    Stream () {}

    bool xor_encrypt();
    bool xor_decrypt();

    bool read_input_file(istream& input_file);
    bool read_keyfile(istream& keyfile);
    bool write_output(ostream& file);

private:
    string text;
    string key;

};


#endif //A1_STREAM_H
