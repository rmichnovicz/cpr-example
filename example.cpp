#include <iostream>

#include <cpr/cpr.h>
#include <json.hpp>
#include "Api.h"


int main(int argc, char** argv) {
    Api a;
    std::string url = "[out:json];(way[\"highway\"=\"primary\"](33.770652831622,-84.399268627167,33.774385164345,-84.393609166145););out;>;out skel qt;";
    a.setMap(url);
    a.setElevations();

}
