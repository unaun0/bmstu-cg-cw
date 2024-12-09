#include "colorRGB.hpp"

ColorRGB::ColorRGB() : r(0.0f), g(0.0f), b(0.0f) {}

ColorRGB::ColorRGB(float r, float g, float b) {
    if (std::isnan(r) || std::isnan(g) || std::isnan(b))
        throw std::invalid_argument("One or more ColorRGB parameters are NaN");
    if (r < 0.0 || r > 1.0 || g < 0.0 || g > 1.0 || b < 0.0 || b > 1.0)
        throw std::out_of_range("ColorRGB parameter(s) outside of expected range");
    this->r = r;
    this->g = g;
    this->b = b;
}

ColorRGB ColorRGB::mul(const ColorRGB& oth) const {
    return ColorRGB(r * oth.r, g * oth.g, b * oth.b);
}

ColorRGB ColorRGB::mul(float t) const {
    t = std::min(1.0f, t);
    return ColorRGB(r * t, g * t, b * t);
}

ColorRGB ColorRGB::div(float t) const {
    if (t == 0.0f) throw std::invalid_argument("Division by zero in ColorRGB::div");
    return ColorRGB(
        std::clamp(r / t, 0.0f, 1.0f),
        std::clamp(g / t, 0.0f, 1.0f),
        std::clamp(b / t, 0.0f, 1.0f)
    );
}

ColorRGB ColorRGB::add(float t) const {
    return ColorRGB(std::min(1.0f, r + t), 
                 std::min(1.0f, g + t), 
                 std::min(1.0f, b + t));
}

ColorRGB ColorRGB::add(const ColorRGB& oth) const {
    return ColorRGB(std::min(1.0f, r + oth.r), 
                 std::min(1.0f, g + oth.g), 
                 std::min(1.0f, b + oth.b));
}

ColorRGB ColorRGB::operator+(const ColorRGB& oth) const {
    return add(oth);
}

ColorRGB ColorRGB::operator*(const ColorRGB& oth) const {
    return mul(oth);
}

const ColorRGB ColorRGB::BLACK = ColorRGB(0.0f, 0.0f, 0.0f);
const ColorRGB ColorRGB::WHITE = ColorRGB(1.0f, 1.0f, 1.0f);
const ColorRGB ColorRGB::RED = ColorRGB(1.0f, 0.0f, 0.0f);
const ColorRGB ColorRGB::GREEN = ColorRGB(0.0f, 1.0f, 0.0f);
const ColorRGB ColorRGB::BLUE = ColorRGB(0.0f, 0.0f, 1.0f);
const ColorRGB ColorRGB::SKYBLUE = ColorRGB(0.596f, 0.898f, 0.996f);

ColorRGB ColorRGB::lrp(const ColorRGB& ca, const ColorRGB& cb, float t) {
    return ColorRGB(
        ca.r + t * (cb.r - ca.r),
        ca.g + t * (cb.g - ca.g),
        ca.b + t * (cb.b - ca.b)
    );
}
