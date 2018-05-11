#pragma once

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            class IGameScene {
            public:
                void virtual update() = 0;
                void virtual initialize() = 0;
            };
        }
    }
}
