#pragma once
#include <unordered_map>
#include <optional>
#include <string>

class weighted_graph {
    std::unordered_map<std::string,
                       std::unordered_map<std::string, int>> graph;
public:
    weighted_graph() = default;
    void AddNode(const std::string& str, const std::string& neighbour, int weight);
    std::optional<std::unordered_map<std::string, int>>
        search_optimal(const std::string& node);
};