

#include "Main.h"

void gameRunning(Game& GameInstance)
{
    if (GameInstance.run())
    {
        gameRunning(GameInstance);
    }
}

int main()
{
    Game game;
    gameRunning(game);
    return 0;
}

Game::Game()
    : mWindow(sf::VideoMode(540, 840), "SFML Application"),                                                                    //
                                                                                                                               //
      Atom1Chart(atomGrid.GetAtomOnSide(),                                                                                     //
          sf::Vector2f(atomGrid.Location.x + atomGrid.SideSize / atomGrid.GetAtomOnSide() / 2,                                 //
              atomGrid.Location.y + atomGrid.SideSize * 3 / 2 + 20.f),                                                         //
          sf::Vector2f(atomGrid.SideSize * (atomGrid.GetAtomOnSide() - 1) / atomGrid.GetAtomOnSide(), atomGrid.SideSize / 2),  //
          atomGrid.clFirstAtom),                                                                                               //
                                                                                                                               //
      Atom2Chart(atomGrid.GetAtomOnSide(),                                                                                     //
          sf::Vector2f(atomGrid.Location.x + atomGrid.SideSize / atomGrid.GetAtomOnSide() / 2,                                 //
              atomGrid.Location.y + atomGrid.SideSize * 3 / 2 + 20.f),                                                         //
          sf::Vector2f(atomGrid.SideSize * (atomGrid.GetAtomOnSide() - 1) / atomGrid.GetAtomOnSide(), atomGrid.SideSize / 2),  //
          atomGrid.clSecondAtom)                                                                                               //
{
}

bool Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    BeginPlay();

    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render(TimePerFrame);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            return true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            return false;
        }
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed: handlePlayerInput(event.key.code, true); break;
            case sf::Event::KeyReleased: handlePlayerInput(event.key.code, false); break;
            case sf::Event::Closed: mWindow.close(); break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    // if (key == sf::Keyboard::Escape) mWindow.close();
}

bool Game::Restart()
{
    return false;
}

void Game::BeginPlay() {}

void Game::update(sf::Time deltaTime)
{
    atomGrid.MoveVacancy(deltaTime);
}

void Game::render(sf::Time deltaTime)
{

    mWindow.clear();
    atomGrid.DisplayGrid(mWindow);

    Atom1Chart.DrawSeries(atomGrid.ValsX, atomGrid.ValsY1, mWindow, Atom1Chart);
    Atom2Chart.DrawSeries(atomGrid.ValsX, atomGrid.ValsY2, mWindow, Atom2Chart);

    mWindow.display();
}

AtomGrid::AtomGrid()
{
    GridVector.resize(AtomOnSide);
    int VacancyCounter = 0;
    AtomRadius = SideSize / AtomOnSide / 2;
    for (int x = 0; x < AtomOnSide; x++)
    {
        GridVector[x].resize(AtomOnSide);
        for (int y = 0; y < AtomOnSide; y++)
        {
            GridVector[x][y].setRadius(AtomRadius);
            GridVector[x][y].setPosition(Location.x + x * AtomRadius * 2, Location.y + y * AtomRadius * 2);

            if (x < AtomOnSide / 2)
            {
                GridVector[x][y].setFillColor(clFirstAtom);
            }
            if (x >= AtomOnSide / 2)
            {
                GridVector[x][y].setFillColor(clSecondAtom);
            }

            float r = (rand() % 100);
            if (r <= 100 * VacancyAmount / (AtomOnSide * AtomOnSide))
            {
                if (VacancyCounter < VacancyAmount)
                {
                    GridVector[x][y].setFillColor(clVacancy);
                    VacancyCounter++;
                    VacancyCoords.push_back(sf::Vector2i(x, y));
                }
            }
        }
    }
    CalculateAtom();
}

void AtomGrid::DisplayGrid(sf::RenderWindow& window)
{
    for (int x = 0; x < AtomOnSide; x++)
    {
        for (int y = 0; y < AtomOnSide; y++)
        {
            window.draw(GridVector[x][y]);
        }
    }
}

void AtomGrid::MoveVacancy(sf::Time DeltaTime)
{
    ChartTimer += DeltaTime;

    for (int i = 0; i < VacancyAmount; i++)
    {
        int xDirection = 0;
        int yDirection;

        float r = (rand() % 100);
        if (r >= 50)
        {
            xDirection = 1;
        }
        else
        {
            xDirection = -1;
        }

        r = (rand() % 100);
        if (r >= 50)
        {
            yDirection = 1;
        }
        else
        {
            yDirection = -1;
        }

        if (VacancyCoords[i].x + xDirection >= AtomOnSide) xDirection *= -1;
        if (VacancyCoords[i].x + xDirection < 0) xDirection *= -1;

        if (VacancyCoords[i].y + yDirection >= AtomOnSide) yDirection *= -1;
        if (VacancyCoords[i].y + yDirection < 0) yDirection *= -1;

        sf::Color clLastAtom = GridVector[VacancyCoords[i].x + xDirection][VacancyCoords[i].y + yDirection].getFillColor();

        if (clLastAtom == clVacancy)
        {
            yDirection = 0;
            xDirection = 0;
            clLastAtom = GridVector[VacancyCoords[i].x + xDirection][VacancyCoords[i].y + yDirection].getFillColor();
        }

        GridVector[VacancyCoords[i].x][VacancyCoords[i].y].setFillColor(clLastAtom);

        GridVector[VacancyCoords[i].x + xDirection][VacancyCoords[i].y + yDirection].setFillColor(clVacancy);

        VacancyCoords[i] = sf::Vector2i(VacancyCoords[i].x + xDirection, VacancyCoords[i].y + yDirection);
    }
    if (ChartTimer.asSeconds() > 0.5f)
    {
        ChartTimer = sf::seconds(0);
        CalculateAtom();
    }
}

void AtomGrid::CalculateAtom()
{
    ValsX.clear();
    ValsY1.clear();
    ValsY2.clear();

    for (int x = 0; x < AtomOnSide; x++)
    {
        ValsX.push_back(x);
        int count1Atom = 0;
        int count2Atom = 0;

        for (int y = 0; y < AtomOnSide; y++)
        {
            if (GridVector[x][y].getFillColor() == clFirstAtom) count1Atom++;
            if (GridVector[x][y].getFillColor() == clSecondAtom) count2Atom++;
        };

        ValsY1.push_back(count1Atom);
        ValsY2.push_back(count2Atom);
    }
}

LineChart::LineChart(int pPoints, sf::Vector2f location, sf::Vector2f size, sf::Color pColor)
{
    Points = pPoints;
    Location = location;
    Size = size;
    color = pColor;

    VertexArray::setPrimitiveType(sf::PrimitiveType::LinesStrip);
    VertexArray::resize(pPoints);
}

void LineChart::DrawSeries(vector<float>& pValsX, vector<float>& pValsY, sf::RenderWindow& win, LineChart& instance)
{
    sf::Vector2f vector;

    for (int x = 0; x < Points; x++)
    {
        float a = Size.x / (Points - 1) * pValsX[x] + Location.x;
        float b = Location.y - (pValsY[x] / Points * Size.y);
        vector = sf::Vector2f(a, b);

        instance[x].position = vector;
        instance[x].color = color;
        sf::CircleShape shape;

        shape.setRadius(3.f);
        shape.setPosition(vector.x - 1.5f, vector.y - 1.5f);
        shape.setFillColor(color);
        win.draw(shape);
    };

    win.draw(*this);
}

void LineChart::DrawBackground(sf::Color color, float Offset, sf::RenderWindow& win)
{
    sf::RectangleShape GraficField;
    float x = Location.x - Offset / 2;
    float y = Location.y - Size.y - Offset / 2;

    sf::Vector2f vector = sf::Vector2f(x, y);

    GraficField.setFillColor(color);
    GraficField.setPosition(vector);
    sf::Vector2f GraficSize(Size.x + Offset / 2, Size.y + Offset);
    GraficField.setSize(GraficSize);

    win.draw(GraficField);
}