#pragma once

#include "TransformModel.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            struct Camera {
                Vector3 position = {0,0,0};
                Vector3 target = {0,0,0};
                Vector3 upVector = {0,0,0};
            };
            
        }
    }
}
