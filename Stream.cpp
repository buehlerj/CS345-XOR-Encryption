#include "Stream.h"

bool Stream::xor_encrypt() {
    for (int i = 0; i < text.size(); i++) {
        key[i] = text[i] ^ key[i % key.size()];
    }
    return true;
}

bool Stream::xor_decrypt() {
    for (int i = 0; i < text.size(); i++) {
        key[i] = text[i] ^ key[i % key.size()];
    }
    return true;
}



bool Stream::read_input_file(istream& input_file) {
    while (!input_file.eof()) {
        char current = (char) input_file.get();
        if (input_file.fail())
            break;
        text += current;
    }
    return true;
}

bool Stream::read_keyfile(istream& keyfile) {
    while (!keyfile.eof()) {
        char current = (char) keyfile.get();
        if (keyfile.fail())
            break;
        key += current;
    }
    return true;
}

bool Stream::write_output(ostream& output_file) {
    for (int i = 0; i < text.size(); i++) {
        output_file << text[i];
    }
    return true;
}
