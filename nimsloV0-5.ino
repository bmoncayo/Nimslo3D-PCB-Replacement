// Definir los pines de conexión
const int lightPin = A0;      // Pin analógico para el fotorresistor
const int buttonDisparador = 5;     // Pin digital para el botón
const int shutterPin = 6;    // Pin digital para el obturador
const int ledflashtrue = 7;        // Pin digital para el LED indicador
const int ledflashfalse = 8;
const int buttonObturador = 9;
const int ledmarcador = 10;
const int releflash = 11;
int shutterSpeed = 0;        // Variable para almacenar la velocidad de obturación

void setup() {
  pinMode(buttonDisparador, INPUT_PULLUP); // Configurar el botón como entrada con resistencia pull-up interna
  pinMode(shutterPin, OUTPUT);      // Configurar el pin del obturador como salida
  pinMode(ledflashtrue, OUTPUT);          // Configurar el pin del LED como salida
  pinMode(ledflashfalse, OUTPUT);
  pinMode(ledmarcador, OUTPUT);
  pinMode(releflash, OUTPUT);  
}

void loop() {
  // Leer la intensidad de luz del fotorresistor
  int lightIntensity = analogRead(lightPin);

  // Calcular la velocidad de obturación en función de la luz ambiente y los parámetros de la cámara
  shutterSpeed = calculateShutterSpeed(lightIntensity);

  // Verificar si la velocidad de obturación es menor a 1/30
  if (shutterSpeed < 30) {
    digitalWrite(ledflashtrue, HIGH); // Encender el LED indicador
    delay (500);
    digitalWrite(ledflashtrue, LOW);  // Apagar el LED indicador
  } else {
    digitalWrite(ledflashfalse, HIGH);  // Apagar el LED indicador
    delay (500);
    digitalWrite(ledflashfalse, LOW);
  }
if (digitalRead(buttonObturador) == HIGH){
  // Verificar si el botón ha sido presionado
  if (digitalRead(buttonDisparador) == LOW) {
    if (shutterSpeed < 1.0/30.0) {
       digitalWrite(releflash, HIGH);
       shutterSpeed = 1.0/60.0;
    }
    // Activar el obturador por un breve periodo de tiempo
    digitalWrite(shutterPin, HIGH);
    delay(shutterSpeed);
    digitalWrite(shutterPin, LOW);
    delay(500);
    digitalWrite(ledmarcador, HIGH);
    delay(500);
    digitalWrite(ledmarcador, LOW);
    digitalWrite(releflash, LOW);
  }
}
}

int calculateShutterSpeed(int lightIntensity) {
  // Cálculo de la velocidad de obturación en función de la luz ambiente y la configuración de la cámara
  float aperture = 5.6;   // Valor f/5.6
  int iso = 400;          // ISO 400
  float ev = log(2)*(aperture * aperture / shutterSpeed) + log(2)*(iso / 100.0);  // Cálculo de la Exposición de Valor (EV)
  float shutterTime = pow(2, -ev);  // Cálculo del tiempo de obturación en segundos

  
  shutterTime = constrain(shutterTime, 1.0 / 500.0, 1.0 / 30.0);

  return shutterTime;
}
