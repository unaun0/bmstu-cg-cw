#ifndef COLORRGB_HPP
#define COLORRGB_HPP

#include <stdexcept>
#include <algorithm>
class ColorRGB {
public:
    float r;
    float g;
    float b;

    ColorRGB();
    ColorRGB(float r, float g, float b);

    ColorRGB mul(const ColorRGB& oth) const;
    ColorRGB mul(float t) const;
    ColorRGB div(float t) const;
    ColorRGB add(const ColorRGB& oth) const;
    ColorRGB add(float t) const;
    ColorRGB operator+(const ColorRGB& oth) const;
    ColorRGB operator*(const ColorRGB& oth) const;
    static ColorRGB lrp(const ColorRGB& ca, const ColorRGB& cb, float t);

    static const ColorRGB BLACK;
    static const ColorRGB WHITE;
    static const ColorRGB RED;
    static const ColorRGB GREEN;
    static const ColorRGB BLUE;
    static const ColorRGB SKYBLUE;
};

#endif // COLORRGB_HPP
