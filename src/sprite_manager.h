#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>

#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstddef>

using SpriteID = size_t;

class SpriteManager {
private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::vector<Sprite> sprites;
public:
    sf::Texture& registerTexture(const std::string& filepath) {
        auto it = textures.find(filepath);
        if (it != textures.end()) {
            return *it->second;

        }
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(filepath)) {
            throw std::runtime_error("failed to load sprite");
        }
        sf::Texture& result = *texture;
        textures.emplace(filepath, std::move(texture));
        return result;
    }
    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        sprites.emplace_back(std::forward<Args>(args)...);
        return sprites.size() - 1;
    } 
    Sprite& getSprite(SpriteID id) {
        return sprites.at(id);
    }
};

#endif  // SPRITE_MANAGER_H
