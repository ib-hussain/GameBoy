#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
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
#include<algorithm>
#include<ctime>
using namespace std;


class Player{
private:
    const string filename;
public:
    string name;
    int snake_score;
    int wordle_score;
    int hangman_score;
    unsigned short int age;
    char gender;
    static int playersnum1;
    int playersnum;
    Player(string nam, int age1, char gender1, string welp = ".txt"):age(age1), name(nam), gender(gender1), filename((nam+welp)) {
        playersnum1++;
        snake_score = wordle_score = hangman_score = 0;
        write_to();
    }
    Player(string filen): filename(filen){
        read_to();
    }
    void write_to(){
        ofstream players(filename);
        
        players<<name<<"\n";
        players<<age<<"\n";
        players<<gender<<"\n";
        players<<playersnum1<<"\n";
        players<<snake_score<<"\n";
        players<<wordle_score <<"\n";
        players<<hangman_score<<"\n";

        // players<<"Name: "<<name<<"\n";
        // players<<"Age: "<<age<<"\n";
        // players<<"Gender: "<<gender<<"\n";
        // players<<"Player Number: "<<playersnum<<"\n";
        // players<<"Snake Game Highscore: "<<snake_score<<"\n";
        // players<<"Wordle Highscore: "<<wordle_score <<"\n";
        // players<<"Hangman Highscore: "<<hangman_score<<"\n";
        players.close();
    }
    void read_to(){
        ifstream players(filename);
        players>>name;
        // getline (players, name)
        players>>age;
        players>>gender;
        players>>playersnum;
        players>>snake_score;
        players>>wordle_score ;
        players>>hangman_score;
        players.close();
        // cout<<"Name: "<<name<<"\n";
        // cout<<"Age: "<<age<<"\n";
        // cout<<"Gender: "<<gender<<"\n";
        // cout<<"Player Number: "<<playersnum<<"\n";
        // cout<<"Snake Game Highscore: "<<snake_score<<"\n";
        // cout<<"Wordle Highscore: "<<wordle_score <<"\n";
        // cout<<"Hangman Highscore: "<<hangman_score<<"\n";
    }
};
int Player::playersnum1 = 0;



#endif