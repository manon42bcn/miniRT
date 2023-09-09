cmake_minimum_required(VERSION 3.10)

# Definir el proyecto
project(v3d)

# Especificar la ubicación de los archivos de cabecera
include_directories(inc)

# Especificar los archivos fuente que serán utilizados
set(SOURCES
        src/v3d_algebra.c
        src/v3d_arithmetics.c
        src/v3d_extra.c
        src/v3d_utils.c
        )

# Crear una biblioteca estática con los archivos fuente
add_library(v3d STATIC ${SOURCES})
