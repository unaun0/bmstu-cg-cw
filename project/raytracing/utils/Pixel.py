from raytracing.rendering.Color import Color

class PixelData:
    def __init__(self, color = Color(), depth = 0.0, emission = 0.0):
        self._color = color
        self._depth = depth
        self._emission = emission

    @property
    def color(self):
        return self._color

    @color.setter
    def color(self, value):
        # Можно добавить дополнительные проверки или преобразования при установке цвета
        self._color = value

    @property
    def depth(self):
        return self._depth

    @depth.setter
    def depth(self, value):
        self._depth = value

    @property
    def emission(self):
        return self._emission

    @emission.setter
    def emission(self, value):
        self._emission = value
