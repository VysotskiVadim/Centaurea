#pragma once

#include "TransformModel.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            struct Camera {
                Vector3 position = {0.0f,0.0f,0.0f};
                Vector3 target = {0.0f,0.0f,0.0f};
                Vector3 upVector = {0.0f,0.0f,0.0f};
                float fieldOfView = 45.0f;
                float aspectRatio = 1.0f;
                float nearClippingPlane = 0.1f;
                float farClippingPlane = 100.0f;
            };
            
        }
    }
}
