from raytracing.math.Vector import Vector

class LightSource:
    def __init__(self, position = Vector()):
        self._position = position
    
    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, value):
        self._position = value
