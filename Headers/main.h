#ifndef MAIN_H
#define MAIN_H

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
#include "game.h"

RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "HANGMAN GAME");

int main1(){
    Game game;
    game.run();
    return 0;
}

#endif