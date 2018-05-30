#pragma once

#include <glm/glm.hpp>
#include "TransformModel.h"
#include "Camera.h"

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            glm::mat4 getModelMatrix(const TransformModel &model) {
                glm::mat4 modelMatrix;
                modelMatrix = glm::translate(modelMatrix, glm::vec3(model.bounds.position.x, model.bounds.position.y, model.bounds.position.z));
                modelMatrix = glm::rotate(
                                          modelMatrix,
                                          glm::radians(model.rotationAngle),
                                          glm::vec3(0.0f, 0.0f, 1.0f)
                                          );
                return modelMatrix;
            }
            
            glm::mat4 getViewMatrix(const Camera &camera) {
                glm::mat4 view = glm::lookAt(
                                             glm::vec3(camera.position.x, camera.position.y, camera.position.z),
                                             glm::vec3(camera.target.x, camera.target.y, camera.target.z),
                                             glm::vec3(camera.upVector.x, camera.upVector.y, camera.upVector.z)
                                             );
                return view;
            }
            
            glm::mat4 getProjectctionMatrix(const Camera &camera) {
                glm::mat4 proj = glm::perspective(glm::radians(camera.fieldOfView), camera.aspectRatio, camera.nearClippingPlane, camera.farClippingPlane);
                return proj;
            }
            
        }
    }
}
