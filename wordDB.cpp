#include <wordDB.h>
#pragma once

using namespace std;

//1. DB�� �ܾ� �߰�
void WordDB::addWords(string newWord) {
    // ���ο� �ܾ data�� �߰�
    Word newWordObj(newWord);
    data.push_back(newWordObj);

    // ���Ͽ� ������ �� ��� ������
    stringstream outputData;
    for (const Word& w : data) {
        outputData << w.getWord();
        for (const auto& loc : w.getWordLocation()) {
            outputData << "|" << loc.first << ", " << loc.second;
        }
        outputData << endl;
    }

    // ���Ͽ� ������ ����
    ofstream outputFile("wordDB.txt");
    if (outputFile.is_open()) {
        outputFile << outputData.str(); // ���Ͽ� ������ ���
        outputFile.close();
        cout << "Word added to database: " << newWord << endl;
    }
    else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}

//2. DB�� ����� �ܾ� ����
void WordDB::deleteWords(string targetWord) {
    auto it = remove_if(data.begin(), data.end(), [targetWord](const Word& w) {
        return w.getWord() == targetWord;
        });

    // ���Ϳ��� ������ ��� �����
    data.erase(it, data.end());

    cout << "Word deleted from database: " << targetWord << endl;
}

//3. DB�� ����� �ܾ� �˻�
string WordDB::search(string targetWord) {
    bool found = false;
    string result;

    // ���Ϳ��� ��� �ܾ� �˻�
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

    // �˻� ��� ���s
    if (found) {
        cout << "Word found in database: " << targetWord << endl;
    }
    else {//���� �ÿ� �߰�
        cout << "Word not found in database, Add this word: " << targetWord << endl;
        addWords(targetWord);
    }

    return targetWord + " | " + result;//targetWord | 1:2, 2:3 
}