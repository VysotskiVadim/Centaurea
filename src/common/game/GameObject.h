#pragma once

#import <memory>
#import "IGraphicComponent.h"
#import "IDisposable.h"

using namespace std;

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class GameObject: public IDisposable {
            private:
                shared_ptr<IGraphicComponent> _graphicComponent;
            public:
                GameObject(shared_ptr<IGraphicComponent>);
                void update(float elapsed);
                void dispose();
            };
        }
    }
}
