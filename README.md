```

                                               @@@@@@@@@@  @@@@@@@@@@@@                 
                                               @@@    @@@@.    %@@@                     
                                               @@@     @@@@    %@@@                     
                                               @@@     @@@@    %@@@                     
                                               @@@@@@@@@@@     %@@@                     
                                               @@@@@@@@@       %@@@                     
                                               @@@   @@@@      %@@@                     
                                                      @@@&     %@@@                     
                          %@@@                 @@@     @@@.    %@@@                     
                          %@@@                 @@@     &@@@    %@@@                     
     ,@@@@@@@@@@@@@@@@@          @@@@@@@@@@                        
     ,@@@.  *@@@%   @@@/  %@@@   @@@@   @@@@   @@@                    
     ,@@@    @@@    @@@/  %@@@   @@@@   @@@@   @@@                     
     ,@@@    @@@    @@@/  %@@@   @@@@   @@@@   @@@                     
     ,@@@    @@@    @@@/  %@@@   @@@@   @@@@   @@@                       
     ,@@@    @@@    @@@/  %@@@   @@@@   @@@@   @@@                        
     ,@@@    @@@    @@@/  %@@@   @@@@   @@@@   @@@                     
```

# miniRT #
A simple Ray Tracing engine created in C. This project uses the MiniLibX, a simple graphics library, to showcase the fundamentals of ray tracing with some bonus features like textures and supersampling.

[Important]
This project was made as part of 42 Barcelona Cursus. You are welcome to clone it and use it as reference, but copy it without understand it is cheat yourself. All project is documented and commented to make it easy to understand.

## Features: ##

- Basic Shapes: The program supports rendering of basic geometric shapes like spheres and cylinders.
- Complex Shapes: supported with bonus version.
- Ray Tracing: Calculates the path taken by rays of light as they travel through the scene.
- Camera Eye Calculations: Adjusts the camera's perspective based on scene parameters.
- MLX Start: Uses the MiniLibX library to initialize the graphical representation of the scene.
- Key Hooks: Interactivity is provided with various key hooks to manipulate the scene in real-time.
- Supersampling: Implements anti-aliasing using supersampling for a better visual output.
- Textures: Supports textures like checkerboards, waves, and rainbows. (Bonus version)
- Refraction & Reflection: Simulates light refraction and reflection based on scene objects. (Bonus version)
- Scene Parsing: Parses a custom scene file format to generate the scene.
- Vector Operations: Provides operations for 3D vectors, supporting calculations required for ray tracing.
- Color Management: Handles RGB color operations and conversions.
- Equation Solvers: Contains solvers for geometric equations, ensuring correct light-object interactions.

## How to Run: ##
- Compile the program using the provided Makefile.
- Run the program with ./miniRT <scene_file.rt>


### RT File: Mandatory Version ###

| COMPONENT      | ID | Values                |
|----------------|----|-----------------------|
| Ambient Light  | A  | (R) (RGB)             |
| Camera         | C  | (C) (N) (FOV)         |
| Light          | L  | (C) (R) (RGB-BNS)     |
| Plane          | pl | (C) (N) (RGB)         |
| Sphere         | sp | (C) (D) (RGB)         |
| Cylinder       | cy | (C) (N) (D) (H) (RGB) |

    - [R] -> Ratio: 0.1 - 1.0.
    - [RGB] -> RGB color: (0-255) R,G,B.
    - [C] -> Coordinates X,Y,Z.
    - [N] -> Normalized 3D-Vector (-1, 1).
    - [FOV] -> Field Of View (0, 180).
    - [D] -> Diameter.
    - [H] -> Height.

To create a scene properly it should have: Ambient Light, Camera, Light and at least one object. All Values are compulsory.
At mandatory version, those components described with uppercase ids (A,C,L) can be declared just one.

### RT File: Bonus Version ###

| COMPONENT     | ID | Values                      |
|---------------|----|-----------------------------|
| Ambient Light | A  | (R) (RGB)                   |
| Camera        | C  | (C) (N) (FOV)               |
| Light         | L  | (C) (R) (RGB)               |
| Plane         | pl | (C) (N) (RGB)               |
| Sphere        | sp | (C) (D) (RGB) (BNS)         |
| Cylinder      | cy | (C) (N) (D) (H) (RGB) (BNS) |
| Cone          | co | (C) (N) (D) (H) (RGB) (BNS) |
| Rectangle     | cy | (C) (N) (W) (H) (RGB) (BNS) |
| Triangle      | tr | (v1) (v2) (v3) (RGB) (BNS)  |
| Box (cuboid)  | bx | (C) (W) (H) (D) (RGB) (BNS) |


    - [R] -> Ratio: 0.1 - 1.0.
    - [RGB] -> RGB color: (0-255) R,G,B.
    - [C] -> Coordinates X,Y,Z.
    - [N] -> Normalized 3D-Vector (-1, 1).
    - [FOV] -> Field Of View (0, 180).
    - [D] -> Diameter.
    - [W] -> Width.
    - [H] -> Height.
    - [v1 - v2 - v3] -> Coordinates of 3 vortex to define a triangle.
    - [BNS] Bonus string, two bonus behaviour can be defined.
        BUMP: to load a bump map. -> xpm:[path/to/xpmmap.xpm]
        TEXTURES: to apply bonus features. -> BNS:[RFC;RFL;SPC;TXT;WL]
            - RFC : Refraction (> 0).
            - RFL : Reflex (> 0).
            - SPC : Specular (> 0).
            - Texture values:
                - NO TEXTURE : 0
                - CHECKBOARD : 1
                - WAVES : 2
                - RAINBOW : 3
                - NO CAPS: 4 (No caps for cylinder, half sphere)
                - WAVE LENGHT: (> 0) if WAVES is defined.
                - NOTE: you can use some textures at the same time, but you Specular will overwrite others.

Bonus mandatory allows more than one camera, and more than one light.


- To get details about the format of a .rt file, please check en.subject.md file.

# HOOKS - BEHAVIOUR

------------------------------

## KEY | MODE

- **S:** Selection Mode. Select an object to interact with it. After an object is selected, it will change color.
- **T:** Translate a selected object using arrow keys.
- **D:** Increase or reduce width or radius of a selected object using + or - keys.
- **H:** Increase or reduce height of a selected object using + or - keys.
- **R:** Rotate a selected object using arrow keys.
- **E:** Orbit a camera around a selected object using arrow keys.
- **L:** Light mode. Select a light to translate using arrow keys or change brightness using B or V keys.
- **Q:** Back to normal.

### MOVE KEYS

- **Up-Down:** Move using the y-axis.
- **Left-Right:** Move using the x-axis.
- **Plus-Minus:** Move using the z-axis.

- **ESC:** Exit miniRT.

------------------------------

## Dependencies: ##
- MiniLibX: This project uses the MiniLibX library for graphical representations. Ensure it's properly installed before compiling.
- V3D: A custom 3D vector library used for calculations involving vectors in three-dimensional space.
- RGB: A library for handling RGB color operations and conversions, providing color-related utilities for the engine.
- Parser: Custom parser for reading the scene file format and initializing scene objects.
- Solver: Contains solutions for different geometric equations used in ray-object interaction.
- Libft-extended: 42 library with extra functions.

### Why libraries and modules ###
You may be asking yourself why the code is separated in libs and modules:
- libraries can be used without problem in others projects, they provided (rgb, v3d) mainly maths formulas to solve some common operations with 3D vectors or RGB colors.
- Modules are clustered functionalities of the project. E.g. Parser Module is used in some point of the workflow. This separation allow us to modify or work on that specific part of the workflow keeping the rest intact.
But, why? Well this project was produced for academic purposes, and it was a great opportunity to work with this approach (and it's easier to work with teammates).
This code doesn't pretend to be super compact or the most optimal approach, but understandable to us. Keep that in mind!


## miniRT Program Flow ##

### Start: ###

- The program kicks off in the main function where the number of user-provided arguments is checked.
- The scene file is parsed with readfile_parser(argv[1]). 

### Preprocessing: ###

- After the file is parsed, a post-parsing process is done with after_parse_process(mrt).
- Initial values for scene resolution and ratio are set.
- Cleanup functions for window and image are initialized.
- Handlers (hooks) are loaded with load_hooks(mrt) and MLX is started with mlx_starter(mrt).

### Main Rendering: ###

- The function render_main(t_mrt *mrt) goes through each camera and for each one, renders the scene with render_scene(mrt).
- The render_scene function is responsible for calculating the color for each pixel in the scene.

### Pixel Calculations: ###

- For each pixel, it is determined if it's an edge pixel or a center one using sample_pixel.
- Pixel color is calculated based on its position: first_pixel, sides_pixel, and centre_pixel.
- These calculations lean on the calc_ray function which computes the color based on direction and object interactions.

### Ray Interactions: ###

- tracer is responsible for tracing rays from an origin towards a direction, assessing interactions with objects, and determining the final color.
- The functions lighted, brightness, specular_transform, and ligth_hit handle light interactions and how they affect the final color of a pixel.
- hit_direction determines the direction of a ray upon hitting an object.

### Texturing: ###

- If an object has a texture applied, texturize determines the texture color to apply to the pixel.
- Functions like texture_checkboard, texture_waves, and texture_rainbow provide different textures.

### Antialiasing via Supersampling: ###

- The supersample function handles antialiasing, using sub-sampling to get a better visual result.

### Interactivity & Display: ###

- Once the scene is rendered, an MLX window is created with mlx_new_window.
- Keyboard and mouse handlers are assigned for interactivity: mlx_key_hook, mlx_hook.
- The to_win function is responsible for placing the rendered image in the window.
- Finally, the MLX loop is started with mlx_loop.

### Termination: ###

- On window close (click on x, or use esc key) program end, all resources are cleaned up with clear_all.

### NOTES ###

DOCUMENTATION: Have been created with Doxygen tool.
