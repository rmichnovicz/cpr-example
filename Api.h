//
// Created by Randy on 9/19/2019.
//

#ifndef CPR_EXAMPLE_API_H
#define CPR_EXAMPLE_API_H

using namespace std;

class Api {
    unordered_map<int, int> node_id_to_index;
    vector<tuple<double, double>> latLng;
    vector<vector<int>> graph;
    vector<vector<int>> steps;
    vector<double> elevation;
    const double third_arc_second = 1.0/60/60/3;
    public:
        void setMap(string a);
        void setElevations();
};


#endif //CPR_EXAMPLE_API_H
