#define BLYNK_TEMPLATE_ID "TMPL2wH6etfVY"
#define BLYNK_TEMPLATE_NAME "GrupoYepezValenzuelaMoreiraVillares"
#define BLYNK_AUTH_TOKEN "4nHKBN8oAUeNik0EYqk1o8WLo4zbw2F1"

#include <BlynkSimpleShieldEsp8266.h>
#include <ESP8266_Lib.h>

// char ssid[] = "";
// char pass[] = "";

#define EspSerial Serial1
ESP8266 wifi(&EspSerial);

#define BLYNK_PRINT Serial

// Definición de pines para los LEDs
int ledBlanco = 4;
int ledRojo = 5;
int ledAmarillo = 6;
int ledAzul = 7;

// Pin de la fotocelda
int fotoCeldaPin = A1;
// Pin del sensor de humedad
int sensorHumedadPin = A2;
// Pin del sensor Lluvia
int sensorLluviaPin = 3;  

// Umbrales
int umbralTemperatura = 3;
int umbralHumedad = 800;
int umbralLuminosidad = 3;

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  EspSerial.begin(115200);
  EspSerial.write("AT+UART_DEF=9600,8,1,0,0\r\n");
  EspSerial.write("AT+RST\r\n");
  delay(100);
  EspSerial.begin(9600);
  delay(10);

  pinMode(ledBlanco, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledAzul, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);
  timer.setInterval(1000L, checkSensors);
}

void loop() {
  Blynk.run();
  timer.run();
}

void checkSensors() {
  int temperatura = readTemperatura();
  int humedad = readHumedad();
  int luminosidad = readLuminosidad();
  int lluvia = digitalRead(sensorLluviaPin);

  controlLEDs(temperatura, humedad, luminosidad, lluvia);

  // Envío de datos a Blynk
  Blynk.virtualWrite(V4, luminosidad);
  Blynk.virtualWrite(V5, humedad);
  Blynk.virtualWrite(V6, temperatura);
  Blynk.virtualWrite(V8, lluvia == LOW ? "Está lloviendo" : "No está lloviendo");
}

int readTemperatura() {
  // Leer el valor del sensor de temperatura
  int temperatura = analogRead(A0);  
  return temperatura;
}

int readHumedad() {
  // Leer el valor del sensor de humedad
  int humedad = analogRead(sensorHumedadPin);
  return humedad;
}

int readLuminosidad() {
  // Leer el valor del sensor de luminosidad
  int luminosidad = analogRead(fotoCeldaPin);
  return luminosidad;
}

void controlLEDs(int temperatura, int humedad, int luminosidad, int lluvia) {
  // Control de los LEDs
  if (temperatura > umbralTemperatura || humedad > umbralHumedad) {
    digitalWrite(ledRojo, HIGH);
    Serial.println("Temperatura alta y Humedad alta");
    delay(5000);
  } else {
    digitalWrite(ledRojo, LOW);
  }

  if (humedad < umbralHumedad && lluvia == LOW) {
    digitalWrite(ledAzul, LOW);
  } else {
    digitalWrite(ledAzul, HIGH);
    Serial.println("Humedad Baja y sin lluvia");
    delay(5000);
  }

  if (luminosidad < umbralLuminosidad) {
    digitalWrite(ledAmarillo, HIGH);
    Serial.println("Sin Iluminacion");
    delay(5000);
  } else {
    digitalWrite(ledAmarillo, LOW);
  }

  if (luminosidad > umbralLuminosidad && lluvia == LOW) {
    digitalWrite(ledBlanco, HIGH);
    Serial.println("Iluminacion Alta y lluvia");
    delay(5000);
  } else {
    digitalWrite(ledBlanco, LOW);
  }
}

BLYNK_WRITE(V9) {
  int ledAmarilloValor = param.asInt();
  if (ledAmarilloValor == HIGH) {
    // Acción cuando se enciende el LED amarillo
    digitalWrite(ledAmarillo, HIGH);
  } else {
    // Acción cuando se apaga el LED amarillo
    digitalWrite(ledAmarillo, LOW);
  }
}

BLYNK_WRITE(V1) {
  int ledRojoValor = param.asInt();
  if (ledRojoValor == HIGH) {
    // Acción cuando se enciende el LED rojo
    digitalWrite(ledRojo, HIGH);
  } else {
    // Acción cuando se apaga el LED rojo
    digitalWrite(ledRojo, LOW);
  }
}

BLYNK_WRITE(V2) {
  int ledAzulValor = param.asInt();
  if (ledAzulValor == HIGH) {
    // Acción cuando se enciende el LED azul
    digitalWrite(ledAzul, LOW);
  } else {
    // Acción cuando se apaga el LED azul
    digitalWrite(ledAzul, HIGH);
  }
}

BLYNK_WRITE(V3) {
  int ledBlancoValor = param.asInt();
  if (ledBlancoValor == HIGH) {
    // Acción cuando se enciende el LED blanco
    digitalWrite(ledBlanco, HIGH);
  } else {
    // Acción cuando se apaga el LED blanco
    digitalWrite(ledBlanco, LOW);
  }
}

BLYNK_WRITE(V4) {
  int luminosidadValor = readLuminosidad();
  Blynk.virtualWrite(V4, luminosidadValor);
}

BLYNK_WRITE(V5) {
  int humedadValor = readHumedad();
  Blynk.virtualWrite(V5, humedadValor);
}

BLYNK_WRITE(V6) {
  int temperaturaValor = readTemperatura();
  Blynk.virtualWrite(V6, temperaturaValor);
}
