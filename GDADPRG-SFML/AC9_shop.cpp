#include "GD_BaseEngine.h"
#include "GD_GameResource.h"
#include "GD_GameObject.h"
#include "ACO_Background.h"
#include "GD_TextObject.h"

#include "GD_ModularObject.h"
#include "GD_Trn.h"

#include "ACO_BulletObject.h"
#include "ACO_ChargeComp.h"
#include "ACO_ColliderComp.h"

#include "ACO_BulletPool.h"
#include "ACO_GameCharFactory.h"

#include "GD_SceneManager.h"
#include "GD_Scene.h"
#include "GD_ScenedGameEngine.h"
#include "ACO_GameData.h"

#include "ACO_Button.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define TILE_SIZE 50.0f

#define GAME_GRID_SIZE 10
#define MENU_HEIGHT 2

class MenuScene: public GD_Scene{
    private:
        int selected;

    public:
        std::vector<ACO_Button*> buttons;

    public:
        MenuScene(): GD_Scene("MenuScene"){
        }
        void onLoad(){
            addObject(new ACO_Background("bg3","tile",
                TILE_SIZE,GAME_GRID_SIZE+MENU_HEIGHT,GAME_GRID_SIZE,0,0));
            addObject(new GD_TextObject("menu-title",
                "ANIMAL CITY",
                TILE_SIZE,5+2*TILE_SIZE) );
            addObject(new GD_TextObject("menu-text1",
                "This is the pause menu.",
                TILE_SIZE,5+4*TILE_SIZE) );
            addObject(new GD_TextObject("menu-text2",
                "Press p to go back to",
                TILE_SIZE,5+5*TILE_SIZE) );
            addObject(new GD_TextObject("menu-text3",
                "the game!",
                TILE_SIZE,5+6*TILE_SIZE) );
            
            

            ACO_Button* btn1 = new ACO_Button("btn1","Start");
            btn1->setPosition(TILE_SIZE,5+TILE_SIZE*(GAME_GRID_SIZE-2));
            btn1->setSize(TILE_SIZE*3,TILE_SIZE);
            btn1->toggleSelected();
            
            ACO_Button* btn2 = new ACO_Button("btn2","Buy(5)");
            btn2->setPosition(TILE_SIZE*5,5+TILE_SIZE*(GAME_GRID_SIZE-2));
            btn2->setSize(TILE_SIZE*4,TILE_SIZE);
            
            addObject(btn1);
            addObject(btn2);
            buttons.push_back(btn1);
            buttons.push_back(btn2);
            selected = 0;
            
            ACO_GameData* gameData = ACO_GameData::createInstance();
            addObject(new GD_TextObject("menu-text4",
                "SCORE: "+std::to_string(gameData->getScore()),
                TILE_SIZE,5+TILE_SIZE*GAME_GRID_SIZE) );
                
            int health = 6;
            if(gameData->getObjSnapshot().size()>0){
                for(GD_GameObject* obj: gameData->getObjSnapshot()){
                    if(obj->getName()=="player"){
                        GD_ModularObject* player = (GD_ModularObject*)obj;
                        ACO_CharHealthComp* healthComp = (ACO_CharHealthComp*)player->getComponent("ACO_CharHealthComp");
                        health = healthComp->getHP();
                    }//end if
                }//end for
            }
            addObject(new GD_TextObject("menu-text5",
                    "HP: "+std::to_string(health),TILE_SIZE*6,5+TILE_SIZE*GAME_GRID_SIZE) );
        }
        void onUnload(){
            for(GD_GameObject* obj: getAllObjects())
                delete obj;
            removeAllObjects();
        }
        
        void keyPressTrigger(sf::Keyboard::Scan keyCode){
            if(     keyCode==sf::Keyboard::Scan::A || 
                    keyCode==sf::Keyboard::Scan::S || 
                    keyCode==sf::Keyboard::Scan::D || 
                    keyCode==sf::Keyboard::Scan::W){
                selected++;
                ACO_Button* btn1 = (ACO_Button*)findObject("btn1");
                ACO_Button* btn2 = (ACO_Button*)findObject("btn2");

                if (selected % 2 == 0) {
                    btn1->toggleSelected();
                    btn2->toggleSelected();
                }
                else {
                    btn2->toggleSelected();
                    btn1->toggleSelected();
                }

            }else if(keyCode==sf::Keyboard::Scan::P){
                GD_SceneManager* sman = GD_SceneManager::createInstance();
                sman->loadScene("GameScene");
            }else if(keyCode==sf::Keyboard::Scan::Space){
                if(selected%2==0){
                    GD_SceneManager* sman = GD_SceneManager::createInstance();
                    sman->loadScene("GameScene");
                }
                else {

                    std::cout << "IM HERE" << std::endl;
                    ACO_GameData* playerData = ACO_GameData::createInstance();
                    int playerScore = playerData->getScore();

                    if (playerScore >= 5) {
                        GD_ModularObject* player = nullptr;
                        for (GD_GameObject* obj : playerData->getObjSnapshot()) {
                            if (obj->getName() == "player") {
                                player = (GD_ModularObject*)obj;
                                break;
                            }
                        }

                        if (player != nullptr) {
                            ACO_CharHealthComp* playerHealth = (ACO_CharHealthComp*)player->getComponent("ACO_CharHealthComp");

                            
                            if (playerHealth != nullptr) {
                                playerData->addScore(-5);
                                playerHealth->decreaseHP(-1);

                                GD_TextObject* scoreText = (GD_TextObject*)findObject("menu-text4");
                                if (scoreText != nullptr)
                                    scoreText->setText("SCORE: " + std::to_string(playerData->getScore()));

                               GD_TextObject* healthText = (GD_TextObject*)findObject("menu-text5");
                                if (healthText != nullptr)
                                  healthText->setText("HP: " + std::to_string(playerHealth->getHP()));
                            }
                        }
                    }
                }
            }
        }
        void keyReleaseTrigger(sf::Keyboard::Scan keyCode){}
};

class GameScene: public GD_Scene{
    private:
        ACO_BulletPool* bulletPool;
        int loadTimeout;
    public:
        GameScene(ACO_BulletPool* pool): GD_Scene("GameScene"){
            bulletPool = pool;
        }
        void onLoad(){
            loadTimeout = 60;
            ACO_GameData* gameData = ACO_GameData::createInstance();
            std::vector<GD_GameObject*> snapshot = gameData->getObjSnapshot();
            if(snapshot.empty()){
                addObject(new ACO_Background("bg1","grass",
                    TILE_SIZE,GAME_GRID_SIZE,GAME_GRID_SIZE,0,0));
                addObject(new ACO_Background("bg2","tile",
                    TILE_SIZE,MENU_HEIGHT,GAME_GRID_SIZE,0,500));
                addObject(new GD_TextObject("score",
                    "SCORE: 0",TILE_SIZE,5+TILE_SIZE*GAME_GRID_SIZE) );
                addObject(new GD_TextObject("hp",
                    "HP: 6",TILE_SIZE*6,5+TILE_SIZE*GAME_GRID_SIZE) );
                    
                GD_ModularObject* player = ACO_GameCharFactory::makePlayer(TILE_SIZE,1,1);
                
                addObject(ACO_GameCharFactory::makeSide(1,TILE_SIZE,player) );
                addObject(ACO_GameCharFactory::makeSide(2,TILE_SIZE,player) );
                addObject(player);
                
                addObject(ACO_GameCharFactory::makeBonus(1,TILE_SIZE,GAME_GRID_SIZE) );
                addObject(ACO_GameCharFactory::makeBonus(2,TILE_SIZE,GAME_GRID_SIZE) );
                
                addObject(ACO_GameCharFactory::makeEnemy(1,TILE_SIZE,player,9,9) );
                addObject(ACO_GameCharFactory::makeEnemy(2,TILE_SIZE,player,1,9) );
                addObject(ACO_GameCharFactory::makeEnemy(3,TILE_SIZE,player,9,1) );
                
                for(GD_GameObject* obj: getAllObjects())
                    obj->init();
            }else{
                GD_TextObject* txt2 = nullptr;
                GD_ModularObject* player = nullptr;
                for(GD_GameObject* obj: snapshot){
                    addObject(obj);
                    if(obj->getName()=="score"){
                        GD_TextObject* txt = (GD_TextObject*)obj;
                        txt->setText("SCORE: "+std::to_string(gameData->getScore()));
                    }else if(obj->getName()=="hp"){
                        txt2 = (GD_TextObject*)obj;
                    }else if(obj->getName()=="player"){
                        player = (GD_ModularObject*)obj;
                    }
                }
                if(txt2!=nullptr && player!=nullptr){

                    ACO_CharHealthComp* playerHealth = (ACO_CharHealthComp*)player->getComponent("ACO_CharHealthComp");
                    if (playerHealth != nullptr) {
                        txt2->setText("HP: " + std::to_string(playerHealth->getHP()));
                    }
                    //Update the health of the object here
                }
                
                gameData->clearObjSnapshot();
            }
        }
        
        void onUnload(){
            ACO_GameData* gameData = ACO_GameData::createInstance();
            for(GD_GameObject* obj: getAllObjects())
                gameData->addObjSnapshot(obj);
            removeAllObjects();
        }
        
        void update(sf::Time deltaTime){
            GD_Scene::update(deltaTime);
            if(loadTimeout>0)loadTimeout--;
            GD_ModularObject* player = (GD_ModularObject*)findObject("player");
            GD_ModularObject* bonus1 = (GD_ModularObject*)findObject("bonus1");
            GD_ModularObject* bonus2 = (GD_ModularObject*)findObject("bonus2");
            ACO_GameData* gameData = ACO_GameData::createInstance();
            
            if(bonus1->getTileX()==player->getTileX() && 
                    bonus1->getTileY()==player->getTileY()){
                GD_Trn::moveToRand(bonus1, GAME_GRID_SIZE);
                GD_TextObject* txt = (GD_TextObject*)findObject("score");
                gameData->addScore(1);
                txt->setText("SCORE: "+std::to_string(gameData->getScore()));
            }
            if(bonus2->getTileX()==player->getTileX() && 
                    bonus2->getTileY()==player->getTileY()){
                GD_Trn::moveToRand(bonus2, GAME_GRID_SIZE);
                GD_TextObject* txt = (GD_TextObject*)findObject("score");
                gameData->addScore(1);
                txt->setText("SCORE: "+std::to_string(gameData->getScore()));
            }
            
            //Delete timed objects
            for(GD_GameObject* obj: getAllObjects()){
                GD_ModularObject* mobj = dynamic_cast<GD_ModularObject*>(obj);
                if(mobj==nullptr) continue;
                
                GD_Component* cmp = mobj->getComponent("ACO_TimedLifeComp");
                if(cmp == nullptr || !((ACO_TimedLifeComp*)cmp)->isElapsed())
                    continue;
                    
                if(dynamic_cast<ACO_BulletObject*>(obj)!=nullptr)
                    bulletPool->releaseObject((ACO_BulletObject*)obj);
                removeObject(obj);
            }
        }
        
        void keyPressTrigger(sf::Keyboard::Scan keyCode){
            GD_ModularObject* player = (GD_ModularObject*)findObject("player");
            
            if(keyCode == sf::Keyboard::Scan::W)
                GD_Trn::moveUp(player);
            else if(keyCode == sf::Keyboard::Scan::S)
                GD_Trn::moveDown(player);
            else if(keyCode == sf::Keyboard::Scan::A)
                GD_Trn::moveLeft(player);
            else if(keyCode == sf::Keyboard::Scan::D)
                GD_Trn::moveRight(player);
            else if(keyCode == sf::Keyboard::Scan::Q)
                GD_Trn::turnLeft(player);
            else if(keyCode == sf::Keyboard::Scan::E)
                GD_Trn::turnRight(player);
            else if(keyCode == sf::Keyboard::Scan::P && 0==loadTimeout){
                //wait atleast 60 frames before allowing to pause again
                GD_SceneManager* sman = GD_SceneManager::createInstance();
                sman->loadScene("MenuScene");
            }else{
                ACO_ChargeComp* chrg = (ACO_ChargeComp*)player->getComponent("ACO_ChargeComp");
                if(keyCode == sf::Keyboard::Scan::Space && !chrg->isCharging()){
                    chrg->startCharge();
                    std::cout << "START" << std::endl;
                }
            }//end else
        }
        
        void keyReleaseTrigger(sf::Keyboard::Scan keyCode){
            if(keyCode == sf::Keyboard::Scan::Space){
                GD_ModularObject* player = (GD_ModularObject*)findObject("player");
                ACO_ChargeComp* chrg = (ACO_ChargeComp*)player->getComponent("ACO_ChargeComp");
                chrg->endCharge();
                
                int scale = 1;
                if(chrg->getChargeLevel()>=1)
                    scale++;
                
                ACO_BulletObject* newBullet = bulletPool->requestObject();
                if(newBullet==nullptr) return;
                
                newBullet->resetLife();
                newBullet->resizeBullet(scale);
                newBullet->positionBullet(player);
                addObject(newBullet);
            }
        }
};

class Game: public GD_ScenedGameEngine{
    private:
        ACO_BulletPool* bulletPool;
    public:
        void init(){
            GD_ScenedGameEngine::init();
            bulletPool = new ACO_BulletPool(5, TILE_SIZE);
            GD_SceneManager* sman = getSceneManager();
            sman->registerScene(new MenuScene());
            sman->registerScene(new GameScene(bulletPool));
            sman->loadScene("MenuScene");
        }
        
        void keyPressTrigger(sf::Keyboard::Scan keyCode){
            GD_SceneManager* sman = getSceneManager();
            MenuScene* menu = dynamic_cast<MenuScene*>(sman->getCurrentScene());
            if(nullptr != menu)
                menu->keyPressTrigger(keyCode);
            GameScene* game = dynamic_cast<GameScene*>(sman->getCurrentScene());
            if(nullptr != game)
                game->keyPressTrigger(keyCode);
        }

        void keyReleaseTrigger(sf::Keyboard::Scan keyCode){
            GD_SceneManager* sman = getSceneManager();
            MenuScene* menu = dynamic_cast<MenuScene*>(sman->getCurrentScene());
            if(nullptr != menu)
                menu->keyReleaseTrigger(keyCode);
            GameScene* game = dynamic_cast<GameScene*>(sman->getCurrentScene());
            if(nullptr != game)
                game->keyReleaseTrigger(keyCode);
        }
        
        ~Game(){
            GD_GameResource* resources = GD_GameResource::createInstance();
            delete resources;
            ACO_GameData* gameData = ACO_GameData::createInstance();
            delete gameData;
            delete bulletPool;
        }
};

int main() {
    Game game;
    game.run(   "Hands-on 9: Shop", 
                TILE_SIZE*GAME_GRID_SIZE, 
                TILE_SIZE*(GAME_GRID_SIZE+MENU_HEIGHT));
    return 0;
}
