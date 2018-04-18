#pragma once

#include <memory>
#include "glwrapper.h"
#include "ITextureLoader.h"


namespace Cenraurea {
    namespace Common {
        namespace Game {

            class Game {
            private:
                unsigned int _shaderProgram = 0;
                bool setupShaders(void);
                std::shared_ptr<ITextureLoader> _textureLoader;
            public:
                Game(std::shared_ptr<ITextureLoader>);
                void on_surface_created(void);
                void on_surface_changed(void);
                void on_draw_frame(void);
            };

        }
    }
}

