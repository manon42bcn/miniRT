cmake_minimum_required(VERSION 3.10)
project(miniRT)

# Especificaciones para el compilador
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,16777216")

# Incluir directorios de encabezados
include_directories(
        inc
        common
        libs/lib/inc
        libs/rgb/inc
        libs/v3d/inc
        mod/hooks/inc
        mod/parser/inc
        mod/solvers/inc
)

# Agregar todos los archivos fuente en la carpeta srcs
file(GLOB_RECURSE SOURCES "srcs/*.c")
add_executable(miniRT ${SOURCES})

# Agregar los subdirectorios de las bibliotecas y módulos
add_subdirectory(libs/lib)
add_subdirectory(libs/rgb)
add_subdirectory(libs/v3d)
add_subdirectory(mod/hooks)
add_subdirectory(mod/parser)
add_subdirectory(mod/solvers)

# Vincular las bibliotecas con el ejecutable principal
target_link_libraries(
        miniRT
        lib
        lib_rgb
        lib_v3d
        libhooks
        libparser
        libsolvers
)