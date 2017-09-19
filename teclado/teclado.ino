// TESTE DE BOTOES

#include <LiquidCrystal.h>  

// Declara o display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  
  
void setup()   
{  
 // Inicializa o display
 lcd.begin(16, 2);  
 // Define a posicao do cursor
 lcd.setCursor(0,0);  
 // Imprime um texto
 lcd.print("UTFPR - SAES");  
 lcd.setCursor(0,1);  
 
 lcd.print("Tecla->");  
}  
  
void loop()  
{  
 int botao;  
 botao = analogRead (0);  //Leitura do valor da porta analógica A0
 lcd.setCursor(8,1);  
 // Para cada botão há uma faixa específica
 if (botao < 100) {  
  lcd.print ("Direita ");  
 }  
 else if (botao < 200) {  
  lcd.print ("Cima    ");  
 }  
 else if (botao < 400){  
  lcd.print ("Baixo   ");  
 }  
 else if (botao < 600){  
  lcd.print ("Esquerda");  
 }  
 else if (botao < 800){  
  lcd.print ("Select  ");  
 }  
}
