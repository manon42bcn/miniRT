
# MiniRT Hooks Module

This library provides functionality to handle user input, enabling dynamic transformations on 3D objects like spheres, cylinders, lights, and the camera in a scene. Each function responds to specific key presses, causing updates in the runtime structure and subsequently triggering a re-render of the scene.

To better understanding of hooks functionality:
* https://harm-smits.github.io/42docs/libs/minilibx/hooks.html

## Overview
Our ray-tracing library provides a comprehensive solution to render 3D scenes using the ray-tracing technique. This README offers a high-level overview of the library's features, its flow, and other relevant details that can assist developers in understanding and utilizing its capabilities.

## ASCII Flow Diagram
```
+--------------+       +-----------+       +----------+        +---------+
| Key Presses  | ----> | Key Modes | ----> | Behavior |  ----> | Actions |
+--------------+       +-----------+       +----------+        +---------+
      ^                                                             |
      |                                                             v
+--------------+                                             +--------------+
| Mouse Events |                                             | Scene Update |
+--------------+                                             +--------------+
```

## Key Features:

1. **Multiple Modes**: The library supports several modes like SELECTION, TRANSLATE, ROTATE, and more, offering precise control over objects and lights in the scene.

2. **Flexible Interactions**: Users can control the scene via both key presses and mouse events, ensuring a more immersive experience.

3. **Object and Light Manipulation**: Objects and lights in the scene can be translated, rotated, and adjusted in brightness, size, and position.

4. **Camera Handling**: Users can switch between multiple cameras present in the scene for varied viewpoints.

5. **Resource Management**: Built-in functions ensure proper allocation and deallocation of resources, promoting optimal performance.

## Detailed Breakdown:

1. **Key Handlers**: Functions like `key_behaviour` and `key_modes` process key inputs, determining the type of action or mode change required.

2. **Mouse Selection**: The `mouse_select` function facilitates selection of scene objects using the mouse, aiding in direct interaction.

3. **Object Modification**: Functions such as `object_traslation`, `object_rotation`, `object_width`, and `object_height` offer extensive control over objects in the scene.

4. **Light Handling**: The library contains functions like `light_mode`, `light_traslation`, and `light_bright` for manipulating scene lights.

5. **Camera Management**: The `change_camera` function lets users toggle between different cameras in the scene.

6. **Cleanup Operations**: With the `window_handler` function, the library ensures that resources are correctly released upon application exit.

## Camera Rotation around Selected Object

One of the unique features of our ray-tracing library is the ability to rotate the camera around a selected object. This feature offers a more in-depth view of the object from different angles, enhancing scene visualization.

### How it Works:

1. **Object Selection**:
  - The first step involves selecting an object. This is achieved through the `mouse_select` function which, when a mouse click is detected on an object, sets it as the currently selected object.
  - The selected object is then highlighted, indicating it's ready for camera rotation.

2. **Camera Rotation Activation**:
  - With an object selected, the user can initiate camera rotation mode using specific key bindings. The `camera_rotation_mode` function is responsible for activating this mode.

3. **Rotation Execution**:
  - During rotation, the camera moves in an orbit around the selected object, maintaining a consistent distance from it.
  - The library ensures the camera's focus remains on the object, giving a revolving view of the object.
  - The functions `cam_rotation` and `cam_translate` assist in adjusting the camera's position and orientation during this rotation.

4. **Exit Rotation Mode**:
  - Once the desired view is achieved, users can exit the camera rotation mode and return to the standard camera view or switch to other modes.

### Benefits:

- **Enhanced Visualization**: This feature allows users to gain a 360-degree perspective of an object, useful for understanding its geometry and visual attributes from all angles.

- **Intuitive Interactions**: Rotating the camera around an object is a more natural way to explore the scene, especially for intricate objects or when meticulous details need to be observed.
