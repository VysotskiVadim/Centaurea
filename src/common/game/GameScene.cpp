#import "GameScene.h"
#import "gameObject.h"

using Cenraurea::Common::Game;

GameScene::GameScene(std::shared_ptr<IGraphicComponentFactory> graphicComponentFactory)
: _graphicComponentFactory(graphicComponentFactory)
{ }

void GameScene::update(){
    for (GameObject obj in _objects) {
        obj.update();
    }
}

void GameScene::initialize() {
    
}
