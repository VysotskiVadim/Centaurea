#pragma once

#include <memory>
#include "IGraphicComponentFactory.h"
#include "ITextureLoader.h"
#include "Screen.h"
#include "IGameScene.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            class Game {
            private:
                std::shared_ptr<IGameScene> _gameScene;
            public:
                std::shared_ptr<ITextureLoader> textureLoader;
                std::shared_ptr<IGraphicComponentFactory> graphicComponentFactory;
                Screen screen;
                Game(std::shared_ptr<ITextureLoader>, std::shared_ptr<IGraphicComponentFactory>);
                void on_surface_created(void);
                void on_surface_changed(std::int32_t width, std::int32_t height);
                void on_draw_frame(void);
                void setGameScene(std::shared_ptr<IGameScene> gameScene);
            };
            
            

        }
    }
}
