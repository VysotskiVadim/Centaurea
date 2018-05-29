#pragma once

#include <glm/glm.hpp>
#include "TransformModel.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            glm::mat4 getModelMatrix(TransformModel model) {
                glm::mat4 modelMatrix;
                modelMatrix = glm::translate(modelMatrix, glm::vec3(model.bounds.position.x, model.bounds.position.y, model.bounds.position.z));
                modelMatrix = glm::rotate(
                                          modelMatrix,
                                          glm::radians(model.rotationAngle),
                                          glm::vec3(0.0f, 0.0f, 1.0f)
                                          );
                return modelMatrix;
            }
            
        }
    }
}
