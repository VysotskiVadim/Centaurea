#import "GameObject.h"

using namespace Cenraurea::Common::GameEngine;

GameObject::GameObject(std::shared_ptr<IGraphicComponent> graphic)
:_graphicComponent(graphic)
{}

void GameObject::update(float elapsed) {
    _graphicComponent->update(elapsed);
}

void GameObject::dispose() {
    _graphicComponent->dispose();
}
