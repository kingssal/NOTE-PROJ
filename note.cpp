#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

//Note클래스 정의
class Note{
private:
    int id;
    std::string title;
    std::string content;
    std::time_t createdTime;
    std::time_t lastModifiedTime;
public:
    Note(int id, std::string title, std::string content){
        this->id = id;
        this->title = title;
        this->content = content;
        this->createdTime = std::time(nullptr);
        this->lastModifiedTime = createdTime;
    }   
    // 노트 저장
    void saveNote() {
        std::string filename = title + ".txt";
        std::ofstream file(filename);

        if (file.is_open()) {
            file << "Title: " << title << "\n";
            file << "Created Time: " << ctime(&createdTime);
            file << "Last Modified Time: " << ctime(&lastModifiedTime);
            file << "Content: " << content << "\n";
            file.close();
            std::cout << "노트 저장 완료 " << filename << std::endl;
        } else {
            std::cout << "Unable to open file" << std::endl;
        }
    }

    // 노트 수정
    void editNote(std::string newTitle, std::string newContent) {
        this->title = newTitle;
        this->content = newContent;
        this->lastModifiedTime = std::time(nullptr);
    }

    // 노트 정보 출력
    void printNote() {
        std::cout << "ID: " << id << "\nTitle: " << title << "\nContent: " << content << std::endl;
        std::cout << "Created Time: " << ctime(&createdTime);
        std::cout << "Last Modified Time: " << ctime(&lastModifiedTime) << std::endl;
    }
};

// 메인 함수
int main() {
    std::string title, content;
    int id = 1; // 임시 ID 할당, 실제 응용에서는 고유한 ID 생성 필요

    std::cout << "Enter the title of the note: ";
    std::getline(std::cin, title);

    std::cout << "Enter the content of the note: ";
    std::getline(std::cin, content);

    Note myNote(id, title, content);
    myNote.printNote();
    myNote.saveNote();

    return 0;
}