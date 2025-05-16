#ifndef CATEGORY_H
#define CATEGORY_H

#include "constants.h"
// #include "guessedWord.h"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>
using namespace std;

string guessedWord;

class Category
{
private:
    string categoryName;
    const string *words; // the list of words of particular category

public:
    Category();
    Category(string categoryNameVal);

    void setCategoryName(string categoryVal);
    void assignWordList(string categoryNameVal);
    void generateRandomWord();
};

Category::Category() : categoryName("Animal")
{
    words = new string[20];
    words = WORDLIST[0];
    generateRandomWord();
}
Category::Category(string categoryNameVal)
    : categoryName(categoryNameVal)
{
    words = new string[20];
    if (categoryNameVal == "animal")
    {

        words = WORDLIST[0];
    }
    else if (categoryNameVal == "country")
    {
        words = WORDLIST[1];
    }
    else if (categoryNameVal == "fruit")
    {
        words = WORDLIST[2];
    }
}

void Category::setCategoryName(string categoryVal)
{
    this->categoryName = categoryVal;
    assignWordList(categoryVal);
}

void Category::assignWordList(string categoryNameVal)
{
    words = new string[20];
    if (categoryNameVal == "animal")
    {

        words = WORDLIST[0];
    }
    else if (categoryNameVal == "country")
    {
        words = WORDLIST[1];
    }
    else if (categoryNameVal == "fruit")
    {
        words = WORDLIST[2];
    }
}

void Category::generateRandomWord()
{
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % 20;
    guessedWord = words[randomIndex];
    cout << "Generated Random Word: " << guessedWord << endl;
}

#endif