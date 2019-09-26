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
//#include "ElevationFetcher.h"

using namespace std;


double latLngToDist(double startLat, double startLng, double latInterval, double lngInterval);

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
//            cout << "key: " << key << ", value:" << way << '\n';
        }
    }

}

void Api::setElevations() {
    // generate set of elevations to query by generating points a maximum of 1/3 arc second apart
    const char *filename = "usgs_ned_13_n34w085_gridfloat.flt";
    GridfloatReader gridfloatReader(filename, 34, -85);
    double startLat, startLng, endLat, endLng;
//    steps.resize(graph.size(), vector<int>());
    std::copy(graph.begin(), graph.end(), back_inserter(steps));
    vector<long> query = vector<long>();
    for (unsigned long i = 0; i < graph.size(); i++) {
//        steps[i].resize(graph[i].size());
        tie(startLat, startLng) = latLng[i];
        for (unsigned long j = 0; j < graph[i].size(); j++) {
            tie(endLat, endLng) = latLng[graph[i][j]];
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
//    query.emplace_back(gridfloatReader.toFilePosition(34.0-.000005, -85.5+.000005));
//    query.emplace_back(gridfloatReader.toFilePosition(34.0 + 5.0/60/60/3, -85.0 -  6.0/60/60/3));
    unordered_map<long, float> elevationsResult = gridfloatReader.readElevationsMmap(query);
//    for (auto& [key, val]: elevationsResult) {
//        cout << key << ": " << val << '\n';
//    }
//    auto query2 = vector<pair<int, int>>();
//    pair<int, int> a(1, 0);
//    query2.emplace_back(a);
//    ElevationFetcher e("grdn34w085_13");
//    vector<float> res = e.getElevations(query2);
//    for (float ele: res) {
//        cout << ele << '\n';
//    }
    graphElevations.resize(graph.size(), vector<vector<float>>());
    energyChange.resize(graph.size(), vector<float>());

    for (unsigned long i = 0; i < graph.size(); i++) {
        graphElevations[i].resize(graph[i].size(), vector<float>());
        tie(startLat, startLng) = latLng[i];
        for (unsigned long j = 0; j < graph[i].size(); j++) {
            tie(endLat, endLng) = latLng[j];
//            double dist = sqrt(pow((endLat - startLat), 2) + pow((endLng - startLng), 2));
//            int numSteps = ceil(dist / third_arc_second);
            int numSteps = steps[i][j];
            graphElevations[i][j] = vector<float>(numSteps);
            double lat = startLat;
            double lng = startLng;
            double latInterval = endLat - startLat;
            double lngInterval = endLng - startLng;
            double dist = latLngToDist(lat, lng, latInterval, lngInterval)
            for (int steps_i = 0; steps_i <= numSteps; steps_i++) {
                graphElevations[i][j][steps_i] = elevationsResult[gridfloatReader.toFilePosition(lat, lng)];
                lat += latInterval;
                lng += lngInterval;
            }
            energyChange[i][j] = getEnergyChange(graphElevations[i][j], dist)
        }
    }
    cout<< "hi"<<'\n';
}

void Api::createGraph() {
    speed.resize(graph.size(), defaultSpeed);
    prevNode.resize(graph.size(), -1);
}

double latLngToDist(double startLat, double startLng, double latInterval, double lngInterval) {
    return 0;
}

double Api::getEnergyChange(vector<float>& elevation, double dist) {
    return 0;
}

double Api::getNewVelocity(vector<float>& elevation, double dist, double v0) {
    return 0;
}
