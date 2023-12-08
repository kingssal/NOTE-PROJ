#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include "word.h"

using namespace std;

class WordDB {

private:
	vector<Word> data;
public:
    void addWords(string);
    void deleteWords(string);
    string search(string);
};