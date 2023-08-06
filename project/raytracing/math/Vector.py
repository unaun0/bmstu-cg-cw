import math

class Vector:
    def __init__(self, x = 0, y = 0, z = 0):
        self._x = x
        self._y = y
        self._z = z

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        self._x = value

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        self._y = value

    @property
    def z(self):
        return self._z

    @z.setter
    def z(self, value):
        self._z = value

    # Перегрузка оператора доступа к элементу объекта через квадратные скобки ([])
    def __getitem__(self, i):
        return [self._x, self._y, self._z][i]
    
    # Оператор умножения на скаляр
    def __mul__(self, scalar):
        return Vector(self._x * scalar, self._y * scalar, self._z * scalar)
    
    # Оператор сложения векторов
    def __add__(self, vect):
        return Vector(self._x + vect.x, self.y + vect.y, self.z + vect.z)

    # Оператор вычитания векторов
    def __sub__(self, vect):
        return Vector(self._x - vect.x, self._y - vect.y, self._z - vect.z)

    # Оператор унарного минуса
    def __neg__(self):
        return Vector(-self._x, -self._y, -self._z)
    
     # Оператор сложения векторов
    def add(self, scalar):
        return Vector(self._x + scalar, self.y + scalar, self.z + scalar)

    # Оператор сложения векторов
    def sub(self, scalar):
        return Vector(self._x - scalar, self.y - scalar, self.z - scalar)
    
    # Умножение векторов (векторное произведение)
    def cross(self, v):
        cross_x = self._y * v.z - self._z * v.y
        cross_y = self._z * v.x - self._x * v.z
        cross_z = self._x * v.y - self._y * v.x
        return Vector(cross_x, cross_y, cross_z)

    # Умножение векторов (скалярное произведение)
    def dot(self, v):
        return self._x * v.x + self._y * v.y + self._z * v.z

    # Вычисления нормы (длины) вектора
    def norm(self):
        return math.sqrt(self._x * self._x + self._y * self._y + self._z * self._z)

    # Нормализация вектора
    def normalized(self):
        n = self.norm()
        return Vector(self._x / n, self._y / n, self._z / n)
    
    # Перегрузка оператора представления объекта в виде строки
    def __repr__(self):
        return f"Vector({self._x}, {self._y}, {self._z})"
    
    # Перегрузка оператора сравнения (==) для векторов.
    def __eq__(self, other):
        return self._x == other.x and self.y == other.y and self.z == other.z
    
    # Перегрузка оператора сравнения (!=) для векторов
    def __ne__(self, other):
        return not self.__eq__(other)

