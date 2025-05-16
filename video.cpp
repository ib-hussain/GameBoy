#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>
using namespace std;
#include "Headers/constants.h"
#include "Headers/snake.h"
#include "Headers/wordle.h"
#include "Headers/player.h"
#include "Headers/button.h"
#include "Headers/main.h"
//      || || | \\\\\\\\\\   //

int main()
{
    sf::RenderWindow window(sf::VideoMode(x_screen_length, y_screen_length), "GameBoy", sf::Style::Close | sf::Style::Titlebar);
    sf::RectangleShape line_up(sf::Vector2f(x_screen_length, 10));
    line_up.setFillColor(sf::Color::Black);
    sf::RectangleShape line_down(sf::Vector2f(x_screen_length, 10));
    line_down.setPosition(sf::Vector2f(0, y_screen_length - 10));
    line_down.setFillColor(sf::Color::Black);
    sf::RectangleShape line_left(sf::Vector2f(10, y_screen_length));
    line_left.setFillColor(sf::Color::Black);
    sf::RectangleShape line_right(sf::Vector2f(10, y_screen_length));
    line_right.setPosition(sf::Vector2f(x_screen_length - 10, 0));
    line_right.setFillColor(sf::Color::Black);
    sf::SoundBuffer win;
    if (!win.loadFromFile("Sounds/Game_won.wav"))
    {
    }
    sf::Sound win_s;
    win_s.setBuffer(win);
    sf::SoundBuffer loose;
    if (!loose.loadFromFile("Sounds/Game_loss.wav"))
    {
    }
    sf::Sound loose_s;
    loose_s.setBuffer(loose);
    sf::SoundBuffer hangman;
    if (!hangman.loadFromFile("Sounds/Hangman.wav"))
    {
    }
    sf::Sound hangman_s;
    hangman_s.setBuffer(hangman);
    sf::SoundBuffer hs;
    if (!hs.loadFromFile("Sounds/Highscore.wav"))
    {
    }
    sf::Sound hs_s;
    hs_s.setBuffer(hs);
    sf::SoundBuffer snake;
    if (!snake.loadFromFile("Sounds/snake_back.wav"))
    {
    }
    sf::Sound snake_s;
    snake_s.setBuffer(snake);
    sf::SoundBuffer wordlee;
    if (!wordlee.loadFromFile("Sounds/wordle.wav"))
    {
    }
    sf::Sound wordle_s;
    wordle_s.setBuffer(wordlee);
    /**
    wordle_s.play();
                // sf::sleep(sf::seconds(2));
    */
    // screen1:
    // Button new_player();
    // Button select_player();//maybe make this a dynamic array
    Button QUIT1(" Quit ", sf::Vector2f(x_screen_length / 2, 550), 40);
    // screen 2:
    // screen 3:
    Button main_snake_select(" Play Snake Game ", sf::Vector2f((x_screen_length / 2), (y_screen_length / 2) - 100), 40);
    Button Hangman_select(" Play Hangman ", sf::Vector2f(x_screen_length / 2, y_screen_length / 2), 40);
    Button Wordle_select(" Play Wordle ", sf::Vector2f(x_screen_length / 2, (y_screen_length / 2) + 100), 40);
    Button QUIT3(" Quit ", sf::Vector2f(x_screen_length / 2, (y_screen_length / 2) + 200), 40);
    // screen 4:
    // Snake main_snake;
    // screen 10:
    Button wordle_display(" Wordle ", sf::Vector2f(((x_screen_length - 540) / 2) + 24, y_screen_length - 698), 20);
    // sf::Texture wor;
    // wor.loadFromFile("PNG/wordle_logo.jpg");
    // wordle_display.shape.setTexture(&wor);
    Wordle game_wordle;
    // screen 5:
    // Button message5(" You won the game with highscore: "+to_string(main_snake.score), sf::Vector2f(x_screen_length/2,y_screen_length-500), 40);
    Button message5(" You won the game with highscore: " + to_string(750), sf::Vector2f(x_screen_length / 2, y_screen_length - 500), 40);
    Button QUIT5(" Quit ", sf::Vector2f(x_screen_length / 2, 500), 40);
    // screen 6:
    // Button message6(" You lost the game with score: "+to_string(main_snake.score), sf::Vector2f(x_screen_length/2,y_screen_length-500), 40);
    Button message6(" You lost the game with score: " + to_string(12), sf::Vector2f(x_screen_length / 2, y_screen_length - 500), 40);
    Button QUIT6(" Quit ", sf::Vector2f(x_screen_length / 2, 500), 40);
    // 11 screen-> wordle win
    Button message11(" You won the game with score: " + to_string(game_wordle.score), sf::Vector2f(x_screen_length / 2, y_screen_length - 500), 40);
    Button QUIT11(" Quit ", sf::Vector2f(x_screen_length / 2, 500), 40);
    // 14 screen-> wordle highscore
    Button message14(" You won the game with highscore: " + to_string(game_wordle.score), sf::Vector2f(x_screen_length / 2, y_screen_length - 500), 40);
    Button QUIT14(" Quit ", sf::Vector2f(x_screen_length / 2, 500), 40);
    // 12 screen-> wordle loose
    Button message12(" You lost the game with score: " + to_string(game_wordle.score), sf::Vector2f(x_screen_length / 2, y_screen_length - 500), 40);
    Button QUIT12(" Quit ", sf::Vector2f(x_screen_length / 2, 500), 40);

    while (window.isOpen())
    {
        window.clear(sf::Color::Green);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        switch (screen_num)
        {
        case 3: // 3 screen -> gameselect
            QUIT3.updateHover(sf::Mouse::getPosition(window));
            if (QUIT3.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    window.close();
                }
            }
            main_snake_select.updateHover(sf::Mouse::getPosition(window));
            Wordle_select.updateHover(sf::Mouse::getPosition(window));
            Hangman_select.updateHover(sf::Mouse::getPosition(window));
            if (main_snake_select.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    // main_snake.again_play();
                    main2();
                    screen_num = 4;
                }
            }
            if (Hangman_select.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    screen_num = 7;
                }
            }
            if (Wordle_select.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    screen_num = 10;
                }
            }
            break;
        case 4: // 4 screen -> main_snake game
            snake_s.play();
            // sf::sleep(sf::seconds(2));
            // main_snake.movement();
            // main_snake.wall_collide();
            // main_snake.food_eat();
            // main_snake.body_kill();
            // main_snake.check_Win();
            // if (!main_snake.life) {
            //     main_snake.dead();
            // }
            // if (main_snake.finish_won) {
            //     main_snake.win();
            // }
            main2();
            break;
        case 5: // 5 screen -> main_snake finish
            win_s.play();
            // sf::sleep(sf::seconds(7));
            hs_s.play();
            // sf::sleep(sf::seconds(2));
            QUIT5.updateHover(sf::Mouse::getPosition(window));
            if (QUIT5.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    screen_num = 3;
                }
            }
            break;
        case 6: // 6 screen -> main_snake die
            loose_s.play();
            // sf::sleep(sf::seconds(1));
            QUIT6.updateHover(sf::Mouse::getPosition(window));
            if (QUIT6.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    screen_num = 3;
                }
            }
            break;
        case 11: // 11 screen-> wordle win
            win_s.play();
            // sf::sleep(sf::seconds(7));
            QUIT11.updateHover(sf::Mouse::getPosition(window));
            if (QUIT11.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    screen_num = 3;
                }
            }
            break;
        case 14: // 14 screen-> wordle highscore
            hs_s.play();
            // sf::sleep(sf::seconds(2));
            QUIT14.updateHover(sf::Mouse::getPosition(window));
            if (QUIT14.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    screen_num = 3;
                }
            }
            break;
        case 12: // 12 screen-> wordle loose
            loose_s.play();
            // sf::sleep(sf::seconds(1));
            QUIT12.updateHover(sf::Mouse::getPosition(window));
            if (QUIT12.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    screen_num = 3;
                }
            }
            break;
        case 10: // 10 screen-> wordle game
            wordle_s.play();
            // sf::sleep(sf::seconds(2));
            game_wordle.gameplay();
            break;

        case 1: // 1 screen -> player select
            QUIT1.updateHover(sf::Mouse::getPosition(window));
            if (QUIT1.isClicked(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    window.close();
                }
            }
            break;
        case 2: // 2 screen -> new player make then redirect to 1 page

            break;
        case 7: // 7 screen -> hangman game
            hangman_s.play();
            main1();
            // sf::sleep(sf::seconds(6));
            break;
        case 8: // 8 screen -> hangman die
            loose_s.play();
            // sf::sleep(sf::seconds(1));
            break;
        case 9: // 9 screen -> hangman win
            win_s.play();
            // sf::sleep(sf::seconds(7));
            break;
        case 15: // 15 screen-> hangman highscore
            hs_s.play();
            // sf::sleep(sf::seconds(2));
            break;
        case 13: // 13 screen -> maybe put a pause screen here
            break;
        }

        // drawing
        switch (screen_num)
        {
        case 3: // 3 screen -> gameselect
            QUIT3.draw(window);
            main_snake_select.draw(window);
            Wordle_select.draw(window);
            Hangman_select.draw(window);
            break;
        case 4: // 4 screen -> main_snake game
            // window.draw(main_main_snake.head);
            // main_snake.draw(window);
            break;
        case 5: // 5 screen -> main_snake finish and higghscore
            // message5.text.setString(" You won the game with highscore: "+to_string(main_snake.score));
            message5.text.setString(" You won the game with highscore: " + to_string(750));

            message5.draw(window);
            QUIT5.draw(window);
            break;
        case 6: // 6 screen -> main_snake die
            // message6.text.setString(" You lost the game with score: "+to_string(main_snake.score));
            message6.text.setString(" You won the game with highscore: " + to_string(12));
            message6.draw(window);
            QUIT6.draw(window);
            break;
        case 10: // 10 screen-> wordle game
            wordle_display.draw(window);
            game_wordle.draw(window);
            break;
        case 11: // 11 screen-> wordle win
            message11.text.setString(" You won the game with score: " + to_string(game_wordle.score));
            message11.draw(window);
            QUIT11.draw(window);
            break;
        case 14: // 14 screen-> wordle highscore
            message14.text.setString(" You won the game with highscore: " + to_string(game_wordle.score));
            message14.draw(window);
            QUIT14.draw(window);
            break;
        case 12: // 12 screen-> wordle loose
            message12.text.setString(" You lost the game with score: " + to_string(game_wordle.score));
            message12.draw(window);
            QUIT12.draw(window);
            break;

        case 1: // 1 screen -> player select
            QUIT1.draw(window);
            break;
        case 2: // 2 screen -> new player make then redirect to 1 page
            break;
        case 7: // 7 screen -> hangman game
            break;
        case 8: // 8 screen -> hangman die
            break;
        case 9: // 9 screen -> hangman win
            break;
        case 15: // 15 screen-> hangman highscore
            break;
        case 13: // 13 screen -> maybe put a pause screen here
            break;
        }
        window.draw(line_up);
        window.draw(line_down);
        window.draw(line_left);
        window.draw(line_right);
        window.display();
    }
    return 0;
}

// 7 is maximum number of hangman tries
// 32 SPACE
// 13 ENTER
// 8 BACKSPACE
/**
// 65 A
// 66 B
// 67 C
// 68 D
// 69 E
// 70 F
// 71 G
// 72 H
// 73 I
// 74 J
// 75 K
// 76 L
// 77 M
// 78 N
// 79 O
// 80 P
// 81 Q
// 82 R
// 83 S
// 84 T
// 85 U
// 86 V
// 87 W
// 88 X
// 89 Y
// 90 Z

// 97 a
// 98 b
// 99 c
// 100 d
// 101 e
// 102 f
// 103 g
// 104 h
// 105 i
// 106 j
// 107 k
// 108 l
// 109 m
// 110 n
// 111 o
// 112 p
// 113 q
// 114 r
// 115 s
// 116 t
// 117 u
// 118 v
// 119 w
// 120 x
// 121 y
// 122 z
**/