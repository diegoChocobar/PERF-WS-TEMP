
# PERF-WS-TEMP

--------------------------------------------------------------------------------------------

Version 1.0 PERF-WS-TEMP. int -- 23/04/2026
    En esta version incializamos el proyecto de lectura de temperatura y profundidas para el perfilador. Partimos de la version Version 2.05 PERF-WS-I.

    De aqui en adelante vamos a cambiar lo que fuese necesario para adaptar el codigo para medir la temperatura y la profundidad segun lo especificado.
    
    PUNTO DE PARTIDA:
    1- Conexion a WIFI y MQTT estable.
    2- Pantalla de Visualizacion de Datos Generales.
    3- Pantalla de Visualizacion de ADS1115, utilizada para poder realizar la calibracion.
    4- El flunjo del programa esta manejado para manejar por eventos, se trato de ningun evento sea bloqueante.
        - Evento de Pulsadores.      ---> Probado y funcionando
        - Eventos de Print.          ---> Probado y funcionando
        - Eventos de Lectura de ADS  ---> Probado y funcionando
        - Evento de Envio de Datos   ---> Probado y funcionando
        - Evento de Recepcion de Datos -> No programado 

-------------------------------------------------------------------------------------------

REVISAR!
Durante la implementación de la medición de profundidad y la integración con el sistema de eventos, detecté varios problemas en la arquitectura del código que afectaban tanto la claridad como el comportamiento del sistema. Por un lado, tuve errores funcionales como la dirección I2C incorrecta del LCD, el uso inapropiado de CHANGE en la interrupción del encoder que cancelaba el conteo, y un falso problema en los incrementos de profundidad que en realidad estaba causado por el umbral de actualización en pantalla (RES_PROF).

Más importante aún, identifiqué una redundancia significativa en el flujo de datos entre estructuras y funciones. Actualmente los valores pasan por múltiples capas (ADS → Corrientes → Temperaturas) sin que exista una transformación real entre ellas, lo que genera complejidad innecesaria y dificulta el mantenimiento. Funciones como AjusteValores y MedirTemperatura terminan duplicando lógica o copiando datos sin aportar valor, probablemente por una estrategia conservadora para no perder información, pero que termina afectando la legibilidad y el diseño.

También observé que el sistema de eventos estaba mal acoplado en algunos puntos, especialmente al tener múltiples eventos potencialmente disparando la misma medición. Esto puede generar ejecuciones duplicadas o inconsistentes, por lo que decidí centralizar la medición en un único evento (MEDIRTEMPERATURA), que internamente se encarga de toda la cadena de adquisición.

Como medida temporal, implementé una función MedirTemperatura que simplemente replica los valores de corriente sin aplicar aún la conversión física, con el objetivo de validar correctamente el flujo completo (medición, impresión en LCD y publicación por MQTT). Una vez verificado esto, la idea es incorporar la función de conversión real en ese punto, manteniendo una separación clara entre adquisición eléctrica y magnitud física.

Queda pendiente una revisión más profunda para redefinir responsabilidades, simplificar estructuras y evitar este tipo de encapsulamientos innecesarios que hoy están complicando el sistema sin aportar beneficios claros.

revisar puntualmente la variable deltaI que resulta innecesaria a menos que se quiera seguir imprimiendo corriente en display. Y es que no se la utiliza en LeerCorriente.h ni en las funciones que se llaman dentro de LeerCorrietnes.h

Queda pendiente medir y entender con precisión los tiempos de ejecución de cada parte del sistema para poder balancear correctamente la frecuencia de muestreo, la actualización visual y la comunicación MQTT sin comprometer la responsividad general.

Revisar ValueADS MedirADS1115(int canal, int escala){} em LeerADS1115.h porque el parámetro "escala" no se usa.