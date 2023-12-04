#include "noteDB.h"

//note객체 추가
NoteDB::addNote(Note& note) {
	notes.push_back(note);
}

//id로 삭제
NoteDB::deleteNote(int i) {
	for (auto n = notes.begin(); n !=notes.end();n++) {
		if (n->id == i) {
			notes.erase(n);
			break;
		}
	}
}

//id로 검색
NoteDB::search(int i) {
	for (auto n = notes.begin(); n != notes.end(); n++) {
		if (n->id == i) {
			return *n;
		}
	}
	return NULL;
}

NoteDB::update(string filename) {
	ifstream input(filename + "txt");

	//어떤기능의 update로 구현할건지 알아야함
}