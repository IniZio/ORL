#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>

#include <algorithm>
#include <functional>

#include <direct.h>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int main(){
    ifstream file("real_data/namelist.txt");

    string name;
    vector<string> names;

    while(getline(file, name)){
        names.push_back(name);
    }
    file.close();



    string rubbish, school;
    vector<string> schools;
    file.open("real_data/brief_info.txt");
    getline(file, rubbish);
    while(getline(file, school)){
        schools.push_back(school);
    }
    file.close();

    srand (time(NULL));

    ofstream file1("real_data/answer_sheets.txt");
    cout << names.size();
    for(int i = 0; i < names.size(); i++){
        file1 << names[i] << '\n';
        file1 << i+1 << '\n';
        file1 << schools[rand() % 31] << '\n';

        for (int j = 0; j < 20; j++){
            if ((rand() % 3) < 2) {file1 << "1";} else {file1 << "0";};
            if ((rand() % 10) < 2) {file1 << "1";} else {file1 << "0";};
            if ((rand() % 12) < 2) {file1 << "1";} else {file1 << "0";};
            if ((rand() % 14) < 2) {file1 << "1";} else {file1 << "0";};
            file1 << '\n';
        }

        if (i < (names.size()-1)) {file1 << "-----" << '\n';}
    }
    file1.close();

    return 0;
}
