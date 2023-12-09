#include "greeter.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime> 

Greeter::Greeter (NoteDB n, WordDB w, RoadMap* r) : noteDB(n), wordDB(w), rootRoadMap(r) {}
void printTitle(){
    cout << "               :::        ::::::::::: ::::    :::  ::::::::  ::::::::::: :::::::::: \n";
	cout << "               :+:            :+:     :+:+:   :+: :+:    :+:     :+:     :+:        \n";
	cout << "               +:+            +:+     :+:+:+  +:+ +:+    +:+     +:+     +:+        \n";
	cout << "               +#+            +#+     +#+ +:+ +#+ +#+    +:+     +#+     +#++:++#   \n";
	cout << "               +#+            +#+     +#+  +#+#+# +#+    +#+     +#+     +#+        \n";
	cout << "               #+#            #+#     #+#   #+#+# #+#    #+#     #+#     #+#        \n";
	cout << "               ########## ########### ###    ####  ########      ###     ########## \n";;
    cout << endl;
};
void printOption(){
	cout << "        --------------------------------------------------------------------------\n";
	cout << "             1.New note                                5.Open roadmap\n";
	cout << "             2.Open note                               6.Move parent Roadmap\n";
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

	system("CLS");
	switch (select) {
        case 1: {
            greeterAddNote();
            break;
        }
        case 2: {
            openNote();
            break;
        }
        case 3: {
            deleteNote();
            break;

        }
        case 4: {
            newRoadMap();
            break;
        }
        case 5: {
            opneRoadMap(); 
            break;
        }
        case 6: {
            deleteRoadMap();
            break;
        }
        case 7: {
            searchWord();
            break;
        }
        case 8: {
            exit(0);
            break;
        }
        default: 
        {
            cout << "Entered it incorrectly. Enter a number between 1 and 8.\n";
            system("pause");
	    }

	}
}
void Greeter::greeterAddNote(){
    srand((unsigned int)time(NULL));
    int noteID;
    cout << "        Enter a note ID(If you enter an invalid value, set the ID randomly):";
    int noteID;
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
} //1
void Greeter::openNote(){
    int noteID;
    cout << "        Enter a Note ID:";
    if(cin >> noteID && noteDB.search(noteID).getNoteID() != -1){
        noteDB.search(noteID).printNote();
    }
    else {
        cerr << "Invalid input. Please enter a valid input." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
} //2
void Greeter::deleteNote(){
    int noteID;
    cout << "        Enter a Note ID:";
    if(cin >> noteID && noteDB.search(noteID).getNoteID() != -1){
        noteDB.deleteNote(noteID);
    }
    else {
        cerr << "Invalid input. Please enter a valid input." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
} //3
void Greeter::newRoadMap(){
    string roadMapName;
    cout << "        Enter a roadmap name: ";
    getline(cin, roadMapName);
    RoadMap RoadMap(roadMapName);
    rootRoadMap->addBranch(roadMapName);
    rootRoadMap->addChildRoadMap(RoadMap);
} //4
void Greeter::opneRoadMap(){
    string roadMapName;
    cout << "        Enter a roadmap name: ";
    getline(cin, roadMapName);
    rootRoadMap = &rootRoadMap->findRoadMap(roadMapName);
} //5
void Greeter::deleteRoadMap(){
    string roadMapName;
    cout << "        Enter a roadmap name: ";
    getline(cin, roadMapName);
    rootRoadMap->deleteBranch(roadMapName);
    rootRoadMap->deleteChildRoadMap(roadMapName);
} //6
void Greeter::searchWord(){
    string word;
    cout << "        Enter a roadmap word: ";
    getline(cin, word);
    rootRoadMap->printLine(word);
} //7