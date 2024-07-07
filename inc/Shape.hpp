#pragma once

#include <glm/glm.hpp>
#include "Color.hpp"
#include "Ray.hpp"

/**
 * @brief Абстрактный базовый класс для геометрических фигур.
 */
class Shape {
protected:
    glm::vec3 position;     ///< Позиция центра фигуры в трёхмерном пространстве.
    Color color;            ///< Цвет фигуры.
    float reflectivity;     ///< Коэффициент отражения (от 0.0 до 1.0).
    float refractivity;     ///< Коэффициент преломления (от 0.0 до 1.0).
    float emission;         ///< Интенсивность излучения.

public:
    /**
     * @brief Конструктор для инициализации параметров фигуры.
     * @param pos Позиция центра фигуры.
     * @param col Цвет фигуры.
     * @param refl Коэффициент отражения (от 0.0 до 1.0).
     * @param refr Коэффициент преломления (от 0.0 до 1.0).
     * @param emit Интенсивность излучения.
     */
    Shape(const glm::vec3& pos, const Color& col, float refl, float refr, float emit);

    /**
     * @brief Виртуальный деструктор по умолчанию.
     */
    virtual ~Shape() = default;

    /**
     * @brief Возвращает точку пересечения луча с фигурой, если она есть.
     * @param ray Луч, с которым проверяется пересечение.
     * @return Указатель на точку пересечения или nullptr, если пересечения нет.
     */
    virtual glm::vec3* intersect(const Ray& ray) const = 0;

    /**
     * @brief Возвращает нормаль к фигуре в заданной точке.
     * @param point Точка, в которой нужно получить нормаль.
     * @return Нормаль к фигуре в заданной точке.
     */
    virtual glm::vec3 getNormal(const glm::vec3& point) const = 0;

    /**
     * @brief Возвращает текстуру фигуры в заданной точке.
     * @param point Точка, в которой нужно получить текстуру.
     * @return Цвет текстуры в заданной точке.
     */
    virtual Color getTexture(const glm::vec3& point) const = 0;
};
