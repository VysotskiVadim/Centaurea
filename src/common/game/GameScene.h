#pragma once

#import "gameObject.h"
#import <vector>
#import <memory.h>
#import "IGraphicComponentFactory.h"

using namespace Centaurea::Common::Game;

namespace Cenraurea {
    namespace Common {
        namespace Game {
            class GameScene {
            private:
                std::shared_ptr<IGraphicComponentFactory> _graphicComponentFactory;
                std::vector<std::shared_ptr<GameObject>> _objects;
            public:
                GameScene(std::shared_ptr<IGraphicComponentFactory>);
                void update();
                void initialize();
            };
        }
    }
}
