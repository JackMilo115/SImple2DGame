#include <SFML/Graphics.hpp>
#include <cmath>

class Player {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float maxSpeed;
    float friction;

    Player() {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        shape.setFillColor(sf::Color::White);
        shape.setPosition(375.0f, 275.0f); // Center of the window
        velocity = sf::Vector2f(0.0f, 0.0f);
        acceleration = sf::Vector2f(0.0f, 0.0f);
        maxSpeed = 5.0f;
        friction = 0.80f;
    }

    void handleInput() {
        acceleration = sf::Vector2f(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            acceleration.y -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            acceleration.y += 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            acceleration.x -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            acceleration.x += 1.0f;
    }

    void update() {
        velocity += acceleration;
        if (std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > maxSpeed) {
            float angle = std::atan2(velocity.y, velocity.x);
            velocity = sf::Vector2f(std::cos(angle) * maxSpeed, std::sin(angle) * maxSpeed);
        }
        velocity *= friction;
    }

    void move() {
        shape.move(velocity);
    }

    void resolveCollision(const sf::RectangleShape& obstacle) {
        if (checkCollision(obstacle)) {
            // Undo the last movement
            shape.move(-velocity);
            // Stop the player
            velocity = sf::Vector2f(0.0f, 0.0f);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    bool checkCollision(const sf::RectangleShape& other) {
        return shape.getGlobalBounds().intersects(other.getGlobalBounds());
    }
};