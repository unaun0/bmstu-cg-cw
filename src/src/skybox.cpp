#include "skybox.hpp"
#include "colorRGB.hpp"

Skybox::Skybox(const std::string& right, const std::string& left,
               const std::string& up, const std::string& down,
               const std::string& front, const std::string& back) {
    if (!loadTextures(right, left, up, down, front, back)) {
        throw std::runtime_error("Не удалось загрузить текстуры Skybox");
    }
}

bool Skybox::loadTextures(const std::string& right, const std::string& left,
                          const std::string& up, const std::string& down,
                          const std::string& front, const std::string& back) {
    if (!textureRight.loadFromFile(right) || !textureLeft.loadFromFile(left) ||
        !textureUp.loadFromFile(up) || !textureDown.loadFromFile(down) ||
        !textureFront.loadFromFile(front) || !textureBack.loadFromFile(back)) {
        return false;
    }

    imageRight = textureRight.copyToImage();
    imageLeft = textureLeft.copyToImage();
    imageUp = textureUp.copyToImage();
    imageDown = textureDown.copyToImage();
    imageFront = textureFront.copyToImage();
    imageBack = textureBack.copyToImage();

    sizeRight = imageRight.getSize();
    sizeLeft = imageLeft.getSize();
    sizeUp = imageUp.getSize();
    sizeDown = imageDown.getSize();
    sizeFront = imageFront.getSize();
    sizeBack = imageBack.getSize();

    return true;
}

ColorRGB Skybox::getColorRGB(const vec3& dir) const {
    const sf::Image* image = nullptr;
    sf::Vector2u size;

    if (std::abs(dir.x) > std::abs(dir.y) && std::abs(dir.x) > std::abs(dir.z)) {
        if (dir.x > 0) {
            image = &imageLeft;
            size = sizeLeft;
        } else {
            image = &imageRight;
            size = sizeRight;
        }
    } else if (std::abs(dir.y) > std::abs(dir.z)) {
        if (dir.y > 0) {
            image = &imageUp;
            size = sizeUp;
        } else {
            image = &imageDown;
            size = sizeDown;
        }
    } else {
        if (dir.z > 0) {
            image = &imageBack;
            size = sizeBack;
        } else {
            image = &imageFront;
            size = sizeFront;
        }
    }

    float u, v;
    if (image == &imageRight) { // Правая сторона (+X)
        u = 0.5f - (dir.z / std::abs(dir.x)) * 0.5f;
        v = 0.5f - (dir.y / std::abs(dir.x)) * 0.5f;
    } else if (image == &imageLeft) { // Левая сторона (-X)
        u = 0.5f + (dir.z / std::abs(dir.x)) * 0.5f;
        v = 0.5f - (dir.y / std::abs(dir.x)) * 0.5f;
    } else if (image == &imageUp) { // Верхняя сторона (+Y)
        u = 0.5f + (dir.x / std::abs(dir.y)) * 0.5f;
        v = 0.5f - (dir.z / std::abs(dir.y)) * 0.5f;
    } else if (image == &imageDown) { // Нижняя сторона (-Y)
        u = 0.5f + (dir.x / std::abs(dir.y)) * 0.5f;
        v = 0.5f + (dir.z / std::abs(dir.y)) * 0.5f;
    } else if (image == &imageFront) { // Передняя сторона (+Z)
        u = 0.5f + (dir.x / std::abs(dir.z)) * 0.5f;
        v = 0.5f - (dir.y / std::abs(dir.z)) * 0.5f;
    } else { // Задняя сторона (-Z)
        u = 0.5f - (dir.x / std::abs(dir.z)) * 0.5f;
        v = 0.5f - (dir.y / std::abs(dir.z)) * 0.5f;
    }
    unsigned int px = static_cast<unsigned int>(std::clamp(u * size.x, 0.0f, static_cast<float>(size.x - 1)));
    unsigned int py = static_cast<unsigned int>(std::clamp(v * size.y, 0.0f, static_cast<float>(size.y - 1)));

    sf::Color pixelColor = image->getPixel(px, py);
    return ColorRGB(pixelColor.r / 255.0f, pixelColor.g / 255.0f, pixelColor.b / 255.0f);
}
