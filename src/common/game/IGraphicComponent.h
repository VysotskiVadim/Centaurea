#pragma once

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class IGraphicComponent {
            public:
                void virtual initialize() = 0;
                void virtual update(float elapsed) = 0;
            };
        }
    }
}
