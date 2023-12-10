#include "greeter.h"
//#include <iostream>
//#include <algorithm>
//#include <cctype>
//#include <cstdlib>
//#include <ctime> 

Greeter::Greeter(NoteDB n, WordDB w, RoadMap* r) : noteDB(n), wordDB(w), rootRoadMap(r) {}
void Greeter:: printTitle() {
    cout << "               :::        ::::::::::: ::::    :::  ::::::::  ::::::::::: :::::::::: \n";
    cout << "               :+:            :+:     :+:+:   :+: :+:    :+:     :+:     :+:        \n";
    cout << "               +:+            +:+     :+:+:+  +:+ +:+    +:+     +:+     +:+        \n";
    cout << "               +#+            +#+     +#+ +:+ +#+ +#+    +:+     +#+     +#++:++#   \n";
    cout << "               +#+            +#+     +#+  +#+#+# +#+    +#+     +#+     +#+        \n";
    cout << "               #+#            #+#     #+#   #+#+# #+#    #+#     #+#     #+#        \n";
    cout << "               ########## ########### ###    ####  ########      ###     ########## \n";;
    cout << endl;
};
void Greeter::printRoadMap() {
    rootRoadMap->showBranch();
}
void Greeter:: printOption() {
    cout << "        --------------------------------------------------------------------------\n";
    cout << "             1.New note                                5.Open roadmap\n";
    cout << "             2.Open note                               6.Move parent roadmap\n";
    cout << "             3.Delete note                             7.Delete raodmap\n";
    cout << "             4.New roadmap                             8.Word Finder\n";
    cout << "        --------------------------------------------------------------------------\n";
    cout << endl;
    cout << "        Enter Number:";
}
void Greeter::selectOption() {

    string selectedOption;
    cin >> selectedOption;
    int select;

    if (all_of(selectedOption.begin(), selectedOption.end(), [](unsigned char c) { return std::isdigit(c); })) {
        select = stoi(selectedOption);
    }
    else {
        select = -1;
    }

#ifdef _WIN32
    // Windows
    system("cls");
#else
    // Unix (Linux, macOS, etc.)
    system("clear");
#endif 

    switch (select) {
    case 1: {
        greeterAddNote();
        break;
    }
    case 2: {
        greeterOpenNote();
        break;
    }
    case 3: {
        greeterDeleteNote();
        break;

    }
    case 4: {
        greeterAddRoadMap();
        break;
    }
    case 5: {
        greeterOpneRoadMap();
        break;
    }
    case 6: {
        greeterCloseRoadMap();
        break;
    }
    case 7: {
        greeterDeleteRoadMap();
        break;
    }
    case 8: {
        greeterSearchWord();
        break;
    }
    default:
    {
        cout << "Entered it incorrectly. Enter a number between 1 and 8.\n";
        system("pause");
    }

    }
}
void Greeter::greeterAddNote() {
    srand((unsigned int)time(NULL));
    int noteID;
    cout << "        Enter a note ID(If you enter an invalid value, set the ID randomly):";
    // 입력 받은 값을 변수에 저장
    if (!(cin >> noteID)) {
        // 정수가 아닌 값이 입력되었을 때
        cerr << "Invalid value. Set ID to random." << endl;
        noteID = rand();
        while (noteDB.search(noteID).getNoteID() != -1)
        {
            noteID = rand();
        }
    }
    string noteName = "New note";
    cout << "        Enter a note name: ";
    getline(cin, noteName);
    noteDB.addNote(noteID, noteName, "");
    rootRoadMap->addBranch(noteName);
} //1
void Greeter::greeterOpenNote() {
    int noteID;
    cout << "        Enter a Note ID:";
    if (cin >> noteID && noteDB.search(noteID).getNoteID() != -1) {
        noteDB.search(noteID).printNote();
    }
    else {
        cerr << "Invalid input. Please enter a valid input." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    rootRoadMap->addBranch(noteDB.search(noteID).getTitle());
} //2
void Greeter::greeterDeleteNote() {
    int noteID;
    cout << "        Enter a Note ID:";
    if (cin >> noteID && noteDB.search(noteID).getNoteID() != -1) {
        noteDB.deleteNote(noteID);
    }
    else {
        cerr << "Invalid input. Please enter a valid input." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    rootRoadMap->deleteBranch(noteDB.search(noteID).getTitle());
} //3
void Greeter::greeterAddRoadMap() {
    string roadMapName;
    cout << "        Enter a roadmap name: ";
    getline(cin, roadMapName);
    RoadMap RoadMap(roadMapName);
    rootRoadMap->addBranch(roadMapName);
    rootRoadMap->addChildRoadMap(RoadMap);
} //4
void Greeter::greeterOpneRoadMap() {
    string roadMapName;
    cout << "        Enter a roadmap name: ";
    getline(cin, roadMapName);
    rootRoadMap = &rootRoadMap->findRoadMap(roadMapName);
} //5
void Greeter::greeterCloseRoadMap() {
    string roadMapName;
    rootRoadMap = rootRoadMap->getParentRoadMap();
} //5
void Greeter::greeterDeleteRoadMap() {
    string roadMapName;
    cout << "        Enter a roadmap name: ";
    getline(cin, roadMapName);
    rootRoadMap->deleteBranch(roadMapName);
    rootRoadMap->deleteChildRoadMap(roadMapName);
} //6
void Greeter::greeterSearchWord() {
    string word;
    cout << "        Enter a roadmap word: ";
    getline(cin, word);
    rootRoadMap->printLine(word);
} //7
