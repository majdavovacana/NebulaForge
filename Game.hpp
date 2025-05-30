#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class Game {
private:
    sf::RenderWindow& window;
    std::unique_ptr<Entity> probe;
    std::vector<std::unique_ptr<Entity>> clouds;
    std::vector<std::unique_ptr<Entity>> hazards;
    std::unique_ptr<Entity> beacon;
    sf::Vector2f cursorPos;
    float cloudDensity;
    std::mt19937 rng;
    bool isBeaconReached;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
