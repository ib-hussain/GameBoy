#ifndef CONSTANTS_H
#define CONSTANTS_H

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
#include <cstring>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>
using namespace std;

unsigned const short int y_screen_length = 720;
unsigned const short int x_screen_length = 1440;
unsigned const short int snake_head_radius = 30;
unsigned int snake_highscore = 0;
unsigned int wordle_highscore = 0;
unsigned int hangman_highscore = 0;
unsigned const short int wordle_box = 100;
unsigned int short screen_num = 3;

#include <string>
using std::string;

const string IMG_PATHS[9] = {"Hangman_Images/Capture1.JPG", "Hangman_Images/Capture2.JPG",
                             "Hangman_Images/Capture3.JPG", "Hangman_Images/Capture4.JPG",
                             "Hangman_Images/Capture5.JPG", "Hangman_Images/Capture6.JPG",
                             "Hangman_Images/Capture7.JPG", "Hangman_Images/Capture8.png",
                             "Hangman_Images/Capture9.png"};

const string WORDLIST[3][20] = { // 3 categories and 20 words per category
    {"ALLIGATOR",                // wordList[0][20] -> animal category
     "CROCODILE",
     "PORCUPINE",
     "JELLYFISH",
     "COCKATOOS",
     "ARMADILLO",
     "CORMORANT",
     "PANGOLINS",
     "HEDGEHOGS",
     "SEAHORSES",
     "GOLDFINCH",
     "WOLVERINE",
     "BARRACUDA",
     "CHAMELEON",
     "NIGHTJARS",
     "GRASSHOPS",
     "MUSKOXENS",
     "SPOONBILL",
     "OYSTERCAT",
     "FLAMINGOS"},

    {"Argentina", // wordList[1][20] -> coutry category
     "Australia",
     "Dominican",
     "Guatemala",
     "Indonesia",
     "Lithuania",
     "Mauritius",
     "Nicaragua",
     "Singapore",
     "Venezuela",
     "Amsterdam",
     "Barcelona",
     "Bucharest",
     "Edinburgh",
     "Frankfurt",
     "Jerusalem",
     "Liverpool",
     "Marseille",
     "Nashville",
     "Newcastle"},

    {"BLUEBERRY", // wordList[2][20] -> fruit category
     "RASPBERRY",
     "PINEAPPLE",
     "CRANBERRY",
     "TANGERINE",
     "CHERIMOYA",
     "NECTARINE",
     "PLUMBERRY",
     "MANDARINS",
     "ASPARAGUS",
     "ARTICHOKE",
     "BEETROOTS",
     "CHOCOLATE",
     "FROSTBITE",
     "BUTTERNUT",
     "KIWIFRUIT",
     "JACKFRUIT",
     "ARTICHOKE",
     "BLACKBEAN",
     "CHICKPEAS"}};

extern string guessedWord;

const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 720;
const float BUTTON_WIDTH = 50.0;
const float BUTTON_HEIGHT = 50.0;
const float BUTTON_SPACING = 15.0;
const float BUTTON_RADIUS = 30.0;
const float KEYBOARD_START_X = 550.0;
const float KEYBOARD_START_Y = 300.0;
const float HANGMAN_START_X = 280.0;
const float HANGMAN_START_Y = 300.0;

#endif