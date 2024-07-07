#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Класс, представляющий камеру в трёхмерной сцене.
 */
class Camera {
private:
    glm::vec3 position; ///< Позиция камеры в трёхмерном пространстве.
    float yaw;          ///< Угол поворота вокруг оси Y (горизонтальный угол).
    float pitch;        ///< Угол поворота вокруг оси X (вертикальный угол).
    float fov;          ///< Угол обзора (Field of View).

public:
    /**
     * @brief Конструктор по умолчанию для инициализации камеры в начальное состояние.
     */
    Camera();

    /**
     * @brief Смещает позицию камеры на указанный вектор.
     * @param vec Вектор смещения камеры.
     */
    void translate(const glm::vec3& vec);

    /**
     * @brief Возвращает текущую позицию камеры.
     * @return Текущая позиция камеры.
     */
    const glm::vec3& getPosition() const;

    /**
     * @brief Устанавливает новую позицию камеры.
     * @param pos Новая позиция камеры.
     */
    void setPosition(const glm::vec3& pos);

    /**
     * @brief Возвращает текущий угол поворота вокруг оси Y (горизонтальный угол).
     * @return Текущий угол поворота вокруг оси Y.
     */
    float getYaw() const;

    /**
     * @brief Устанавливает новый угол поворота вокруг оси Y (горизонтальный угол).
     * @param angle Новый угол поворота вокруг оси Y.
     */
    void setYaw(float angle);

    /**
     * @brief Возвращает текущий угол поворота вокруг оси X (вертикальный угол).
     * @return Текущий угол поворота вокруг оси X.
     */
    float getPitch() const;

    /**
     * @brief Устанавливает новый угол поворота вокруг оси X (вертикальный угол).
     * @param angle Новый угол поворота вокруг оси X.
     */
    void setPitch(float angle);

    /**
     * @brief Возвращает текущий угол обзора камеры.
     * @return Текущий угол обзора камеры.
     */
    float getFOV() const;

    /**
     * @brief Устанавливает новый угол обзора камеры.
     * @param fieldOfView Новый угол обзора камеры.
     */
    void setFOV(float fieldOfView);

    /**
     * @brief Возвращает матрицу вида камеры.
     * @return Матрица вида камеры.
     */
    glm::mat4 getViewMatrix() const;

private:
    /**
     * @brief Возвращает направление взгляда камеры (направление вперёд).
     * @return Направление взгляда камеры в трёхмерном пространстве.
     */
    glm::vec3 getFront() const;
};
