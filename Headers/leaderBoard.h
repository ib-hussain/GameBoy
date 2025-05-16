#ifndef LEADER_BOARD_H
#define LEADER_BOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>
using namespace std;

class LeaderBoard
{
private:
    int points;
    int gamesPlayed;
    int winPoints; // points given on winning a game
    int won;
    int streak;

public:
    LeaderBoard() : points(0), gamesPlayed(0), winPoints(7), won(0), streak(1) {}
    void updatePoints();
    void updateGamesPlayed(int newPlayed = 1);
    void updateWon(int newWon = 1);
    void updateStreak(int newWon = 1);
    void resetStreak();
    int getPoints();
    int getGamesPlayed();
    int getWon();
    int getStreak();
};
void LeaderBoard::updatePoints()
{
    this->points += streak * winPoints;
}
void LeaderBoard::updateGamesPlayed(int newPlayed)
{
    this->gamesPlayed += newPlayed;
}
void LeaderBoard::updateWon(int newWon)
{
    this->won += newWon;
}
void LeaderBoard::updateStreak(int newWon)
{
    this->streak += newWon;
}
void LeaderBoard::resetStreak()
{
    this->streak = 1;
}

int LeaderBoard::getPoints()
{
    return this->points;
}
int LeaderBoard::getGamesPlayed()
{
    return this->gamesPlayed;
}
int LeaderBoard::getWon()
{
    return this->won;
}
int LeaderBoard::getStreak()
{
    return this->streak;
}

#endif