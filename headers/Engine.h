#ifndef GAMES_ENGINE_H
#define GAMES_ENGINE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;

class Engine {
private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

public:
    Engine();

    void draw();

    void run();
};


#endif //GAMES_ENGINE_H
