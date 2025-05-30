#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual ~Entity() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual bool isActive() const = 0;
    virtual float getDensity() const { return 0.f; } // For clouds
    virtual void applyForce(const sf::Vector2f& force) {} // For probe
};

#endif // ENTITY_HPP
