#pragma once

#include "Ray.hpp"
#include <glm/glm.hpp>
#include "Shape.hpp"

/**
 * @brief Структура, представляющая информацию о пересечении луча с объектом.
 */
class Hit {
public:
    const Ray ray;              ///< Луч, с которым произошло пересечение.
    const Shape& shape;         ///< Ссылка на фигуру, с которой произошло пересечение.
    const glm::vec3 position;   ///< Точка пересечения луча с объектом.
    const glm::vec3 normal;     ///< Нормаль к объекту в точке пересечения.

    /**
     * @brief Конструктор для инициализации информации о пересечении луча с объектом.
     * @param ray Луч, с которым произошло пересечение.
     * @param shape Ссылка на фигуру, с которой произошло пересечение.
     * @param position Точка пересечения луча с объектом.
     */
    Hit(const Ray& ray, const Shape& shape, const glm::vec3& position);
};
