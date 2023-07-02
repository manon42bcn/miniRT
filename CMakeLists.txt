project(miniRT)

# Agrega los subdirectorios de las librerías
add_subdirectory(libs/lib)
add_subdirectory(libs/parser)
add_subdirectory(libs/rgb)
add_subdirectory(libs/v3d)

# ...

# Agrega tu archivo fuente principal y crea el ejecutable
add_executable(miniRT)

# Enlaza las librerías necesarias
target_link_libraries(miniRT lib lib_parser lib_rgb lib_v3d)
