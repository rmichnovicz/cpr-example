//
// Created by Randy on 9/23/2019.
//
// Make sure you do sudo apt-get install libboost-iostreams-dev
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <boost/iostreams/device/mapped_file.hpp>
#ifndef CPR_EXAMPLE_GRIDFLOATREADER_H
#define CPR_EXAMPLE_GRIDFLOATREADER_H

class GridfloatReader {
    int topLat;
    int leftLng;
    const double third_arc_second = 1.0/60/60/3;
    const long nCols = 10812;
    const long xBuffer = 6;
    const long yBuffer = 6;
//    std::ifstream file;
    boost::iostreams::mapped_file_source mmapFile;
public:
    double originX;
    double originY;
    double pixelX;
    double pixelY;
    explicit GridfloatReader(const std::string& fileName, int lat, int lng);
    // TODO make setFile with header
    long toFilePosition(double lat, double lng);
    std::pair<double, double> fromFilePosition(long position);
    std::unordered_map<long, float> readElevationsMmap(std::vector<long>& positions);
};


#endif //CPR_EXAMPLE_GRIDFLOATREADER_H
