#pragma once

#include "glwrapper.h"

namespace Cenraurea {
    namespace Common {
        namespace Game {

            class Game {
            private:
                unsigned int _shaderProgram = 0;
                bool setupShaders(void);
            public:
                void on_surface_created(void);
                void on_surface_changed(void);
                void on_draw_frame(void);
            };

        }
    }
}

