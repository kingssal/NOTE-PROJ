#pragma once

#include <vector>
#include <algorithm>
#include "note.cpp"

using namespace std;

class NoteDB {
private:
	vector<Note> notes;
public:
	void addNote(Note&);
	void deleteNote(int);
	Note search(int);
	void update(string);

};