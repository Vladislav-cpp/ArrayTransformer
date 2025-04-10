#include "TMiscUtils.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>

namespace miscUtils {

std::vector<int> ParseLineToNumbers(const std::string& line) {
    std::vector<int> result;
    std::string token;
    std::istringstream stream(line);

    char ch;
    while(stream.get(ch)) {
        if(std::isdigit(ch) || ch == '-' || ch == '+') {
            token += ch;

        } else if( (ch == ' ' || ch == ',') && !token.empty() ) {
            result.push_back(std::stoi(token));
            token.clear();
        }
    }

    if(!token.empty()) result.push_back(std::stoi(token));

    return result;
}

std::vector<std::vector<int>> ReadArraysFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> arrays;

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return arrays;
    }

    std::string line;
    while (std::getline(file, line)) {
        arrays.push_back(ParseLineToNumbers(line));
    }

    file.close();
    return arrays;
}

}