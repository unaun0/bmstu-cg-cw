#pragma once

#include "Shape.hpp"
#include <glm/glm.hpp>

/**
 * @brief Класс, представляющий цилиндр.
 */
class Cylinder : public Shape {
private:
    float radius;   ///< Радиус основания цилиндра.
    float height;   ///< Высота цилиндра.

public:
    /**
     * @brief Конструктор для инициализации параметров цилиндра.
     * @param position Позиция центра цилиндра.
     * @param radius Радиус основания цилиндра.
     * @param height Высота цилиндра.
     * @param color Цвет цилиндра.
     * @param reflectivity Коэффициент отражения (от 0.0 до 1.0).
     * @param refractivity Коэффициент преломления (от 0.0 до 1.0).
     * @param emission Интенсивность излучения.
     */
    Cylinder(const glm::vec3& position, float radius, float height, const Color& color, float reflectivity, float refractivity, float emission);

    /**
     * @brief Метод определения пересечения луча с цилиндром.
     * @param ray Луч, с которым проверяется пересечение.
     * @return Указатель на точку пересечения или nullptr, если пересечения нет.
     */
    virtual glm::vec3* intersect(const Ray& ray) const override;

    /**
     * @brief Метод определения нормали к цилиндру в заданной точке.
     * @param point Точка, в которой нужно получить нормаль.
     * @return Нормаль к цилиндру в заданной точке.
     */
    virtual glm::vec3 getNormal(const glm::vec3& point) const override;

    /**
     * @brief Метод получения текстуры цилиндра в заданной точке.
     * @param point Точка, в которой нужно получить текстуру.
     * @return Цвет текстуры в заданной точке.
     */
    virtual Color getTexture(const glm::vec3& point) const override;
};
