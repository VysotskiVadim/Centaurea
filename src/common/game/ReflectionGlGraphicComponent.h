#pragma once

#import "IGraphicComponent.h"
#import <string>
#include <memory>
#include "glwrapper.h"
#include "ITextureLoader.h"
#include <chrono>
#include "game.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class ReflectionGlGraphicComponent: public IGraphicComponent {
            private:
                unsigned int _shaderProgram = 0;
                bool setupShaders(void);
                void setupSizes(void);
                std::shared_ptr<Game> _game;
                std::shared_ptr<ITextureLoader> _textureLoader;
                std::chrono::high_resolution_clock::time_point _startTime;
            public:
                ReflectionGlGraphicComponent(std::shared_ptr<Game>);
                void update() override;
                void initialize() override;
            };
        }
    }
}
