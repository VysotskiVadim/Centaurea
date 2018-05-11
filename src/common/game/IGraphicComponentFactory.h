#pragma once

#import "IGraphicComponent.h"
#import <string>
#import <memory>

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
