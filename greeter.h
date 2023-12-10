#pragma once

#include "note.h"
#include "noteDB.h"
#include "word.h"
#include "wordDB.h"
#include "RoadMap.h"
#include <iostream>
#include <cctype>
#include <cstdlib>//
#include <ctime> 

using namespace std;

class Greeter {
private:
    NoteDB noteDB;
    WordDB wordDB;
    RoadMap* rootRoadMap;
public:
    Greeter(NoteDB n, WordDB w, RoadMap* r);
    void printTitle();
    void printRoadMap();
    void printOption();
    void selectOption();
    void greeterAddNote(); //1
    void greeterOpenNote(); //2
    void greeterDeleteNote(); //3
    void greeterAddRoadMap(); //4
    void greeterOpneRoadMap(); //5
    void greeterCloseRoadMap(); //6
    void greeterDeleteRoadMap(); //7
    void greeterSearchWord(); //8
    //exit 8
};
