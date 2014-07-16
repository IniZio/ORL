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

using namespace std;






template<typename T, typename M, template<typename> class C = std::less>
struct member_comparer : std::binary_function<T, T, bool>
{
    explicit member_comparer(M T::*p) : p_(p) { }

    bool operator ()(T const& lhs, T const& rhs) const
    {
        return C<M>()(lhs.*p_, rhs.*p_);
    }

private:
    M T::*p_;
};

template<typename T, typename M>
member_comparer<T, M> make_member_comparer(M T::*p)
{
    return member_comparer<T, M>(p);
}

template<template<typename> class C, typename T, typename M>
member_comparer<T, M, C> make_member_comparer2(M T::*p)
{
    return member_comparer<T, M, C>(p);
}






int no_school = 0;
vector<string> school_names;

class student{
  public:
    int id_num;     // 10000
    string school;
    int ranking;
    string name;
    int score;
    vector<int> submit;

    student();
    void get_score(vector<int> &);
};

student::student(){
    score = 0;
}

void student::get_score(vector<int> &answers){
    for (int i = 0; i < answers.size(); i++){
        if (submit[i] == answers[i]){
            //cout << submit[i] << ", " << answers[i] << endl;
            score++;
        }
    }

    //cout << score << endl;
}

void im_brief(string path){
    ifstream file("real_data/brief_info.txt");
    if (file.is_open()){
        string rubbish;
        getline(file,rubbish);
        string school_name;
        if (rubbish == "school_names"){
            while (getline(file, school_name)){
                    school_names.push_back(school_name);
                    no_school++;
            }
        }

    }else cout << "Fail";
    file.close();
}

vector<int> answers;
int no_answer = 0;

void im_answer(string path){
    ifstream file;

    file.open("real_data/answer.txt");
    if (file.is_open()){
        int answer;
        while (file >> answer){
            answers.push_back(answer);
            no_answer++;
        }
    }
    file.close();
}

vector<student> students;

void im_answersheets(string path){
  ifstream file;
  file.open("real_data/answer_sheets.txt");
  if (file.is_open()){
        string school_name;
        string check;

        do{
            student Candidate;
            getline(file, Candidate.school);
            string intBuff;
            getline(file, intBuff);
            stringstream(intBuff) >> Candidate.id_num;
            getline(file, Candidate.name);
            int given_ans;

            //cout << Candidate.name << endl;

            for (int i = 0; i < no_answer; i++){
                getline(file, intBuff);
                stringstream(intBuff) >> given_ans;
                Candidate.submit.push_back(given_ans);
                //cout << Candidate.submit[i] << endl;
            }

            //cout << "end" << endl;

            students.push_back(Candidate);

            getline(file, check);
        }while(check == "-----");

  }
  file.close();
}

void gen_score(vector<int> &answers){
    for (int i = 0; i < students.size(); i++){
        students[i].get_score(answers);
    }
}

void gen_rank(vector<student> &students){
     sort(students.begin(), students.end(), make_member_comparer2<greater>(&student::score));

     for (int i = 0; i < students.size(); i++){
        students[i].ranking = i+1;
     }
}

void ex_analysis(){
    mkdir("schools");
    ofstream file;
    for (int i = 0; i < school_names.size();i++){
        string path = "schools/" + school_names[i] + ".txt";
        file.open(path.c_str());

        file << school_names[i];

        file.close();
    }
}

int main(){
  im_brief("");
  im_answer("");
  im_answersheets("");

  gen_score(answers);
  gen_rank(students);

  ex_analysis();

  return 0;
}
