// CronometrINO

#include <LiquidCrystal.h>  

// Declara o display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  

// Auxiliar para contar o tempo
unsigned long clockCronometro;
unsigned long tempoCronometro;
unsigned long tempoPausa =0;

// Estado do cronometro
bool statusCronometro; // True - Iniciado; False - parado;

// Auxiliares teclado
byte lastKey = 0;
const int TEMPO_PRESS = 400; // Ira disparar a tecla a cada 300 milissegundos pressionada continuamente
unsigned long iniPress;
// Botoes
const byte BOTAO_DIREITA = 1;
const byte BOTAO_CIMA = 2;
const byte BOTAO_BAIXO = 3;
const byte BOTAO_ESQUERDA = 4; // ZERA
const byte BOTAO_SELECT = 5; // INICIA/PAUSA

void setup()   
{  
 Serial.begin(9600);
 // Inicializa o display
 lcd.begin(16, 2);  
 // Define a posicao do cursor
 lcd.setCursor(0,0);  
 // Imprime um texto
 lcd.print(" [CronometrINO] ");  
 lcd.setCursor(0,1);  
 
 statusCronometro = 0;
 lcd.print("  00:00:00.000  ");  
}  


int lerBotao(){
 int botao;  
 byte key;
 botao = analogRead (0);  //Leitura do valor da porta analógica A0 
 
 // Para cada botão há uma faixa específica
 if (botao < 100) {  
  key = BOTAO_DIREITA;
 }  
 else if (botao < 200) {  
  key = BOTAO_CIMA; 
 }  
 else if (botao < 400){  
  key = BOTAO_BAIXO;
 }  
 else if (botao < 600){  
  key = BOTAO_ESQUERDA; 
 }  
 else if (botao < 800){  
  key = BOTAO_SELECT; 
 }  

 // Tratamento para pressionamento seguido e debounce
 if (key!=lastKey||millis()-iniPress>TEMPO_PRESS){
   iniPress = millis();
   lastKey = key;
   
   return key;
 }

 return 0;
}

// converte millis para hh:mm:ss.iii
char * TimeToString(unsigned long t)
{
 static char str[16];
 long mi = (t % 1000);
 t = t/1000;
 long h = t / 3600;
 t = t % 3600;
 int m = t / 60;
 int s = t % 60;
 sprintf(str, "%02ld:%02d:%02d.%03d", h, m, s, mi);
 return str;
}


// Imprime o tempo decorrido
void imprimirTempo(){
  lcd.setCursor(2,1); 
  lcd.print(TimeToString(tempoCronometro));
}
void loop()  
{  
  // Captura a acao do teclado
  int acao = lerBotao();
  
  // Inicia/Pausa
  if (acao==BOTAO_SELECT){
    // inverte o estado do cronometro
    statusCronometro = !statusCronometro;

    if (statusCronometro){
      clockCronometro = millis();
      tempoPausa = tempoCronometro;
    }
  }
  
  // Zera
   if (acao==BOTAO_ESQUERDA){
      tempoCronometro = 0;
      tempoPausa = 0;
      clockCronometro = millis();
      imprimirTempo();
  }

  // faz o clock do cronometro
  if (statusCronometro){
      tempoCronometro = tempoPausa + (millis() - clockCronometro);
      imprimirTempo();
  }
}
