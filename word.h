#pragma once

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream> // istringstream을 사용하기 위한 헤더
#include <fstream>
#include <cctype>
#include "note.cpp"

using namespace std;

class Word {
private:
    string word; // 단어를 저장하는 변수
    vector<pair<int, int>> wordLocation; // 노트 주소와 단어 위치를 저장하는 벡터
    //pair로 노트의 주소, 단어의 위치(몇번째에 위치하는가) 저장, 벡터로 동적 배열
public:
    // 생성자
    Word(string w);
    // word 멤버 변수에 접근하기 위한 getter 메소드
    string getWord() const ;
    // wordLocation를 추가하는 메소드
    void addLocation(int noteAddress, int position);
    //특수문자 저장하는
    string preprocessWord(const string& str);
    //단어를 검색해 wordLocation를 추가하는 메소드
    void findAndAddLocation(const Note& note);
    //WordLocation test용 잘 작동하나...
    void printWordLocation() const;
    // wordLocation 정보를 반환하는 메소드
    vector<pair<int, int>> getWordLocation() const;
    void clearWordLocation();
};
