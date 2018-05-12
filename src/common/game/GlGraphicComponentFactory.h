#pragma once

#include "Game.h"
#include "IGraphicComponentFactory.h"
#include <memory>

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class GlGraphicComponentFactory: public IGraphicComponentFactory {
            public:
                std::shared_ptr<Game> game;
                std::shared_ptr<IGraphicComponent> loadModel(std::string name) override;
            };
        }
    }
}
