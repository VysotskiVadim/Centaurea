#pragma once

#include <string>
#include <memory>
#include "glwrapper.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {

            class ITextureLoader {
            public:
                virtual void loadTexture(std::string id) = 0;
            };

        }
    }
}
