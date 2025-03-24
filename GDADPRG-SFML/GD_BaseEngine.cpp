#include "GD_BaseEngine.h"

void GD_BaseEngine::run(std::string title, unsigned int width, unsigned int height){
    window.create(sf::VideoMode({width, height}), title);
    window.setFramerateLimit(60);
    init();
    sf::Clock clock;
    sf::Time timestamp = sf::Time::Zero;
    while (window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                 window.close();
            else if(const auto* keyPressed=event->getIf<sf::Event::KeyPressed>())
                keyPressTrigger(keyPressed->scancode);
            else if(const auto* keyPressed=event->getIf<sf::Event::KeyReleased>())
                keyReleaseTrigger(keyPressed->scancode);
        }//end while
        timestamp += clock.restart();
        while(timestamp>TimePerFrame){
            timestamp -= TimePerFrame;
            update(TimePerFrame);
        }
        window.clear();
        draw(&window);
        window.display();
    }//end while
}//end func
