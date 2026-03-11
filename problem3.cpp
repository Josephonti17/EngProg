// Problem 3 
// Homework 2

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

bool parseLine(const std::string& line, 
               std::vector<int>& values) {
    //Parses a line of text into a vector of integers.
    values.clear();
    std::istringstream iss(line);
    std::string token;


    while (iss >> token) {
        std::istringstream tokenStream(token);
        int num;
        tokenStream >> num;

        // Check that the entire token was consumed as an integer
        if (tokenStream.fail() || !tokenStream.eof()) {
            values.clear();
            return false;
        }
        values.push_back(num);
        //Returns true if ALL tokens on the line are valid integers.
        //Returns false if any token is non-numeric.
    }

    // An empty line is not considered valid
    return !values.empty();
}


double average(const std::vector<int>& values) {
    //Computes the average of a vector of integers.
    double sum = 0.0;
    for (int v : values) {
        sum += v;
    }
    return sum / values.size();
}


int main(int argc, char* argv[]) {
    // Read filename from argv
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return 1;
    }

    // Tracking variables
    int totalLines  = 0;
    int validLines  = 0;
    int totalInts   = 0;

    std::string line;
    std::vector<int> values;

    // Process line-by-line
    while (std::getline(infile, line)) {
        totalLines++;

        if (parseLine(line, values)) {
            validLines++;
            totalInts += static_cast<int>(values.size());

            // Output per valid line
            std::cout << std::fixed << std::setprecision(1);
            std::cout << "Line " << totalLines
                      << ": count=" << values.size()
                      << " avg=" << average(values)
                      << std::endl;
        } else {
            std::cout << "Warning: Line " << totalLines
                      << " contains invalid data. Skipped." << std::endl;
        }
    }

    infile.close();

    // Final summary
    std::cout << "\n -Summary-" << std::endl;
    std::cout << "Total lines processed: " << totalLines  << std::endl;
    std::cout << "Total valid lines:     " << validLines  << std::endl;
    std::cout << "Total integers read:   " << totalInts   << std::endl;

    return 0;
}
