#pragma once

#include "IGraphicComponent.h"
#include <string>
#include <memory>

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            class IGraphicComponentFactory {
            public:
                virtual std::shared_ptr<IGraphicComponent> loadModel(std::string name) = 0;
            };
        }
    }
}
