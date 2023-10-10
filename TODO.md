* [x] Terminar de separar la funcionalidad mandatory y bonus.
  * funcionalidad controlada desde el parseo. Las funciones necesarias para lidiar con bonus, también están conidiconadas en el código.
* [x] Terminar de implementar traslaciones y rotaciones.
  * [x] Refactor hooks.
  * [x] Revisar hook rotation cylinder z
  * Pensar en pasar el mouse handler a la tecla space - intro (evitar el click doble y poder hacer transformaciones libres)
  * [x] traslaciones y rotaciones con up an down
  * [x] Aún sin hook definido para el ratón (no tiene porque haber)
* [ ] Instrucciones para opción --help (read and print from file?)
* [x] Revisar el chequeo de datos antes de hacer el parseo
* [x] Decidir que hacer con los malos datos llegados a atoi o atof
* [x] Decidir que hacer en caso de errores, exit directamente o limpiar en casos de error
* [x] Igual que antes, pero en los errores de ejecución
* [ ] Revisar los mensajes de error para homologar los textos (unificar criterios).
* [x] Revisar Makefile, versiones bonus y mandatory (make bonus -> make... estupidez pero bueno...)
  * [x] Make genera mandatory y bonus por separado.
  * [x] Make después de touch a algún archivo fuente de alguna librería o módulo
  * [x] Bonus siempre recompila... revisar
  * [ ] Anque funciona, afinar el make para el bonus y el mandatory (revisar el tema de las dependencias a los .a)
* [x] Chequear que hay suficientes elementos para iniciar render.
* [x] Separar librerías y módulos
* [ ] Bunus, la pirámide es demasiado lenta y problemática según que formas... so
  * [x] Implementar cono
  * [x] Implementar ellipsoide
  * [x] Implementar rectángulo (cajas)
  * [ ] Implementar box
  * [x] Implementar bump map... I'm not really sure...
  * [ ] Hacer un intento con la pirámide como figura compuesta (control desde parseo a triangulos...)
  * [ ] Explorar el usar hilos, para hacer más rápido el bonus
  * [ ] Revisar fuentes de bonus en solvers, o condicionar todo a preproceso (vida más fácil).
* [ ] Norminette general
  * [x] v3d
  * [x] rgb
  * [x] parser
  * [x] solvers
  * [x] hooks
  * [ ] miniRT
* [ ] Leaks (sigo sin encontrar, pero hay que revisar)
* [ ] Make it pretty... 
* [ ] Documentación general - looking pro! - 
  * [x] v3d
  * [x] rgb
  * [x] parser
  * [x] solvers
  * [x] hooks
  * [x] miniRT
* [ ] Crear Doxygen documentation
* [ ] CAMBIAR CRITERIOS DE PARSEO Y MODIFICAR LOS ARCHIVOS QUE HEMOS ENCONTRADO PARA QUE FUNCIONEN CON EL SUBJECT