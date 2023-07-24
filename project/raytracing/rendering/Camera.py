from raytracing.math.Vector import Vector

class Camera:
    def __init__(self, position = Vector(), target = Vector(0, 0, -1), fov = 1.05):
        self._position = position   # Позиция
        self._target = target       # Цель / направление
        self._fov = fov             # Угол обзора

    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, pos):
        self._position = pos

    @property
    def target(self):
        return self._target

    @target.setter
    def target(self, target):
        self._target = target

    @property
    def fov(self):
        return self._fov

    @fov.setter
    def fov(self, fov):
        self._fov = fov

    def translate(self, vect):
        self._position += vect
