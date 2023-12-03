#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream> // istringstream을 사용하기 위한 헤더
#include <fstream>
#pragma once

using namespace std;

//작성을 위한 임시 노트 클래스
class Note {
private:
    int noteID; // 노트 ID
    string text; // 노트의 문자열

public:
    // 생성자
    Note(int id, string t) : noteID(id), text(t) {}

    // noteID에 접근하기 위한 getter
    int getNoteID() const {
        return noteID;
    }

    // text에 접근하기 위한 getter
    string getText() const {
        return text;
    }
};

class Word {
private:
    string word; // 단어를 저장하는 변수
    vector<pair<int, int>> wordLocation; // 노트 주소와 단어 위치를 저장하는 벡터
    //pair로 노트의 주소, 단어의 위치(몇번째에 위치하는가) 저장, 벡터로 동적 배열

public:
    // 생성자
    Word(string w) : word(w) {}

    // word 멤버 변수에 접근하기 위한 getter 메소드
    string getWord() const {
        return word;
    }

    // wordLocation를 추가하는 메소드
    void addLocation(int noteAddress, int position) {
        wordLocation.push_back(make_pair(noteAddress, position));
    }
    //단어를 검색해 wordLocation를 추가하는 메소드
    void findAndAddLocation(const Note& note) {
        string noteText = note.getText();
        istringstream iss(noteText);
        string token;
        int position = 0;

        while (iss >> token) {
            if (token == word) {
                addLocation(note.getNoteID(), position);
            }
            position++;
        }
    }

    //WordLocation test용 잘 작동하나...
    void printWordLocation() const {
        cout << "Word: " << word << endl;
        cout << "Locations: " << endl;
        for (const auto& loc : wordLocation) {
            cout << "Note Address: " << loc.first << ", Position: " << loc.second << endl;
        }
    }
    // wordLocation 정보를 반환하는 메소드
    vector<pair<int, int>> getWordLocation() const {
        return wordLocation;
    }
    
    void clearWordLocation() {
        wordLocation.clear();
    }
    
};

class WordDB {
private:
    vector<Word> data = {};
public:
    //1. DB에 단어 추가
    void addWords(string newWord){
        // 새로운 단어를 data에 추가
        Word newWordObj("newWord");
        data.push_back(newWordObj);
        //파일에 데이터 저장
        ofstream outputFile("wordDB.txt");
        if (outputFile.is_open()) {
            for (const Word& w : data) {
                outputFile << w.getWord() << endl;
            }
            outputFile.close();
            cout << "Word added to database: " << newWord << endl;
        }
        else {
            cerr << "Error: Unable to open file for writing." << endl;
        }
        // 파일 갱신
        // update(newWord);
    }

    //2. DB에 저장된 단어 삭제
    void deleteWords(string targetWord) {
        auto it = remove_if(data.begin(), data.end(), [targetWord](const Word& w) {
            return w.getWord() == targetWord;
            });

        // 벡터에서 삭제된 요소 지우기
        data.erase(it, data.end());

        cout << "Word deleted from database: " << targetWord << endl;
        // 파일 갱신
        //update(targetWord);

    }
    
    //3. DB에 저장된 단어 검색
    void search(string targetWord) {
        bool found = false;

        // 벡터에서 대상 단어 검색
        for (const Word& w : data) {
            if (w.getWord() == targetWord) {
                found = true;
                break;
            }
        }

        // 검색 결과 출력
        if (found) {
            cout << "Word found in database: " << targetWord << endl;
        }
        else {//없을 시에 추가
            cout << "Word not found in database, Add this word: " << targetWord << endl;
            addWords(targetWord);
        }
    }
};
