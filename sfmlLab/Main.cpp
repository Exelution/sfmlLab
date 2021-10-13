
#include "Main.h"

int main()
{
    Model model;
    Math math;
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    int scale = 300;
    float windowXSize = model.CirclesXCount * model.CircleRadius * 2 + model.DrawOffset * 2;
    float windowYSize = model.CirclesYCount * model.CircleRadius * 2 + model.DrawOffset * 2;
   

    RenderWindow window(VideoMode(windowXSize + 200, windowYSize + 400), "SFML Lab", Style::Default, settings);

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
            model.DrawGrafic(window,time);


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
    timer += time;
    if (timer < time1) return;
    timer = 0;
    for (int i = 0; i < CirclesYCount; i++)
    {
        int x = VacancyArray[i].first;
        int y = VacancyArray[i].second;

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
        if (!CirclesArray[x + right][y + up]) return;
        if (x + right < 0 || x + right >= CirclesXCount - 1) return;
        if (y + up < 0 || y + up >= CirclesYCount - 1) return;

        if (CirclesArray[x + right][y + up] == 3)
            return;
        else
        {
            CirclesArray[x][y] = CirclesArray[x + right][y + up];
            DrawCircleColor(win, x, y, CirclesArray[x + right][y + up]);
            CirclesArray[x + right][y + up] = 3;
            DrawCircleColor(win, x + right, y + up, 3);
            VacancyArray[i].first = x + right;
            VacancyArray[i].second = y + up;
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
                FirstAtom.setPosition(localX * i + DrawOffset, localY * j + DrawOffset);
                win.draw(FirstAtom);
                win.display();
                CirclesArray[i][j] = 1;
            }
            if (i > CirclesXCount / 2)
            {
                SecondAtom.setPosition(localX * i + DrawOffset, localY * j + DrawOffset);
                win.draw(SecondAtom);
                win.display();
                CirclesArray[i][j] = 2;
            }
            if (i == CirclesXCount / 2)
            {
                Vacancy.setPosition(localX * i + DrawOffset, localY * j + DrawOffset);
                win.draw(Vacancy);
                win.display();
                CirclesArray[i][j] = 3;
                VacancyArray[j].first = i;
                VacancyArray[j].second = j;
            }
        }
    bGridDrawed = true;

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

void Model::SetVars() {}

void Model::DrawGrafic(RenderWindow& win, float time)
{

    timerG += time;
    if (timerG < time2) return;
    timerG = 0; 
    Math math;
    VertexArray graficVertex(LineStrip, 40);
    VertexArray graficVertexB(LineStrip, 40);

    int yPoint = CirclesYCount * CircleRadius * 2 + DrawOffset * 2 + CirclesYCount * CircleRadius;
    int xPoint = DrawOffset;

    int width = CirclesXCount * CircleRadius * 2;
    int heigth = CirclesYCount * CircleRadius;

    GraficField.setFillColor(Color::Black);
    GraficField.setPosition(xPoint - 5, yPoint - CirclesYCount * CircleRadius - 5);
    Vector2f GraficSize(width + 5, 30 + heigth);
    GraficField.setSize(GraficSize);
    win.draw(GraficField);
    win.display();

    int GraficStepSize = CircleRadius * 2;

    for (int x = 0; x < CirclesXCount; x++)
    {
        int count1Atom = 0;
        int count2Atom = 0;

        for (int y = 0; y < CirclesYCount; y++)
        {
            if (CirclesArray[x][y] == 1) count1Atom++;
            if (CirclesArray[x][y] == 2) count2Atom++;
        };

        Vector2f vector;
        Vector2f vectorB;

        int vx = x * GraficStepSize + xPoint;
        int vy = yPoint - (count1Atom * heigth / CirclesYCount);

        int vxB = x * GraficStepSize + xPoint;
        int vyB = yPoint - (count2Atom * heigth / CirclesYCount);

        vector = Vector2f(vx, vy);
        vectorB = Vector2f(vxB, vyB);
        graficVertex[x].position = vector;
        graficVertexB[x].position = vectorB;

        graficVertex[x].color = clFirstAtom;
        graficVertexB[x].color = clSecondAtom;

    };

    win.draw(graficVertex);
    win.draw(graficVertexB);
    win.display();
}
