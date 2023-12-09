#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;
namespace fs = std::__fs::filesystem;

class RoadMap {
public:
    RoadMap(const std::string& RoadMapName);
    void printLine(const std::string& input);
    void addBranch(const std::string& fileName);
    void deleteBranch(const std::string& fileName);
    RoadMap& findRoadMap(const std::string& RoadMapName) ;
    void addChildRoadMap(RoadMap& child);
    void deleteChildRoadMap(const string& childRoadMapName);
    void setParentRoadMap(RoadMap* parent);
    string getRoadMapName() const;
    void showBranch();
    void deleteMap();
    std::vector<int> getIDFile();

private:
    void createDirectory();
    void showRecursive(const std::string& currentPath, int depth);

    string RoadMapName;
    string fileID;
    vector<RoadMap> childRoadMap;
    RoadMap* parentRoadMap;
};