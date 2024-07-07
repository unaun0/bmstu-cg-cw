#pragma once

#include <glm/glm.hpp>
#include <algorithm>
#include <stdexcept>

/**
 * @brief Представляет цвет в формате RGB.
 */
class Color {
public:
    float red;   ///< Компонента красного цвета (от 0.0 до 1.0).
    float green; ///< Компонента зелёного цвета (от 0.0 до 1.0).
    float blue;  ///< Компонента синего цвета (от 0.0 до 1.0).

    /**
     * @brief Конструирует объект цвета по заданным компонентам RGB.
     * @param r Красная компонента (от 0.0 до 1.0).
     * @param g Зелёная компонента (от 0.0 до 1.0).
     * @param b Синяя компонента (от 0.0 до 1.0).
     * @throw std::invalid_argument Если какая-либо компонента выходит за пределы диапазона [0.0, 1.0] или является NaN.
     */
    Color(float r, float g, float b);

    /**
     * @brief Умножает текущий цвет на другой цвет.
     * @param other Другой цвет для умножения.
     * @return Новый цвет, полученный в результате умножения компонент RGB.
     */
    Color multiply(const Color& other) const;

    /**
     * @brief Умножает текущий цвет на яркость.
     * @param brightness Яркость (от 0.0 до 1.0).
     * @return Новый цвет, полученный в результате умножения компонент RGB на яркость.
     */
    Color multiply(float brightness) const;

    /**
     * @brief Добавляет другой цвет к текущему цвету.
     * @param other Другой цвет для сложения.
     * @return Новый цвет, полученный в результате сложения компонент RGB.
     */
    Color add(const Color& other) const;

    /**
     * @brief Перегруженный оператор сложения цветов.
     * @param other Другой цвет для сложения.
     * @return Новый цвет, полученный в результате сложения компонент RGB.
     */
    Color operator+(const Color& other) const;

    /**
     * @brief Перегруженный оператор умножения цветов.
     * @param other Другой цвет для умножения.
     * @return Новый цвет, полученный в результате умножения компонент RGB.
     */
    Color operator*(const Color& other) const;

    /**
     * @brief Добавляет к текущему цвету другой цвет.
     * @param other Другой цвет для сложения.
     */
    void addSelf(const Color& other);

    /**
     * @brief Добавляет яркость к текущему цвету.
     * @param brightness Яркость (от 0.0 до 1.0).
     * @return Новый цвет, полученный в результате сложения компонент RGB с яркостью.
     */
    Color add(float brightness) const;

    /**
     * @brief Возвращает цвет в формате ARGB (целое число).
     * @return Цвет в виде целого числа, представляющего ARGB.
     */
    unsigned int getRGB() const;

    /**
     * @brief Вычисляет яркость цвета по формуле Y = 0.2126*R + 0.7152*G + 0.0722*B.
     * @return Яркость цвета.
     */
    float luminance() const;

    /**
     * @brief Создаёт цвет из целого числа ARGB.
     * @param argb Целое число ARGB.
     * @return Цвет, полученный из целого числа ARGB.
     */
    static Color fromInt(int argb);

    /**
     * @brief Выполняет линейную интерполяцию между двумя цветами.
     * @param a Первый цвет (при t=0).
     * @param b Второй цвет (при t=1).
     * @param t Коэффициент интерполяции (от 0 до 1).
     * @return Интерполированный цвет между a и b.
     */
    static Color lerp(const Color& a, const Color& b, float t);

    static const Color BLACK;       ///< Чёрный цвет (0, 0, 0).
    static const Color WHITE;       ///< Белый цвет (1, 1, 1).
    static const Color RED;         ///< Красный цвет (1, 0, 0).
    static const Color GREEN;       ///< Зелёный цвет (0, 1, 0).
    static const Color BLUE;        ///< Синий цвет (0, 0, 1).
    static const Color MAGENTA;     ///< Пурпурный цвет (1, 0, 1).
    static const Color GRAY;        ///< Серый цвет (0.5, 0.5, 0.5).
    static const Color DARK_GRAY;   ///< Тёмно-серый цвет (0.2, 0.2, 0.2).
    static const Color TREE;        ///< Цвет дерева (0.40, 0.26, 0.13).
    static const Color BURGUNDY;    ///< Бургундский цвет (0.55, 0.01, 0.04).
    static const Color CORNSILK;    ///< Цвет кукурузы (1, 0.99, 0.8).
};
