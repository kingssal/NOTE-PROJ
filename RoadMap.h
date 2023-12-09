#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

class RoadMap {
public:
    RoadMap(const std::string& RoadMapName);
    void printLine(const std::string& input);
    void addBranch(const std::string& fileName);
    void deleteBranch(const std::string& fileName);
    void show();
    void deleteMap();
    std::vector<int> getIDFile();

private:
    void createDirectory();
    void showRecursive(const std::string& currentPath, int depth);

    std::string RoadMapName;
    std::string fileID;
};