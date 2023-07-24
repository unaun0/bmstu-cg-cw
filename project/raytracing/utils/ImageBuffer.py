import numpy as np
import copy

class ImageBuffer:
    def __init__(self, width, height):
        self._width = width
        self._height = height
        # Создание буфера пикселей с помощью NumPy массива
        self._Image = np.empty((width, height), dtype=np.object)
        self._depthBuffer = np.full((width, height), float('inf'), dtype=float)

    def setPixel(self, x, y, pixel):
        pass

    def resize(self):
        pass

    def clone(self):
        pass