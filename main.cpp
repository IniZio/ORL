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

#include<string.h>
#include <iomanip>

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

class student{
  public:
    int id_num;     // 10000
    string school_name;
    int ranking;
    string name;
    int score;
    vector<int> submit;

    student();
    void get_score(vector<int> &);
    //student(const student&);
};

student::student(){
    score = 0;
}

/*student::student(const student& other){
    id_num = other.id_num;     // 10000
    school_name = other.school_name;
    ranking = other.ranking;
    name = other.name;
    score = other.score;
    submit = other.submit;
}*/

void student::get_score(vector<int> &answers){
    for (int i = 0; i < answers.size(); i++){
        if (submit[i] == answers[i]){
            score++;
        }
    }
}

/*bool Sorter(student* a, student* B)/>
{
    return a->score > b->score;
}*/

class school{
    public:
    string name;
    double mean;
    int ranking;
    vector<student *> pupils;

    double get_mean();
};

double school::get_mean(){
    double total_score = 0.0;

    for (int i = 0; i < pupils.size(); i++){
        total_score+= pupils[i]->score;
    }

    //cout << "toot" << total_score << endl;

    int a = pupils.size();

    //cout << "size" << pupils.size() << endl;

    //cout << "A" << a << endl;

    mean = double(total_score)/a;

    cout << "mean" << mean << endl;

    //cout << "mean" << mean << endl;

    return mean;
}

vector<school> schools;

void im_brief(string path){
    ifstream file("real_data/brief_info.txt");
    if (file.is_open()){
        school skl;
        string rubbish;
        getline(file,rubbish);
        string school_name;
        if (rubbish == "school_names"){
            while (getline(file, skl.name)){
                    schools.push_back(skl);
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
            students.push_back(Candidate);
            getline(file, students.back().name);
            string intBuff;
            getline(file, intBuff);
            stringstream(intBuff) >> students.back().id_num;
            getline(file, students.back().school_name);

            int given_ans;


            for (int i = 0; i < no_answer; i++){
                stringstream(intBuff) >> given_ans;
                getline(file, intBuff);
                students.back().submit.push_back(given_ans);
            }

            //students.push_back(student(Candidate));

//            students[students.size()-1].name = Candidate.name;
//           students[students.size()-1].school_name = Candidate.school_name;

            //cout << students[0].school_name << endl;
            for (int i = 0; i < schools.size(); i++){
                //cout << schools[i].name<< endl;
                if (strcmp(students.back().school_name.c_str() ,schools[i].name.c_str())== 0){
                    //cout << students.back().school_name << ", " << schools[i].name << endl;
                    (schools[i].pupils).push_back(new student);          // caustion!!!!!!!  still cant ensure the string can be copied also
                    schools[i].pupils.back() = &students.back();
                    //cout << schools[i].pupils.back()->name << endl;
                }
            }

            getline(file, check);
        }while(check == "-----");


        for (int i = 0; i < students.size(); i++){
            cout << students[i].name << endl;
        }


        //cout << students[0].school_name << endl;
  }
  file.close();
}

void gen_score(vector<int> &answers){
    for (int i = 0; i < students.size()-1; i++){
        students[i].get_score(answers);

        cout << "score" << students[i].score << endl;
    }
}

void gen_rank(vector<student> &students){
     sort(students.begin(), students.end(), make_member_comparer2<greater>(&student::score));

     for (int i = 0; i < students.size(); i++){
        students[i].ranking = i+1;
     }
}

/*void gen_skl_mean(){
    for(int i = 0; i < schools.size(); i++){
        schools[i].get_mean
    }
}*/

void gen_skl_rank(){
    for (int i = 0; i < schools.size(); i++){
        schools[i].get_mean();
        //cout << "mean" << schools[i].mean << endl;
    }

    int ranks[schools.size()];
	for(int i=0;i<schools.size();i++){
		int rnk=0;
		for(int z=0;z<schools.size();z++){
			if(schools[z].mean < schools[i].mean)
				rnk++;
		}
    ranks[i]=rnk;
	}
    for(int i=0;i<schools.size();i++){
        schools[i].ranking =ranks[i];
    }
}

void ex_analysis(){
    mkdir("schools");
    ofstream file;
    for (int i = 0; i < schools.size();i++){
        string path = "schools/" + schools[i].name + ".txt";
        file.open(path.c_str());

        // the analysis of schools
        file << "School analysis" << endl << "=================" << endl;
        file << "school name: " << schools[i].name << '\n';
        file << "school mean: " << schools[i].get_mean() << '\n';
        file << "school rank: " << schools[i].ranking << '\n';
        file << '\n';
        // the analysis of students
        file << "Individual analysis" << endl << "=================" << endl;
        for (int j = 0; j < schools[i].pupils.size(); j++){
            file << "student id: " << setfill('0') << setw(4)<< schools[i].pupils[j]->id_num << '\n';
            file << "student name: " << schools[i].pupils[j]->name << '\n';
            cout << "student school name: " << schools[i].pupils[j]->school_name << '\n';
            cout << "student rank: " << schools[i].pupils[j]->ranking << '\n';
            cout << "student score: " << schools[i].pupils[j]->score << '\n';
            file << '\n';
            cin.get();
        }

        file.close();
        cout << "df" << endl;
    }
}

int main(){
  im_brief("");
  im_answer("");
  im_answersheets("");

  gen_score(answers);
  gen_rank(students);
  gen_skl_rank();

   ex_analysis();
   cin.get();
   cout << "done" << endl;

  return 0;
}
