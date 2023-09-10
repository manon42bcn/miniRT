# miniRT Parser Library #
The miniRT Parser Library is a dedicated module for extracting, interpreting, and validating data from scene description files in the miniRT project. The library ensures that every object, camera, light, and scene setting is correctly parsed, verified, and represented in memory.

## Features ##
- Robust Error Handling: The library is equipped to identify and alert on various forms of incorrect input, ensuring the integrity of data ingested into the renderer.
- Object Parsing: Dedicated parsers for various objects like spheres, planes, and cylinders.
- Camera and Light Parsing: Specialized functions for cameras and lights, handling both their positional and characteristic data.
- Color Parsing: Extracts RGB color data in a consistent format for rendering.
- BONUS Features: Includes additional functionalities when compiled with the BONUS directive. BONUS behaviour is mainly controlled by parse library.
To get all the details, please read docs/en.subject.md.

## Key Functions ##
- closer_object(t_cmr \*camera, t_obj \*obj): Determines the closest object to a given camera. Utilizes ft_distance_v3d() to measure distances.
- check_common(t_mrt \*mrt, int last): Verifies and extracts shared object attributes such as color and additional properties if in BONUS mode.
- get_v3d(t_mrt \*mrt, char \*line, int mode): Parses 3D vector data (x, y, z) from the input, with error checks for vector normalization if required.
- inp_sphere(t_mrt \*mrt): Parses specific attributes for spheres such as elm.sph.centre (center) and elm.sph.radius (radius) from the scene description.
- inp_plane(t_mrt \*mrt): Processes plane attributes, including elm.pl.centre (center) and elm.pl.orient (orientation).
- inp_cylinder(t_mrt \*mrt): Extracts cylinder data, including its center (elm.cyl.centre), orientation (elm.cyl.dir), radius, and height.
- inp_ambient(t_mrt \*mrt): Extracts the scene's ambient lighting information, defining brightness (scn.bright) and color (scn.amb_rgb).
- inp_camera(t_mrt \*mrt): Parses camera data, setting position (cmr->position), direction (cmr->dir), and field of view (cmr->inp_fov and cmr->fov).
- inp_light(t_mrt \*mrt): Parses light source data, detailing origin (scn.light->origin), brightness ratio (scn.light->bright), and color (scn.light->color).
- inp_resolution(t_mrt \*mrt): Determines the resolution for rendering, specifying width (scn.w_x) and height (scn.w_y).
- clear_all(t_mrt \*mrt, int status, int (\*win)(void \*, void \*), int (\*img)(void \*, void \*)): Frees all dynamically allocated memory associated with the parsed scene and closes the file if open.

## Usage ##
- Initialize the main structure (t_mrt).
- Call readfile_parser() with the path to your scene description file.
- The library will parse each line, populating the t_mrt structure with objects, cameras, lights, and settings for your scene.
- Handle any errors thrown by the parser.
- Use the parsed data in your rendering module.