#include "SFML/Graphics.hpp"
#include "iostream"

using namespace sf;
using namespace std;

class Math
{
};

const class Model
{
public:
    int CirclesXCount = 50;
    int CirclesYCount = 50;

    CircleShape FirstAtom;
    CircleShape SecondAtom;
    CircleShape Vacancy;
    CircleShape Black;

    Color clFirstAtom = Color(255, 0, 0);
    Color clSecondAtom = Color(0, 255, 0);
    Color clVacancy = Color(255, 255, 255);

    float CircleRadius = 10.0f;
    float DrawOffset = 50.0f;

    int xCoords = 1;
    int yCoords = 1;

    bool bGridDrawed = false;

    void SetCircleColor()
    {
        FirstAtom.setFillColor(clFirstAtom);
        FirstAtom.setRadius(CircleRadius);
        SecondAtom.setFillColor(clSecondAtom);
        SecondAtom.setRadius(CircleRadius);
        Vacancy.setFillColor(clVacancy);
        Vacancy.setRadius(CircleRadius);
        Black.setFillColor(Color::Black);
        Black.setRadius(CircleRadius);
        return;
    };

    void DrawCircles(RenderWindow& win, float time)
    {
        float localX = xCoords * 2 * CircleRadius;
        float localY = yCoords * 2 * CircleRadius;

        win.draw(Vacancy);
        Vacancy.setPosition(50 + (std::rand() % (50 - 1 + 1)) * 2 * CircleRadius, 50 + (std::rand() % (50 - 1 + 1)) * 2 * CircleRadius);
        win.display();
    };

    void DrawCircleGrid(RenderWindow& win)
    {

        if (bGridDrawed) return;

        float localX = xCoords * 2 * CircleRadius;
        float localY = yCoords * 2 * CircleRadius;

        for (int j = 0; j < CirclesYCount; j++)
            for (int i = 0; i < CirclesXCount; i++)
            {
                if (i < CirclesXCount / 2)
                {
                    win.draw(FirstAtom);
                    FirstAtom.setPosition(localX * i + DrawOffset, localY * j + DrawOffset);
                    win.display();
                }
                if (i >= CirclesXCount / 2)
                {
                    win.draw(SecondAtom);
                    SecondAtom.setPosition(localX * i + DrawOffset, localY * j + DrawOffset);
                    win.display();
                }
            }
        bGridDrawed = true;

        win.draw(FirstAtom);
        FirstAtom.setPosition(localX * 100 + DrawOffset, localY * 100 + DrawOffset);
        win.display();

        win.draw(SecondAtom);
        SecondAtom.setPosition(localX * 100 + DrawOffset, localY * 100 + DrawOffset);
        win.display();

        win.draw(Black);
        win.display();

        return;
    }

    void setting() { return; };

    void ClearGrid(RenderWindow& win)
    {
        win.clear();
        bGridDrawed = false;
    }
};

int main()
{
    Model model;
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(model.CirclesXCount * model.CircleRadius * 2 + model.DrawOffset * 2,
                            model.CirclesYCount * model.CircleRadius * 2 + model.DrawOffset * 2),
        "SFML works!", Style::None, settings);

    model.SetCircleColor();

    sf::Event event;
    Clock clock;
    float timer = 0.0f;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        timer += time;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        model.DrawCircleGrid(window);

        if (timer >= 3.0f)
        {
            timer = 0.0f;
            model.DrawCircles(window, time);
        }

        if (Keyboard::isKeyPressed(Keyboard::C))
        {
            model.ClearGrid(window);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
    }

    return 0;
}
