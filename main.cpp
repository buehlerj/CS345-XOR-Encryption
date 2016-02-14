#include <iostream>
#include <fstream>
#include "Block.h"
#include "Stream.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

// (B/D) input output keyfile (E/D)
// Test 1
// b D:\jeffs\Documents\test_input\test2.txt D:\jeffs\Documents\test_output\test1_out.txt D:\jeffs\Documents\test_input\keyfile2.txt e
// b D:\jeffs\Documents\test_output\test1_out.txt D:\jeffs\Documents\test_output_2\test1_out_out.txt D:\jeffs\Documents\test_input\keyfile2.txt d

// Test Alphabet
// b D:\jeffs\Documents\test_input\alphabet1.txt D:\jeffs\Documents\test_output\alphabet1_out.txt D:\jeffs\Documents\test_input\keyalphabet1.txt e
// b D:\jeffs\Documents\test_output\alphabet1_out.txt D:\jeffs\Documents\test_output_2\alphabet1_out_out.txt D:\jeffs\Documents\test_input\keyalphabet1.txt d

// Test Stream
// s D:\jeffs\Documents\test_input\alphabet1.txt D:\jeffs\Documents\test_output\alphabet1_out.txt D:\jeffs\Documents\test_input\keyalphabet1.txt e
// s D:\jeffs\Documents\test_output\alphabet1_out.txt D:\jeffs\Documents\test_output_2\alphabet1_out_out.txt D:\jeffs\Documents\test_input\keyalphabet1.txt d
void test() {

}

int main(int argc, char*argv[]) {
    test();
    if (argc != 6) {
        cerr << "Number of Arguments incorrect (" << argc << ")" << endl;
        return -1;
    }

    // Arg1: Block or Stream: cipher_type
    string arg1 = argv[1];
    if (arg1.size() != 1) {
        cerr << "Argument 1 format is invalid (" << arg1 << ")" << endl;
        return -1;
    }
    char cipher_type = (char) tolower(arg1[0]);
    if (cipher_type != 'b' && cipher_type != 's') {
        cerr << "Argument 1 is not correct, please choose (B/S) : " << cipher_type << endl;
        return -1;
    }

    // Arg2: Input file: input_file
    ifstream input_file(argv[2]);
    if (input_file.fail()) {
        cerr << "Error opening the input file (" << argv[2] << ")" << endl;
        return -1;
    }

    // Arg3: Output file: output_file
    ofstream output_file(argv[3]);
    if (output_file.fail()){
        cerr << "Error creating the output file (" << argv[3] << ")" << endl;
        return -1;
    }

    // Arg4: Key File: keyfile
    ifstream keyfile(argv[4]);
    if (keyfile.fail()){
        cerr << "Error opening the key file (" << argv[4] << ")" << endl;
        return -1;
    }

    // Arg5: (En/De)Crypt: mode_of_operation
    string arg5 = argv[5];
    if (arg5.size() != 1) {
        cerr << "Argument 5 format is invalid (" << arg5 << ")" << endl;
        return -1;
    }
    char mode_of_operation = (char) tolower(arg5[0]);
    if (mode_of_operation != 'e' && mode_of_operation != 'd') {
        cerr << "Argument 5 is not correct, please choose (e/d) : " << mode_of_operation << endl;
        return -1;
    }


    if (cipher_type == 'b') { // Block Cipher
        Block block;
        if (!block.read_input_file(input_file)) {cerr << "Error: Problem reading the input file" << endl; return -1;}
        if (!block.read_keyfile(keyfile)) {cerr << "Error: Problem reading the keyfile" << endl; return -1;}
        if (mode_of_operation == 'e') {
            block.xor_encrypt(); // Encrypt
            if (!block.write_output(output_file, false)) {cerr << "Error: Problem writing the output file" << endl; return -1;}
        }
        else {
            block.xor_decrypt(); // Decrypt
            if (!block.write_output(output_file, true)) {cerr << "Error: Problem writing the output file" << endl; return -1;}

        }
    }
    else { // Stream Cipher
        Stream stream;
        if (!stream.read_input_file(input_file)) {cerr << "Error: Problem reading input file" << endl; return -1;}
        if (!stream.read_keyfile(keyfile)) {cerr << "Error: Problem reading keyfile" << endl; return -1;}
        if (mode_of_operation == 'e')
            stream.xor_encrypt(); // Encrypt
        else
            stream.xor_decrypt(); // Decrypt
        if (!stream.write_output(output_file)) {cerr << "Error: Problem writing output file" << endl; return -1;}
    }
    
    return 0;
}
