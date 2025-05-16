#ifndef GAME_H
#define GAME_H

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
#include "hangman.h"
#include "leaderBoard.h"

class Game
{
private:
    Hangman hangman;
    LeaderBoard leaderBoard;

public:
    Game();
    void run();

private:
    void processEvents();
    void render();
};

Game::Game() {}

void Game::run()
{
    double i = 0.0;
    while (window.isOpen())
    {
        processEvents();
        hangman.hangmanfigure.drawKeyboard();
        hangman.hangmanfigure.drawTrueGuesses();
        render();
    }
}

void Game::processEvents()
{
    Event event;
    int i = 0;
    // cout << "welcome to poll event" << endl;
    while (window.pollEvent(event))
    {
        i++;
        if (event.type == Event::Closed)
        {
            window.close();
        }
        // Handle mouse clicks
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {

            Vector2i mousePos = Mouse::getPosition(window);

            char clickedLetter = hangman.checkClick(mousePos);
            if (clickedLetter != '\0')
            {
                hangman.trackGuesses(clickedLetter);
            }

            // ### New Game Button functionalities ###
            else if (mousePos.x >= KEYBOARD_START_X && mousePos.x <= KEYBOARD_START_X + BUTTON_WIDTH + 115 &&
                     mousePos.y >= 60 && mousePos.y <= 60 + BUTTON_HEIGHT)
            {
                hangman.setInitialHangmanStates();
                hangman.hangmanfigure.setInitialHangfigStates();
            }
        }
    }
}

void Game::render()
{
    window.clear(Color::Green);
    hangman.hangmanfigure.setImage();
    hangman.hangmanfigure.drawLeaderBoard(hangman.lBoard);
    hangman.hangmanfigure.drawNewGameButton();

    for (int i = 0; i < 26; i++)
    {
        if (i < 9)
        {
            window.draw(hangman.hangmanfigure.trueGuessesBoard[i]);
            window.draw(hangman.hangmanfigure.trueGuessesChar[i]);
        }
        window.draw(hangman.hangmanfigure.keyboard[i]);
        window.draw(hangman.hangmanfigure.innerLetters[i]);
    }
    window.display();
}

#endif