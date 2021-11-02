
#include "Main.h"

class LineChart : VertexArray
{
public:
    LineChart(int pPoints, pair<int, int> pLocation, pair<int, int> pSize, Color pColor = Color::Red);

    void DrawSeries(vector<float>& pValsX, vector<float>& pValsY, RenderWindow& win, LineChart& instance);

    void DrawBackground(Color color, float Offset, RenderWindow& win);

private:
    int Points = 0;
    pair<int, int> Location;
    pair<int, int> Size;
    Color color = Color::Red;
};

int main()
{

    Model model;
    Math math;
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    int scale = 300;
    float windowXSize = model.CirclesXCount * model.CircleRadius * 2 + model.DrawOffset * 2;
    float windowYSize = model.CirclesYCount * model.CircleRadius * 2 + model.DrawOffset * 2;
    model.CalculateSize();
    LineChart Chart1(model.CirclesXCount, model.GraficLoc, model.GraficSize);
    LineChart Chart2(model.CirclesXCount, model.GraficLoc, model.GraficSize, model.clSecondAtom);

    RenderWindow window(VideoMode(windowXSize + 200, windowYSize + 400), "SFML Lab", Style::Default, settings);

    // window.setFramerateLimit(600);
    model.SetCircleColor();

    sf::Event event;
    Clock clock;
    float time = 0.0f;
    float DeltaTime = 0.0f;
    float LastTime = 0.0f;
    float FPSTimer = 0.0f;

    model.DrawCircleGrid(window);

    while (window.isOpen())
    {
        time = clock.getElapsedTime().asSeconds();
        DeltaTime = time - LastTime;
        LastTime = time;

        FPSTimer += DeltaTime;

        cout << "timer: " << time << endl;
        cout << "time: " << DeltaTime << endl;
        cout << "truefps: " << 1 / DeltaTime << endl;
        cout << "fps: " << 1 / FPSTimer << endl;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (FPSTimer >= 0.025f)
        {
           // window.clear();

            model.DrawCircles(window, time);
            model.CalculateAtoms();
            Chart1.DrawBackground(Color(20, 20, 20), 20, window);
            Chart1.DrawSeries(model.ValsX, model.ValsY1, window, Chart1);
            Chart2.DrawSeries(model.ValsX, model.ValsY2, window, Chart2);

            FPSTimer = 0.0f;
        }

        if (Keyboard::isKeyPressed(Keyboard::C))
        {

             model.ClearGrid(window);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        window.display();
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

void Model::CalculateAtoms()
{
    ValsX.clear();
    ValsY1.clear();
    ValsY2.clear();

    for (int x = 0; x < CirclesXCount; x++)
    {
        ValsX.push_back(x);
        int count1Atom = 0;
        int count2Atom = 0;

        for (int y = 0; y < CirclesYCount; y++)
        {
            if (CirclesArray[x][y] == 1) count1Atom++;
            if (CirclesArray[x][y] == 2) count2Atom++;
        };

        ValsY1.push_back(count1Atom);
        ValsY2.push_back(count2Atom);
    }
}

void Model::CalculateSize()
{
    GraficLoc.second = CirclesYCount * CircleRadius * 2 + DrawOffset * 2 + CirclesYCount * CircleRadius;
    GraficLoc.first = DrawOffset;

    GraficSize.first = CirclesXCount * CircleRadius * 2;
    GraficSize.second = CirclesYCount * CircleRadius;
}


LineChart::LineChart(int pPoints, pair<int, int> pLocation, pair<int, int> pSize, Color pColor)
{
    Points = pPoints;
    Location = pLocation;
    Size = pSize;
    color = pColor;

    VertexArray::setPrimitiveType(PrimitiveType::LinesStrip);
    VertexArray::resize(pPoints);
}

void LineChart::DrawSeries(vector<float>& pValsX, vector<float>& pValsY, RenderWindow& win, LineChart& instance)
{
    Vector2f vector;

    for (int x = 0; x < Points; x++)
    {
        float a = Size.first / Points * pValsX[x] + Location.first;
        float b = Location.second - (pValsY[x] * Size.second / Points);

        vector = Vector2f(a, b);
        instance[x].position = vector;
        instance[x].color = color;
        /*
                cout << "x: " << x << endl;
        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        cout << "Points: " << Points << endl;
        cout << "Size.first: " << Size.first << endl;
        cout << "Size.second: " << Size.second << endl;
        cout << "Location.first: " << Location.first << endl;
        cout << "Location.second: " << Location.second << endl;
        */
    };

    win.draw(instance);
}

void LineChart::DrawBackground(Color color, float Offset, RenderWindow& win)
{
    RectangleShape GraficField;
    float x = Location.first - Offset / 2;
    float y = Location.second - Size.second - Offset / 2;

    Vector2f vector = Vector2f(x, y);

    GraficField.setFillColor(color);
    GraficField.setPosition(vector);
    Vector2f GraficSize(Size.first + Offset / 2, Size.second + Offset);
    GraficField.setSize(GraficSize);

    win.draw(GraficField);
}
