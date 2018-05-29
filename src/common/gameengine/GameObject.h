#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "IGraphicComponent.h"
#include "IDisposable.h"
#include "TransformModel.h"
#include "IGameObject.h"

using namespace std;

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class GameObject: public IGameObject {
            private:
                shared_ptr<IGraphicComponent> _graphicComponent;
            public:
                GameObject(shared_ptr<IGraphicComponent>);
                void virtual update(float elapsed) override;
                void virtual dispose() override;
            };
        }
    }
}
