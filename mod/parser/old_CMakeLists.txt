cmake_minimum_required(VERSION 3.10)

# Definir el proyecto
project(parser)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D BONUS=1")
# Especificar la ubicación de los archivos de cabecera
include_directories(inc)

# Especificar los archivos fuente que serán utilizados
set(SOURCES
        srcs/builders.c
        srcs/cleaners.c
        srcs/cylinder.c
        srcs/parser_ambient.c
        srcs/parser_builders.c
        srcs/parser_camera.c
        srcs/parser_light.c
        srcs/parser_resolution.c
        srcs/parser_rgb.c
        srcs/parser_utils.c
        srcs/parser_v3d.c
        srcs/plane.c
        srcs/readfile.c
        srcs/sphere.c
        srcs/box.c
        srcs/triangle.c
        srcs/ellipsoid.c
        srcs/rectangle.c
        )

# Crear una biblioteca estática con los archivos fuente
add_library(parser STATIC ${SOURCES})
