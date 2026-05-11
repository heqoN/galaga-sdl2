#include "leaderboard.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void Leaderboard::saveScore(int score){
    ofstream file("../assets/data/leaderboard.txt",ios::app);

    if(file.is_open()){
        file<<score<<'\n';
    }
    else{
        cout<<"Leaderboard file can't opened ."<<endl;
    }
}

vector<int> Leaderboard::getScores(){
    ifstream file("../assets/data/leaderboard.txt");

    if(!file.is_open()){
        cout<<"Leaderboard file can't opened ."<<endl;
        return {};
    }

    int score;
    vector<int> scores;
    scores.reserve(5);
    while(file>>score){
        scores.push_back(score);
    }
    
    sort(scores.begin(),scores.end(),greater<int>());

    if(scores.size()>5){
        scores.resize(5);
    }

    return scores;
}
