#import "GameObject.h"

using Cenraurea::Common::Game;

GameObject::GameObject(std::shared_ptr<IGraphicComponent> graphic)
:_graphicComponent(graphic)
{}

GameObject::update() {
    _graphicComponent.update();
}
