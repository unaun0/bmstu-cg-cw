#pragma once

#include <glm/glm.hpp>
#include "Line.hpp"

/**
 * @brief Представляет луч в трёхмерном пространстве, заданный начальной точкой и направлением.
 */
class Ray {
public:
    glm::vec3 orig; ///< Начальная точка луча.
    glm::vec3 dir; ///< Направляющий вектор луча (должен быть нормализован).

    /**
     * @brief Конструирует луч с заданной начальной точкой и направлением.
     * @param origin Начальная точка луча.
     * @param direction Направление луча (не обязательно нормализовано).
     */
    Ray(const glm::vec3& origin, const glm::vec3& direction);

    /**
     * @brief Преобразует луч в отрезок прямой заданной длины.
     * @param length Длина результирующего отрезка прямой.
     * @return Объект типа Line, представляющий луч как отрезок прямой.
     */
    Line asLine(float length) const;
};
