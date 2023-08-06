from raytracing.math.Vector import Vector
from raytracing.render.Color import Color

class LightSource:
    def __init__(self, position = Vector(), color = Vector(255, 255, 255)):
        self._position = position
        self._color = color
    
    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, value):
        self._position = value

    @property
    def color(self):
        return self._color

    @color.setter
    def color(self, value):
        self._color = value
