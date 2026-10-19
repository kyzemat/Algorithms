#include <iostream>
#include <limits>
#include <unordered_map>
#include <optional>
#include <queue>
#include "graph.h"
using std::pair;
using std::cout;
using std::unordered_map;
using std::string;


   
    void weighted_graph::AddNode(const std::string& str, const std::string& neighbour, int weight) {
        if(weight < 0){
            cout << "\nЗначение не было добавлено, так как вес должен быть положительным!\n";\
            return;
        }
        graph[str];                 // гарантируем, что str есть
        graph[neighbour];           // гарантируем, что neighbour есть
        graph[str][neighbour] = weight;
    }

    std::optional<unordered_map<string, int>> weighted_graph::search_optimal(const string &node) {
        if(graph.find(node) == graph.end()){
            cout << "\nТакого узла нет в графе!\n";
            return std::nullopt;
        }
        
        unordered_map<string, int> weights;
        unordered_map<string, string> path;
        
        for(const auto& [v, _] : graph){
            weights[v] = INT_MAX;
            path[v] = "";
        }
        weights[node] = 0;

        using P = pair<int, string>;
        std::priority_queue<P, std::vector<P>, std::greater<>> pq;//Задаем приоритетную Min очередь. На верху минимальные
        pq.push({0, node});

        while(!pq.empty()){
            auto [weight, parent] = pq.top();
            pq.pop();

            if(weight > weights[parent]) continue;

            for(const auto& [neighbour, cost] : graph.at(parent)){
                if(weight + cost< weights[neighbour]){
                    weights[neighbour] = weight + cost;
                    path[neighbour] = parent;
                    pq.push({weights[neighbour], neighbour});
                }
            }
        }
        return weights;
    }