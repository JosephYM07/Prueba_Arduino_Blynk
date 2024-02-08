## Integrantes:
-  Moreira A.
-  Valenzuela J.
-  Villares W.
-  Yépez J.
## **Control de sensores y LEDs con Blynk**

Este proyecto consiste en un código para controlar una serie de sensores (temperatura, humedad, luminosidad y lluvia) y LEDs utilizando la plataforma Blynk para la visualización y control remoto. A continuación, se proporciona una descripción de los componentes principales del código y cómo usarlo.

## **Requisitos**

Para ejecutar este proyecto, necesitarás los siguientes componentes:

- Un microcontrolador compatible con Arduino Mega 2560
- Un módulo ESP8266 para la conexión Wi-Fi.
- Sensores de temperatura, humedad, luminosidad y lluvia.
- LEDs para indicar diferentes condiciones.
- Acceso a la plataforma Blynk y un token de autorización.

## **Configuración**

Antes de cargar el código en tu microcontrolador, asegúrate de seguir estos pasos:

1. Configura el archivo **`BlynkConfig.h`** con tu información de autenticación Blynk.
2. Asegúrate de que los pines definidos para los LEDs y los sensores coincidan con tu configuración física.
3. Si es necesario, ajusta los umbrales de temperatura, humedad y luminosidad según tus requisitos.
4. Instala las bibliotecas necesarias de Blynk y ESP8266 en tu entorno de desarrollo Arduino.

## **Uso**

Una vez que hayas cargado el código en tu microcontrolador y configurado la aplicación Blynk con los widgets correspondientes, puedes seguir estos pasos para usar el sistema:

1. Enciende el dispositivo y espera a que se conecte a la red Wi-Fi.
2. Abre la aplicación Blynk en tu dispositivo móvil y abre el proyecto asociado.
3. Monitorea las lecturas de los sensores (temperatura, humedad, luminosidad y lluvia) a través de los widgets en la aplicación.
4. Controla los LEDs manualmente a través de los widgets en la aplicación o deja que el sistema los controle automáticamente según las condiciones ambientales.
## **Umbrales de los sensores**

- Umbral de temperatura: 3
- Umbral de humedad: 800
- Umbral de luminosidad: 3

## **Comportamiento**

- Si el nivel de temperatura y/o humedad es alto (por encima de los umbrales definidos), se activará un LED rojo y se indicará en el monitor serial cuál o cuáles son las variables con valores altos.
- Si el nivel de humedad es bajo y no hay presencia de lluvia, se activará un LED azul.
- Si el nivel de iluminación es bajo, se encenderá un LED amarillo, que también puede ser controlado desde Blynk para apagar o encender.
- Si el nivel de iluminación es alto y hay presencia de lluvia, se activará un LED blanco.

## **Control desde Blynk**

Se puede monitorear y controlar los datos de los sensores enviados por Arduino a Blynk tanto en la aplicación móvil como en la plataforma web. Utiliza los widgets proporcionados por Blynk para visualizar las lecturas de los sensores y controlar el estado de los LEDs de manera remota.
