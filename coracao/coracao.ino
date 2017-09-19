// Caracteres gerados em: https://omerk.github.io/lcdchargen/
#include <LiquidCrystal.h>

// initialize the library
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  

// Coracao cheio
byte coracaoCheio[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

// Coracao vazio
byte coracaoVazio[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b01010,
  0b00100,
  0b00000
};

// 1 e 0 para coracao cheio/vazio
bool statusCoracao;
// Tempo(ms) da batida do coracao
const int TEMPO_BATIDA = 500;
// Variavel auxiliar para contarmos o tempo de animacao da batida 
unsigned long msUltimaBatida;


void setup()
{
  // create a new custom character
  lcd.createChar(0, coracaoVazio);
  lcd.createChar(1, coracaoCheio);
  
  // set up number of columns and rows
  lcd.begin(16, 2);

  lcd.setCursor(0,0); 
  
  // print the custom char to the lcd
  // why typecast? see: http://arduino.cc/forum/index.php?topic=74666.0
  lcd.write((uint8_t)0);
}

// Funcao responsavel por fazer a iteracao do coracao
void animaCoracao(){
  // Verifica se ja passou tempo suficiente para animar o coracao
  if ((millis()-msUltimaBatida)>TEMPO_BATIDA){
    // reinicia o auxiliar de tempo
    msUltimaBatida = millis(); 
    // inverte o status do coracao
    statusCoracao = !statusCoracao;
    
    lcd.setCursor(0,0); 
    
    // imprime no display
    lcd.write((uint8_t) statusCoracao);
  }
}


void loop()
{
    // Chama a funcao de animacao
    animaCoracao(); 
    // Mais codigos aqui no loop....
    // Sem delay, ok?
}
