#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "IGraphicComponent.h"
#include "IDisposable.h"
#include "TransformModel.h"

using namespace std;

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class IGameObject: public IDisposable {
            public:
                TransformModel transform;
                void virtual update(float elapsed) = 0;
            };
        }
    }
}

