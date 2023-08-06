'''
import sys
from PyQt5.QtWidgets import QApplication
from views.mainwindow import MainWindow        

def main():
    app = QApplication(sys.argv)
    window = MainWindow() 
    window.show()
    app.exec_()

if __name__ == '__main__': 
    main()
'''

from raytracing.geometry.Sphere import Sphere
from raytracing.render.Camera import Camera
from raytracing.render.LightSource import LightSource
from raytracing.scene.Scene import Scene
from raytracing.math.Vector import Vector
from raytracing.render.Material import Material
from raytracing.render.Color import Color
from raytracing.math.Ray import Ray
import numpy as np

plastic = Material(1, [0.8, 0.2, 0.0, 0.0], Vector(0, 255, 0), 1)
center = Vector(0, 0, 0)

sphere = Sphere(center, 10, plastic)
camera = Camera(Vector(0, 5, -5), Vector(0, 0, 0), 1.05)
light = LightSource(Vector(0, 5, -5), Vector(255, 255, 255))
scene = Scene()
scene.addLight(light)
scene.addObject(sphere)
scene.addCamera(camera)

W = 640
H = 480

sampleCount = 32
maxBounces = 32

for y in range(H):
    for x in range(W):
        color = Vector(0, 0, 0)
        limitingFactor = max(W/2, H/2)
        for sample in range(sampleCount):
            horizontalCoefficient = (x + np.random.uniform() - W / 2) / limitingFactor
            verticalCoefficient = (y + np.random.uniform() - H / 2) / limitingFactor
            ray = Ray(
                position = scene.camera.position,
                direction = scene.camera.direction + (scene.camera.right * horizontalCoefficient) + (scene.camera.up * verticalCoefficient)
                )
            color += Vector(0, 0, 0)
            print(x, y, color)
                
                


