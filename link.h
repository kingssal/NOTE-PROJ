#include <iostream>
#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <string>
#include "WordDB.h"  // WordDB Ŭ������ ��� ������ include
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
            std::cout << object1 << "�� " << object2 << " ������ �� ����" << std::endl;
            // �߰����� �ڵ�: �� ���� ����
        }
    }

private:
    WordDB& wordDB;

    std::unordered_set<std::string> getWord(const std::string& object) {
        std::string pos = extractPOS(object);
        return wordDB.getWordsByPOS(pos);
    }

    std::string extractPOS(const std::string& word) {
        return word;  // ���⿡ ���� ǰ�� ���� ���� �߰�
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
    // �ٸ� ��Ű���� �ִ� WordDB Ŭ������ ����
    WordDB wordDB;

    // ����ڷκ��� Word �Է� �ޱ�
    std::string searchWord;
    std::cout << "�˻��� Word�� �Է��ϼ���: ";
    std::cin >> searchWord;

    // ����ڷκ��� Note1, Note2 �Է� �ޱ�
    std::string note1, note2;
    std::cout << "������ �� Note�� �Է��ϼ���: ";
    std::cin >> note1 >> note2;

    // Line ��ü ���� �� ����ġ ���
    Line line1(note1, note2, wordDB);
    line1.updateWeight();

    // ��� ���
    std::cout << "�� Note�� ����ġ�� ������ �����ϴ�." << std::endl;
    std::cout << "����ġ: " << line1.weight << std::endl;

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

            // ��Ʈ �� ������ ��Ÿ���� line ������ ������ �߰�
            line += " -> " + fileName;

            std::cout << "�귣ġ �߰� ����: " << fileName << " -> " << RoadMapName << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "����: " << e.what() << std::endl;
        }
    }

    void show() {
        try {
            std::cout << "�ε�� '" << RoadMapName << "'�� ���Ե� ���� ���:" << std::endl;
            showRecursive(RoadMapName, 0);

            // ��Ʈ �� ���� ������ ǥ��
            std::cout << "��Ʈ ����: " << line << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "����: " << e.what() << std::endl;
        }
    }
    void deleteMap() {// ���丮 ������ ������
        try {
            fs::remove_all(RoadMapName);
            std::cout << "�ε�� ���� ����: " << RoadMapName << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "����: " << e.what() << std::endl;
        }
    }

private:
    void createDirectory() {
        try {
            if (!fs::exists(RoadMapName)) {
                fs::create_directory(RoadMapName);
                std::cout << "���丮 ���� ����: " << RoadMapName << std::endl;
            }
            else {
                std::cout << "���丮 �̹� ������: " << RoadMapName << std::endl;
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "���丮 ���� ����: " << e.what() << std::endl;
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
    std::string line; // ��Ʈ �� ������ �����ϴ� ����


}