#include "noteDB.h"

//note��ü �߰�
NoteDB::addNote(Note& note) {
	notes.push_back(note);
}

//id�� ����
NoteDB::deleteNote(int i) {
	for (auto n = notes.begin(); n !=notes.end();n++) {
		if (n->id == i) {
			notes.erase(n);
			break;
		}
	}
}

//id�� �˻�
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

	//������ update�� �����Ұ��� �˾ƾ���
}