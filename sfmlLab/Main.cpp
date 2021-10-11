
#include "Main.h"

int main()
{
    Model model;
    Math math;
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    float windowXSize = model.CirclesXCount * model.CircleRadius * 2 + model.DrawOffset * 2;
    float windowYSize = model.CirclesYCount * model.CircleRadius * 2 + model.DrawOffset * 2;

    RenderWindow window(VideoMode(windowXSize + 500, windowYSize), "SFML Lab", Style::Default, settings);

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

        model.DrawCircles(window, time);

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

void Model::SetCircleColor()
{
    FirstAtom.setFillColor(clFirstAtom);
    FirstAtom.setRadius(CircleRadius);

    SecondAtom.setFillColor(clSecondAtom);
    SecondAtom.setRadius(CircleRadius);

    Vacancy.setFillColor(clVacancy);
    Vacancy.setRadius(CircleRadius);

    return;
}
void Model::DrawCircles(RenderWindow& win, float time)
{
    Math math;
    for (int j = 0; j < CirclesYCount-1 ; j++)
        for (int i = 0; i < CirclesXCount - 1; i++)
        {
            cout << "i: " << i << "  j: " << j << endl;
            if (CirclesArray[i][j] == 3)
            {
                int right = 0;
                int up = 0;

                if (math.RandBool())
                    right = 1;
                else
                    right = -1;

                if (math.RandBool())
                    up = 1;
                else
                    up = -1;
                if (!CirclesArray[i + right][j + up]) return;
                if (i + right < 0 || i + right >= CirclesXCount - 1) return;
                if (j+up < 0 || j +up >= CirclesYCount-1 ) return;

                if (CirclesArray[i + right][j + up] == 3)
                    return;
                else
                {
                    cout << "i + right: " << i + right << "  j + up: " << j + up << endl;
                    CirclesArray[i][j] = CirclesArray[i + right][j + up];
                    DrawCircleColor(win, i, j, CirclesArray[i + right][j + up]);
                    CirclesArray[i + right][j + up] = 3;
                    DrawCircleColor(win, i + right, j + up, 3);
                }
            }
        }
}

void Model::DrawCircleGrid(RenderWindow& win)
{
    Math math;
    if (bGridDrawed) return;

    float localX = 2 * CircleRadius;
    float localY = 2 * CircleRadius;

    for (int j = 0; j < CirclesYCount; j++)
        for (int i = 0; i < CirclesXCount; i++)
        {

            if (i < CirclesXCount / 2)
            {
                win.draw(FirstAtom);
                FirstAtom.setPosition(localX * i + DrawOffset, localY * j + DrawOffset);
                win.display();
                CirclesArray[i][j] = 1;
            }
            if (i > CirclesXCount / 2)
            {
                win.draw(SecondAtom);
                SecondAtom.setPosition(localX * i + DrawOffset, localY * j + DrawOffset);
                win.display();
                CirclesArray[i][j] = 2;
            }
            if (i == CirclesXCount / 2)
            {
                win.draw(Vacancy);
                Vacancy.setPosition(localX * i + DrawOffset, localY * j + DrawOffset);
                win.display();
                CirclesArray[i][j] = 3;
            }
        }
    bGridDrawed = true;

    win.draw(FirstAtom);
    CirclesArray[50][50] = 1;
    win.display();

    win.draw(SecondAtom);
    CirclesArray[50][50] = 2;
    win.display();

    return;
}

void Model::setting() {}
void Model::ClearGrid(RenderWindow& win)
{
    win.clear();
    bGridDrawed = false;
}

void Model::DrawCircleColor(RenderWindow& win, int x, int y, int num)
{
    float xLocal = (DrawOffset) + ((x)*2 * CircleRadius);
    float yLocal = (DrawOffset) + ((y)*2 * CircleRadius);

    if (num == 1)
    {
        win.draw(FirstAtom);
        FirstAtom.setPosition(xLocal, yLocal);
    }
    if (num == 2)
    {
        win.draw(SecondAtom);
        SecondAtom.setPosition(xLocal, yLocal);
    }
    if (num == 3)
    {
        win.draw(Vacancy);
        Vacancy.setPosition(xLocal, yLocal);
    }

    win.display();
}

bool Math::RandBool()
{
    float r = (rand() % 100);
    if (r >= 50)
        return true;
    else
        return false;
}
