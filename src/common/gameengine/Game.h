#pragma once

#include <memory>
#include "IGraphicComponentFactory.h"
#include "ITextureLoader.h"
#include "Screen.h"
#include "IGameScene.h"
#include <chrono>
#include "Camera.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            class Game {
            private:
                std::shared_ptr<IGameScene> _gameScene;
                bool _isInitialized = false;
                std::chrono::high_resolution_clock::time_point _previousFrameTime;
            public:
                std::shared_ptr<ITextureLoader> textureLoader;
                std::shared_ptr<IGraphicComponentFactory> graphicComponentFactory;
                Screen screen;
                Camera camera;
                Game(std::shared_ptr<ITextureLoader>, std::shared_ptr<IGraphicComponentFactory>);
                void initialize(void);
                void screenSizeChanged(std::int32_t width, std::int32_t height);
                void update(void);
                void setGameScene(std::shared_ptr<IGameScene> gameScene);
            };
            
            

        }
    }
}
