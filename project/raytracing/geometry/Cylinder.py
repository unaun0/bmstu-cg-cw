from raytracing.scene.SceneObject import SceneObject
from raytracing.math.Vector import Vector
from raytracing.render.Material import Material

class Cylinder(SceneObject):
    def __init__(self, center = Vector(), radius = 1, height = 1, material = Material()):
        super().__init__()
        self._center = center
        self._radius = radius
        self._height = height
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
    def height(self):
        return self._height

    @height.setter
    def height(self, value):
        self._height = value

    @property
    def material(self):
        return self._material

    @material.setter
    def material(self, value):
        self._material = value

    # Метод для проверки пересечения луча с цилиндром
    def ray_intersect(self, orig, dir):
        a = dir.x ** 2 + dir.z ** 2
        if abs(a) < 1e-6:
            return False, 0, 0

        b = 2 * (dir.x * (orig.x - self.center.x) + dir.z * (orig.z - self.center.z))
        c = (orig.x - self.center.x) ** 2 + (orig.z - self.center.z) ** 2 - self.radius ** 2

        discriminant = b ** 2 - 4 * a * c

        if discriminant < 0:
            return False, 0, 0

        t0 = (-b - np.sqrt(discriminant)) / (2 * a)
        t1 = (-b + np.sqrt(discriminant)) / (2 * a)

        y0 = orig.y + t0 * dir.y
        y1 = orig.y + t1 * dir.y

        if y0 < self.center.y or y0 > self.center.y + self.height:
            t0 = float('inf')
        if y1 < self.center.y or y1 > self.center.y + self.height:
            t1 = float('inf')

        t = min(t0, t1)
        if t < 0:
            return False, 0, 0

        pt = orig + dir * t
        normal = Vector(pt.x - self.center.x, 0, pt.z - self.center.z).normalized()
        return True, t, normal
