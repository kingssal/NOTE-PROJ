#pragma once

#include "note.h"
#include "noteDB.h"
#include "word.h"
#include "wordDB.h"
#include "RoadMap.h"
#include <iostream>

using namespace std;

class Greeter {
private:
    NoteDB noteDB;
    WordDB wordDB;
    RoadMap* rootRoadMap;
public:
    Greeter (NoteDB n, WordDB w, RoadMap* r);
    void printTitle();
    void printOption();
    void selectOption();
    void greeterAddNote(); //1
    void openNote(); //2
    void deleteNote(); //3
    void newRoadMap(); //4
    void opneRoadMap(); //5
    void deleteRoadMap(); //6
    void searchWord(); //7
    //exit 8
};
