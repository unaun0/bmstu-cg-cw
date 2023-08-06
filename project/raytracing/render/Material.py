from raytracing.math.Vector import Vector

class Material:
    def __init__(self, refractive_index = 1, albedo = [0.8, 0.2, 0.0, 0.0], diffuse_color = Vector(0, 255, 0), specular_exponent = 1):
        self._refractive_index = refractive_index       # Показатель преломления материала
        self._specular_exponent = specular_exponent     # Коэффициент блика материала
        self._diffuse_color = diffuse_color             # Цвет диффузного освещения материала
        self._albedo = albedo                           # Веса отраженного света, диффузного цвета, 
                                                        #   цвета зеркальных бликов и цвета преломленного света.
        
    @property
    def refractive_index(self):
        return self._refractive_index

    @refractive_index.setter
    def refractive_index(self, value):
        self._refractive_index = value

    @property
    def albedo(self):
        return self._albedo

    @albedo.setter
    def albedo(self, value):
        self._albedo = value

    @property
    def diffuse_color(self):
        return self._diffuse_color

    @diffuse_color.setter
    def diffuse_color(self, value):
        self._diffuse_color = value

    @property
    def specular_exponent(self):
        return self._specular_exponent

    @specular_exponent.setter
    def specular_exponent(self, value):
        self._specular_exponent = value

    # Перегрузки оператора представления объекта в виде строки
    def __repr__(self):
        return f"Material(refractive_index={self._refractive_index}, specular_exponent={self._specular_exponent}, " \
               f"diffuse_color={self._diffuse_color}, albedo={self._albedo})"

