
/*ENEMY FACTORY BUT ENEMY NOT SPAWNING*/
// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>

// #define SCROLL_SPEED 2.f

// class GameObject{
// 	private:
// 		std::string name;
// 	public:
// 	    GameObject(std::string objName){ name = objName; }
// 	    std::string getName(){ return name; }
// 		virtual void init() = 0;
//         virtual void update(sf::Time deltaTime) = 0;
//         virtual void draw(sf::RenderWindow *window) = 0;
// };

// class Background : public GameObject {
//     private:
//         sf::Texture texture;
//         sf::Sprite* sprite1;
//         sf::Sprite* sprite2;
//         float speed;
//         const float acceleration = 80.f;
//         const float maxSpeed = 1000.f;
//         const float friction = 5.f;
    
//     public:
//         Background() : GameObject("Grass"), speed(0.f) {
//             if (texture.loadFromFile("/Users/naomi/Documents/SFML_setup/images/road.png")) {
//                 sprite1 = new sf::Sprite(texture);
//                 sprite2 = new sf::Sprite(texture);
//                 sprite2->setPosition(sf::Vector2f(0.f, -500.f));
//             }
//         }
    
//         ~Background() {
//             delete sprite1;
//             delete sprite2;
//         }

//         void init() {
//             sprite1->setPosition(sf::Vector2f(0.f, 0.f));
//             sprite2->setPosition(sf::Vector2f(0.f, -500.f));
//         }
    
//         void update(sf::Time deltaTime) {
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
//                 speed += acceleration;
//                 if (speed > maxSpeed) speed = maxSpeed;
//             } else {
//                 speed -= friction;
//                 if (speed < 0) speed = 0;
//             }
    
//             sprite1->move(sf::Vector2f (0.0f, speed * deltaTime.asSeconds()));
//             sprite2->move(sf::Vector2f(0.0f, speed * deltaTime.asSeconds()));
    
//             if (sprite1->getPosition().y >= 500) {
//                 sprite1->setPosition(sf::Vector2f(0.f, 0.f));
//                 sprite2->setPosition(sf::Vector2f(0.f, -500.f));
//             }
//             if (sprite2->getPosition().y >= 500) {
//                 sprite2->setPosition(sf::Vector2f(0.f, 0.f));
//                 sprite1->setPosition(sf::Vector2f(0.f, -500.f));
//             }
//         }
    
//         void draw(sf::RenderWindow* window) {
//             window->draw(*sprite1);
//             window->draw(*sprite2);
//         }
// };

// class Enemy : public GameObject {
//     private:
//         sf::Texture texture;
//         sf::Sprite sprite;
//         float speed;
    
//     public:
//         Enemy(float x, float y) : GameObject("Enemy"), texture(), sprite(texture), speed(100.f) {
//             sprite.setPosition(sf::Vector2f(x, y));
//         }
    
    
    
//         void init() override {}
    
//         void update(sf::Time deltaTime) override {
//             sprite.move(sf::Vector2f(0.f, speed * deltaTime.asSeconds()));
//         }
    
//         void draw(sf::RenderWindow* window) override {
//             window->draw(sprite);
//         }
    
//         bool isOffScreen() {
//             return sprite.getPosition().y > 500;
//         }
// };

// class EnemyFactory {
//     private:
//         std::vector<Enemy*> enemies;
//         sf::Clock spawnClock;
//         sf::Time spawnInterval;
    
//     public:
//         EnemyFactory() : spawnInterval(sf::seconds(2.f)) {
//             std::srand(static_cast<unsigned>(std::time(nullptr)));
//         }
    
//         ~EnemyFactory() {
//             for (auto enemy : enemies) {
//                 delete enemy;
//             }
//         }
    
//         void update(sf::Time deltaTime) {
//             if (spawnClock.getElapsedTime() > spawnInterval) {
//                 float x = static_cast<float>(std::rand() % 400 + 50);
//                 enemies.push_back(new Enemy(x, -50.f));
//                 std::cout << "Enemy spawned at x: " << x << ", y: -50" << std::endl;
//                 spawnClock.restart();
//             }
    
//             for (auto it = enemies.begin(); it != enemies.end();) {
//                 (*it)->update(deltaTime);
//                 if ((*it)->isOffScreen()) {
//                     delete *it;
//                     it = enemies.erase(it);
//                 } else {
//                     ++it;
//                 }
//             }
//         }
    
//         void draw(sf::RenderWindow* window) {
//             for (auto& enemy : enemies) {
//                 enemy->draw(window);
//             }
//         }
// };

// int main() {
//     sf::RenderWindow window(sf::VideoMode({500, 500}), "Game Object");
//     window.setFramerateLimit(60);
    
//     Background bg;
//     EnemyFactory enemyFactory;
    
//     sf::Clock clock;
//     sf::Time timestamp = sf::Time::Zero;
//     const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
    
//     bg.init();
    
//     while (window.isOpen()){
//         while(const std::optional event = window.pollEvent()){
//             if(event->is<sf::Event::Closed>())
//                 window.close();
//         }
        
//         timestamp += clock.restart();
//         while(timestamp > TimePerFrame){
//             timestamp -= TimePerFrame;
//             bg.update(TimePerFrame);
//             enemyFactory.update(TimePerFrame);
//         }
        
//         window.clear();
//         bg.draw(&window);
//         enemyFactory.draw(&window);
//         window.display();
//     }
//     return 0;
// }
