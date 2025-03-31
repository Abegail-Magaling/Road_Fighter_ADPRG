#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define SCROLL_SPEED 2.f
#define PLAYER_SPEED 200.f
#define PLAYER_DECELERATION 300.f
#define PLAYER_SKID_SPEED 100.f
#define ROAD_LEFT 50.f
#define ROAD_RIGHT 450.f

class GameObject {
protected:
    std::string name;
public:
    GameObject(std::string objName) : name(objName) {}
    std::string getName() { return name; }
    virtual void init() = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
};

class Background : public GameObject {
    private:
        sf::Texture texture;
        sf::Sprite* sprite1;
        sf::Sprite* sprite2;
        float speed;
        const float acceleration = 80.f;
        const float maxSpeed = 1000.f;
        const float friction = 5.f;
    
    public:
        Background() : GameObject("Grass"), sprite1(nullptr), sprite2(nullptr), speed(0.f) {
            if (texture.loadFromFile("/Users/naomi/Documents/SFML_setup/images/road.png")) {
                sprite1 = new sf::Sprite(texture);
                sprite2 = new sf::Sprite(texture);
                sprite2->setPosition(sf::Vector2f(0.f, -500.f));
            } else {
                std::cerr << "Failed to load background texture!" << std::endl;
            }
        }
    
        ~Background() {
            delete sprite1;
            delete sprite2;
        }
    
        void init() {}
    
        void update(sf::Time deltaTime) {
            if (!sprite1 || !sprite2) return; 
    
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
                speed += acceleration;
                if (speed > maxSpeed) speed = maxSpeed;
            } else {
                speed -= friction;
                if (speed < 0) speed = 0;
            }
    
            sprite1->move(sf::Vector2f(0.0f, speed * deltaTime.asSeconds()));
            sprite2->move(sf::Vector2f(0.0f, speed * deltaTime.asSeconds()));
    
            if (sprite1->getPosition().y >= 500) {
                sprite1->setPosition(sf::Vector2f(0.f, 0.f));
                sprite2->setPosition(sf::Vector2f(0.f, -500.f));
            }
            if (sprite2->getPosition().y >= 500) {
                sprite2->setPosition(sf::Vector2f(0.f, 0.f));
                sprite1->setPosition(sf::Vector2f(0.f, -500.f));
            }
        }
    
        void draw(sf::RenderWindow* window) {
            if (sprite1) window->draw(*sprite1);
            if (sprite2) window->draw(*sprite2);
        }
    };
    

class Player : public GameObject {
    private:
        sf::Texture texture;
        sf::Sprite* sprite;
        float speed;
        float skidSpeed;
        bool skidding;
    
    public:
    Player() : GameObject("Player"), sprite(nullptr), speed(0.f), skidSpeed(0.f), skidding(false) {
        if (!texture.loadFromFile("/Users/naomi/Documents/SFML_setup/images/crab.png")) {
            std::cerr << "Failed to load crab.png" << std::endl;
        } else {
            sprite = new sf::Sprite(texture);
    
            sprite->setScale(sf::Vector2f(0.1f, 0.1f));
            sprite->setScale(sf::Vector2f(0.1f, 0.1f)); 

            sf::Vector2f size = static_cast<sf::Vector2f>(texture.getSize());

            // Adjust for the scaling
            size.x *= sprite->getScale().x;
            size.y *= sprite->getScale().y;

            sprite->setPosition(sf::Vector2f((500.f - size.x) / 2, 500.f - size.y - 20.f));

        }
    }
    
    
        ~Player() {
            delete sprite;
        }
    
        void init() {}
    
        void update(sf::Time deltaTime) {
            if (!sprite) return; 
        
            float moveAmount = 0.f;
        
            if (!skidding) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
                    moveAmount = -PLAYER_SPEED * deltaTime.asSeconds();
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
                    moveAmount = PLAYER_SPEED * deltaTime.asSeconds();
                }
            } else {
                moveAmount = skidSpeed * deltaTime.asSeconds();
                skidSpeed -= PLAYER_DECELERATION * deltaTime.asSeconds();
                if (std::abs(skidSpeed) < 10.f) {
                    skidding = false;
                    skidSpeed = 0.f; 
                }
            }
        
            sprite->move(sf::Vector2f(moveAmount, 0.f));
        
            // Check collisions
            if (sprite->getPosition().x < ROAD_LEFT) {
                sprite->setPosition(sf::Vector2f(ROAD_LEFT, sprite->getPosition().y));
                if (skidSpeed < 0) skidSpeed = 0;
                crash(PLAYER_SKID_SPEED); 
            } else if (sprite->getPosition().x > ROAD_RIGHT) {
                sprite->setPosition(sf::Vector2f(ROAD_RIGHT, sprite->getPosition().y));
                if (skidSpeed > 0) skidSpeed = 0;
                crash(-PLAYER_SKID_SPEED);
            }
        }
        
    
        void draw(sf::RenderWindow* window) {
            if (sprite) window->draw(*sprite);
        }
    
        void crash(float skid) {
            skidding = true;
            skidSpeed = skid;
        }
    };    

int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Game Object");
    window.setFramerateLimit(60);

    Background bg;
    Player player;
    
    sf::Clock clock;
    sf::Time timestamp = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        timestamp += clock.restart();
        while (timestamp > TimePerFrame) {
            timestamp -= TimePerFrame;
            bg.update(TimePerFrame);
            player.update(TimePerFrame);
        }

        window.clear();
        bg.draw(&window);
        player.draw(&window);
        window.display();
    }
    return 0;
}


