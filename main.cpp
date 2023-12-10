//#include "note.h"
//#include "noteDB.h"
//#include "word.h"
//#include "wordDB.h"
#include "greeter.h"


using namespace std;

int main(int argc, char const* argv[])
{
    NoteDB noteDB;
    WordDB wordDB;
    RoadMap rootRoadmap("rootRoadmap");
    Greeter greeter(noteDB, wordDB, &rootRoadmap);

    while (1) {
#ifdef _WIN32
        // Windows
        system("cls");
#else
        // Unix (Linux, macOS, etc.)
        system("clear");
#endif
        greeter.printTitle();
        greeter.printRoadMap();
        greeter.printOption();
        greeter.selectOption();
    }
    return 0;
}
