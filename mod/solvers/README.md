# Ray Tracing Solver Module #

Some resources to better understanding of the solvers library:
- https://www.scratchapixel.com
- https://raytracing.github.io
- https://computergraphics.stackexchange.com
- https://www.youtube.com/watch?v=Qz0KTGYJtUk

## Features ##

- Robust Solvers: From basic geometries to composite objects, our solvers got you covered.
- Error Handling: Graceful identification and reporting of computational and object-definition anomalies.
- Optimized for Performance: Minimize computational overhead with algorithms optimized for speed.

## Functions

### Sphere Solver

- **Function:** `double sphere_solver(t_v3d origin, t_v3d dir, t_sphere sph)`
- **Description:** Calculates the intersection point of a ray with a sphere defined by its center and radius.
- **Normal:** `t_v3d sphere_normal(t_v3d dir, t_v3d hit, t_inter *inter)`
- **Description:** Calculates the normal vector at the point of intersection on the sphere's surface.

### Cylinder Solver

- **Function:** `double cylinder_solver(t_v3d from, t_v3d dir, t_cylinder cyl, t_inter *inter)`
- **Description:** Calculates the intersection point of a ray with a cylinder, accounting for its height and caps.
- **Normal:** `t_v3d cylinder_normal(t_v3d dir, t_v3d hit, t_inter *inter)`
- **Description:** Calculates the normal vector at the point of intersection on the cylinder's surface.

### Plane Solver

- **Function:** `double plane_solver(t_v3d origin, t_v3d dir, t_plane pl)`
- **Description:** Calculates the intersection point of a ray with a plane defined by its center and orientation.
- **Normal:** `t_v3d plane_normal(t_v3d dir, t_v3d hit, t_inter *inter)`
- **Description:** Calculates the normal vector for a point of intersection on the plane's surface.

### Rectangle Solver

- **Function:** `double rectangle_solver(t_v3d origin, t_v3d dir, t_rectangle rc)`
- **Description:** Calculates the intersection point of a ray with a rectangle defined by its center, orientation, width, and height.
- **Normal:** `t_v3d rectangle_normal(t_v3d dir, t_v3d hit, t_inter *inter)`
- **Description:** Calculates the normal vector at the point of intersection on the rectangle's surface.

### Triangle Solver

- **Function:** `double triangle_solver(t_v3d origin, t_v3d dir, t_triangle trg)`
- **Description:** Calculates the intersection point of a ray with a triangle defined by its vertices and normal direction.
- **Normal:** `t_v3d triangle_normal(t_v3d dir, t_v3d hit, t_inter *inter)`
- **Description:** Calculates the normal vector at the point of intersection on the triangle's surface.

### Ellipsoid Solver

- **Function:** `double ellipsoid_solver(t_v3d origin, t_v3d dir, t_ellip elp)`
- **Description:** Calculates the intersection point of a ray with an ellipsoid defined by its center and radii.
- **Normal:** `t_v3d ellipsoid_normal(t_v3d dir, t_v3d hit, t_inter *inter)`
- **Description:** Calculates the normal vector at the point of intersection on the ellipsoid's surface.

## How Solvers Work

Solvers play a crucial role in 3D rendering by finding the points where rays intersect with geometric objects. These intersections are fundamental for rendering realistic scenes, determining shadows, and implementing reflections and refractions.

When a ray intersects with an object, the solver calculates the intersection point and the normal vector at that point. The normal vector is essential for shading calculations, such as determining how light interacts with the surface.

## Importance of Normals

In the context of a ray tracing project like MiniRT, normals are crucial for various tasks such as shading, lighting calculations, and determining how light interacts with the surfaces of 3D objects. Here's why normals are essential:

- **Shading:** Normals play a central role in shading computations. They help determine how light rays interact with object surfaces, influencing the color and intensity of each pixel in the rendered image. By understanding the orientation of normals, the renderer can simulate effects like diffuse, specular, and ambient reflection.

- **Lighting Calculations:** Normals are used to calculate the direction and intensity of light at each point on the surface. They are essential for simulating realistic lighting, casting shadows, and creating highlights and shadows.

- **Surface Interactions:** Normals guide the behavior of light rays when they hit an object. Depending on the angle between the incoming ray and the normal vector at the point of intersection, the renderer can determine whether the surface acts as a mirror, refracts light, or exhibits different reflective properties.

In summary, normals are a fundamental part of the rendering process in a ray tracing project. They allow for realistic lighting, shading, and interactions with surfaces, which ultimately contribute to the creation of visually compelling 3D scenes.

Understanding and correctly computing normals is essential for achieving high-quality and realistic renderings in MiniRT and similar ray tracing applications.

## Additional Information

- The `t_inter` structure is used to store information about the intersection, including the normal vector at the intersection point, whether the ray is inside or outside the object, and other relevant data.

- Some solvers also handle special cases based on object properties, such as caps for cylinders or specific textures.

- These solvers are an essential part of the MiniRT project, which aims to create a simple ray tracing renderer.


## Additional Information

- The `t_inter` structure is used to store information about the intersection, including the normal vector at the intersection point and whether the ray is inside or outside the object.

- Some solvers check for specific object properties, such as caps for cylinders or the texture flag, to handle special cases or materials.

- These solvers are an essential part of the MiniRT project, which aims to create a simple ray tracing renderer.
