# Класс SceneObject
from raytracing.math.Vector import Vector
from raytracing.math.Ray import Ray
from raytracing.rendering.Color import Color

class SceneObject:
    def __init__(self):
        pass
    
    def render(self):
        raise NotImplementedError("Метод render должен быть переопределен в производном классе.")
    
    def getNormal(self, point = Vector()):
        raise NotImplementedError("Метод getNormal должен быть переопределен в производном классе.")
    
    def getIntersection(self, point = Ray()):
        raise NotImplementedError("Метод getIntersection должен быть переопределен в производном классе.")
    
    def getColor(self, point = Vector()) -> Color():
        raise NotImplementedError("Метод getColor должен быть переопределен в производном классе.")