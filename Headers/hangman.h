#ifndef HANGMAN_H
#define HANGMAN_H

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
// #include <gameBoy.h>
// #include <game.h>
#include "hangmanFigure.h"
#include "category.h"

class Hangman
{
public:
    HangmanFigure hangmanfigure;
    Category category;
    string trueGuesses;  // maximum possible true guesses are 9
    string falseGuesses; // because we have 8 states of hangman
    LeaderBoard lBoard;
    bool isGameOver;
    bool isGameWon;

public:
    Hangman();
    void trackGuesses(char ch);
    void setLeaderBoard(LeaderBoard &lBoard);
    void gameOver();
    void gameWon();
    void drawHangman();
    void manageLives();
    char checkClick(Vector2i mousePos); // Check if a button was clicked
    void setInitialHangmanStates();
};

Hangman::Hangman()
{
    setInitialHangmanStates();
}

void Hangman::trackGuesses(char ch)
{
    if (isGameOver || isGameWon)
        return; // don't execute the function if game is over

    bool isfalse = true; // initially assume the user guess is false

    // Solution of a problem: The problem was that the nested if condition doesn't allow the
    // second presence of the same letter to call the functions
    int isOne = 0; // if the character is only once in the word or more than one
    for (int i = 0; i < 9; i++)
    {
        if (guessedWord[i] == ch)
        {
            isOne++;

            trueGuesses[i] = ch;
            isfalse = false; // the user guess is not false

            int buttonNo = int(ch) - 65;
            if (isOne >= 2 || (hangmanfigure.keyboard[buttonNo].getFillColor() != Color::Red && hangmanfigure.keyboard[buttonNo].getFillColor() != Color(192, 255, 62)))
            {
                hangmanfigure.drawTrueGuesses(ch, i);
                hangmanfigure.drawKeyboard(buttonNo, 1);
            }
        }
    }

    if (guessedWord == trueGuesses) // why this condition is always false??
    {
        gameWon();
    }

    else if (isfalse)
    {
        // cout << "Your click: " << ch << endl;
        falseGuesses.push_back(ch);
        int buttonNo = int(ch) - 65;
        if (hangmanfigure.keyboard[buttonNo].getFillColor() != Color::Red && hangmanfigure.keyboard[buttonNo].getFillColor() != Color(192, 255, 62))
        {
            hangmanfigure.drawKeyboard(int(ch) - 65, -1);
            hangmanfigure.setImage();
            hangmanfigure.updateImageNo();
        }
        if (falseGuesses.size() >= 7)
        {
            gameOver();
        }
    }
}

// Check if a button was clicked
char Hangman::checkClick(Vector2i mousePos)
{
    for (int i = 0; i < 26; i++)
    {
        if (hangmanfigure.keyboard[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            return 'A' + i; // Return the corresponding letter
        }
    }
    return '\0'; // No button clicked
}

void Hangman::setLeaderBoard(LeaderBoard &lBoard)
{
    this->lBoard = lBoard;
}

void Hangman::gameOver()
{
    isGameOver = true;
    lBoard.updateGamesPlayed();
    lBoard.resetStreak();
}

void Hangman::gameWon()
{
    isGameWon = true;
    hangmanfigure.updateImageNo(isGameWon); // pass the isWon argument as true
    hangmanfigure.setImage();
    lBoard.updateWon();
    lBoard.updateGamesPlayed();
    lBoard.updatePoints();
    lBoard.updateStreak();
}

void Hangman::drawHangman()
{
}

void Hangman::manageLives()
{
}

void Hangman::setInitialHangmanStates()
{
    trueGuesses = "_________"; // initialize true guesses
    falseGuesses = "\0\0\0\0\0\0\0\0\0";
    isGameOver = false;
    isGameWon = false;
    category.generateRandomWord();
}

#endif