from raytracing.math.Vector import Vector
from raytracing.render.Color import Color
from raytracing.render.Material import Material

class RenderState:
    def __init__(self, 
                 position = Vector(), 
                 normal = Vector, 
                 t = float, 
                 color = Color(), 
                 material = Material()):
        self._position = position
        self._normal = normal
        self._t = t
        self._color = color
        self._material = material
    
    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, position = Vector()):
        self._position = position
    
    @property
    def normal(self):
        return self._normal

    @normal.setter
    def normal(self, normal = Vector()):
        self._normal = normal
    
    @property
    def t(self):
        return self._t

    @t.setter
    def t(self, t = float()):
        self._t = t
    
    @property
    def color(self):
        return self._color

    @color.setter
    def color(self, color = Color()):
        self._color = color
    
    @property
    def material(self):
        return self._material

    @t.setter
    def material(self, material = Material):
        self._material = material
    