from raytracing.math.Vector import Vector

class Renderer:
    GLOBAL_ILLUMINATION = 0.2
    SKY_EMISSION = 0.5
    MAX_REFLECTION_BOUNCES = 5
    SHOW_SKYBOX = True

    @staticmethod
    def get_normalized_screen_coordinates(x, y, width, height):
        u, v = 0.0, 0.0
        if width > height:
            u = (x - width / 2 + height / 2) / height * 2 - 1
            v = -y / height * 2 + 1
        else:
            u = x / width * 2 - 1
            v = -((y - height / 2 + width / 2) / width * 2 - 1)
        return u, v

    @staticmethod
    def get_diffuse_brightness(scene, hit):
        scene_light = scene.light
        light_direction = (scene_light.position - hit.position).normalize()
        light_blocker = scene.raycast(Ray(scene_light.position, light_direction))
        if light_blocker is not None and light_blocker.solid is not hit.solid:
            return Renderer.GLOBAL_ILLUMINATION
        else:
            return max(Renderer.GLOBAL_ILLUMINATION,
                       min(1.0, Vector3.dot(hit.normal, scene_light.position - hit.position)))

    @staticmethod
    def get_specular_brightness(scene, hit):
        hit_pos = hit.position
        camera_direction = (scene.camera.position - hit_pos).normalize()
        light_direction = (hit_pos - scene.light.position).normalize()
        light_cos = Vector3.dot(light_direction, hit.normal)
        light_reflection_vector = light_direction - (hit.normal.multiply(2 * light_cos))
        specular_factor = max(0.0, min(1.0, Vector3.dot(light_reflection_vector, camera_direction)))
        return specular_factor ** 2 * hit.solid.reflectivity

    @staticmethod
    def refract_ray(I, n, cos, theataT, theataI):
        if cos < 0:
            return Renderer.refract_ray(I, n, -cos, theataI, theataT)
        eta = theataI / theataT
        k = 1 - eta ** 2 * (1 - cos ** 2)
        if k < 0:
            return Vector3(1.0, 0.0, 0.0)
        return I.multiply(eta) + n.multiply(eta * cos - math.sqrt(k))

    @staticmethod
    def compute_pixel_info_at_hit(scene, hit, recursion_limit):
        hit_pos = hit.position
        ray_dir = hit.ray.direction
        hit_solid = hit.solid
        hit_color = hit_solid.get_texture_color(hit_pos.subtract(hit_solid.position))
        brightness = Renderer.get_diffuse_brightness(scene, hit)
        specular_brightness = Renderer.get_specular_brightness(scene, hit)
        reflectivity = hit_solid.reflectivity
        emission = hit_solid.emission
        fractivity = hit_solid.fractivity

        reflection = PixelData(Color.black(), float('inf'), 0.0)
        reflection_vector = ray_dir - (hit.normal.multiply(2 * Vector3.dot(ray_dir, hit.normal)))
        reflection_ray_origin = hit_pos.add(reflection_vector.multiply(0.001))
        reflection_hit = None
        if recursion_limit > 0:
            reflection_hit = scene.raycast(Ray(reflection_ray_origin, reflection_vector))
        if reflection_hit is not None:
            reflection = Renderer.compute_pixel_info_at_hit(scene, reflection_hit, recursion_limit - 1)
        else:
            sb_color = scene.skybox.get_color(reflection_vector)
            reflection = PixelData(sb_color, float('inf'), sb_color.luminance * Renderer.SKY_EMISSION)

        refract_ray = Renderer.refract_ray(ray_dir, hit.normal, Vector3.dot(ray_dir, hit.normal), fractivity, 1.0)
        refract_ray_origin = hit_pos.add(refract_ray.multiply(0.001))
        refract_hit = None
        if recursion_limit > 0:
            refract_hit = scene.raycast(Ray(refract_ray_origin, refract_ray))
        refraction = PixelData(Color.black(), float('inf'), 0.0)
        if refract_hit is not None:
            refraction = Renderer.compute_pixel_info_at_hit(scene, refract_hit, recursion_limit - 1)
        else:
            sb_color = scene.skybox.get_color(refract_ray)
            refraction = PixelData(sb_color, float('inf'), sb_color.luminance * Renderer.SKY_EMISSION)

        pixel_color = (Color.lerp(hit_color, reflection.color, reflectivity)  # Reflected color
                       .multiply(brightness)  # Diffuse lighting
                       .add(specular_brightness)  # Specular lighting
                       .add(reflection.color.multiply(reflectivity * emission))  # Indirect illumination
                       .add(refraction.color.multiply(fractivity)))  # Refraction

        depth_pixel = Vector3.distance(scene.camera.position, hit_pos)
        pixel_emission = min(1.0, emission + reflection.emission * reflectivity + specular_brightness + fractivity)

        return PixelData(pixel_color, depth_pixel, pixel_emission)

    @staticmethod
    def compute_pixel_info(scene, u, v):
        eye_pos = Vector3(0.0, 0.0, (-1 / math.tan(math.radians(scene.camera.fOV / 2.0))))
        cam = scene.camera
        ray_dir = Vector3(u, v, 0.0).subtract(eye_pos).normalize().rotate_yp(cam.yaw, cam.pitch)
        hit = scene.raycast(Ray(eye_pos.add(cam.position), ray_dir))
        if hit is not None:
            return Renderer.compute_pixel_info_at_hit(scene, hit, Renderer.MAX_REFLECTION_BOUNCES)
        elif Renderer.SHOW_SKYBOX:
            sb_color = scene.skybox.get_color(ray_dir)
            return PixelData(sb_color, float('inf'), sb_color.luminance * Renderer.SKY_EMISSION)
        else:
            return PixelData(Color.black(), float('inf'), 0.0)

    @staticmethod
    def render_scene(scene, gfx, width, height, resolution):
        block_size = int(1 / resolution)
        start = time.time()
        for x in range(0, width, block_size):
            for y in range(0, height, block_size):
                u, v = Renderer.get_normalized_screen_coordinates(x, y, width, height)
                pixel_data = Renderer.compute_pixel_info(scene, u, v)
                color = pixel_data.color.to_rgb()
                gfx[x:x + block_size, y:y + block_size] = color
        print((time.time() - start))
