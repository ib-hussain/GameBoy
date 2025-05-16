#ifndef BUTTON_H
#define BUTTON_H

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

class Button
{
public:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    sf::Color runningcolor;
    Button(const string &button_text, const sf::Vector2f &position, unsigned int font_size = 10)
    {
        sf::Vector2f size(0, 0);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Transparent);
        runningcolor = shape.getFillColor();

        font.loadFromFile("Fonts/Baskervville-Regular.ttf");
        text.setFont(font);
        text.setString(button_text);
        text.setCharacterSize(font_size);
        // text.setOrigin(sf::Vector2f(size.x/2, size.y/2));
        text.setFillColor(sf::Color::Black);
        // text.setOutlineColor(sf::Color::Black);
        // text.setOutlineThickness(2);
        // put any remaining functionalityy that needed in here accordign to buton need

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, (textBounds.height / 2) + 4);
        text.setPosition(position.x, position.y - 4);
        size.x = textBounds.width + 4;
        size.y = textBounds.height + 10;
        shape.setSize(size);
        shape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
        window.draw(text);
    }
    bool isClicked(const sf::Vector2i &mousePosition)
    {
        // if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        //     sf::Vector2i mouse_position= sf::Mouse::getPosition(window);
        //     circle.setPosition(float(mouse_position.x), float(mouse_position.y));
        //     circle.setRotation(0);
        // }
        // auto startTime = std::chrono::steady_clock::now();
        // std::srand(static_cast<unsigned int>(std::time(nullptr)));
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
    }
    void updateHover(const sf::Vector2i &mousePosition)
    {
        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            shape.setFillColor(sf::Color(0x94, 0x92, 0x92));
        }
        else
        {
            shape.setFillColor(runningcolor);
        }
    }
};

#endif