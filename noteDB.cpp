#include "noteDB.h"

//note객체 추가
void NoteDB::addNote(int id, string title, string content) {
	Note temp(id,title, content);
	notes.push_back(temp);
	sortDB();
}

//id로 삭제
void NoteDB::deleteNote(int i) {
	for (auto n = notes.begin(); n !=notes.end();n++) {
		if (n->id == i) {
			notes.erase(n);
			break;
		}
	}
}

Note& NoteDB::search(int id) {
	for (auto& n : notes) {
		if (n.id == id) {
			return n;
		}
	}
	Note temp(-1, "NULL", "NULL"); //없는 Note인경우 쓰레기Note반환 (id 는 -1)
	return temp;
}

void NoteDB::update() {
	notes.clear();
	ifstream input("filelist.txt");
	ifstream file;
	string str;
	while (getline(input, str)) {
		file.open(str + ".txt");
		Note temp(00000, str, "");
		temp.loadNote();
		notes.push_back(temp);
	}
	sortDB();
}

void NoteDB::updateList() {
	sortDB();
	ofstream output("filelist.txt");
	for (auto& n : notes) {
		output << n.title << endl;
	}
}

void NoteDB::save() {
	for (auto& n : notes) {
		n.saveNote();
	}
}
void NoteDB::sortDB() {
	sort(notes.begin(), notes.end(), compareNote);
}

bool compareNote(Note& a, Note& b) {
	return a.title <= b.title;
}
