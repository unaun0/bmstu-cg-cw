#include "Light.hpp"

/**
 * @brief Конструктор для инициализации позиции источника света.
 * 
 * @param position Позиция источника света в трёхмерном пространстве.
 */
Light::Light(const glm::vec3& position)
    : position(position) {}

/**
 * @brief Возвращает текущую позицию источника света.
 * 
 * @return Текущая позиция источника света в трёхмерном пространстве.
 */
const glm::vec3& Light::getPosition() const {
    return position;
}

/**
 * @brief Устанавливает новую позицию источника света.
 * 
 * @param pos Новая позиция источника света в трёхмерном пространстве.
 */
void Light::setPosition(const glm::vec3& pos) {
    position = pos;
}
