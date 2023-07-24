from raytracing.math.Vector import Vector
import math 

class Ray:
    def __init__(self, origin = Vector(), direction = Vector()):
        self._origin = origin
        self._direction = direction.normalize()

    @property
    def origin(self):
        return self._origin

    @origin.setter
    def origin(self, origin):
        self._origin = origin

    @property
    def direction(self):
        return self._direction

    @direction.setter
    def direction(self, direction):
        self._direction = direction.normalize()

    # Метод для нахождения точки на луче по параметру t
    def point_at_parameter(self, t):
        return self._origin + self._direction * t
    
    # Статический метод для создания объекта класса Ray из объекта класса Line
    @staticmethod
    def from_line(line):
        return Ray(line.pointA, line.pointB - line.pointA)
    
    class RayHit:
        def __init__(self, ray, sceneObject, position):
            self._ray = ray
            self._sceneObject = sceneObject
            self._position = position
            self._normal = sceneObject.getNormal(position)