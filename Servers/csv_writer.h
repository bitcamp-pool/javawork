#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <string>
#include "analyzer.h"

class CSVWriter {
public:
    CSVWriter(const std::string& filename);
    void write(const Statistics& stats);

private:
    std::string filename;
};

#endif  // CSV_WRITER_H
