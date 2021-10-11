#pragma once

#include "SFML/Graphics.hpp"
#include "iostream"

using namespace sf;
using namespace std;

const class Model
{
public:
    const int CirclesXCount = 25;
    const int CirclesYCount = 25;

    int CirclesArray[25][25];


    CircleShape FirstAtom;
    CircleShape SecondAtom;
    CircleShape Vacancy;
    CircleShape Black;

    Color clFirstAtom = Color(255, 0, 0);
    Color clSecondAtom = Color(0, 255, 0);
    Color clVacancy = Color(255, 255, 255);

    float CircleRadius = 14.0f;
    float DrawOffset = 35.0f;

    int xCoords = 1;
    int yCoords = 1;

    bool bGridDrawed = false;

    void SetCircleColor();
    void DrawCircles(RenderWindow& win, float time);
    void DrawCircleGrid(RenderWindow& win);
    void setting();
    void ClearGrid(RenderWindow& win);
    void DrawCircleColor(RenderWindow& win,int x, int y, int num);
};


const class Math
{
public:
    bool RandBool();
};
