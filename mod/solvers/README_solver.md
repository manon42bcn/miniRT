# Ray Tracing Solver Library #

Some resources to better understanding of the solvers library:
- https://www.scratchapixel.com
- https://raytracing.github.io
- https://computergraphics.stackexchange.com
- https://www.youtube.com/watch?v=Qz0KTGYJtUk

## Features ##

- Robust Solvers: From basic geometries to composite objects, our solvers got you covered.
- Error Handling: Graceful identification and reporting of computational and object-definition anomalies.
- Optimized for Performance: Minimize computational overhead with algorithms optimized for speed.

---

## Available Solvers ##

### 1. Basic Shapes ###
Some basic shapes are beyond mandatory subject.
- Sphere: double sphere_solver(t_v3d origin, t_v3d dir, t_obj \*sph);
- Plane: double plane_solver(t_v3d origin, t_v3d dir, t_obj \*obj);
- Cylinder: double cylinder_solver(t_v3d from, t_v3d dir, t_obj \*cyl);
- Square: double square_solver(t_v3d origin, t_v3d dir, t_obj \*sqr);
- Triangle: double triangle_solver(t_v3d origin, t_v3d dir, t_obj \*trg);

### 2. Composite Shapes ###
- Cube: double cube_solver(t_v3d origin, t_v3d dir, t_obj \*obj);
- Pyramid: double pyramid_solver(t_v3d origin, t_v3d dir, t_obj \*obj);

## Usage ##

Just like any other C library, include the appropriate header file. 
- \#include "ray_tracing_solver.h"
Depending on the geometric object, call the corresponding solver.