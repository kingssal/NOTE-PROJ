#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "noteDB.h"

class Note {
    friend class NoteDB;
    friend bool compareNote(Note&, Note&);
private:
    int id;
    std::string title;
    std::string content;
public:
    Note(int id, std::string title, std::string content);
    int getNoteID() const;
    void saveNote();
    void editNote(std::string newTitle, std::string newContent);
    void printNote();
    std::string getText() const;
    void loadNote();
    void setText(std::string);

};

