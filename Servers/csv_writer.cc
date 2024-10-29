#include "csv_writer.h"
#include <fstream>

using namespace Oasis;
using namespace Jeong;

CSVWriter::CSVWriter(const std::string& filename) : filename(filename) {}

void
CSVWriter::OasisStatisticsWrite(const OasisStatistics& stats) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    // CSV 헤더 출력
    file << "name,value\n";

    for (const auto& key : stats.keyOrder) {
        auto it = stats.mapper.find(key);
        if (it != stats.mapper.end()) {

            if (key == "filename" ||
                key == "cell_maxrefs" ||
                key == "cell_maxshapes_a_layer" ||
                key == "layer_maxshapes_a_layer" ||
                key == "cell_maxshapes_all_layer" ||
                key == "cell_maxcblockcount_a_cell" ||
                key == "cell_maxcellsize" ||
                key == "cell_mincellsize" ||
                key == "cell_maxplist" ||
                key == "layer_maxplist")
            {
                // Handle string values
                const std::string* strValue = static_cast<const std::string*>(it->second);
                file << key << "," << *strValue << "\n";

            } else if (key == "cblock" || key == "strict" || key == "xyrelative" || key == "xyabsolute") {
                // Handle boolean values
                const bool* boolValue = static_cast<const bool*>(it->second);
                file << key << "," << (*boolValue ? "on" : "off") << "\n";

            } else {
                // Handle long long values
                const long long* llValue = static_cast<const long long*>(it->second);
                file << key << "," << *llValue << "\n";
            }

        }

    }

    file.close();
}

