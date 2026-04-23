

# SEV-WS-I
Este proyecto parte de la base que tenemos en SEV_Corriente, lo que moficamos es que toda la comunicacion se realiza mediante WebSocket.

Inicio de Proyecto: 20-12-2021

Version: 0.1 -->  20-12-2021
    Esta version contiene de base el soft anterior (comunicacion por HTTP->POST). 

Version 0.5  -->  03-05-2022
    En esta version trabajamos en:
     * Conexión a red Wifi.
     * Conexión a WebSocket.
     * Respuesta a Check Funcionamiento.

Version 0.6 -->  04-05-2022
    En esta version trabajamos en:
     * Mejora en visor de valores en lcd.
     * Calibración desactivada y Rshunt = 1.
     * Funcion de Enviar datos OK

Version 0.61 -->  04-05-2022
    En esta version trabajamos en:
     * Correcion string Envio de datos
     * Mejora en el tiempo de muestreo de carteles de inicio

Version 0.7  --> 13-09-2022
    En esta version trabajamos en:
     * en function incluimos la recepcion de dato por websocket para hacer hold
     * ya no recibimos señal digital para hacer hold

Version 0.9 --> 23-09-2022
    En esta version trabajamos en:
     * Reemplazamos HoldSet por Hold, ahora recibimos la orden de hold por el pulsador y la enviamos a la placa de tension
     * Cambiamos la velocidad de toma de datos de sensor ads1115, la dejamos en 490sps al igual que la placa de tension
     * La calibracion se encuentra desactivada

Version 1.0 --> 27-12-2022
    En esta version trabajamos en:
     * Limpiamos el codigo
     * Check la funcion de disparo
     * La calibracion se encuentra desactivada

Version 2.0 --> 23-01-2023
    En esta version trabajamos en:
     * Crear codigo para que la señal de corriente sea tratada con array y mejoramos asi el calculo
     * Todas las funciones fueron adaptadas para que funcionen.
     * Agregamos un panel de visualizacion para la calibracion.
     * Resistencia de Shunto no agregada
     * La calibracion se encuentra desactivada

Version 2.1 --> 23-01-2023
    Esta es la version que contiene el equipo de Aguas de Catamarca:
    * Se agrego Resistencia de Shunt y circuito de proteccion contra sobre corriente
    * Se agrego la calibracion de equipo.

Version 2.2 --> 26-12-2023
    Esta es la version que contiene el equipo de Aguas de Catamarca:
    * Se cambio el valor de las escalas, ahora podemos medir hasta 5000ma
    * Se agrego la calibracion de equipo, teniendo en cuenta la nueva placa de acondicionamiento de señal de I

Version 2.3 --> 26-12-2023
    Esta es la version que contiene el equipo de Aguas de Catamarca:
    * Se cambio el valor de las escalas, ahora podemos medir hasta 50000ma
    * Se adapto la visualizacion en LCD para soportar las corriente maximas de cada escala
    * Se desactivo calibracion.
    
Version 2.4 --> 29-12-2023
    Esta es la version que contiene el equipo de Aguas de Catamarca:
    * Se cambio logica de lectura para que me discrine las medidas negativas.

Version 2.5 stable --> 16-03-2024
    Esta es una version stable 
    *Se mejoro el CALCULO DEL VALOR MEDIDO teniendo en cuenta desvio standar con Limite inferior y Limite superior

Version 2.6 NewScales --> 04-04-2024
    Esta es una version stable 
    * En esta version se modificaron las escalas con las que trabajamos para la toma de datos
    * Mejoramos la muestra del cero

Version 2.7 --> 08/07/2024
    En esta version trabajamos 
    * Mejora de la comunicacion websocket
    * Mejora de visualizacion en pantalla de calibracion, se visualiza las escalas en mv

Version 2.71 stable-- 15/08/2024
    En esta version trabajamos:
    * Calibracion desactivada.
    * Corregimos la visualizacion en PrintDeltaI (fondos de escala).
    * Corregimos la visualizacion en cambio de escala.
    * Las oscilaciones cerca del CERO "0" solo se corrigen en la visualizacion, lo que no nos influye en ninguna otra parte del codigo.
    
Version 2.72 stable -- 29/08/2024
    En esta version trabajamos:
    * Cambiamos pines I/O para correcto funcionamiento de zumbador
    * Agregamos Numero de Serie
    * Cambio del la frecuencia del ADS a 32sps, esto proporciona una medidas con menos ruido

Version 2.73 stable -- 09/09/2024
    En esta version trabajamos:
    * Eliminamos el Hold por Button.
    * Activamos Hold por señal de activacion.

Version 2.74 stable -- 16/10/2024
    En esta version trabajamos:
    * Modificamos los nombre de variables de los pulsador para que sean mas legibles.
    * Agregamos botton para detectar si estamos trabajando con fuente interna.
    * Agregamos delay y funcion de deteccion de conexion WEBSOCKET para evitar que se caiga

Version 2.75 stable -- 31/10/2024
    En esta version trabajamos:
    * Agregamos deteccion modo calibracion, se producion cuando esta precionado el boton de "zero" al incializar
    * Cuando entramos en modo normal, entramos en la funciones de calibracion segun corresponda.
    * Cuando entramos en modo calibracion, se activa la visualizacion de calibracion y desactivamos las funciones de calibracion.

Version 2.76 stable -- 01/11/2024
    En esta version trabajamos:
    * Cambiamos los pines del "zumbador" por el de "pulsador de fuente interna" para que el micro inicie sin problemas.
    
Version 2.77 stable -- 03/04/2025
    En esta version trabajamos:
    * Mejora en caida de conexion WebSocket
    * Mejoramos la visualización de una corriente mas pequeña cuando no estamos en calibracion  

Version 2.78 stable -- 12/04/2025
    En esta version trabajamos:
    * Mejora en caida de conexion WebSocket, los tiempo de espera de  reconexion son minimos.
    * Correccion de comentarios de escalas en calibracion (no afecta al codigo)

Version 3.0 stable -- 03/05/2025
    En esta version trabajamos:
    * Cambiamos el pulsador de hold por una llave.
    * se cambio las entradas de zumbador y pulsador hold

Version 3.10       -- 03/05/2025
    En esta version trabajamos:
    * Eliminamos todo lo que tenga que ver con websocket

Version 3.10  s250502 -- 21/05/2025
    En esta version trabajamos:
    * Eliminamos todo lo que tenga que ver con websocket


Version 4.01  MQTT -- 22/05/2025
    En esta version trabajamos:
    * Inciamos el MQTT:
        * Enviar mensajes inciales y de check.
        * Recibir mensajes de check.
        * Enviar y recibir Hold
        * Enviar datos de medida.
        * Recibir orden de disparo de la web

Version 4.02 MQTT + Calibracion -- 22/05/2025
    En esta version trabajamos:
    * Calibracion:
        * Habilitamos la calibracion con fuente interna.
    * SelectEscala.h:
        * Modificamosm las escalas para adecuar con las mediciones que puede realizar el equipo
    * PrintDelataI.h:
        * Se adecuo la visualizacion de las escalas
    * LeerDeltaI.h
        * Se habilito solo la calibracion Fuente Interna.

Version 4.03 MQTT Stable -- 12/08/2025
    En esta version trabajamos:
    * Calibracion:
        * Se puso una bandera para habilitar la medida calibrada o no. Pasa o no pasa por la funcionde calibracion
    * SelectEscala:
        * Se volvio a usar las escalas de 2000ma 1000ma y 250ma
    * Setup:
        * Adecuacion de variables para entrar en modo calibracion.
    * Variables:
        * Se agragaron las banderas para modoCalibracion y medida calibrada.
        * Se adecuaron las variables para los pines de entrada y salida de acuerdo a la nueva placa SEV-WS v6.0
    * PrintDeltaI:
        * Adecuacion de visualizacion de escalas.
        * Correccion de variables modocalibracion.
    * LeerDeltaI:
        * Habilitamos la seleccion para entrar a corregir la medida segun la calibracion o no. Esto se realiza mediante la varible "bandCalibracion" que se encuentra en el main.
    * main: 
        * Iniciacion de bandCalibracion, la misma determina si entramos a corregir la medida segun la formula de la calibracion.

Version 4.04 MQTT Stable -- 27/10/2025
    En esta version trabajamos principalmente en estabilizar las medidas tomadas.
    * Setup.h:
        - Se modifico la frecuencia de muestreo del ads RATE_ADS1115_8SPS
    * Variables.h:
        - Se cambio el numero de iteraciones para que funcione con la frecuencia nueva del ads.
        - Se modificaficaron pines io de zumbador y disparo.
    * Calibracion.h:
        - Limpiamos la calibracion.
    * LeerDeltaI.h
        - ajustamos a 1 el nivel de confianza de la medida (68% aprox).
    
Version 4.10 MQTT Stable -- 31/10/2025
    En esta version trabajamos especificamente en poder configurar los parametros de Frec_ADS, Iteraciones y Confianza medicion desde el exterior.
    Tambien se habilito el envio de datos full que sera visualizado en la web config.php

Version 4.11 MQTT Stable -- 04/11/2025
    En esta version trabajamos especialmete en poder recibir/enviar la escala con la que queremos trabajar desde la pagina web config.php <-> esp
    - Se modifico el valor de iteraciones a 7 para que tiempo de la medida sea mas acorde, y el valor de la confianza de la medida a 1.25.
    - Se trabajo en PrintDeltaI.h mejorando la visualizacion de todos los parametros, y se implemento el fuera de escala para valores negativos

Version 4.12 MQTT Stable -- 04/11/2025
    En esta version trabajamos visualizar el estado del disparo (dependiendo de su llava de accion)
    
Version 4.13 MQTT Stable -- 13/11/2025
    En esta version trabajamos:
    Calibracion.h:   Se elimino la funcion Calibrar con fuente Interna, ahora existe una sola calibracion.
                     Se corrigio para devuelva el valor de "x", ya no se usa la variable resultado.
    LeerDelaI.h:     Se modifico la logica del codigo para que solo llame a la funcion Calibrar() en caso de ser necesario.
    Setup.h:         Se modifico la visualizacion Inicial, ahora se ve si esta habilitada la calibracion de los datos.

