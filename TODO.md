* [x] Terminar de separar la funcionalidad mandatory y bonus.
  * funcionalidad controlada desde el parseo. Las funciones necesarias para lidiar con bonus, también están conidiconadas en el código.
* [x] Terminar de implementar traslaciones y rotaciones.
  * [x] Refactor hooks.
  * [x] Revisar hook rotation cylinder z
  * Pensar en pasar el mouse handler a la tecla space - intro (evitar el click doble y poder hacer transformaciones libres)
  * [x] traslaciones y rotaciones con up an down
  * [ ] Aún sin hook definido para el ratón (no tiene porque haber)
* [ ] Instrucciones para opción --help (read and print from file?)
* [x] Revisar el chequeo de datos antes de hacer el parseo
* [ ] Decidir que hacer con los malos datos llegados a atoi o atof
* [x] Decidir que hacer en caso de errores, exit directamente o limpiar en casos de error
* [ ] Igual que antes, pero en los errores de ejecución
* [ ] Revisar los mensajes de error para homologar los textos (unificar criterios).
* [x] Revisar Makefile, versiones bonus y mandatory (make bonus -> make... estupidez pero bueno...)
  * [x] Make genera mandatory y bonus por separado.
  * [ ] Bonus siempre recompila... revisar
* [x] Chequear que hay suficientes elementos para iniciar render.
* [ ] Norminette general
* [ ] Leaks (sigo sin encontrar, pero hay que revisar)