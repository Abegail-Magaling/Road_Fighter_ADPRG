#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define SCROLL_SPEED 2.f

class GameObject{
	private:
		std::string name;
	public:
	    GameObject(std::string objName){ name = objName; }
	    std::string getName(){ return name; }
		virtual void init() = 0;
        virtual void update(sf::Time deltaTime) = 0;
        virtual void draw(sf::RenderWindow *window) = 0;
};
class Background : public GameObject {
    private:
        sf::Texture texture;
        sf::Sprite* sprite1;
        sf::Sprite* sprite2;
        float speed;
        const float acceleration = 100.f;
        const float maxSpeed = 1000.f;
        const float friction = 5.f; // Deceleration when W is released
    
    public:
        Background() : GameObject("Grass"), speed(0.f) {
            if (texture.loadFromFile("/Users/naomi/Documents/SFML_setup/images/road.png")) {
                sprite1 = new sf::Sprite(texture);
                sprite2 = new sf::Sprite(texture);
                sprite2->setPosition(sf::Vector2f(0.f, -500.f)); // Set sprite2 above sprite1
            }
        }
    
        ~Background() {
            delete sprite1;
            delete sprite2;
        }

        void init() {
            sprite1->setPosition(sf::Vector2f(0.f, 0.f));
            sprite2->setPosition(sf::Vector2f(0.f, -500.f)); // Position sprite2 above sprite1
        }
    
        void update(sf::Time deltaTime) {
            // Handle user input for movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
                speed += acceleration;
                if (speed > maxSpeed) speed = maxSpeed; // Limit max speed
            } else {
                speed -= friction;
                if (speed < 0) speed = 0; // Stop at 0 speed
            }
    
            // Move background downwards based on speed
            sprite1->move(sf::Vector2f (0.0f, speed * deltaTime.asSeconds()));
            sprite2->move(sf::Vector2f(0.0f, speed * deltaTime.asSeconds()));
    
            // Reset positions when a sprite moves out of view
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
            window->draw(*sprite1);
            window->draw(*sprite2);
        }
    };
    
    

int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Game Object");
    window.setFramerateLimit(60);
    
    Background bg;
    
    sf::Clock clock;
    sf::Time timestamp = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
    
    bg.init();
    
    while (window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
        }//end while
        
        timestamp += clock.restart();
        while(timestamp > TimePerFrame){
            timestamp -= TimePerFrame;
            bg.update(TimePerFrame);
        }//end while
        
        window.clear();
        bg.draw(&window);
        window.display();
    }//end while
    return 0;
}
