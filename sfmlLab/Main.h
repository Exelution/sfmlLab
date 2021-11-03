#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "SFML/Graphics.hpp"
#include "iostream"

using namespace std;

class LineChart : sf::VertexArray
{
public:
    LineChart(int pPoints, sf::Vector2f location, sf::Vector2f size, sf::Color pColor = sf::Color::Red);
    void DrawSeries(vector<float>& pValsX, vector<float>& pValsY, sf::RenderWindow& win, LineChart& instance);
    void DrawBackground(sf::Color color, float Offset, sf::RenderWindow& win);

private:
    int Points = 0;
    sf::Vector2f Location;
    sf::Vector2f Size;
    sf::Color color = sf::Color::Red;
};

class AtomGrid
{
public:
    AtomGrid();
    void DisplayGrid(sf::RenderWindow& window);
    void MoveVacancy(sf::Time DeltaTime);
    int GetAtomOnSide() { return AtomOnSide; };

    int SideSize = 500;
    sf::Vector2f Location = sf::Vector2f(20.f, 20.f);

    vector<float> ValsX;
    vector<float> ValsY1;
    vector<float> ValsY2;

    sf::Color clFirstAtom = sf::Color::Red;
    sf::Color clSecondAtom = sf::Color::Green;
    int AtomRadius = 0;

private:
    void CalculateAtom();

private:
    int AtomOnSide = 25;
    int VacancyAmount = 40;

    vector<vector<sf::CircleShape>> GridVector;
    vector<sf::Vector2i> VacancyCoords;

    sf::Color clVacancy = sf::Color::White;
    sf::Time ChartTimer = sf::seconds(0);
};

class Game
{
public:
    Game();
    bool run();

private:
    void BeginPlay();
    void processEvents();
    void update(sf::Time deltaTime);
    void render(sf::Time deltaTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    bool Restart();

private:
    AtomGrid atomGrid;
    LineChart Atom1Chart;
    LineChart Atom2Chart;

    sf::ContextSettings settings;
    sf::RenderWindow mWindow;
    sf::CircleShape shape;

    int TargetFPS = 45;
    sf::Time TimePerFrame = sf::seconds(1.f / TargetFPS);
};