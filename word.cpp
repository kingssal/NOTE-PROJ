#include "word.h"


Word::Word(string w) : word(w) {}

    // word 멤버 변수에 접근하기 위한 getter 메소드
string Word::getWord() const {
    return word;
}

    // wordLocation를 추가하는 메소드
void Word::addLocation(int noteAddress, int position) {
    wordLocation.push_back(make_pair(noteAddress, position));
}
    //특수문자 저장하는
string Word::preprocessWord(const string& str) {
    string processed;
    for (char ch : str) {
        if (!ispunct(ch)) { // 특수 문자가 아닐 경우
            processed += tolower(ch); // 소문자로 변환하여 추가
        }
    }
    return processed;
}
    //단어를 검색해 wordLocation를 추가하는 메소드
void Word::findAndAddLocation(const Note& note) {
    string noteText = note.getText();
    string processedWord = preprocessWord(word); // Word 객체의 단어도 전처리
    istringstream iss(noteText);
    string token;
    int position = 0;

    while (iss >> token) {
        if (preprocessWord(token) == processedWord) { // 전처리된 단어 비교
            addLocation(note.getNoteID(), position);
        }
        position++;
    }
}

    //WordLocation test용 잘 작동하나...
void Word::printWordLocation() const {
    cout << "Word: " << word << endl;
    cout << "Locations: " << endl;
    for (const auto& loc : wordLocation) {
        cout << "Note Address: " << loc.first << ", Position: " << loc.second << endl;
    }
}
    // wordLocation 정보를 반환하는 메소드
vector<pair<int, int>> Word::getWordLocation() const {
    return wordLocation;
}
    
void Word::clearWordLocation() {
    wordLocation.clear();
}
