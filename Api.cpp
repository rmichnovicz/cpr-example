#include <iostream>

#include <cpr/cpr.h>
#include <json.hpp>
#include "GridfloatReader.h"
//#include <gdal_priv.h>
//#include <fstream>
//
// Created by Randy on 9/19/2019.
//

#include "Api.h"
#include "hash_pair.h"

using namespace std;
void Api::setMap(std::string a) {
    // Fetch map
    auto response = cpr::Post(cpr::Url{"https://overpass.kumi.systems/api/interpreter"},
                 cpr::Body{std::move(a)});
    if (response.status_code != 200) {
        return;
    }
    nlohmann::json elements = nlohmann::json::parse(response.text).at("elements");
    // Add nodes to latLng data structure
    int num_nodes = 0;
    for (auto& [key, node] : elements.items()) {
        if ((string) node["type"] == "node"){
            node_id_to_index[node["id"]] = num_nodes;
            latLng.emplace_back(node["lat"], (node["lon"]));
            num_nodes++;
        }
    }
    // Create graph with each element pointing to a vector of 'next' elements
    graph = vector<vector<int>>(num_nodes, vector<int>());
    for (auto& [key, way] : elements.items()) {
        if ((string) way["type"] == "way") {
            vector<int> nodes(way["nodes"].size());
            transform(way["nodes"].begin(), way["nodes"].end(), nodes.begin(), [&](int id) {return this->node_id_to_index[id];});
            for (unsigned long i = 1; i < nodes.size(); i++) {
                graph[nodes[i]].push_back(nodes[i-1]);
                graph[nodes[i-1]].push_back(nodes[i]);
            }
            cout << "key: " << key << ", value:" << way << '\n';
        }
    }

}

void Api::setElevations() {
    // generate set of elevations to query by generating points a maximum of 1/3 arc second apart
    const char *filename = "usgs_ned_13_n34w085_gridfloat.flt";
    GridfloatReader gridfloatReader(filename, 34, -85);
    double startLat, startLng, endLat, endLng;
    steps.resize(graph.size(), vector<int>());
    // Points are represented as a (lat_pixels, lng_pixels) offset from the origin
//    auto elevationsToQuery = unordered_set<pair<int, int>, hash_pair>();
//    const double pixelX = elevationFetcher.pixelX;
//    const double pixelY = elevationFetcher.pixelY;
//    const double originX = elevationFetcher.originX;
//    const double originY = elevationFetcher.originY;
    vector<long> query = vector<long>();
    for (unsigned long i = 0; i < graph.size(); i++) {
        steps[i].resize(graph[i].size());
        tie(startLat, startLng) = latLng[i];
        for (unsigned long j = 0; j < graph[i].size(); j++) {
            tie(endLat, endLng) = latLng[j];
            double dist = sqrt(pow((endLat - startLat), 2) + pow((endLng - startLng), 2));
            int numSteps = ceil(dist / third_arc_second);
            steps[i][j] = numSteps;
            double lat = startLat;
            double lng = startLng;
            double latInterval = endLat - startLat;
            double lngInterval = endLng - startLng;
            for (int steps_i = 0; steps_i <= numSteps; steps_i++) {
                query.emplace_back(gridfloatReader.toFilePosition(lat, lng));
                lat += latInterval;
                lng += lngInterval;
            }
        }
    }
//    query.emplace_back(gridfloatReader.toFilePosition(34.0, -85));
//    query.emplace_back(gridfloatReader.toFilePosition(34.0  - 0.000092592, -85));
    unordered_map<long, float> elevations = gridfloatReader.readElevationsMmap(query);
    for (auto& [key, val]: elevations) {
        cout << key << ": " << val << '\n';
    }
    cout<< "hi"<<'\n';
}