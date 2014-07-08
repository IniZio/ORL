#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

class student{
  private:
    int id_num;     // 1000
    int form;
    int rank;
    string name;
    int score;
  public:

};

void get_brief(string path){
    ifstream file;
    file.open("brief_info.txt");
    if (file.is_open()){

    }
    file.close();
}

void get_answer(string path){
    ifstream file;
    file.open("answer.txt");
    if (file.is_open()){

    }
    file.close();
}

void get_answersheets(string path){
  ifstream file;
  file.open("answer_sheets.txt");
  if (file.is_open()){

  }
  file.close();
}

int main(){
  get_answersheets;
  return 0;
}
