#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "vec3.hpp"
#include "colorRGB.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class Skybox {
private:
    sf::Texture textureRight, textureLeft, textureUp, textureDown, textureFront, textureBack;
    sf::Image imageRight, imageLeft, imageUp, imageDown, imageFront, imageBack;
    sf::Vector2u sizeRight, sizeLeft, sizeUp, sizeDown, sizeFront, sizeBack;

public:
    Skybox(const std::string& right, const std::string& left,
           const std::string& up, const std::string& down,
           const std::string& front, const std::string& back);

    bool loadTextures(const std::string& right, const std::string& left,
                      const std::string& up, const std::string& down,
                      const std::string& front, const std::string& back);

    ColorRGB getColorRGB(const vec3& dir) const;
};

#endif // SKYBOX_HPP