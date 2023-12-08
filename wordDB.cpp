#include <wordDB.h>
#pragma once

using namespace std;

//1. DB에 단어 추가
void WordDB::addWords(string newWord) {
    // 새로운 단어를 data에 추가
    Word newWordObj(newWord);
    data.push_back(newWordObj);

    // 파일에 데이터 및 출력 모으기
    stringstream outputData;
    for (const Word& w : data) {
        outputData << w.getWord();
        for (const auto& loc : w.getWordLocation()) {
            outputData << "|" << loc.first << ", " << loc.second;
        }
        outputData << endl;
    }

    // 파일에 데이터 저장
    ofstream outputFile("wordDB.txt");
    if (outputFile.is_open()) {
        outputFile << outputData.str(); // 파일에 데이터 기록
        outputFile.close();
        cout << "Word added to database: " << newWord << endl;
    }
    else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}

//2. DB에 저장된 단어 삭제
void WordDB::deleteWords(string targetWord) {
    auto it = remove_if(data.begin(), data.end(), [targetWord](const Word& w) {
        return w.getWord() == targetWord;
        });

    // 벡터에서 삭제된 요소 지우기
    data.erase(it, data.end());

    cout << "Word deleted from database: " << targetWord << endl;
}

//3. DB에 저장된 단어 검색
string WordDB::search(string targetWord) {
    bool found = false;
    string result;

    // 벡터에서 대상 단어 검색
    for (const Word& w : data) {
        if (w.getWord() == targetWord) {
            found = true;
            vector<pair<int, int>> locations = w.getWordLocation();
            for (const auto& loc : locations) {
                if (!result.empty()) {
                    result += ", ";
                }
                result += to_string(loc.first) + ":" + to_string(loc.second);
            }
            break;
        }
    }

    // 검색 결과 출력s
    if (found) {
        cout << "Word found in database: " << targetWord << endl;
    }
    else {//없을 시에 추가
        cout << "Word not found in database, Add this word: " << targetWord << endl;
        addWords(targetWord);
    }

    return targetWord + " | " + result;//targetWord | 1:2, 2:3 
}