from raytracing.math.Vector import Vector
import math 

class Line:
    def __init__(self, startPoint = Vector(), endPoint = Vector()):
        self._startPoint = startPoint
        self._endPoint = endPoint

    # Метод для вычисления длины линии
    def length(self):
        # Вычисляем расстояние между начальной точкой (start_point) и конечной точкой (end_point)
        return math.sqrt((self._endPoint.x - self._startPoint.x) ** 2 + 
                         (self._endPoint.y - self._startPoint.y) ** 2 + 
                         (self._endPoint.z - self._startPoint.z) ** 2)
    
    def __str__(self):
        return f"Line(Start Point {self._startPoint}, End Point {self._endPoint})"

    def __repr__(self):
        return f"Line({self._startPoint}, {self._endPoint})"
    
    # Статический метод для создания объекта класса Line из объекта класса Ray
    @staticmethod
    def from_ray(ray):
        return Line(ray.origin, ray.point_at_parameter(1))