#pragma once

#include "IDisposable.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class IGraphicComponent: public IDisposable {
            public:
                void virtual initialize() = 0;
                void virtual update(float elapsed) = 0;
            };
        }
    }
}
