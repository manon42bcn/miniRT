cmake_minimum_required(VERSION 3.10)

# Definir el proyecto
project(rgb)

# Especificar la ubicación de los archivos de cabecera
include_directories(inc)

# Especificar los archivos fuente que serán utilizados
set(SOURCES
        src/rgb_algebra.c
        src/rgb_arithmetics.c
        )

# Crear una biblioteca estática con los archivos fuente
add_library(rgb STATIC ${SOURCES})
