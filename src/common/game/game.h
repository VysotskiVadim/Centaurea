#pragma once

namespace Cenraurea {
    namespace Common {
        namespace Game {

            class Game {
            public:
                void on_surface_created(void);
                void on_surface_changed(void);
                void on_draw_frame(void);
            };
        }
    }
}

