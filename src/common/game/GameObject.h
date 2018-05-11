#pragma once

#import <memory>
#import "IGraphicComponent.h"

using namespace std;

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class GameObject {
            private:
                shared_ptr<IGraphicComponent> _graphicComponent;
            public:
                GameObject(shared_ptr<IGraphicComponent>);
                void update(void);
            };
        }
    }
}
