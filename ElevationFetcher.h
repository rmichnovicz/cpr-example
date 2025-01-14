//
// Created by Randy on 9/20/2019.
//

#include <gdal_priv.h>
#include <unordered_set>
#ifndef CPR_EXAMPLE_ELEVATIONFETCHER_H
#define CPR_EXAMPLE_ELEVATIONFETCHER_H
#include <tuple>
#include "hash_pair.h"
// function has to live in the std namespace
// so that it is picked up by argument-dependent name lookup (ADL).
using namespace std;

class ElevationFetcher {
    GDALDataset  *poDataset;
    public:
    double originX;
    double originY;
    double pixelX;
    double pixelY;
    GDALRasterBand  *poBand;
        explicit ElevationFetcher(const char* folderName);
        vector<float> getElevations(const vector<pair<int, int>>& latLngs);
//        vector<float> getElevations(const unordered_set<pair<int, int>, hash_pair>& latLngs);
};


#endif //CPR_EXAMPLE_ELEVATIONFETCHER_H
