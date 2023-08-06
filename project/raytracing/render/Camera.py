from raytracing.math.Vector import Vector

class Camera:
    def __init__(self, position = Vector(), direction = Vector(), fov = 1.05):
        self._position = position
        self._direction = direction
        self._fov = fov
        self._right = self.direction.cross(Vector(0, 1, 0))
        self._up = self._right.cross(self.direction)

    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, pos):
        self._position = pos

    @property
    def direction(self):
        return self._direction

    @direction.setter
    def direction(self, direction):
        self._direction = direction
        self._right = self.direction.cross(Vector(0, 1, 0))
        self._up = self._right.cross(self.direction)

    @property
    def right(self):
        return self._right

    @property
    def up(self):
        return self._up

    @property
    def fov(self):
        return self._fov

    @fov.setter
    def fov(self, fov):
        self._fov = fov
    
    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, pos):
        self._position = pos
    
    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, pos):
        self._position = pos

    def translate(self, vect):
        self._position += vect
