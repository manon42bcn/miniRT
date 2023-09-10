
# Hooks Module for mrt #

This library provides functionality to handle user input, enabling dynamic transformations on 3D objects like spheres, cylinders, lights, and the camera in a scene. Each function responds to specific key presses, causing updates in the runtime structure and subsequently triggering a re-render of the scene.

To better understanding of hooks functionality:
* https://harm-smits.github.io/42docs/libs/minilibx/hooks.html

## Key Functionality ##

* Dynamic Transformations: Apply translations, rotations, and size adjustments to the scene's 3D objects.
* Camera Handling: Modify camera position, orientation, and perspective based on user input.
* User Feedback: Informative console messages guide the user's input experience.
* Integrated Event Loop: Seamless integration with the event loop, ensuring that user input is constantly monitored and processed.

## Function Prototypes and functionality ##

- Common: 
  - void	load_hooks(t_mrt \*mrt);
- Windows handler:
  - int	window_handler(t_mrt \*mrt);

- Common rotation functions for 3D vectors
  * t_v3d	rotate_x(t_v3d old, double angle);
  * t_v3d	rotate_y(t_v3d old, double angle);
  * t_v3d	rotate_z(t_v3d old, double angle);

- Camera-related functions:
  - Rotate over closest object:
    * void	camera_closest_y(t_mrt \*mrt, int key_dir);
    * void	camera_closest_x(t_mrt \*mrt, int key_dir);
    * void	camera_closest_z(t_mrt \*mrt, int key_dir);
  - Rotate over a fixed orbit:
    * void	camera_orbit_y(t_mrt \*mrt, int key_dir);
    * void	camera_orbit_x(t_mrt \*mrt, int key_dir);
    * void	camera_orbit_z(t_mrt \*mrt, int key_dir);

- Cylinders related functions:
  - Translation:
    * void	cylinder_y_translation(t_mrt \*mrt, int key_dir);
    * void	cylinder_x_translation(t_mrt \*mrt, int key_dir);
    * void	cylinder_z_translation(t_mrt \*mrt, int key_dir);
  - Rotation:
    * void	cylinder_rotation_x(t_mrt \*mrt, int key_dir);
    * void	cylinder_rotation_y(t_mrt \*mrt, int key_dir);
    * void	cylinder_rotation_z(t_mrt \*mrt, int key_dir);
  - Sizes:
    * void	cylinder_diam(t_mrt \*mrt, int key_dir);
    * void	cylinder_height(t_mrt \*mrt, int key_dir);

- Light-related functions
  - Rotation:
    * void	light_rotation_x(t_mrt \*mrt, int key_dir);
    * void	light_rotation_y(t_mrt \*mrt, int key_dir);
    * void	light_rotation_z(t_mrt \*mrt, int key_dir);

- Sphere related functions
  - Translation:
    * void	sphere_y_translation(t_mrt \*mrt, int key_dir);
    * void	sphere_x_translation(t_mrt \*mrt, int key_dir);
    * void	sphere_z_translation(t_mrt \*mrt, int key_dir);
  - Size:
    * void	sphere_diam(t_mrt \*mrt, int key_dir);

- Informative and handler functions
  * static inline void	axis_informator(int key);
  * static inline void	handler_informator(int key);
  * static inline int	action_handler(t_mrt \*mrt, int key);
  * static inline int	change_camera(t_mrt \*mrt);
  * int	keys_handler(int key, t_mrt \*mrt);

## Usage ##

To use a hook you have to use a particular key combinatios, according this table:

| Description               | Key1 | Key2 | Key3 |
|---------------------------|------|------|------|
| Cylinder Y translation    | C    | T    | Y    |
| Cylinder X translation    | C    | T    | X    |
| Cylinder Z translation    | C    | T    | Z    |
| Cylinder Diameter         | C    | D    | Enter|
| Cylinder Height           | C    | H    | Enter|
| Sphere Y translation      | S    | T    | Y    |
| Sphere X translation      | S    | T    | X    |
| Sphere Z translation      | S    | T    | Z    |
| Sphere Diameter           | S    | D    | Enter|
| Camera X closest obj      | E    | N    | Y    |
| Camera Y closest obj      | E    | N    | X    |
| Camera Z closest obj      | E    | N    | Z    |
| Camera Y orbit            | E    | O    | Y    |
| Camera X orbit            | E    | O    | X    |
| Camera Z orbit            | E    | O    | Z    |
| Cylinder Y Rotation       | C    | R    | Y    |
| Cylinder X Rotation       | C    | R    | X    |
| Cylinder Z Rotation       | C    | R    | Z    |
| Light Y Rotation          | L    | R    | Y    |
| Light X Rotation          | L    | R    | X    |
| Light Z Rotation          | L    | R    | Z    |
| Camera Free (Y)           | E    | F    | Y    |
| Camera Free (Enter)       | E    | F    | Enter|

the order is not important. If you make a mistake or want to chance the behaviour of the hook, press esc.
After set a particular behaviour, you can apply them using key arrows (up-down-right-left).









