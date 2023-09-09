# Especifica que este directorio contendrá un proyecto,
# aunque en este caso será una biblioteca y no un ejecutable.
project(lib)

# Añadir todos los archivos fuente en las subcarpetas
file(GLOB_RECURSE LIB_SOURCES
        srcs/*.c
        srcs/ext/*.c
        srcs/ft/*.c
        srcs/gnl/*.c
        srcs/lst/*.c
        )

# Crear una biblioteca estática a partir de los archivos fuente
add_library(lib STATIC ${LIB_SOURCES})

# Incluir los encabezados
target_include_directories(lib PUBLIC inc)