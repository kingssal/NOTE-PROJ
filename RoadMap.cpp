#include "RoadMap.h"

RoadMap::RoadMap(const std::string& RoadMapName) : RoadMapName(RoadMapName), fileID(RoadMapName + ".txt") {
    createDirectory();
}

void RoadMap::printLine(const std::string& input) {// input은 wordDB에서 얻어온 문자열 apple | 1:2, 1:3 이런 형식 사용
    // 단어에 대해서 가중치 표현하는 함수

    std::unordered_map<string, float> countMap;

    size_t pipe_pos = input.find('|');
    std::string result;
    string findWord = input.substr(0, pipe_pos);

    // |가 발견되지 않았거나 문자열의 끝이 아니라면 | 이후의 부분을 저장
    if (pipe_pos != std::string::npos && pipe_pos != input.size() - 1) {
        result = input.substr(pipe_pos + 1);
    }
    std::istringstream iss(result);
    std::string pattern;

    while (std::getline(iss, pattern, ',')) {
        // ':'를 기준으로 숫자를 분할
        size_t pos = pattern.find(':');

        if (pos != std::string::npos) {
            std::string key = pattern.substr(0, pos);

            // 맵에 패턴이 이미 있는지 확인 후 카운트 증가
            countMap[key]++;

        }
    }
    ifstream file(fileID);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileID << std::endl;
        exit(1);
    }
    float max_value = std::numeric_limits<float>::min();
    string line;
    while (getline(file, line)) {
        if (countMap.find(line) != countMap.end()) {
            if (countMap[line] > max_value) max_value = countMap[line];
        }
    }

    // 최대값을 이용하여 모든 int에 나누기
    if (max_value != std::numeric_limits<float>::min() && max_value != 0) {
        for (auto& pair : countMap) {
            pair.second /= max_value;
        }
    }
    file.clear();
    file.seekg(0, ios::beg);


    std::cout << "Similarity for " << findWord << std::endl;
    while (getline(file, line)) {
        if (countMap.find(line) != countMap.end()) {
            cout << "ID" << line << ": ";
            printf("%.2f\n", countMap[line]);
        }
        else {
            cout << "ID" << line << " : 0\n";
        }
    }
    file.close();


}
void RoadMap::addBranch(const std::string& fileName) { // 파일을 디렉토리에 복사하여 저장함. 파일 값이 변할 때 마다 호출해야함
    try {

        fs::path sourcePath = fileName;
        fs::path destinationPath = fs::path(RoadMapName) / fileName;
        if (!fs::is_directory(fileName)) {
            ifstream inputFile(fileName);
            if (!inputFile.is_open()) {
                std::cerr << "Error opening input file." << std::endl;
                exit(1);
            }

            string line;
            getline(inputFile, line);
            size_t pos = line.find(":");
            string ID = line.substr(pos + 1);
            ofstream outputFile(fileID, ios::app);
            if (!outputFile.is_open()) {
                std::cerr << "Error opening output file." << std::endl;
                exit(1);
            }


            ifstream file(fileID);
            if (!file.is_open()) {
                std::cerr << "Error opening input file." << std::endl;
                exit(1);
            }
            bool first = true;
            while (getline(file, line)) {
                if (!ID.compare(line)) {
                    first = false;
                    break;
                }
            }
            if (first) {

                outputFile << ID << std::endl;

            }

            file.close();
            inputFile.close();
            outputFile.close();
        }
        fs::copy(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
        std::cout << "브랜치 추가 성공: " << fileName << " -> " << RoadMapName << std::endl;

    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "오류: " << e.what() << std::endl;
    }
}
void RoadMap::deleteBranch(const std::string& fileName) {//파일을 디렉토리에서 삭제함.
    try {
        fs::path filePath = fs::path(RoadMapName) / fileName;

        // 파일이 존재하는지 확인
        if (fs::exists(filePath)) {
            fs::remove(filePath);
            std::cout << "브랜치 삭제 성공: " << fileName << " -> " << RoadMapName << std::endl;
        }
        else {
            std::cout << "오류: 파일이 존재하지 않습니다. 삭제 실패: " << fileName << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "오류: " << e.what() << std::endl;
    }
}
void RoadMap::showBranch() {// 디렉토리 안에 있는 파일 이름을 출력함 // 
    try {
        std::cout << "로드맵 '" << RoadMapName << "'에 포함된 파일 목록:" << std::endl;
        showRecursive(RoadMapName, 0);  // 재귀 호출 시작
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "오류: " << e.what() << std::endl;
    }
}
RoadMap& RoadMap::findRoadMap(const std::string& RoadMapName) {
    for (RoadMap& child : childRoadMap) {
        if (child.getRoadMapName() == RoadMapName) {
            return child;
        }
    }
    std::cerr << "Error: RoadMap '" << RoadMapName << " not found." << std::endl;
    throw std::runtime_error("Error: RoadMap '" + RoadMapName + "' not found.");
}
void RoadMap::addChildRoadMap(RoadMap& child) {
    childRoadMap.push_back(child);
    child.setParentRoadMap(this); // 부모 설정
}
void RoadMap::deleteChildRoadMap(const std::string& childRoadMapName) {
    auto it = std::remove_if(childRoadMap.begin(), childRoadMap.end(),
        [&](const RoadMap& child) { return child.RoadMapName == childRoadMapName; });

    if (it != childRoadMap.end()) {
        childRoadMap.erase(it, childRoadMap.end());
    }
    else {
        std::cerr << "Error: RoadMap '" << childRoadMapName << "' not found." << std::endl;
    }
}
void RoadMap::setParentRoadMap(RoadMap* parent) {
    parentRoadMap = parent;
}
string RoadMap::getRoadMapName() const {
    return RoadMapName;
}
void RoadMap::deleteMap() {// 디렉토리 파일을 삭제함
    try {
        fs::remove_all(RoadMapName);
        std::cout << "로드맵 삭제 성공: " << RoadMapName << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "오류: " << e.what() << std::endl;
    }
}
void RoadMap::createDirectory() { // RoadMap을 선언하면 디렉토리를 생성함

    try {
        if (!fs::exists(RoadMapName)) {
            fs::create_directory(RoadMapName);
            std::cout << "디렉토리 생성 성공: " << RoadMapName << std::endl;
        }
        else {
            std::cout << "디렉토리 이미 존재함: " << RoadMapName << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "디렉토리 생성 실패: " << e.what() << std::endl;
    }
}
vector<int> RoadMap::getIDFile() {
    vector<int> idList;

    ifstream file(fileID);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileID << std::endl;
        exit(1);
    }

    int id;
    while (file >> id) {
        idList.push_back(id);
    }

    file.close();
    return idList;
}
RoadMap* RoadMap::getParentRoadMap() {
    return parentRoadMap;
}
void RoadMap::showRecursive(const std::string& currentPath, int depth) {
    for (const auto& entry : fs::directory_iterator(currentPath)) {
        for (int i = 0; i < depth; ++i) {
            std::cout << " - ";
        }
        std::cout << entry.path().filename() << std::endl;

        if (fs::is_directory(entry)) {
            // 디렉토리인 경우 재귀 호출
            showRecursive(entry.path().string(), depth + 1);
        }
    }
}
