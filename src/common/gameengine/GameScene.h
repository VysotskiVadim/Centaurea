#pragma once

#include "GameObject.h"
#include <vector>
#include <memory.h>
#include "Game.h"
#include "IGameScene.h"

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
