// Copyright (C) 2024 DJ Rao (raodm@miamioh.edu)

#include <iostream>
#include <string>
#include "Dictionary.h"

// Forward declaration for the processFile method
void processFile(std::istream&, const Dictionary&);

/*
 * The main method that processses command-line argument and calls
 * the processFile method to do the actual processing.
 */
int main(int argc, char** argv) {
    // Create the dictionary object to be used in this program.
    // Call methods as: dict.toEngWord(word) and 
    // dict.isEnglishWord(word)
    Dictionary dict;

    // Process command-line arguments.
    if (argc < 2) {
        std::cerr << "Missing command-line arguments.\n";
        return 1;  // Non-zero exit code on error.
    }
    std::ifstream input(argv[1]);
    if (!input.good()) {
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        return 2;
    }
    // Now have the helper method do all the processing
    processFile(input, dict);
    // All done.
    return 0;
}
