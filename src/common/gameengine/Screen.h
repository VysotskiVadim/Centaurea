#pragma once

namespace Cenraurea {
    namespace Common {
        namespace GameEngine {
            
            struct Size {
                std::int32_t width = 0;
                std::int32_t height = 0;
            };
            
            class Screen {
            public:
                Size size;
            };
            
        }
    }
}
