#pragma once

#import "IGraphicComponent.h"
#import <string>
#include <memory>
#include "glwrapper.h"
#include "ITextureLoader.h"
#include "Game.h"

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
                float _rotationAngle = 0;
            public:
                ReflectionGlGraphicComponent(std::shared_ptr<Game>);
                void update(float elapsed) override;
                void initialize() override;
            };
        }
    }
}
