cmake_minimum_required(VERSION 3.10)

# Definir el proyecto
project(solvers)

# Especificar la ubicación de los archivos de cabecera
include_directories(inc)

# Especificar los archivos fuente que serán utilizados
set(SOURCES
        srcs/cylinder.c
        srcs/cylinder_tops.c
        srcs/plane.c
        srcs/solvers.c
        srcs/sphere.c
        bns/cube.c
        bns/pyramid.c
        bns/square.c
        bns/triangle.c
        bns/cone.c
        )

# Crear una biblioteca estática con los archivos fuente
add_library(solvers STATIC ${SOURCES})
