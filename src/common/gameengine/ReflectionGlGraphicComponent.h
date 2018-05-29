#pragma once

#include "IGraphicComponent.h"
#include <string>
#include <memory>
#include "glwrapper.h"
#include "ITextureLoader.h"
#include "Game.h"

const int TEXTURE_COUNT = 2;

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
                
                GLuint _textures[TEXTURE_COUNT];
                GLuint _vertexBufferObject;
            public:
                ReflectionGlGraphicComponent(std::shared_ptr<Game>);
                void update(float elapsed, IGameObject* obj) override;
                void initialize() override;
                void dispose() override;
            };
        }
    }
}
