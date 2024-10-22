#include "csv_writer.h"
#include <fstream>

CSVWriter::CSVWriter(const std::string& filename) : filename(filename) {}

void CSVWriter::write(const Statistics& stats) {
    std::ofstream file(filename);
    file << "name,value\n";
    file << "total_cells," << stats.totalCells << "\n";
    file << "total_layers," << stats.totalLayers << "\n";
    file << "total_shapes," << stats.totalShapes << "\n";
    file << "total_placements," << stats.totalPlacements << "\n";
    file << "cell_with_max_refs," << stats.cellWithMaxRefs << "\n";
    file << "cell_with_max_shapes," << stats.cellWithMaxShapes << "\n";
    file.close();
}
