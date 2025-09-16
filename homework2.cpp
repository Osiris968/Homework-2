/* 
 * File:   homework2.cpp
 *
 * Copyright (C) Michael Kestner kestnemr@miamioh.edu
 * 
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <format>
#include "Dictionary.h"


/** A simple string to print the HTML header. */
const std::string HTML_HEADER =
        "<html>\n"
        "  <body>\n"
        "    <table border=\"1\">\n"
        "      <tr><td>First and last line</td><td>Word counts</td></tr>\n";

/** A simple string to finish the HTML. */
const std::string HTML_TRAILER =
        "    </table>\n"
        "  </body>\n"
        "</html>\n";

/**
 * Convenience method to count number words and number of valid English
 * words in a given line.
 *
 * @param dict The dictionary to be used to clean-up words and check for
 * valid English words.
 * 
 * @param line The line whose words are to be counted by this method.
 *
 * @param wordCounts The current set of counters to be updated by this
 *     method.  This array should have 2 entries, first one being number
 *     of words and the second number is number of valid English words.
 * 
 */
void updateWordCounts(const Dictionary& dict, const std::string& line, 
        int wordCounts[]) {
    // Create a istringstream to read words from the given line.
    std::istringstream wordin(line);
    // Now you can use "wordin" stream the same way as std::cin
    // Process each word and update counters.

    std::string word;
    while (wordin >> word) {
        word = dict.toEngWord(word);
        if (dict.isEnglishWord(word)) {
            wordCounts[1]++;
        }
        wordCounts[0]++;
    }

    // Use dict.toEngWord and dict.isEnglishWord appropriately.
}

/** 
 * Helper method to print summary information about a paragraph in HTML
 * format. 
 * 
 * @param firstLine The first line of the paragraph to be printed.
 * @param lastLine The last line of the paragraph to be printed.
 * @param wordCount An array with count of words and count of valid
 *     English words.
 */
void printInfo(const std::string& firstLine, const std::string& lastLine,
        int wordCount[]) {
    // Print the HTML out in the necessary format
    std::cout << HTML_HEADER << std::endl;

    // BAD GET RID OF
    if (firstLine[0] == 'HTTP/2' || firstLine[0] == 'HTTP/1.1') {
        std::cout << "test first paragraph catch" << std::endl;
        wordCount[0] = wordCount[1] = 0;
        return;
    }

    std::string printLine = ("      <tr><td>" + firstLine 
                            + "<br>" + lastLine + "</td><td>Words: " 
                            + std::to_string(wordCount[0]) 
                            + "<br>English words: " 
                            + std::to_string(wordCount[1]) 
                            + "</td><tr>");

    std::cout << printLine << std::endl;

    std::cout << HTML_TRAILER << std::endl;

    // Reset the word counts
    wordCount[0] = wordCount[1] = 0;
}

/**
 * The top-level method (to be implemented by student) to perform
 * the necessary operation to: 1. count words, 2. count valid English
 * words, and 3. print required output in HTML format. This method
 * is called from main.
 * 
 * \param[in] input The input stream (similar to std::cin) from where
 * lines are to be read (using std::getline) and processed line-by-line.
 * 
 */
void processFile(std::istream& input, const Dictionary& dictionary) {
    // Track word counts:
    //    wordCount[0]: Assume/use as total number of words
    //    wordCount[1]: Assume/use as total valid English words
    // Pass wordCount to the 2 helper methods in this file.
    int wordCount[2] = {0, 0}; 

    size_t words, englishWords;
    std::string line = "", prevLine = "", firstLine = "", lastLine = "";
    std::string word;

    while (std::getline(input, line)) {
        std::cout << "TEST process file" << std::endl;
        updateWordCounts(dictionary, line, wordCount);
        // Indicates first line of paragraph.
        if (!line.empty() && firstLine.empty()) {
            std::cout << "test first line" << std::endl;
            firstLine = line;
        }
        // Indicates last line of paragraph.
        if (line.empty() && !firstLine.empty() && lastLine.empty()) {
            std::cout << "test last line and print" << std::endl;
            lastLine = prevLine;

            // Duplicate lines indicate a one-line paragraph.
            if (lastLine == firstLine) {
                lastLine = "";
            }

            printInfo(firstLine, lastLine, wordCount);
            firstLine = lastLine = "";
        }
        prevLine = line;
    }

    // If while loop skips the last paragraph, (it does in java) uncomment the following:
    // if (!prevLine.empty()) {
    //     if (prevLine == firstLine) {
    //         prevLine = "";
    //     }
    //     printInfo(firstLine, prevLine, wordCount);
    // }

    // Implement rest of this method to do the necessary processing.
}
