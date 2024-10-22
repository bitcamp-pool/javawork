#include <iostream>
#include <chrono>
#include "parser.h"
#include "analyzer.h"
#include "csv_writer.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: anuvad-analysis <input.oas> <output.csv>" << endl;
        return 1;
    }

    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    auto start = high_resolution_clock::now();

    try {
        Oasis::OasisParser parser(inputFile);
        Analyzer analyzer;

        parser.parseFile(&analyzer);

        CSVWriter writer(outputFile);
        writer.write(analyzer.getStatistics());

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end - start).count();
    cout << "Analysis completed in " << duration << " seconds." << endl;

    return 0;
}
