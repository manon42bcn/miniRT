Flujo del Programa miniRT
Inicio:

El programa comienza en la función main, donde se verifica la cantidad de argumentos proporcionados por el usuario.
Se parsea el archivo de la escena con readfile_parser(argv[1]).
Preprocesamiento:

Una vez parseado el archivo, se realiza un proceso posterior al análisis con after_parse_process(mrt).
Se establecen valores iniciales para la resolución y la proporción de la escena.
Se inicializan las funciones de limpieza para la ventana y la imagen.
Se cargan los controladores (hooks) con load_hooks(mrt) y se inicia MLX con mlx_starter(mrt).
Renderizado Principal:

La función render_main(t_mrt *mrt) recorre todas las cámaras y, para cada una, realiza el renderizado de la escena con render_scene(mrt).
La función render_scene es responsable de calcular el color de cada píxel de la escena.
Cálculos de Pixel:

Para cada píxel, se determina si es un píxel en los bordes o en el centro usando sample_pixel.
Se calcula el color de cada píxel según su posición: first_pixel, sides_pixel y centre_pixel.
Estos cálculos dependen de la función calc_ray, que calcula el color basándose en la dirección y la interacción con los objetos.
Interacciones de Rayos:

tracer se encarga de trazar los rayos desde el origen hacia una dirección, evaluando las interacciones con los objetos y determinando el color final.
Las funciones lighted, brightness, specular_transform, y ligth_hit tratan las interacciones de luz y cómo afectan al color final de un píxel.
hit_direction determina la dirección de un rayo al golpear un objeto.
Texturizado:

Si un objeto tiene una textura aplicada, texturize determina el color de la textura a aplicar en el píxel.
Las funciones como texture_checkboard, texture_waves, y texture_rainbow proveen diferentes texturas.
Antialiasing con Supersampling:

La función supersample se encarga del antialiasing, usando sub-muestreo para obtener un mejor resultado visual.
Interactividad y Visualización:

Una vez renderizada la escena, se crea una ventana MLX con mlx_new_window.
Se asignan controladores de teclado y ratón para interactividad: mlx_key_hook, mlx_hook.
La función to_win se encarga de colocar la imagen renderizada en la ventana.
Finalmente, se inicia el bucle MLX con mlx_loop.
Finalización:

Al cerrar la ventana o al terminar el programa, se limpian todos los recursos con clear_all.