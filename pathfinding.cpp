#include "pathfinding.h"
#include <limits>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <iostream>
template <typename Iterator>
void customReverse(Iterator begin, Iterator end) {
    while ((begin != end) && (begin != --end)) {
        std::iter_swap(begin++, end);
    }
}
Pathfinding::Pathfinding(
    const std::map<std::string, std::pair<double, double>>& locations,
    const std::vector<std::tuple<std::string, std::string, double>>& edges)
    : locations(locations) {
    buildGraph(edges);
}

void Pathfinding::buildGraph(const std::vector<std::tuple<std::string, std::string, double>>& edges) {
    for (const auto& edge : edges) {
        const std::string& start = std::get<0>(edge);
        const std::string& end = std::get<1>(edge);
        double distance = std::get<2>(edge);

        graph[start].emplace_back(end, distance);
        graph[end].emplace_back(start, distance); // Assuming undirected graph
    }
}

std::vector<std::string> Pathfinding::findShortestPath(const std::string& start, const std::string& end) {
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> previous;
    std::priority_queue<std::pair<double, std::string>,
                        std::vector<std::pair<double, std::string>>,
                        std::greater<>> pq;
    // Step 1: Initialize distances and priority queue
    for (const auto& node : locations) {
        distances[node.first] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0.0;

    pq.emplace(0.0, start);
    // Step 2: Dijkstra's Algorithm loop
    while (!pq.empty()) {
        auto [currentDistance, currentNode] = pq.top();
        pq.pop();

        if (currentNode == end) break;

        if (currentDistance > distances[currentNode]) continue;

        for (const auto& [neighbor, weight] : graph[currentNode]) {
            double newDistance = currentDistance + weight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                previous[neighbor] = currentNode;
                pq.emplace(newDistance, neighbor);
            }
        }
    }

    // Reconstruct path
    std::vector<std::string> path;
    for (std::string at = end; at != ""; at = previous[at]) {
        path.push_back(at);
    }
    customReverse(path.begin(), path.end());

    return path;
}

double Pathfinding::calculateDistance(const std::vector<std::string>& route) {
    double totalDistance = 0.0;

    for (size_t i = 1; i < route.size(); ++i) {
        const std::string& start = route[i - 1];
        const std::string& end = route[i];

        for (const auto& neighbor : graph[start]) {
            if (neighbor.first == end) {
                totalDistance += neighbor.second;
                break;
            }
        }
    }

    return totalDistance;
}
