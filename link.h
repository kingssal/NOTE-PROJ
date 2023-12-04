#include <iostream>
#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <string>
#include "WordDB.h"  // WordDB 클래스의 헤더 파일을 include
using namespace std;
namespace fs = std::filesystem;

class Line {
public:
    std::string object1;
    std::string object2;
    int weight;

    Line(std::string obj1, std::string obj2, WordDB& wordDB) : object1(obj1), object2(obj2), weight(0), wordDB(wordDB) {}

    void updateWeight() {
        std::unordered_set<std::string> words1 = getWord(object1);
        std::unordered_set<std::string> words2 = getWord(object2);

        weight = countCommonWords(words1, words2);
    }

    void deleteLine() {
        if (weight == 0) {
            std::cout << object1 << "와 " << object2 << " 사이의 선 삭제" << std::endl;
            // 추가적인 코드: 선 삭제 로직
        }
    }

private:
    WordDB& wordDB;

    std::unordered_set<std::string> getWord(const std::string& object) {
        std::string pos = extractPOS(object);
        return wordDB.getWordsByPOS(pos);
    }

    std::string extractPOS(const std::string& word) {
        return word;  // 여기에 실제 품사 추출 로직 추가
    }

    int countCommonWords(const std::unordered_set<std::string>& words1, const std::unordered_set<std::string>& words2) {
        int commonCount = 0;
        for (const auto& word : words1) {
            if (words2.count(word) > 0) {
                commonCount++;
            }
        }
        return commonCount;
    }
};

int main() {
    // 다른 패키지에 있는 WordDB 클래스를 참조
    WordDB wordDB;

    // 사용자로부터 Word 입력 받기
    std::string searchWord;
    std::cout << "검색할 Word를 입력하세요: ";
    std::cin >> searchWord;

    // 사용자로부터 Note1, Note2 입력 받기
    std::string note1, note2;
    std::cout << "선택할 두 Note를 입력하세요: ";
    std::cin >> note1 >> note2;

    // Line 객체 생성 및 가중치 계산
    Line line1(note1, note2, wordDB);
    line1.updateWeight();

    // 결과 출력
    std::cout << "두 Note의 가중치는 다음과 같습니다." << std::endl;
    std::cout << "가중치: " << line1.weight << std::endl;

    line1.deleteLine();

    return 0;
}


class RoadMap {
public:
    RoadMap(const std::string& RoadMapName) : RoadMapName(RoadMapName) {
        createDirectory();
    }

    void addBranch(const std::string& fileName) {
        try {
            fs::path sourcePath = fileName;
            fs::path destinationPath = fs::path(RoadMapName) / fileName;

            fs::copy(sourcePath, destinationPath, fs::copy_options::overwrite_existing);

            // 노트 간 연결을 나타내는 line 변수에 정보를 추가
            line += " -> " + fileName;

            std::cout << "브랜치 추가 성공: " << fileName << " -> " << RoadMapName << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "오류: " << e.what() << std::endl;
        }
    }

    void show() {
        try {
            std::cout << "로드맵 '" << RoadMapName << "'에 포함된 파일 목록:" << std::endl;
            showRecursive(RoadMapName, 0);

            // 노트 간 연결 정보를 표시
            std::cout << "노트 연결: " << line << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "오류: " << e.what() << std::endl;
        }
    }
    void deleteMap() {// 디렉토리 파일을 삭제함
        try {
            fs::remove_all(RoadMapName);
            std::cout << "로드맵 삭제 성공: " << RoadMapName << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "오류: " << e.what() << std::endl;
        }
    }

private:
    void createDirectory() {
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

    void showRecursive(const std::string& currentPath, int depth) {
        for (const auto& entry : fs::directory_iterator(currentPath)) {
            for (int i = 0; i < depth; ++i) {
                std::cout << "->";
            }
            std::cout << entry.path().filename() << std::endl;

            if (fs::is_directory(entry)) {
                showRecursive(entry.path().string(), depth + 1);
            }
        }
    }

    std::string RoadMapName;
    std::string line; // 노트 간 연결을 저장하는 변수


}