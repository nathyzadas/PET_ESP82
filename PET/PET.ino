#include <Wire.h>
#include "SSD1306Wire.h"

// SDA = D2, SCL = D1
SSD1306Wire display(0x3c, D2, D1);

// posição das pupilas
int pupila = 0;
bool indoDireita = true;

// -------------------------------
// DESENHO DOS OLHOS
// -------------------------------
void desenharOlhos(int desloc) {
  display.clear();

  // olho esquerdo
  display.drawCircle(40, 30, 14);
  display.fillCircle(40 + desloc, 30, 6);

  // olho direito
  display.drawCircle(88, 30, 14);
  display.fillCircle(88 + desloc, 30, 6);

  display.display();
}

// -------------------------------
// PISCAR
// -------------------------------
void piscar() {
  // fecha
  display.clear();
  display.drawLine(26, 30, 54, 30);
  display.drawLine(74, 30, 102, 30);
  display.display();
  delay(120);

  // abre
  display.clear();
  desenharOlhos(pupila);
  delay(50);
}

// -------------------------------
// BOCA: SORRISO
// -------------------------------
void bocaSmile() {
  // boca estilo curva simples :)
  display.drawLine(50, 48, 78, 48);
  display.drawLine(50, 48, 52, 52);
  display.drawLine(78, 48, 76, 52);
}

// -------------------------------
// BOCA: TRISTE :(
// -------------------------------
void bocaSad() {
  display.drawLine(50, 52, 78, 52);
  display.drawLine(50, 52, 52, 48);
  display.drawLine(78, 52, 76, 48);
}

// -------------------------------
// BOCA: RAIVA  >:( 
// -------------------------------
void bocaAngry() {
  display.drawLine(50, 50, 78, 50);
  display.drawLine(40, 20, 54, 28); // sobrancelha esquerda
  display.drawLine(74, 28, 98, 20); // sobrancelha direita
}

// -------------------------------
// BOCA: SONO  -_-
// -------------------------------
void bocaSono() {
  display.drawLine(50, 50, 78, 50);
  display.drawLine(26, 30, 54, 30); // olhos semi-fechados
  display.drawLine(74, 30, 102, 30);
}

// -------------------------------
// EXPRESSÃO COMPLETA
// -------------------------------
void expressaoSmile() {
  desenharOlhos(pupila);
  bocaSmile();
  display.display();
}

void expressaoSad() {
  desenharOlhos(pupila);
  bocaSad();
  display.display();
}

void expressaoAngry() {
  desenharOlhos(pupila);
  bocaAngry();
  display.display();
}

void expressaoSono() {
  bocaSono();
  display.display();
}

// -------------------------------
// SETUP
// -------------------------------
void setup() {
  Wire.begin(D2, D1);
  display.init();
  display.flipScreenVertically();
  randomSeed(analogRead(0));
}

// -------------------------------
// LOOP — alterna emoções
// -------------------------------
void loop() {

  // MOVIMENTO DA PUPILA
  desenharOlhos(pupila);

  if (indoDireita) {
    pupila++;
    if (pupila > 5) indoDireita = false;
  } else {
    pupila--;
    if (pupila < -5) indoDireita = true;
  }

  // Chance de piscar
  if (random(0, 18) == 5) piscar();

  bocaSmile();
  display.display();
  delay(100);
  
  // ALEATORIZA emoções
  int emo = random(0, 100);

  if (emo < 5) {            // bravo
    display.clear();
    expressaoAngry();
    delay(600);
  } 
  else if (emo < 10) {       // triste
    display.clear();
    expressaoSad();
    delay(600);
  }
  else if (emo < 15) {       // sonolento
    display.clear();
    expressaoSono();
    delay(600);
  }
  else if (emo < 25) {      // piscando múltiplas vezes
    piscar();
    piscar();
  }
}
