#pragma once

#include "ITextureLoader.h"
#include <string>

using Cenraurea::Common::Game::ITextureLoader;

class IosTextureLoader : public ITextureLoader {
public:
    void loadTexture(std::string id) override;
};
