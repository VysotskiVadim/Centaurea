#pragma once

#import "GameObject.h"
#import <vector>
#import <memory.h>
#import "Game.h"
#import "IGameScene.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class GameScene: public IGameScene {
            private:
                std::shared_ptr<Game> _game;
                std::vector<std::shared_ptr<GameObject>> _objects;
            public:
                GameScene(std::shared_ptr<Game>);
                void virtual update(float elapsed) override;
                void virtual initialize() override;
            };
        }
    }
}
