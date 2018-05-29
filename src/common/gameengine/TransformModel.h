#pragma once

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {

            struct Vector3 {
                float x;
                float y;
                float z;
            };

            struct BoundingCoube {
                Vector3 position = {0,0,0};
            };

            struct TransformModel {
                BoundingCoube bounds;
                float rotationAngle = 0;
            };
        }
    }
}
