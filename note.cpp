#include "note.h"

    Note::Note(int id, std::string title, std::string content) {
        this->id = id;
        this->title = title;
        this->content = content;
    }
    int Note::getNoteID() const {
        return this->id;
    }

    void Note::saveNote() {
        std::string filename = title + ".txt";
        std::ofstream file(filename);

        if (file.is_open()) {
            file << "ID: " << id << "\n";
            file << "Title: " << title << "\n";
            file << "Content: " << content << "\n";
            file.close();
            std::cout << "Note save completed " << filename << std::endl;
        }
        else {
            std::cout << "Unable to open file" << std::endl;
        }
    }

    void Note::editNote(std::string newTitle, std::string newContent) {
        this->title = newTitle;
        this->content = newContent;
    }

    // 노트 정보 출력
    void Note::printNote() {
        std::cout << "ID: " << id << "\nTitle: " << title << "\nContent: " << content << std::endl;
    }
    std::string Note::getText() const {
        return content;
    }

    void Note::setText(std::string str){
        content = str;
    }
    // 노트  로드
    void Note::loadNote() {
        std::ifstream file;
        std::string tmp;
        file.open(title + ".txt");
        if (!file) std::cout << "Unable to open file: " << title + ".txt" << std::endl;
        else {
            getline(file, tmp);
            id = stoi(tmp.substr(4));
            getline(file, tmp);
            title = tmp.substr(7);

            content = "";
            getline(file, tmp);
            content += tmp.substr(9);
            while (getline(file, tmp)) {
                content += tmp;
            }
        }
    }
