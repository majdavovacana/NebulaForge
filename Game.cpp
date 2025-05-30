#include "Game.hpp"
#include <cmath>

class Probe : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool active;

public:
    Probe(float x, float y) : position(x, y), velocity(0.f, 0.f), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        position += velocity * deltaTime;
        shape.setPosition(position);
    }

    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void applyForce(const sf::Vector2f& force) override { velocity += force; }
    void deactivate() { active = false; }
};

class Cloud : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float density;
    bool active;

public:
    Cloud(float x, float y, float d) : position(x, y), density(d), active(true) {
        shape.setRadius(20.f);
        shape.setFillColor(sf::Color(100, 100, 255, 150));
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    float getDensity() const override { return density; }
};

class Hazard : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Hazard(float x, float y) : position(x, y), active(true) {
        shape.setRadius(15.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
};

class Beacon : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Beacon(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0.f, 0.f), cloudDensity(1.f), rng(std::random_device{}()), isBeaconReached(false) {
    probe = std::make_unique<Probe>(200.f, 300.f);
    hazards.push_back(std::make_unique<Hazard>(400.f, 250.f));
    hazards.push_back(std::make_unique<Hazard>(350.f, 350.f));
    beacon = std::make_unique<Beacon>(600.f, 200.f);
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                probe = std::make_unique<Probe>(200.f, 300.f);
                clouds.clear();
                hazards.clear();
                hazards.push_back(std::make_unique<Hazard>(400.f, 250.f));
                hazards.push_back(std::make_unique<Hazard>(350.f, 350.f));
                beacon = std::make_unique<Beacon>(600.f, 200.f);
                cursorPos = {0.f, 0.f};
                cloudDensity = 1.f;
                isBeaconReached = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Space) {
                clouds.push_back(std::make_unique<Cloud>(cursorPos.x, cursorPos.y, cloudDensity));
            } else if (event.key.code == sf::Keyboard::Q) {
                cloudDensity = std::max(0.5f, cloudDensity - 0.1f);
            } else if (event.key.code == sf::Keyboard::E) {
                cloudDensity = std::min(2.f, cloudDensity + 0.1f);
            }
        }
    }
    // Cursor movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cursorPos.y = std::max(100.f, cursorPos.y - 200.f * 0.016f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cursorPos.y = std::min(500.f, cursorPos.y + 200.f * 0.016f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cursorPos.x = std::max(150.f, cursorPos.x - 200.f * 0.016f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cursorPos.x = std::min(650.f, cursorPos.x + 200.f * 0.016f);
}

void Game::update(float deltaTime) {
    probe->update(deltaTime);
    for (auto& cloud : clouds) {
        cloud->update(deltaTime);
    }
    for (auto& hazard : hazards) {
        hazard->update(deltaTime);
    }
    beacon->update(deltaTime);

    // Cloud effects on probe
    sf::Vector2f probePos = probe->getPosition();
    for (const auto& cloud : clouds) {
        if (cloud->isActive()) {
            sf::Vector2f cloudPos = cloud->getPosition();
            float dist = std::hypot(probePos.x - cloudPos.x, probePos.y - cloudPos.y);
            if (dist < 50.f) {
                sf::Vector2f direction = (probePos - cloudPos) / (dist + 1.f);
                float force = cloud->getDensity() * 50.f;
                dynamic_cast<Probe&>(*probe).applyForce(direction * force * deltaTime);
            }
        }
    }

    // Hazard collision
    for (const auto& hazard : hazards) {
        if (hazard->isActive() && std::hypot(probePos.x - hazard->getPosition().x, probePos.y - hazard->getPosition().y) < 25.f) {
            dynamic_cast<Probe&>(*probe).deactivate();
        }
    }

    // Beacon collision
    if (std::hypot(probePos.x - beacon->getPosition().x, probePos.y - beacon->getPosition().y) < 20.f) {
        isBeaconReached = true;
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw hazards
    for (const auto& hazard : hazards) {
        hazard->render(window);
    }

    // Draw clouds
    for (const auto& cloud : clouds) {
        cloud->render(window);
    }

    // Draw beacon
    beacon->render(window);

    // Draw probe
    probe->render(window);

    // Draw cursor
    sf::CircleShape cursor(10.f);
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(cursorPos - sf::Vector2f(10.f, 10.f));
    window.draw(cursor);

    // Draw density indicator
    sf::Text densityText;
    densityText.setString("Density: " + std::to_string(static_cast<int>(cloudDensity * 100)) + "%");
    densityText.setCharacterSize(20);
    densityText.setFillColor(sf::Color::White);
    densityText.setPosition(50.f, 50.f);
    window.draw(densityText);

    // Draw win/lose condition
    if (isBeaconReached) {
        sf::Text winText;
        winText.setString("Beacon Reached!");
        winText.setCharacterSize(24);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(300.f, 400.f);
        window.draw(winText);
    } else if (!probe->isActive()) {
        sf::Text loseText;
        loseText.setString("Probe Destroyed!");
        loseText.setCharacterSize(24);
        loseText.setFillColor(sf::Color::Red);
        loseText.setPosition(300.f, 400.f);
        window.draw(loseText);
    }

    window.display();
}
