#pragma once

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "SFML/Graphics.hpp"
#include "iostream"

using namespace sf;
using namespace std;

const class Model
{
public:
    const int CirclesXCount = 35;
    const int CirclesYCount = 35;
    float timer = 0;
    float timerG = 0;

    float time1 = 30.0f;
    float time2 = 300.0f;

    int CirclesArray[35][35];

    vector<float> ValsX;
    vector<float> ValsY1;
    vector<float> ValsY2;


    pair<int, int> VacancyArray[35];
    CircleShape FirstAtom;
    CircleShape SecondAtom;
    CircleShape Vacancy;
    CircleShape Black;

    Color clFirstAtom = Color(255, 0, 0);
    Color clSecondAtom = Color(0, 255, 0);
    Color clVacancy = Color(255, 255, 255);

    float CircleRadius = 6.0f;
    float DrawOffset = 35.0f;

    int xCoords = 1;
    int yCoords = 1;

    bool bGridDrawed = false;

    void SetCircleColor();
    void DrawCircles(RenderWindow& win, float time);
    void DrawCircleGrid(RenderWindow& win);
    void setting();
    void ClearGrid(RenderWindow& win);
    void DrawCircleColor(RenderWindow& win, int x, int y, int num);

    void CalculateAtoms();
    void CalculateSize();

    pair<int, int> GraficSize;
    pair<int, int> GraficLoc;

    RectangleShape GraficField;
    // void SetVars();
    //  void DrawGrafic(RenderWindow& win,float time);
};

const class Math
{
public:
    bool RandBool();
};

