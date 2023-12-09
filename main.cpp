#include "note.h"
#include "noteDB.h"
#include "word.h"
#include "wordDB.h"
#include "greeter.h"



int main(int argc, char const *argv[])
{
    NoteDB noteDB;
    WordDB wordDB;
    RoadMap rootRoadmap("rootRoadmap");
    Greeter greeter(noteDB, wordDB, &rootRoadmap);

	while (1) {
		system("cls");
        greeter.printTitle();
		greeter.printOption();
		greeter.selectOption();
	}
    return 0;
}
