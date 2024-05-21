#include "test.hpp"

#include <fstream>
#include <getopt.h>
#include <iostream>


Test::Test() {}


void Test::ReadArgs(int argc, char **argv) {
    const char *const short_opts = "f:m:v:h";
    const option long_opts[] = {
            {"file_name", required_argument, nullptr, 'f'},
            {"method", required_argument, nullptr, 'm'},
            {"searching_word", required_argument, nullptr, 'v'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
        if (-1 == opt) {
            if (args_.empty()) {
                args_["help"] = "true";
            }
            break;
        }
        switch (opt) {
        case 'f':
            args_["file_name"] = std::string(optarg);
            break;
        case 'm':
            args_["method"] = std::string(optarg);
            break;
        case 'v':
            args_["searching_word"] = std::string(optarg);
            break;
        case 'h':
        case '?':
        default:
            args_["help"] = "true";
            break;
        }
    }
}


void Test::ExecuteCommand() {
    try {
        if (args_["help"] == "true") {
            PrintHelp();
        } else if (args_["method"] == "words") {
            CountWord();
            std::cout << word_count_ << '\n';
        } else if (args_["method"] == "checksum") {
            CountChecksum();
            std::cout << checksum_ << '\n';
        } else {
            PrintHelp();
        }
    } catch (ErrorCode &ex) {
        switch (ex) {
        case ErrorCode::ArgError:
            std::cout << "Wrong args\n'";
            break;
        case ErrorCode::WrongFile:
            std::cout << "File \"" << args_["file_name"] << "\" doesn't exist";
            break;
        }
    }
}


void Test::PrintHelp() {
    std::cout <<
        "Program takes a file name and a set of parameters as input.\n"
        "Try one of the following:\n\n"
        "`test -f <file> -m words -v <mother>`  -  Prints the number of words <mother> in the file <file>\n"
        "`test -f <file> -m checksum`           -  Prints a 32-bit checksum calculated using the algorithm \n"
        "                                          checksum = word1 + word2 + ... + wordN\n"
        "                                          (word1..wordN – 32-bit words)\n"
        "`test -h`                              -  Prints program information and parameter descriptions.\n";
}


void Test::CountWord() {
    if (args_["file_name"].empty()) {
        throw ErrorCode::ArgError;
    }

    if (args_["searching_word"].empty()) {
        throw ErrorCode::ArgError;
    }
    std::ifstream inputFile(args_["file_name"]);

    if (!inputFile) {
        throw ErrorCode::WrongFile;
    }
    std::string line;
    std::string word = args_["searching_word"];
    size_t word_size = word.size();

    while (std::getline(inputFile, line)) {
        size_t position = line.find(word);
        while (position != std::string::npos) {
            if (isalpha(line[position-1]) + isalpha(line[position+word_size]) == 0) {
                ++word_count_;
            }
            position = line.find(word, position + word_size);
        }
    }
}


void Test::CountChecksum() {
    std::ifstream inputFile(args_["file_name"]);
    if (!inputFile) {
        throw ErrorCode::WrongFile;
    }

    uint32_t word = 0;
    while (inputFile.read(reinterpret_cast<char*>(&word), sizeof(word))) {
        checksum_ += word;
        word = 0;
    }
    checksum_ += word;
}
