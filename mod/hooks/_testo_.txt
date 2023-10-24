cmake_minimum_required(VERSION 3.10)

# Definir el proyecto
project(hooks)

# Especificar la ubicación de los archivos de cabecera
include_directories(inc)

# Especificar los archivos fuente que serán utilizados
set(SOURCES
        src/camera_hooks.c
        src/camera_orbit_hooks.c
        src/common.c
        src/cylinder_hooks.c
        src/cylinder_rotation_hooks.c
        src/keys_handler.c
        src/light_rotation_hooks.c
        src/main_hooks.c
        src/mouse_handler.c
        src/sphere_hooks.c
        )

# Crear una biblioteca estática con los archivos fuente
add_library(hooks STATIC ${SOURCES})
