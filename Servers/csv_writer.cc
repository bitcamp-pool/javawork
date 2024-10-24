#include "csv_writer.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace Oasis;

CSVWriter::CSVWriter(const std::string& filename) : filename(filename) {}

void CSVWriter::StatisticsWrite(const Statistics& stats) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open CSV file.");
    }

    file << "name,value\n";
    file << "filename," << stats.filename << "\n";
    file << "TAT(s)," << stats.TAT << "\n";
    file << "filesize(MB)," << stats.fileSizeMB << "\n";
    file << "#cells," << stats.totalCells << "\n";
    file << "#layers," << stats.totalLayers << "\n";
    file << "#shapes," << stats.totalShapes << "\n";
    file << "#shapes_expand," << stats.totalShapesExpand << "\n";
    file << "#refs," << stats.totalPlacements << "\n";
    file << "#refs_expand," << stats.totalPlacementsExpand << "\n";

    for (int i = 0; i < 12; ++i) {
        file << "#srep_" << i << "," << stats.srepCounts[i] << "\n";
        file << "#srep_" << i << "_expand," << stats.srepExpandCounts[i] << "\n";
    }

    file.close();
}

