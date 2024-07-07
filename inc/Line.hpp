#pragma once

#include <glm/glm.hpp>

/**
 * @brief Представляет отрезок прямой в трёхмерном пространстве, заданный начальной и конечной точками.
 */
class Line {
public:
    glm::vec3 start; ///< Начальная точка отрезка прямой.
    glm::vec3 end;   ///< Конечная точка отрезка прямой.

    /**
     * @brief Конструирует отрезок прямой по заданным начальной и конечной точкам.
     * @param start Начальная точка отрезка прямой.
     * @param end Конечная точка отрезка прямой.
     */
    Line(const glm::vec3& start, const glm::vec3& end)
        : start(start), end(end) {}
};