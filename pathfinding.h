#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <string>
#include <map>
#include <utility> // for std::pair

class Pathfinding {
public:
    Pathfinding(const std::map<std::string, std::pair<double, double>>& locations,
                const std::vector<std::tuple<std::string, std::string, double>>& edges);

    std::vector<std::string> findShortestPath(const std::string& start, const std::string& end);
    double calculateDistance(const std::vector<std::string>& route);

private:
    std::map<std::string, std::pair<double, double>> locations;
    std::map<std::string, std::vector<std::pair<std::string, double>>> graph;

    void buildGraph(const std::vector<std::tuple<std::string, std::string, double>>& edges);
};

#endif

