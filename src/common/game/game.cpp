#include "game.h"
#include "glwrapper.h"

using Cenraurea::Common::Game::Game;

void Game::on_surface_created(void) {
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void Game::on_surface_changed(void) {
    // No-op
}

void Game::on_draw_frame(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}

