/// a coninuacion se llevara acabo un programa endonde trabaja
//con el LCD 16x2, resisto

// incluimos la libreria LCD
#include <LiquidCrystal.h>

// Incluimos librería DHT11 de humedad
#include <DHT11.h>

// inicializamos los pines
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//se inicializan las variables
/*como java envia carater por caracter, lo que realizael IDE es concatenar
  cada carater para mostrar lo que envio Java desde la interfaz*/
String msg = "";
//variable que se envia desde la interfaz
char input;

//Se declaran las variables para el sensor DHT11
int pin = A5; //Seleccionamos el pin en el que se //conectará el sensor
DHT11 dht11(pin); //Se selecciona el DHT11 (hay //otros DHT)

int cadena[3]=3;

// Variable donde se almacena el valor del LDR
int LDR = A2;  // PIN analógico A2 para la foto resistencia (LDR)
int LED = 9; // PIN digital para el LED
int valor;    // Variable que acumula el valor de la entrada analógica A2
// Ajuste de los valores propios, máximo y mínimo, del LDR.
int maximo = 500;  // Valor máximo que da la foto-resistencia en A2 (con plena luz)
int minimo = 470;  // Valor mínimo que da la foto-resistencia en A2 (sin luz)



void setup() {
  //Iniciamos la comunicación con el puerto serie
  lcd.begin(16, 2);
  //Cofiguramos el tamaño de la LCD

  pinMode(LED, OUTPUT); // PIN digital 9 como salida
  Serial.begin(9600);

}

void loop() {
  //En caso que haya información en el Serial Port, se entra en esta estructura
  if (Serial.available()) {
    input = Serial.read();
    msg += input;
    if (input == '2') {
      Temperatura();
      //Al ser temperatura no hace falta leerlo tan seguido
      delay(100);

      msg = "";
    }
    else {
      //se limpia la pantalla  y se muestra el mensaje enviado de Java
      lcd.clear();
      lcd.print(msg);
    }
  }
  if (Serial.available()) {
    input = Serial.read();
    msg += input;
    if (input == '3') {
      lcd.clear();
      Luz();
      //Al ser temperatura no hace falta leerlo tan seguido
      delay(1000);
      msg = "";
    } else {
      //se limpia la pantalla  y se muestra el mensaje enviado de Java
      lcd.clear();
      lcd.print(msg);
    }

  }
  if (Serial.available()) {
    input = Serial.read();
    msg += input;
    if (input == '4') {
      lcd.clear();
      Humedad();
      //Al ser temperatura no hace falta leerlo tan seguido
      delay(1000);
      msg = "";
    } else {
      //se limpia la pantalla  y se muestra el mensaje enviado de Java
      lcd.clear();
      lcd.print(msg);
    }


  }
  if (Serial.available()) {
    input = Serial.read();
    msg += input;
    if (input == '5') {
      lcd.clear();
      Mensajes();
      //Al ser temperatura no hace falta leerlo tan seguido
      delay(1000);
      msg = "";
    } else {
      //se limpia la pantalla  y se muestra el mensaje enviado de Java
      lcd.clear();
      lcd.print(msg);
    }


  }
}

void Temperatura(){

  //Leemos el valor de la entrada analogica
  float centigrados = leerGradosC();
  //Sacamos por pantalla los grados
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
int cadena[2]= centigrados;  
lcd.print(centigrados)
  
  lcd.print("C");


}
float leerGradosC() {
  int dato;
  float c;
  //Leemos los datos analogicos del sensor de temperatura
  dato = analogRead(A0);
  //Convertimos el dato de entrada en grados C segun la formula
  c = (500.0 * dato / 1024);
  return c;
}

int Luz() {
  valor = analogRead(LDR);
  // Limitamos el valor entre el máximo y el mínimo
  valor = constrain(valor, minimo, maximo);
  // Mostramos a través del LCD 16X2 el valor para ajustar máx y min.
  lcd.print(" Luz:");
  lcd.print(valor);
  int cadena[3]=valor;
  // Acomodamos el valor leído y ajustado, a un valor proporcional entre 0 y 255
  // - Cuando hay plena luz (máximo) --> Valor = 0
  // - Cuando no hay luz (mínimo) --> Valor = 255
  valor = map(valor, maximo, minimo, 0, 255);
  // Aplicamos el valor obtenido a un LED mediante PWM
  analogWrite(LED, valor);
}

float Humedad() {
  float temp, hum;
  int err;
  if ((err = dht11.read(hum, temp)) == 0)
  {

    //    Serial.print("Humedad ");
    //    Serial.print(hum);
    lcd.setCursor(0, 1);
    lcd.print(" Humedad: ");
    lcd.print(hum);
    int cadena [0]=hum;
    Serial.println();

  }
  else
  {
    Serial.println();
    Serial.print("Error Num :");
    Serial.print(err);
    Serial.println();
  }

}

void Mensajes (){
  for(int i=0; i<5;i++)
  lcd.print(cadenas[i]);
  delay(500);
  } 
