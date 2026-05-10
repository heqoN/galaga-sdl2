#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>

using namespace std;

class Leaderboard{
    public:
        void saveScore(int score);
        vector<int> getScores();
};


#endif