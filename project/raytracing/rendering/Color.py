class Color:
    def __init__(self, red = 0, green = 0, blue = 0):
        self._red = red
        self._green = green
        self._blue = blue

    def _validate_color_value(func):
        def inner(self, value):
            if 0 <= value <= 255:
                return func(self, value)
            else:
                raise ValueError("Color value must be between 0 and 255")
        return inner

    @property
    def red(self):
        return self._red

    @property
    def green(self):
        return self._green

    @property
    def blue(self):
        return self._blue

    @red.setter
    @_validate_color_value
    def red(self, value):
        self._red = value

    @green.setter
    @_validate_color_value
    def green(self, value):
        self._green = value

    @blue.setter
    @_validate_color_value
    def blue(self, value):
        self._blue = value

    @property
    def rgb(self):
        return self._red, self._green, self._blue

    def __str__(self):
        return f"Color(R={self._red}, G={self._green}, B={self._blue})"

    def __repr__(self):
        return f"Color({self._red}, {self._green}, {self._blue})"