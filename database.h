#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <tuple>

// Declare locations and edges
extern std::map<std::string, std::pair<double, double>> locations;
extern std::vector<std::tuple<std::string, std::string, double>> edges;

class Database {
public:
    std::pair<double, double> getCoordinates(const std::string& location);
};

#endif
