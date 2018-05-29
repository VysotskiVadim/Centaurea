#include "GameScene.h"
#include "GameObject.h"

using namespace Cenraurea::Common::GameEngine;

GameScene::GameScene(std::shared_ptr<Game> game)
: _game(game)
{ }

void GameScene::update(float elapsed){
    for (auto obj : _objects) {
        obj->transform.rotationAngle += elapsed / 1000 * 180;
        obj->update(elapsed);
    }
}

void GameScene::initialize() {
    auto graphicComponent = _game->graphicComponentFactory->loadModel("reflection");
    graphicComponent->initialize();
    auto gameObject = std::shared_ptr<GameObject>(new GameObject(graphicComponent));
    _objects.push_back(gameObject);
}
