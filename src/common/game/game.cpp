#include "Game.h"

using namespace Cenraurea::Common::GameEngine;

Game::Game(
    std::shared_ptr<ITextureLoader> textureLoader,
    std::shared_ptr<IGraphicComponentFactory> graphicComponentFactory
):
textureLoader(textureLoader),
graphicComponentFactory(graphicComponentFactory)
{}

void Cenraurea::Common::GameEngine::Game::setGameScene(std::shared_ptr<IGameScene> gameScene) {
    _gameScene = gameScene;
    if (_isInitialized) {
        _gameScene->initialize();
    }
}

void Game::initialize(void) {
    if (_gameScene != nullptr) {
         _gameScene->initialize();
    }
    _isInitialized = true;
}

void Game::update(void) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _previousFrameTime).count();
    if (_gameScene != nullptr) {
       _gameScene->update(elapsed);
    }
    _previousFrameTime = currentTime;
}

void Game::screenSizeChanged(std::int32_t width, std::int32_t height) {
    screen.size.height = height;
    screen.size.width = width;
}
