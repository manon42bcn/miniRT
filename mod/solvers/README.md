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

---

## Available Solvers

### 1. Basic Shapes
Some basic shapes are beyond mandatory subject.
- Sphere: `double sphere_solver(t_v3d origin, t_v3d dir, t_obj \*sph);`
- Plane: `double plane_solver(t_v3d origin, t_v3d dir, t_obj \*obj);`
- Cylinder: `double cylinder_solver(t_v3d from, t_v3d dir, t_obj \*cyl);`
- Rectangle: `double	rectangle_solver(t_v3d origin, t_v3d dir, t_obj *obj);`
- Triangle: `double triangle_solver(t_v3d origin, t_v3d dir, t_obj \*trg);`

### 2. Composite Shapes
- Box: `double	box_solver(t_v3d origin, t_v3d dir, t_obj *obj);`

### 3. Second Grade Shapes
- Cone: `double	cone_solver(t_v3d origin, t_v3d dir, t_obj *obj)`
- Ellipsoid `double	ellipsoid_solver(t_v3d origin, t_v3d dir, t_obj *obj)`

# Available Normals
Normal calculation. To shape properly an object, the normal of the hitted point over the figure is important. In few words is different if a light hit an object in a 90 degrees angle or 20 degrees angle. The bright of the point will be different.
To objects that have a flat surface, the normal is calculated with common function, but some needs a particular one.

- Get normal: `t_v3d get_normal(t_obj *obj, t_v3d dir, t_v3d hit);`
- Common: `t_v3d	common_normal(t_v3d dir, t_v3d hit, t_obj *obj);`
- Box: `t_v3d box_normal(t_v3d dir, t_v3d hit, t_obj *obj);`
- Cone: `t_v3d cone_normal(t_v3d dir, t_v3d hit, t_obj *obj);`
- Ellipsoid: `t_v3d ellipsoid_normal(t_v3d dir, t_v3d hit, t_obj *obj);`

## Usage ##

Depending on the geometric object, call the corresponding solver.