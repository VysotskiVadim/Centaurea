#import "GlGraphicComponentFactory.h"
#import "ReflectionGlGraphicComponent.h"
#import "IGraphicComponent.h"

using namespace Cenraurea::Common::GameEngine;

std::shared_ptr<IGraphicComponent> GlGraphicComponentFactory::loadModel(std::string name) {
    if (name == "reflection") {
        return std::shared_ptr<IGraphicComponent>(new ReflectionGlGraphicComponent(game));
    }
    return NULL;
}
