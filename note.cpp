#include "note.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//생성자 구현
note::note(string title, int id, string content){
    this->title = title; 
    this->id =id;
    this->content = content;
    //createdTime과 lastModifiedDate 로직은 추후에 추가
}

// content 수정 메소드
void note::edit(std::string newContent){
    this->content = newContent;
    //lastModifiedDate 업데이트 하는 로직 나중에 추가
}

//노트 display메소드
void note::display() const {
    cout << "Title: " << title << std::endl;
    cout << "Content: " << content << std::endl;
    //일단 이렇게 쓰고 나중에 변경
}

// 노트 저장 메소드 구현
void note::save() const {
    ofstream file;
    file.open(title + ".txt"); //파일 이름을 title로 설정

    if (file.is_open()){
        file << "Title: "<< title << "\n";
        file << "Content: " << content <<   "\n";
        file.close();
        //lastModifiedDate와 createTime은 나중에 추가?
        cout << "Note saved successfully" << endl;
    } 
    else {
        cerr << "unable to open file for writing "<< endl;
    }
}

// 노트 불러오기
void note::load(int id){
    //id를 사용하여 노트를 불러오는 로직 구현
}

//간이 main함수
int main() {
    string title;
    string content;

    
    cout << "Enter the title of the note: ";
    getline(cin, title);

    std::cout << "Enter the content of the note: ";
    std::getline(std::cin, content);

    // note 객체 생성
    note myNote(title, 6767, content); 

    myNote.save();
    

    return 0;
}