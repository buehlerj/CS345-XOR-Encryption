#include "Block.h"

bool Block::xor_encrypt() {
    for (int i = 0; i < blocks_count; i++) {
        for (int j = 0; j < blocks[i].size(); j++) {
            blocks[i][j] = blocks[i][j] ^ key[j];
        }
    }
    if (!swap()) {cerr << "Error: Problem Swapping" << endl; return false;}
    return true;
}

bool Block::xor_decrypt() {
    if (!swap()) {cerr << "Error: Problem Unswapping" << endl; return false;}
    for (int i = 0; i < blocks_count; i++) {
        for (int j = 0; j < (unsigned int) blocks[i].size(); j++) {
            blocks[i][j] = (blocks[i][j] ^ key[j]);
        }
    }
    if (!unpad()) {cerr << "Error: Problem unpadding" << endl; return false;}
    return true;
}


bool Block::read_input_file(istream& input_file) {
    string current_block;
    while (!input_file.eof()) {
        for (int i = 0; i < 8; i++) {
            char current = (char) input_file.get();
            if (input_file.fail()) {
                char_count--;
                current_block += (current >> 8);
            }
            else current_block += current;
            char_count++;
        }
        blocks.insert(blocks.begin() + blocks_count, current_block);
        blocks_count++;
        current_block = "";
    }
    pad_size = 8 - (char_count % 8);
    return true;
}

bool Block::read_keyfile(istream& keyfile) {
    for (int i = 0; i < 8; i++) {
        key += (char) keyfile.get();
        if (keyfile.fail()) {cerr << "Error: Problem reading from the keyfile" << endl; return false;}
    }
    return true;
}

bool Block::write_output(ostream& file) {
    file << to_string_padded();
    if (file.fail()) {
        cerr << "Error: Could not print to file" << endl;
        return false;
    }
    return true;
}





bool Block::swap() {
    string text = to_string_padded();
    int end = 8 * blocks_count - 1;
    for (int i = 0; i < 8 * blocks_count; i++) {
        if (i == end) break;
        char current_key = key[i % 8];
        if ((int)current_key % 2 == 1) {
            char temp = text[i];
            text[end] = text[i];
            text[i] = temp;
            end--;
        }
    }
    for (int i = 0; i < blocks_count; i++) {
        blocks[i] = text.substr(i * 8, 8);
    }
    return true;
}

bool Block::unpad() {
    cout << blocks[blocks_count - 1].size() << endl;
    blocks[blocks_count - 1] = blocks[blocks_count - 1].substr(0, pad_size);
    cout << blocks[blocks_count - 1].size() << endl;
    return true;
}

string Block::to_string_padded() {
    string text = "";
    for (int i = 0; i < blocks_count; i++) {
        text += blocks[i];
    }
    return text;
}

string Block::to_string_unpadded() {
    string text = "";
    for (int i = 0; i < blocks_count; i++) {
        if (i == (blocks_count - 1))
            text += blocks[i].substr(0, (unsigned int) (8 - pad_size));
        else
            text += blocks[i];
    }
    return text;
}


