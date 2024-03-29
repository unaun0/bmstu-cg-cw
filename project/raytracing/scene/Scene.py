from raytracing.scene.SceneObject import SceneObject
from raytracing.rendering.LightSource import LightSource
from raytracing.rendering.Camera import Camera

class Scene:
    def __init__(self):
        self._sceneObjects = []     # Объекты сцены
        self._lightSources = []     # Источники света
        self.camera = Camera()      # Камера
    
    # Метод добавления объекта в сцену
    def addObject(self, scene_object: SceneObject):
        self._sceneObjects.append(scene_object)
    
    # Метод добавления источника света в сцену
    def addLight(self, light_source: LightSource):
        self.lightSources.append(light_source)
    
    # Метод для рендеринга сцены
    def render(self):
        pass

    # Очищение сцены
    def clear(self):
        self._sceneObjects.clear()
        self._lightSources.clear()
        del self.camera
        