#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;
using std::unordered_map;
using std::set;
using std::string;

int main() {
    
    set<string> states_needed = {"mt","wa","or","id","nv","ut","ca","az"};

    vector<string> result;
    unordered_map<string, set<string>> stations;

    stations["kone"] = set<string>({"id","nv","ut"});
    stations["ktwo"] = set<string>({"wa","id","mt"});
    stations["kthree"] = set<string>({"or","nv","ca"});
    stations["kfour"] = set<string>({"nv","ut"});
    stations["kfive"] = set<string>({"ca","az"});

    while(!states_needed.empty()){
        string best_station = "";
        set<string> states_covered = {};

        for(const auto& [station_name, station_states] : stations){
            set<string> covered;

            std::set_intersection(
                states_needed.begin(),
                states_needed.end(),
                station_states.begin(),
                station_states.end(),
                std::inserter(covered, covered.begin())
            );

            if(covered.size() > states_covered.size()){
                states_covered = covered;
                best_station = station_name;
            }
        }

        for(const auto& n : states_covered){
            states_needed.erase(n);
        }

        result.push_back(best_station);
    }

    for(const auto& str : result){
        std::cout << str << ' ';
    }

}