#include <Wire.h>
#include <LiquidCrystal_I2C.h> 

// Pinos para os componentes
#define TRIG_PIN 9        
#define ECHO_PIN 10       
#define LED_VERDE_PIN 2   
#define LED_AMARELO_PIN 3 
#define LED_VERMELHO_PIN 4
#define BUZZER_PIN 5      

// Parâmetros do sistema
const float alturaTotalReservatorio = 400.0; 
const float LIMIAR_ATENCAO_PERCENT = 0.50;   
const float LIMIAR_CRITICO_PERCENT = 0.70;   

const int I2C_ADDR = 0x27; 
const int LCD_COLUMNS = 20;
const int LCD_ROWS = 4;

// Variáveis globais
float distanciaSensorAgua = 0.0;
float nivelAgua = 0.0;
float percentualNivelAgua = 0.0;
String statusSistema = "";

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(9600);

  // Configura os pinos do sensor, LEDs e buzzer
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_VERDE_PIN, OUTPUT);
  pinMode(LED_AMARELO_PIN, OUTPUT);
  pinMode(LED_VERMELHO_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // LEDs e buzzer comecem desligados
  digitalWrite(LED_VERDE_PIN, LOW);
  digitalWrite(LED_AMARELO_PIN, LOW);
  digitalWrite(LED_VERMELHO_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Inicialização no LCD
  lcd.init();      
  lcd.backlight(); 

  lcd.setCursor(0, 0);
  lcd.print("Monitor Nivel Agua");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
}

float lerDistanciaCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000); 
  float distancia = duration * 0.0343 / 2.0;

  if (duration == 0 || distancia > 400) { 
    return 400.0; 
  }
  if (distancia < 2) {
    return 2.0; 
  }
  return distancia;
}

String controlarAlertas(float nivel) {
  float nivelAtencao = alturaTotalReservatorio * LIMIAR_ATENCAO_PERCENT;
  float nivelCritico = alturaTotalReservatorio * LIMIAR_CRITICO_PERCENT;
  String situacaoAtual = "";

  digitalWrite(LED_VERDE_PIN, LOW);
  digitalWrite(LED_AMARELO_PIN, LOW);
  digitalWrite(LED_VERMELHO_PIN, LOW);
  noTone(BUZZER_PIN);

  if (nivel < 0) { 
    situacaoAtual = "ERRO SENSOR";
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_VERMELHO_PIN, HIGH);
      delay(100); 
      digitalWrite(LED_VERMELHO_PIN, LOW);
      delay(100);
    }
  } else if (nivel >= nivelCritico) {
    situacaoAtual = "NIVEL CRITICO";
    digitalWrite(LED_VERMELHO_PIN, HIGH); 
    tone(BUZZER_PIN, 1000, 500); 
  } else if (nivel >= nivelAtencao) {
    situacaoAtual = "NIVEL ATENCAO";
    unsigned long currentMillis = millis();
    if (currentMillis % 1000 < 500) { 
        digitalWrite(LED_AMARELO_PIN, HIGH);
    } else {
        digitalWrite(LED_AMARELO_PIN, LOW);
    }
  } else {
    situacaoAtual = "NIVEL SEGURO";
    digitalWrite(LED_VERDE_PIN, HIGH); 
  }
  return situacaoAtual;
}

void exibirNoLcd(float nivelCm, float percentual, String statusMsg) {
  lcd.clear(); 

  String linhaTexto;

  lcd.setCursor(0, 0);
  linhaTexto = "Nivel: ";
  if (nivelCm < 0) { 
    linhaTexto += "--- cm";
  } else {
    linhaTexto += String(nivelCm, 1) + " cm"; 
  }
  lcd.print(linhaTexto);
  for (int i = linhaTexto.length(); i < LCD_COLUMNS; i++) { 
    lcd.print(" ");
  }

  lcd.setCursor(0, 1);
  linhaTexto = "Perc: ";
  if (percentual < 0) { 
    linhaTexto += "--- %";
  } else {
    linhaTexto += String(percentual, 1) + "%";
  }
  lcd.print(linhaTexto);
  for (int i = linhaTexto.length(); i < LCD_COLUMNS; i++) { 
    lcd.print(" ");
  }

  lcd.setCursor(0, 2);
  linhaTexto = "Situacao:";
  lcd.print(linhaTexto);
  for (int i = linhaTexto.length(); i < LCD_COLUMNS; i++) { 
    lcd.print(" ");
  }

  lcd.setCursor(0, 3);
  linhaTexto = statusMsg; 
  lcd.print(linhaTexto);
  for (int i = linhaTexto.length(); i < LCD_COLUMNS; i++) { 
    lcd.print(" ");
  }
}

void loop() {
  distanciaSensorAgua = lerDistanciaCm();

  if (distanciaSensorAgua >= 2 && distanciaSensorAgua <= alturaTotalReservatorio) {
    nivelAgua = alturaTotalReservatorio - distanciaSensorAgua;
    percentualNivelAgua = (nivelAgua / alturaTotalReservatorio) * 100.0;
  } else if (distanciaSensorAgua > alturaTotalReservatorio) {
    nivelAgua = 0;
    percentualNivelAgua = 0.0;
  } else { 
    nivelAgua = -1; 
    percentualNivelAgua = -1.0; 
  }

  statusSistema = controlarAlertas(nivelAgua);

  Serial.print("Dist (cm): "); Serial.print(distanciaSensorAgua, 1);
  Serial.print(" | Nivel (cm): "); Serial.print(nivelAgua, 1);
  Serial.print(" (");
  if (percentualNivelAgua >= 0) {
    Serial.print(percentualNivelAgua, 1);
    Serial.print("%");
  } else {
    Serial.print("Erro");
  }
  Serial.print(") | Status: "); Serial.println(statusSistema);

  exibirNoLcd(nivelAgua, percentualNivelAgua, statusSistema);

  delay(1000);
}