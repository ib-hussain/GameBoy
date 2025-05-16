#ifndef WORDLE_H
#define WORDLE_H

#include "constants.h"
#include "button.h"
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

class Wordle{
public:
    sf::RectangleShape box[6][5]; 
    char letters[6];//player side
    int flags[5];
    static int lives;//max 6
    char word[6];// the real letters
    int score;
    unsigned int counter;
    sf::Texture pics_temp[5];
    sf::Texture final[6][5];
    sf::Texture defaulti;
    bool keyPressed[26];
    sf::Text scoreText;
    sf::Font font;
    void resetboard(){
        counter=0;
        lives=0;
        score=0;
        ifstream filei("C++ Dev/Wordle.txt");
        char temp[6];
        srand(time(0));
        int line_num= rand()%89; ///change this properly to 89
        for (int a=0;a<line_num;a++){
            filei>>temp;
        }
        filei>>word;
        word[5] = '\0';
        filei.close();
        flags[0] = flags[1] = flags[2] = flags[3] = flags[4] = 1;
        letters[0] = letters[1] = letters[2] = letters[3] = letters[4] = 0;
        font.loadFromFile("Fonts/Baskervville-Regular.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(20); 
        scoreText.setFillColor(sf::Color::Black); 
        scoreText.setPosition(750, y_screen_length-710);
        // flags:
    // 0 doesnot exist             gray
    // 1 initialisation            white
    // 2 exists but wrong place    yellow
    // 3 same place, no tesnion    green
        sf::Vector2f fbox((x_screen_length-540)/2,y_screen_length-678);
        defaulti.loadFromFile("Letters/default.png");
        for(int e=0;e<6;e++){
            for(int g=0;g<5;g++){
                    box[e][g].setSize(sf::Vector2f(wordle_box, wordle_box));
                    box[e][g].setFillColor(sf::Color::White);
                    box[e][g].setOutlineThickness(4);
                    box[e][g].setOutlineColor(sf::Color::Black);
                    box[e][g].setPosition(fbox.x + (g * 108), fbox.y + (e * 108));
                    box[e][g].setTexture(&defaulti);
            }
        }
        //box intialiser^^^
        for (int k=0;k<26;k++) {
            keyPressed[k] = false;
        }
    }
    Wordle(){
        counter=0;
        lives=0;
        score=0;
        ifstream filei("C++ Dev/Wordle.txt");
        char temp[6];
        srand(time(0));
        int line_num= rand()%89; ///change this properly to 89
        for (int a=0;a<line_num;a++){
            filei>>temp;
        }
        filei>>word;
        word[5] = '\0';
        filei.close();
        flags[0] = flags[1] = flags[2] = flags[3] = flags[4] = 1;
        letters[0] = letters[1] = letters[2] = letters[3] = letters[4] = 0;
        font.loadFromFile("Fonts/Baskervville-Regular.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(20); 
        scoreText.setFillColor(sf::Color::Black); 
        scoreText.setPosition(750, y_screen_length-710);
        // flags:
    // 0 doesnot exist             gray
    // 1 initialisation            white
    // 2 exists but wrong place    yellow
    // 3 same place, no tesnion    green
        sf::Vector2f fbox((x_screen_length-540)/2,y_screen_length-678);
        defaulti.loadFromFile("Letters/default.png");
        for(int e=0;e<6;e++){
            for(int g=0;g<5;g++){
                    box[e][g].setSize(sf::Vector2f(wordle_box, wordle_box));
                    box[e][g].setFillColor(sf::Color::White);
                    box[e][g].setOutlineThickness(4);
                    box[e][g].setOutlineColor(sf::Color::Black);
                    box[e][g].setPosition(fbox.x + (g * 108), fbox.y + (e * 108));
                    box[e][g].setTexture(&defaulti);
            }
        }
        //box intialiser^^^
        for (int k=0;k<26;k++) {
            keyPressed[k] = false;
        }
    }
    bool check_win(){
        if((flags[0]==flags[1]==flags[2]==flags[3]==flags[4]) && (flags[3]==3)){
            return true;
        }
        return false;
    }
    int gameplay(){
        //key pressing
        scoreText.setString("Score: " + to_string(score));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !keyPressed[0] && counter < 5) {
                letters[counter] = 'a';
                pics_temp[counter].loadFromFile("Letters/White/A.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[0] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !keyPressed[1] && counter < 5) {
                letters[counter] = 'b';
                pics_temp[counter].loadFromFile("Letters/White/B.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[1] = true; 
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !keyPressed[2] && counter < 5) {
                letters[counter] = 'c';
                pics_temp[counter].loadFromFile("Letters/White/C.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[2] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !keyPressed[3] && counter < 5) {
                letters[counter] = 'd';
                pics_temp[counter].loadFromFile("Letters/White/D.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[3] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !keyPressed[4] && counter < 5) {
                letters[counter] = 'e';
                pics_temp[counter].loadFromFile("Letters/White/E.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[4] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !keyPressed[5] && counter < 5) {
                letters[counter] = 'f';
                pics_temp[counter].loadFromFile("Letters/White/F.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[5] = true; 
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !keyPressed[6] && counter < 5) {
                letters[counter] = 'g';
                pics_temp[counter].loadFromFile("Letters/White/G.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[6] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !keyPressed[7] && counter < 5) {
                letters[counter] = 'h';
                pics_temp[counter].loadFromFile("Letters/White/H.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[7] = true; 
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && !keyPressed[8] && counter < 5) {
                letters[counter] = 'i';
                pics_temp[counter].loadFromFile("Letters/White/I.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[8] = true; 
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && !keyPressed[9] && counter < 5) {
                letters[counter] = 'j';
                pics_temp[counter].loadFromFile("Letters/White/J.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[9] = true; 
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && !keyPressed[10] && counter < 5) {
                letters[counter] = 'k';
                pics_temp[counter].loadFromFile("Letters/White/K.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[10] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && !keyPressed[11] && counter < 5) {
                letters[counter] = 'l';
                pics_temp[counter].loadFromFile("Letters/White/L.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[11] = true; 
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !keyPressed[12] && counter < 5) {
                letters[counter] = 'm';
                pics_temp[counter].loadFromFile("Letters/White/M.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[12] = true; 
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !keyPressed[13] && counter < 5) {
                letters[counter] = 'n';
                pics_temp[counter].loadFromFile("Letters/White/N.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[13] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && !keyPressed[14] && counter < 5) {
                letters[counter] = 'o';
                pics_temp[counter].loadFromFile("Letters/White/O.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[14] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !keyPressed[15] && counter < 5) {
                letters[counter] = 'p';
                pics_temp[counter].loadFromFile("Letters/White/P.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[15] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !keyPressed[16] && counter < 5) {
                letters[counter] = 'q';
                pics_temp[counter].loadFromFile("Letters/White/Q.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[16] = true; 
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !keyPressed[17] && counter < 5) {
                letters[counter] = 'r';
                pics_temp[counter].loadFromFile("Letters/White/R.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[17] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !keyPressed[18] && counter < 5) {
                letters[counter] = 's';
                pics_temp[counter].loadFromFile("Letters/White/S.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[18] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && !keyPressed[19] && counter < 5) {
                letters[counter] = 't';
                pics_temp[counter].loadFromFile("Letters/White/T.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[19] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && !keyPressed[20] && counter < 5) {
                letters[counter] = 'u';
                pics_temp[counter].loadFromFile("Letters/White/U.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[20] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && !keyPressed[21] && counter < 5) {
                letters[counter] = 'v';
                pics_temp[counter].loadFromFile("Letters/White/V.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[21] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !keyPressed[22] && counter < 5) {
                letters[counter] = 'w';
                pics_temp[counter].loadFromFile("Letters/White/W.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[22] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !keyPressed[23] && counter < 5) {
                letters[counter] = 'x';
                pics_temp[counter].loadFromFile("Letters/White/X.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[23] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && !keyPressed[24] && counter < 5) {
                letters[counter] = 'y';
                pics_temp[counter].loadFromFile("Letters/White/Y.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[24] = true;
                return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !keyPressed[25] && counter < 5) {
                letters[counter] = 'z';
                pics_temp[counter].loadFromFile("Letters/White/Z.png");
                box[lives][counter].setTexture(&pics_temp[counter], true);
                counter++;
                keyPressed[25] = true;
                return 0;
            }
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) ||(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))){
            if(letters[counter]!=0){
                box[lives][counter].setTexture(&defaulti, true);
                letters[counter]=0;
                // counter--;
            }
            else if(letters[counter]==0){
                if(counter>0){
                    counter--;
                }
                box[lives][counter].setTexture(&defaulti, true);
                letters[counter]=0;
            }
            for (int k=0;k<26;k++) {
                keyPressed[k] = false;
            }
            return 0;
        }
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))&&(counter==5)&&(lives<=6)){
            if((letters[0] !=0)&&(letters[1] !=0)&&( letters[2] !=0)&&( letters[3] !=0)&&( letters[4] != 0)){
                for (int l= 0;l<26;l++){
                    keyPressed[l] = false;
                }
                flags[0] = flags[1] = flags[2] = flags[3] = flags[4] = 1;
                for(int b=0;b<5;b++){
                    if(letters[b] ==word[b]){
                        flags[b] = 3;
                    }
                }
                //green done
                for(int c=0;c<5;c++){
                    for(int d=0;d<5;d++){
                        if(letters[c]==word[d]){
                            if(flags[c]!=3){
                                flags[c]=2;
                            }
                        }                        
                    }
                }
                //yellow done
                for(int f=0;f<5;f++){
                    if(flags[f]==1){
                        flags[f] =0;
                    }
                }
                //grey done
                auto startTime = std::chrono::steady_clock::now();
                std::srand(static_cast<unsigned int>(std::time(nullptr)));
                std::this_thread::sleep_for(std::chrono::milliseconds(230));
                flag_implementation();
                lives++;
                counter=0;
                result();
                return 0;
            }
        }
        return 0;
        //enter ki working
    }
    void flag_implementation(){
        for(int h=0;h<5;h++){
            if(flags[h]==3){
                if (letters[h] == 'a') {
                    final[lives][h].loadFromFile("Letters/Green/A.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                }
                  else if (letters[h] == 'b') {
                    final[lives][h].loadFromFile("Letters/Green/B.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'c') {
                    final[lives][h].loadFromFile("Letters/Green/C.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'd') {
                    final[lives][h].loadFromFile("Letters/Green/D.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'e') {
                    final[lives][h].loadFromFile("Letters/Green/E.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'f') {
                    final[lives][h].loadFromFile("Letters/Green/F.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'g') {
                    final[lives][h].loadFromFile("Letters/Green/G.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'h') {
                    final[lives][h].loadFromFile("Letters/Green/H.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'i') {
                    final[lives][h].loadFromFile("Letters/Green/I.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'j') {
                    final[lives][h].loadFromFile("Letters/Green/J.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'k') {
                    final[lives][h].loadFromFile("Letters/Green/K.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'l') {
                    final[lives][h].loadFromFile("Letters/Green/L.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'm') {
                    final[lives][h].loadFromFile("Letters/Green/M.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'n') {
                    final[lives][h].loadFromFile("Letters/Green/N.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'o') {
                    final[lives][h].loadFromFile("Letters/Green/O.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'p') {
                    final[lives][h].loadFromFile("Letters/Green/P.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'q') {
                    final[lives][h].loadFromFile("Letters/Green/Q.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'r') {
                    final[lives][h].loadFromFile("Letters/Green/R.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 's') {
                    final[lives][h].loadFromFile("Letters/Green/S.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 't') {
                    final[lives][h].loadFromFile("Letters/Green/T.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'u') {
                    final[lives][h].loadFromFile("Letters/Green/U.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'v') {
                    final[lives][h].loadFromFile("Letters/Green/V.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'w') {
                    final[lives][h].loadFromFile("Letters/Green/W.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'x') {
                    final[lives][h].loadFromFile("Letters/Green/X.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'y') {
                    final[lives][h].loadFromFile("Letters/Green/Y.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'z') {
                    final[lives][h].loadFromFile("Letters/Green/Z.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                }
            }
            else if(flags[h]==2){
                if (letters[h] == 'a') {
                    final[lives][h].loadFromFile("Letters/Yellow/A.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                }
                else if (letters[h] == 'b') {
                    final[lives][h].loadFromFile("Letters/Yellow/B.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'c') {
                    final[lives][h].loadFromFile("Letters/Yellow/C.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'd') {
                    final[lives][h].loadFromFile("Letters/Yellow/D.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'e') {
                    final[lives][h].loadFromFile("Letters/Yellow/E.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'f') {
                    final[lives][h].loadFromFile("Letters/Yellow/F.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'g') {
                    final[lives][h].loadFromFile("Letters/Yellow/G.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'h') {
                    final[lives][h].loadFromFile("Letters/Yellow/H.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'i') {
                    final[lives][h].loadFromFile("Letters/Yellow/I.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'j') {
                    final[lives][h].loadFromFile("Letters/Yellow/J.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'k') {
                    final[lives][h].loadFromFile("Letters/Yellow/K.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'l') {
                    final[lives][h].loadFromFile("Letters/Yellow/L.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'm') {
                    final[lives][h].loadFromFile("Letters/Yellow/M.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'n') {
                    final[lives][h].loadFromFile("Letters/Yellow/N.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'o') {
                    final[lives][h].loadFromFile("Letters/Yellow/O.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'p') {
                    final[lives][h].loadFromFile("Letters/Yellow/P.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'q') {
                    final[lives][h].loadFromFile("Letters/Yellow/Q.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'r') {
                    final[lives][h].loadFromFile("Letters/Yellow/R.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 's') {
                    final[lives][h].loadFromFile("Letters/Yellow/S.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 't') {
                    final[lives][h].loadFromFile("Letters/Yellow/T.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'u') {
                    final[lives][h].loadFromFile("Letters/Yellow/U.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'v') {
                    final[lives][h].loadFromFile("Letters/Yellow/V.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'w') {
                    final[lives][h].loadFromFile("Letters/Yellow/W.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'x') {
                    final[lives][h].loadFromFile("Letters/Yellow/X.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'y') {
                    final[lives][h].loadFromFile("Letters/Yellow/Y.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'z') {
                    final[lives][h].loadFromFile("Letters/Yellow/Z.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                }
            }
            else if(flags[h]==0){
                if (letters[h] == 'a') {
                    final[lives][h].loadFromFile("Letters/Gray/A.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                }
                else if (letters[h] == 'b') {
                    final[lives][h].loadFromFile("Letters/Gray/B.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'c') {
                    final[lives][h].loadFromFile("Letters/Gray/C.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'd') {
                    final[lives][h].loadFromFile("Letters/Gray/D.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'e') {
                    final[lives][h].loadFromFile("Letters/Gray/E.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'f') {
                    final[lives][h].loadFromFile("Letters/Gray/F.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'g') {
                    final[lives][h].loadFromFile("Letters/Gray/G.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'h') {
                    final[lives][h].loadFromFile("Letters/Gray/H.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'i') {
                    final[lives][h].loadFromFile("Letters/Gray/I.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'j') {
                    final[lives][h].loadFromFile("Letters/Gray/J.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'k') {
                    final[lives][h].loadFromFile("Letters/Gray/K.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'l') {
                    final[lives][h].loadFromFile("Letters/Gray/L.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'm') {
                    final[lives][h].loadFromFile("Letters/Gray/M.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'n') {
                    final[lives][h].loadFromFile("Letters/Gray/N.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'o') {
                    final[lives][h].loadFromFile("Letters/Gray/O.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'p') {
                    final[lives][h].loadFromFile("Letters/Gray/P.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'q') {
                    final[lives][h].loadFromFile("Letters/Gray/Q.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'r') {
                    final[lives][h].loadFromFile("Letters/Gray/R.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 's') {
                    final[lives][h].loadFromFile("Letters/Gray/S.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 't') {
                    final[lives][h].loadFromFile("Letters/Gray/T.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'u') {
                    final[lives][h].loadFromFile("Letters/Gray/U.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'v') {
                    final[lives][h].loadFromFile("Letters/Gray/V.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'w') {
                    final[lives][h].loadFromFile("Letters/Gray/W.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'x') {
                    final[lives][h].loadFromFile("Letters/Gray/X.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'y') {
                    final[lives][h].loadFromFile("Letters/Gray/Y.png");
                    box[lives][h].setTexture(&final[lives][h], true);
                } else if (letters[h] == 'z') {
                    final[lives][h].loadFromFile("Letters/Gray/Z.png");
                    box[lives][h].setTexture(&final[lives][h], true);
    }
            }
        }
        score += (flags[0]+flags[1]+flags[2]+flags[3]+flags[4])*(6-lives);
        // flags[0] = flags[1] = flags[2] = flags[3] = flags[4] = 1;
        letters[0] = letters[1] = letters[2] = letters[3] = letters[4] = 0;
    }
    void draw(sf::RenderWindow& window) {
        for(int i=0;i<6;i++){
            for(int j=0;j<5;j++){
                window.draw(box[i][j]);
            }
        }
        window.draw(scoreText);
    }
    void result(){
        if(check_win()){
            auto startTime = std::chrono::steady_clock::now();
            srand(static_cast<unsigned int>(std::time(nullptr)));
            this_thread::sleep_for(std::chrono::milliseconds(500));
            if(wordle_highscore<=score){
                wordle_highscore=score;
                ofstream highscore("C++ Dev/Wordle_hs.txt");
                highscore<<wordle_highscore;
                highscore.close();
                screen_num=14;
            resetboard();
            }
            else{
                screen_num=11;
            resetboard();
            }
        }
        else if(lives==6){
            auto startTime = std::chrono::steady_clock::now();
            srand(static_cast<unsigned int>(std::time(nullptr)));
            this_thread::sleep_for(std::chrono::milliseconds(500));
            screen_num=12;
            resetboard();
        }
        //maybe add some quit functionality here if user wants to quit
    }
};
int Wordle::lives=0;
#endif