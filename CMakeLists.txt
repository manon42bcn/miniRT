project(miniRT)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,16777216")

# Agrega los subdirectorios de las librerías
add_subdirectory(libs/lib)
add_subdirectory(mod/parser)
add_subdirectory(libs/rgb)
add_subdirectory(libs/v3d)
add_subdirectory(mod/hooks)
add_subdirectory(mod/solvers)

# ...

# Agrega tu archivo fuente principal y crea el ejecutable
add_executable(miniRT)

# Enlaza las librerías necesarias
target_link_libraries(miniRT lib libparser.a lib_rgb lib_v3d libhooks.a libsolvers.a)
