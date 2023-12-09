#pragma once

#include <vector>
#include <algorithm>
#include "note.h"

using namespace std;

class NoteDB {
private:
	vector<class Note> notes;
public:
	void addNote(int,string,string);
	void deleteNote(int);
	void update();
	//void addlist(string);
	Note& search(int);
	void updateList();
	void save();
	void sortDB();
	
};
bool compareNote(Note&, Note&);
