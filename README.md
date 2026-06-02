
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

--------------------------------------------------------------------------------------------

Version 1.10 PERF-WS-TEMP STABLE -- 01/06/2026
    Esta es la primer version estable, la cual cuenta con la estructura de eventos y se encuentra funcional midiendo temperatura,profundidad, transmitiendo y recibiendo datos.
    En esta version trabajamos:

    TRABAJOS REALIZADOS:
        * Setup.h:
            - Colocamos la version correcta.
            - Corregimos funcion setearDataRateADS(frec).
        * Variables.h: 
            - Eliminamos variables innecesarias
            - Limpiamos codigo
        * Conectar_WiFi.h:
            - Limpiamos codigo
        * Conectar_Mqtt.h:
            - Corregimos TOPICS
        * ActivarHolh.h:
            - Agregamos el envio de datos de Temperatura y Profundidad
        * EnvioDatos.h
            - Corregimos Topics
        * RecepcionMqtt.h:
            - Corregimos Topics
            - Eliminamos recepcion y funcion de configuracion
        * MedirTemperatura.h:
            - Limpieza de codigo
        * LeerADS1115.h:
            - Correccion de codigo
        * main:
            - Eliminamos Librerias Innecesarias
            - Eliminamos SelectEscala, ya la misma no se altera un vez seleccionada.
            - Cambiamos posicion entre ActivarHold y EnvioDatos. Esto es para enviar el ultimo dato mostrado cuando hacemos Hold
        * Protocolo de Comunicacion PERFILAJE:
            - Corregimos protocolo
    
    
    TRABAJOS A TENER EN CUENTA:


-------------------------------------------------------------------------------------------