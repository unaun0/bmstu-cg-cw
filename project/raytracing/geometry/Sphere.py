from raytracing.scene.SceneObject import SceneObject
from raytracing.math.Vector import Vector
from raytracing.render.Material import Material
from raytracing.render.Color import Color
import math

class Sphere(SceneObject):
    def __init__(self, center = Vector(), radius = 1, material = Material()):
        super().__init__()
        self._center = center
        self._radius = radius
        self._material = material
    
    @property
    def center(self):
        return self._center

    @center.setter
    def center(self, value):
        self._center = value

    @property
    def radius(self):
        return self._radius

    @radius.setter
    def radius(self, value):
        self._radius = value

    @property
    def material(self):
        return self._material

    @material.setter
    def material(self, value):
        self._material = value

    def hit(self, ray, tMin, tMax, renderState):
        offset = ray.position - self._center

        A = ray.direction.dot(ray.direction)
        B = offset.dot(ray.direction) * 2
        C = offset.dot(offset.dot) - self.radius * self.radius

        discriminant = B * B - 4 * A * C
        if discriminant < 0:
            return False
        root = (-B - math.sqrt(discriminant)) / (2 * A)
        if (root < tMin) or (root > tMax):
            root = (-B + math.sqrt(discriminant)) / (2 * A)
            if (root < tMin) or (root > tMax):
                return False
        
        renderState.t = root
        renderState.pos = ray.position + root * ray.direction
        renderState.normal = (ray.position + root * ray.direction - self.center).normalized()
        renderState.material = self.material

        return True
