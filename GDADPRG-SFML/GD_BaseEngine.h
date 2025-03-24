#pragma once

#include <SFML/Graphics.hpp>

class GD_BaseEngine{
    private:
        sf::RenderWindow window;
        const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
    public:
        virtual void init() = 0;
        virtual void update(sf::Time deltaTime) = 0;
        virtual void draw(sf::RenderWindow *window) = 0;
        virtual void keyPressTrigger(sf::Keyboard::Scan keyCode) = 0;
        virtual void keyReleaseTrigger(sf::Keyboard::Scan keyCode) = 0;
        void run(std::string title, unsigned int width, unsigned int height);
};
