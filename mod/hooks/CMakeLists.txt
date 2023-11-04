cmake_minimum_required(VERSION 3.10)

# Definir el proyecto
project(hooks)

# Especificar la ubicación de los archivos de cabecera
include_directories(inc)

# Especificar los archivos fuente que serán utilizados
set(SOURCES
        src/camera_handlers.c
        src/camera_translate_handlers.c
        src/keys_handlers.c
        src/light_handlers.c
        src/modes_handlers.c
        src/normal_handlers.c
        src/objects_handlers.c
        src/selection_handlers.c
        src/special_handlers.c
        )

# Crear una biblioteca estática con los archivos fuente
add_library(hooks STATIC ${SOURCES})
