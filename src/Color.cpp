#include "Color.hpp"

const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
const Color Color::RED = Color(1.0f, 0.0f, 0.0f);
const Color Color::GREEN = Color(0.0f, 1.0f, 0.0f);
const Color Color::BLUE = Color(0.0f, 0.0f, 1.0f);
const Color Color::MAGENTA = Color(1.0f, 0.0f, 1.0f);
const Color Color::GRAY = Color(0.5f, 0.5f, 0.5f);
const Color Color::DARK_GRAY = Color(0.2f, 0.2f, 0.2f);
const Color Color::TREE = Color(0.40f, 0.26f, 0.13f);
const Color Color::BURGUNDY = Color(0.55f, 0.01f, 0.04f);
const Color Color::CORNSILK = Color(1.0f, 0.99f, 0.8f);

Color::Color(float r, float g, float b) {
    if ((r > 1.0f || g > 1.0f || b > 1.0f) || 
        std::isnan(r) || std::isnan(g) || std::isnan(b)) {
        throw std::invalid_argument("Один или несколько параметров цвета выходят за ожидаемый диапазон [0.0, 1.0] или являются NaN");
    }
    red = r;
    green = g;
    blue = b;
}

Color Color::multiply(const Color& other) const {
    return Color(red * other.red, green * other.green, blue * other.blue);
}

Color Color::multiply(float brightness) const {
    brightness = std::min(1.0f, brightness);
    return Color(red * brightness, green * brightness, blue * brightness);
}

Color Color::add(const Color& other) const {
    return Color(
        std::min(1.0f, red + other.red),
        std::min(1.0f, green + other.green),
        std::min(1.0f, blue + other.blue)
    );
}

Color Color::operator+(const Color& other) const {
    return add(other);
}

Color Color::operator*(const Color& other) const {
    return multiply(other);
}

void Color::addSelf(const Color& other) {
    red = std::min(1.0f, red + other.red);
    green = std::min(1.0f, green + other.green);
    blue = std::min(1.0f, blue + other.blue);
}

Color Color::add(float brightness) const {
    return Color(
        std::min(1.0f, red + brightness),
        std::min(1.0f, green + brightness),
        std::min(1.0f, blue + brightness)
    );
}

unsigned int Color::getRGB() const {
    unsigned int redPart = static_cast<unsigned int>(red * 255) << 16 & 0x00FF0000u;
    unsigned int greenPart = static_cast<unsigned int>(green * 255) << 8 & 0x0000FF00u;
    unsigned int bluePart = static_cast<unsigned int>(blue * 255) & 0x000000FFu;
    return 0xFF000000u | redPart | greenPart | bluePart;
}

float Color::luminance() const {
    return red * 0.2126f + green * 0.7152f + blue * 0.0722f;
}

Color Color::fromInt(int argb) {
    float b = static_cast<float>(argb & 0xFF) / 255.0f;
    float g = static_cast<float>(argb >> 8 & 0xFF) / 255.0f;
    float r = static_cast<float>(argb >> 16 & 0xFF) / 255.0f;
    return Color(r, g, b);
}

Color Color::lerp(const Color& a, const Color& b, float t) {
    return Color(
        a.red + t * (b.red - a.red),
        a.green + t * (b.green - a.green),
        a.blue + t * (b.blue - a.blue)
    );
}
