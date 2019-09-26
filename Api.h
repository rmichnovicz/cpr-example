//
// Created by Randy on 9/19/2019.
//

#ifndef CPR_EXAMPLE_API_H
#define CPR_EXAMPLE_API_H

using namespace std;

class Api {
    double defaultSpeed = .03;

    unordered_map<int, int> node_id_to_index;
    vector<tuple<double, double>> latLng;
    vector<vector<int>> graph;
    vector<vector<int>> steps;
    vector<vector<vector<float>>> graphElevations;
    vector<vector<float>> energyChange;
    vector<float> speed;
    vector<int> prevNode;
    const double third_arc_second = 1.0/60/60/3;
    double getEnergyChange(vector<float>& elevations, double dist);
    double getNewVelocity(vector<float>& elevation, double dist, double v0);
    public:
        void setMap(string a);
        void setElevations();
        void createGraph();
};


#endif //CPR_EXAMPLE_API_H
