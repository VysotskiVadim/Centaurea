#pragma once

#import "IGraphicComponent.h"

namespace Centaurea {
    namespace Common {
        namespace Game {
            class IGraphicComponentFactory {
            public:
                IGraphicComponent virtual loadModel(std::string name) = 0;
            };
        }
    }
}
