#pragma once

#include <memory>
#include "Game.h"
#include "IGraphicComponentFactory.h"
#include "GlGraphicComponentFactory.h"
#include "ITextureLoader.h"
#include "GameScene.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            std::shared_ptr<Game> createGlGame(std::shared_ptr<ITextureLoader> textureLoader){
                auto glGraphicComponentFactory = new GlGraphicComponentFactory();
                auto graphicomponentFactory = std::shared_ptr<IGraphicComponentFactory>(glGraphicComponentFactory);
                auto game = std::shared_ptr<Game>(new Game(textureLoader, graphicomponentFactory));
                glGraphicComponentFactory->game = game;
                auto gameScene = new GameScene(game);
                auto gameScenePtr = std::shared_ptr<GameScene>(gameScene);
                game->setGameScene(gameScenePtr);
                return game;
            }
            
        }
    }
}
