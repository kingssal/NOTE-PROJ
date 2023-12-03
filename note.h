//note클래스의 멤버 함수들의 정의

#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

using namespace std;

class note {
private:
    string title;                  //노트의 제목
    int id;                        //노트의 id
    string content;                //노트의 내용
    string createdTime;            //노트의 생성시간
    string lastMoidfiedDate;       //마지막으로 수정된 날짜

public:
    //생성자
    note(string title, int id, string content);

    //나중에 복사 생성자 등을 추가한다


    //-------------------------------------------------------------
    // 아래는 메소드
    //-------------------------------------------------------------

    //수정 edit
    void edit(string newContent);

    //노트 표시
    void display() const;

    //노트 저장
    void save() const;

    //노트 불러오기
    void load(int id);

    // 나머지 메소드는 추후에 여기에 추가
    
};

#endif 