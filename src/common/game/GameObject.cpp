#import "GameObject.h"

using namespace Cenraurea::Common::GameEngine;

GameObject::GameObject(std::shared_ptr<IGraphicComponent> graphic)
:_graphicComponent(graphic)
{}

void GameObject::update(void) {
    _graphicComponent->update();
}
