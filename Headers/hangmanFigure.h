#ifndef HANGMANFIGURE_H
#define HANGMANFIGURE_H

#include "window.h"
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
#include <cmath>
using namespace std;
#include "constants.h"
#include "leaderBoard.h"

using namespace sf;

const Color BUTTON_FILL_COLOR(173, 216, 230); // keyboard button background color

class HangmanFigure
{
public:
    CircleShape keyboard[26];
    Text innerLetters[26];
    RectangleShape trueGuessesBoard[9];
    Text trueGuessesChar[9];
    int currentImageNo;
    Texture texture;
    Sprite sprite;
    Font font;

public:
    HangmanFigure();
    void setImage();
    void updateImageNo(bool isWon = false);
    void drawKeyboard(int index = -1, int status = 0);
    void drawTrueGuesses(char ch = '\0', int index = -1); // section where the user's true guesses stores
    void drawLeaderBoard(LeaderBoard LeaderBoard);
    void setInitialHangfigStates();
    void drawNewGameButton();
};

HangmanFigure::HangmanFigure()
{
    // Load font
    if (!font.loadFromFile("Fonts/Baskervville-Regular.ttf"))
    {
        cout << "Error loading font!" << endl;
        exit(1);
    }
    setInitialHangfigStates();
}

void HangmanFigure::setImage()
{
    if (!texture.loadFromFile(IMG_PATHS[currentImageNo]))
    {
        cout << "Your image is not loaded" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(HANGMAN_START_X, HANGMAN_START_Y);
    window.draw(sprite);
}

void HangmanFigure::updateImageNo(bool isWon)
{
    this->currentImageNo++;
    if (isWon)
        this->currentImageNo = 8;
}

void HangmanFigure::drawKeyboard(int index, int status)
{ // status may have any of three values 0, 1, -1 which decides the color of
  // background(light blue, green or red) in case of normal, trueguess or falseguess
    // Get the Mouse position relative to the window and stroe in 2d vector
    Vector2i mousePos = Mouse::getPosition(window);

    for (int i = 0; i < 26; i++)
    {
        // Create a circle button and adjust the settings
        CircleShape button(BUTTON_RADIUS);
        button.setFillColor(keyboard[i].getFillColor());
        button.setOutlineThickness(2.f);
        button.setOutlineColor(Color::Black);

        if (i == index && status == 1)
        {
            button.setFillColor(Color(192, 255, 62));
        }
        else if (i == index && status == -1)
        {
            button.setFillColor(Color::Red);
        }
        else if (keyboard[i].getFillColor() != Color::Red && keyboard[i].getFillColor() != Color(192, 255, 62))
        {
            button.setFillColor(BUTTON_FILL_COLOR);
        }

        // Calculate button position
        int row = i / 8; // 8 buttons per row
        int col = i % 8;

        // Center the last two buttons
        if (i == 24)
            col = 3;
        else if (i == 25)
            col = 4;

        button.setPosition(
            KEYBOARD_START_X + col * (BUTTON_WIDTH + BUTTON_SPACING),
            KEYBOARD_START_Y + row * (BUTTON_HEIGHT + BUTTON_SPACING));

        // Check hover effect  (Add radius in the coordinates of top left corner to get center)
        Vector2f buttonCenter = button.getPosition() + Vector2f(30.0f, 30.0f);
        float distance = sqrt(pow(mousePos.x - buttonCenter.x, 2) + pow(mousePos.y - buttonCenter.y, 2));

        if (distance <= 30.0f) // If the mouseCursor current position is within the radius
        {
            if (button.getFillColor() != Color::Red && button.getFillColor() != Color(192, 255, 62))
                button.setFillColor(Color(150, 150, 250));
        }
        else
        {
            if (button.getFillColor() != Color::Red && button.getFillColor() != Color(192, 255, 62))
                button.setFillColor(BUTTON_FILL_COLOR);
        }

        // Create text for the button and adjust settings
        Text letter;
        letter.setFont(font);
        letter.setString(string(1, 'A' + i)); // Convert ASCII value to character. argument '1' says repeat char just once.
        letter.setCharacterSize(30);
        letter.setFillColor(Color::Black);

        // # --- Center the text on the button --- #
        // (FloatRect is a bounding box that contains the shape (cirular button)). It has
        // 1) position(x,y): the top left corner of the rectangle
        // 2) size(width, height): the dimension of the rectangle
        FloatRect textBounds = letter.getLocalBounds();
        letter.setPosition(
            button.getPosition().x + 30.0f - textBounds.width / 2.f,
            button.getPosition().y + 30.0f - textBounds.height / 2.f - textBounds.top);

        keyboard[i] = button;
        innerLetters[i] = letter;
    }
}

void HangmanFigure::drawTrueGuesses(char ch, int index)
{
    for (int i = 0; i < 9; i++)
    {
        RectangleShape button(Vector2f(BUTTON_WIDTH - 8, BUTTON_HEIGHT - 8));
        // button.setFillColor(BUTTON_FILL_COLOR);
        button.setOutlineColor(Color::Black);
        button.setOutlineThickness(2.0f);
        button.setPosition(
            (KEYBOARD_START_X + 10) + i * (BUTTON_WIDTH + BUTTON_SPACING - 10),
            KEYBOARD_START_Y - 100);

        Text letter;
        if (i == index)
        {
            trueGuessesChar[i].setString(string(1, ch));
        }

        letter.setFont(font);
        letter.setString(trueGuessesChar[i].getString()); // gets the inner text of the trueGuessesCar[i]
        letter.setCharacterSize(30);
        letter.setFillColor(Color::Black);

        FloatRect textBounds = letter.getLocalBounds();
        letter.setPosition(
            button.getPosition().x + 10.5f, button.getPosition().y + 2.0f);

        trueGuessesBoard[i] = button;
        trueGuessesChar[i] = letter;
    }
}

void HangmanFigure::drawLeaderBoard(LeaderBoard lboard)
{
    Text score[3];

    score[0].setFont(font);
    score[0].setString("-  " + to_string(lboard.getWon()) + " / " + to_string(lboard.getGamesPlayed()));
    score[0].setCharacterSize(25);
    score[0].setFillColor(Color(50, 50, 50));
    score[0].setPosition(HANGMAN_START_X, 50);

    score[1].setFont(font);
    score[1].setString("-  " + to_string(lboard.getPoints()) + "  Words");
    score[1].setCharacterSize(25);
    score[1].setFillColor(Color(50, 50, 50));
    score[1].setPosition(HANGMAN_START_X, 90);

    score[2].setFont(font);
    score[2].setString("-  " + to_string(lboard.getStreak() - 1) + "  Streaks");
    score[2].setCharacterSize(25);
    score[2].setFillColor(Color(50, 50, 50));
    score[2].setPosition(HANGMAN_START_X, 130);

    window.draw(score[0]);
    window.draw(score[1]);
    window.draw(score[2]);
}

void HangmanFigure::setInitialHangfigStates()
{
    this->currentImageNo = 0;
    for (int i = 0; i < 26; i++)
    {
        if (i < 9)
        {
            trueGuessesChar[i].setString('_'); // initialize the initial content of the trueGuessChar to null.
        }
        keyboard[i].setFillColor(BUTTON_FILL_COLOR);
    }
}

void HangmanFigure::drawNewGameButton()
{
    // Create a rectangle for the button
    RectangleShape newGameButton(Vector2f(BUTTON_WIDTH + 115, BUTTON_HEIGHT));
    newGameButton.setPosition(KEYBOARD_START_X, 60);

    // Check if the mouse is hovering over the button
    Vector2i mousePos = Mouse::getPosition(window);
    FloatRect buttonBounds = newGameButton.getGlobalBounds();

    if (buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        // Hover effect: Change the fill and outline color
        newGameButton.setFillColor(Color(0x94, 0x92, 0x92)); // Default light red
        newGameButton.setOutlineColor(Color::Green);         // Default black outline
    }
    else
    {
        // Default appearance
        // sf::Color(0x94, 0x92, 0x92)
        newGameButton.setFillColor(Color::Green);    // Light red
        newGameButton.setOutlineColor(Color::Green); // Darker outline
    }

    newGameButton.setOutlineThickness(2.0f);

    // Create and configure the text
    Text newGame;
    newGame.setFont(font); // Set the font for the text
    newGame.setString(" New Game ");
    newGame.setCharacterSize(20);
    newGame.setFillColor(Color::Black);
    newGame.setPosition(KEYBOARD_START_X + 20, 70); // Adjusted position to center inside button

    // Draw the button and text
    window.draw(newGameButton);
    window.draw(newGame);
}

// void HangmanFigure::drawNewGameButton()
// {
//     RectangleShape newGameButton(Vector2f(BUTTON_WIDTH + 115, BUTTON_HEIGHT));
//     newGameButton.setFillColor(Color(255, 102, 102));
//     newGameButton.setOutlineColor(Color::Black);
//     newGameButton.setOutlineThickness(2.0f);
//     newGameButton.setPosition(KEYBOARD_START_X, 60);

//     // Create and configure the text
//     Text newGame;
//     newGame.setFont(font); // Set the font for the text
//     newGame.setString("New Game");
//     newGame.setCharacterSize(25);
//     newGame.setFillColor(Color(50, 50, 50));
//     newGame.setPosition(KEYBOARD_START_X + 10, 70); // Adjusted position to center inside button

//     // Draw the button and text
//     window.draw(newGameButton);
//     window.draw(newGame);
// }

#endif
