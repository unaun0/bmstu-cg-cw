#include <iostream>
#include <glm/glm.hpp>
#include "Ray.hpp"
#include "Line.hpp"
#include "Color.hpp"
#include "Shape.hpp"

int main() {
    glm::vec3 origin(0.0f, 0.0f, 0.0f);
    glm::vec3 direction(0.0f, 0.0f, 1.0f);

    Ray ray(origin, direction);
    Line line = ray.asLine(5.0f);

    std::cout << "Line start: (" << line.start.x << ", " << line.start.y << ", " << line.start.z << ")\n";
    std::cout << "Line end: (" << line.end.x << ", " << line.end.y << ", " << line.end.z << ")\n";

    Color red = Color::RED;
    Color blue = Color::BLUE;
    Color purple = red + blue;

    std::cout << "Purple RGB: " << std::hex << purple.getRGB() << std::endl;
    std::cout << "Luminance: " << purple.luminance() << std::endl;

    return 0;
}
