//
// Created by Randy on 9/23/2019.
//

#include "GridfloatReader.h"
#include <cmath>
#include <fstream>
#include <algorithm>
#include <boost/iostreams/device/mapped_file.hpp>

using std::sort, std::vector, std::ios, std::string, std::unordered_map;

GridfloatReader::GridfloatReader(const string& fileName, int lat, int lng) {
    topLat = lat;
    leftLng = lng;
    originX = (double) lng - (double) xBuffer * third_arc_second;
    originY = (double) lat + (double) yBuffer * third_arc_second;
    pixelX = third_arc_second;
    pixelY = third_arc_second;
    const std::size_t fileSize = 10812 * 10812 * 4; // 4 is sizeof(float)
    mmapFile.open(fileName, fileSize);
//    file.open(fileName, ios::in | ios::binary);
}

long GridfloatReader::toFilePosition(double lat, double lng) {
    return (xBuffer + (long) round((lng - leftLng)/third_arc_second)) +
           (yBuffer + (long) round((topLat - lat)/third_arc_second)) * nCols;
}

unordered_map<long, float> GridfloatReader::readElevationsMmap(vector<long>& positions) {
    std::sort(positions.begin(), positions.end());
    unordered_map<long, float> results;
    auto elevationFile = (float*) mmapFile.data();
    for (long position: positions) {
        results[position] = elevationFile[position];
    }
    return results;
}
