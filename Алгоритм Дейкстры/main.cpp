#include <iostream>
#include "graph.h"
using std::cout;

int main() {
    std::optional<std::unordered_map<std::string, int>> answer;

    weighted_graph graph;

    graph.AddNode("Начало", "A", 5);
    graph.AddNode("Начало", "B", 2);
    graph.AddNode("B", "A",8);
    graph.AddNode("B","C",7);
    graph.AddNode("A","C",2);
    graph.AddNode("A", "D", 4);
    graph.AddNode("D", "C", 6);
    graph.AddNode("D","Конец",3);
    graph.AddNode("C","Конец", 1);

    answer = graph.search_optimal("Начало");

    if(answer.has_value())
        cout << (*answer)["Конец"];
}