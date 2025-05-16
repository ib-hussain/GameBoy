#ifndef SNAKE_H
#define SNAKE_H

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
#include <algorithm>
#include <ctime>
using namespace std;

// Constants
const int WIDTH = x_screen_length           ;
const int HEIGHT = y_screen_length          ;
const int GRID_SIZE = snake_head_radius*2   ;
const int MAX_SNAKE_LENGTH = 30             ;
const int MAX_OBSTACLES = 7                 ;

class SnakeGame{
public:
    sf::RenderWindow window;
    sf::RectangleShape snakeSegment;
    sf::RectangleShape food;
    sf::RectangleShape obstacle;
    // In the SnakeGame class, add a new member for the snake head sprite
    sf::Sprite snakeHeadSprite;

    int snake[MAX_SNAKE_LENGTH][2]; // Snake body positions
    int snakeLength;
    int foodX, foodY;
    int obstacles[MAX_OBSTACLES][2]; // Obstacles positions
    int obstacleCount;
    int direction; // 0: Up, 1: Right, 2: Down, 3: Left

    int score;
    float speed;
    bool isGameOver;
    bool isMenuActive;
    int difficulty;
    int selectedOption;
    int HightScore;

    sf::Font font;
    sf::Text scoreText;
    sf::Text menuText[4];

    sf::SoundBuffer gamebgBuffer;
    sf::Sound gamebg;
    sf::SoundBuffer foodSoundBuffer;
    sf::Sound foodSound;
    sf::SoundBuffer gameOverSoundBuffer;
    sf::Sound gameOverSound;

public:
    SnakeGame() : window(sf::VideoMode(WIDTH, HEIGHT), "Snake Game") {
        speed = 0.1f; 
        selectedOption = 0; 
        isGameOver = false;
        isMenuActive = true;
        difficulty = 1;
        score = 0;
        direction = 1; 
        snakeLength= 3; 
        // Initialize snake
        for (int i=0;i<snakeLength;i++){
            snake[i][0] = WIDTH / 2 - i * GRID_SIZE;
            snake[i][1] = HEIGHT / 2;
        }

        // Initialize food
        food.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
        food.setFillColor(sf::Color::Yellow);
        generateFood();

        // Initialize snake segment
        snakeSegment.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
        snakeSegment.setFillColor(sf::Color::White);

        // Initialize obstacle
        obstacle.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
        obstacle.setFillColor(sf::Color::Black);

        // Load font
        font.loadFromFile("Fonts/Baskervville-Regular.ttf");

        // Initialize menu text
        menuText[0].setFont(font);
        menuText[0].setString("Start Game");
        menuText[0].setCharacterSize(32);
        menuText[0].setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 100);

        menuText[1].setFont(font);
        menuText[1].setString("Difficulty: Easy");
        menuText[1].setCharacterSize(32);
        menuText[1].setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 50);

        menuText[2].setFont(font);
        menuText[2].setString("Exit");
        menuText[2].setCharacterSize(32);
        menuText[2].setPosition(WIDTH / 2 - 100, HEIGHT / 2);

        updateMenuSelection();

        // Load sound effects
        foodSoundBuffer.loadFromFile("Sounds/snake_back.wav");
        foodSound.setBuffer(foodSoundBuffer);

        gamebgBuffer.loadFromFile("Sounds/snake_back.wav");
        gamebg.setBuffer(gamebgBuffer);
        
        gameOverSoundBuffer.loadFromFile("Sounds/Game_loss.wav");
        gameOverSound.setBuffer(gameOverSoundBuffer);
    }

    void loadHighScore(){
        ifstream inFile("Headers/Snake_hs.txt");
        inFile >> HightScore; // Read the saved high score
        inFile.close();
    }

    void saveHighScore()
    {
        ofstream outFile("Headers/Snake_hs.txt");
        outFile << HightScore; // Save the current high score to the file
        outFile.close();
    }

    void checkHighScore(){
        if (score > HightScore){
            HightScore = score; 
            saveHighScore(); 
        }
    }
    void run()
    {
        sf::Clock clock;
        float timer = 0.0f;

        while (window.isOpen())
        {
            float deltaTime = clock.restart().asSeconds();
            timer += deltaTime;
            // In the SnakeGame constructor:

            // Load snake head texture
            sf::Texture snakeHeadTexture;
            if (!snakeHeadTexture.loadFromFile("snakii.png"))
            {
                std::cerr << "Failed to load snake head texture!" << std::endl;
                return;
            }
            snakeHeadSprite.setTexture(snakeHeadTexture);
            snakeHeadSprite.setScale(static_cast<float>(GRID_SIZE) / snakeHeadTexture.getSize().x,
                                     static_cast<float>(GRID_SIZE) / snakeHeadTexture.getSize().y);

            // In the render method, replace rectangle with sprite for the head:
            for (int i = 0; i < snakeLength; ++i)
            {
                if (i == 0)
                {
                    snakeHeadSprite.setPosition(snake[i][0], snake[i][1]);
                    window.draw(snakeHeadSprite); // Draw the snake head sprite
                }
                else
                {
                    snakeSegment.setPosition(snake[i][0], snake[i][1]);
                    window.draw(snakeSegment); // Draw the body as rectangle
                }
            }

            handleEvents();

            if (!isMenuActive && !isGameOver && timer > speed)
            {
                timer = 0.0f;
                update();
            }

            render();
        }
    }

private:
    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (isMenuActive)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        selectedOption = (selectedOption - 1 + 3) % 3;
                        updateMenuSelection();
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        selectedOption = (selectedOption + 1) % 3;
                        updateMenuSelection();
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        handleMenuSelection();
                    }
                }
            }
            else if (isGameOver)
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                {
                    restartGame();
                }
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != 2)
                    direction = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != 3)
                    direction = 1;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != 0)
                    direction = 2;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != 1)
                    direction = 3;
            }
        }
    }

    void handleMenuSelection()
    {
        switch (selectedOption)
        {
        case 0: // Start Game
            isMenuActive = false;
            generateObstacles();
            break;
        case 1: // Change Difficulty
            cycleDifficulty();
            break;
        case 2: // Exit
            window.close();
            break;
        }
    }

    void update()
    {
        // Move the snake
        for (int i = snakeLength - 1; i > 0; --i)
        {
            snake[i][0] = snake[i - 1][0];
            snake[i][1] = snake[i - 1][1];
        }

        switch (direction)
        {
        case 0:
            snake[0][1] -= GRID_SIZE;
            break; // Up
        case 1:
            snake[0][0] += GRID_SIZE;
            break; // Right
        case 2:
            snake[0][1] += GRID_SIZE;
            break; // Down
        case 3:
            snake[0][0] -= GRID_SIZE;
            break; // Left
        }

        // Wrap-around
        if (snake[0][0] < 0)
            snake[0][0] = WIDTH - GRID_SIZE;
        if (snake[0][0] >= WIDTH)
            snake[0][0] = 0;
        if (snake[0][1] < 0)
            snake[0][1] = HEIGHT - GRID_SIZE;
        if (snake[0][1] >= HEIGHT)
            snake[0][1] = 0;

        // Check collisions
        if (checkCollision())
        {
            isGameOver = true;
            gameOverSound.play();
            checkHighScore(); // Check and save the high score
        }

        // Check food
        if (snake[0][0] == foodX && snake[0][1] == foodY)
        {
            snakeLength++;
            score += 10;
            speed -= 0.005f; // Increase difficulty
            generateFood();
            foodSound.play();
            checkHighScore();
        }
    }

    bool checkCollision()
    {
        // Check self-collision
        for (int i = 1; i < snakeLength; ++i)
        {
            if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
            {
                return true;
            }
        }

        // Check obstacle collision
        for (int i = 0; i < obstacleCount; ++i)
        {
            if (snake[0][0] == obstacles[i][0] && snake[0][1] == obstacles[i][1])
            {
                return true;
            }
        }

        return false;
    }

    void generateFood()
    {
        srand(static_cast<unsigned>(time(0)));
        foodX = (rand() % (WIDTH / GRID_SIZE)) * GRID_SIZE;
        foodY = (rand() % (HEIGHT / GRID_SIZE)) * GRID_SIZE;
        food.setPosition(foodX, foodY);
    }

    void generateObstacles()
    {
        obstacleCount = difficulty * 5;
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < obstacleCount; ++i)
        {
            obstacles[i][0] = (rand() % (WIDTH / GRID_SIZE)) * GRID_SIZE;
            obstacles[i][1] = (rand() % (HEIGHT / GRID_SIZE)) * GRID_SIZE;
        }
    }

    void render()
    {
        window.clear(sf::Color::Green);

        if (isMenuActive)
        {
            // Render menu
            for (int i = 0; i < 3; ++i)
            {
                window.draw(menuText[i]);
            }
        }
        else if (isGameOver)
        {
            renderGameOver();
        }
        else
        {
            // Draw the snake using the sprite for the head and rectangles for the body
            for (int i = 0; i < snakeLength; ++i)
            {
                if (i == 0)
                {
                    // Set position for snake head and draw as sprite
                    snakeHeadSprite.setPosition(snake[i][0], snake[i][1]);
                    window.draw(snakeHeadSprite); // Draw snake head as sprite
                }
                else
                {
                    // Draw body segments as rectangles
                    snakeSegment.setPosition(snake[i][0], snake[i][1]);
                    window.draw(snakeSegment);
                }
            }

            string scoreString = "Score: " + to_string(score);

            // Update the sf::Text object with the score
            sf::Text scoreText(scoreString, font, 30);
            scoreText.setFillColor(sf::Color::White); // You can choose any color
            scoreText.setPosition(10, 10);            // Position it at the top-left

            // Draw the score
            window.draw(scoreText);

            // Draw food
            window.draw(food);

            // Draw obstacles
            for (int i = 0; i < obstacleCount; ++i)
            {
                obstacle.setPosition(obstacles[i][0], obstacles[i][1]);
                window.draw(obstacle);
            }

            // Draw score
            window.draw(scoreText);
        }

        window.display();
    }
    void renderGameOver()
    {
        sf::Text gameOverText("Game Over", font, 48);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 100);
        window.draw(gameOverText);

        sf::Text restartText("Press Enter to Restart", font, 24);
        restartText.setFillColor(sf::Color::White);
        restartText.setPosition(WIDTH / 2 - 140, HEIGHT / 2);
        window.draw(restartText);

        // Display the score
        sf::Text scoreText("Score: " + std::to_string(score), font, 30);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(WIDTH / 2 - 70, HEIGHT / 2 + 40);
        window.draw(scoreText);

        // Display the high score
        sf::Text highScoreText("High Score: " + std::to_string(HightScore), font, 30);
        highScoreText.setFillColor(sf::Color::Yellow);
        highScoreText.setPosition(WIDTH / 2 - 90, HEIGHT / 2 + 80);
        window.draw(highScoreText);
    }

    void cycleDifficulty()
    {
        difficulty = (difficulty % 3) + 1;

        switch (difficulty)
        {
        case 1:
            menuText[1].setString("Difficulty: Easy");
            break;
        case 2:
            menuText[1].setString("Difficulty: Medium");
            break;
        case 3:
            menuText[1].setString("Difficulty: Hard");
            break;
        }
    }

    void restartGame()
    {
        snakeLength = 3;
        direction = 1;
        score = 0;
        speed = 0.1f;
        isGameOver = false;
        isMenuActive = true;

        for (int i = 0; i < snakeLength; ++i)
        {
            snake[i][0] = WIDTH / 2 - i * GRID_SIZE;
            snake[i][1] = HEIGHT / 2;
        }

        generateFood();
        generateObstacles();
    }

    void updateMenuSelection()
    {
        for (int i = 0; i < 3; ++i)
        {
            if (i == selectedOption)
            {
                menuText[i].setFillColor(sf::Color::Red);
            }
            else
            {
                menuText[i].setFillColor(sf::Color::White);
            }
        }
    }
};

int main2()
{
    SnakeGame game;
    game.run();
    return 0;
}

#endif
