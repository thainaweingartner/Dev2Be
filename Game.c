#include <LiquidCrystal.h>
#define botao 6

//======VARIÁVEIS======
int pxpersonagem,pypersonagem,x,contador,score,vel;
bool start;


//======PROTÓTIPO======
void desenhapersonagem();
void menu();
void objetos();
void pontos();
void ini();
void gameover();


//======CARACTERES=======
//=======================
byte personagem[8] = {
  0b10000,
  0b10000,
  0b10011,
  0b11111,
  0b11100,
  0b10010,
  0b00000,
  0b00000
};

byte personagem2[8] = {
  0b10000,
  0b10000,
  0b10011,
  0b11111,
  0b11100,
  0b01100,
  0b00000,
  0b00000
};


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  
  lcd.createChar(0, personagem);
  lcd.createChar(1, personagem2);
  
  pinMode(botao, INPUT);
  lcd.begin(16, 2);
  start=false; 
}

void loop() {
  menu();
  if(digitalRead(botao)){
    delay(100);
    lcd.clear();
    ini();
    while(start){
      desenhapersonagem();
      objetos();
      
      if(x==0){
        score++;
        if(vel>50){
          vel-=30;
        }
      }
      
      pontos();
      gameover();
      delay(vel);
    }
  }
}

void desenhapersonagem(){
  lcd.setCursor(pxpersonagem,pypersonagem);
  lcd.write(byte(0));
  delay(30);
  lcd.setCursor(pxpersonagem,pypersonagem);
  lcd.write(1);
  
  if(digitalRead(botao) || pypersonagem==0){
    pulo();
  }
}

void menu() {
  lcd.setCursor(4,0);
  lcd.print("Dev2Be");
  lcd.setCursor(0,1);
  lcd.print("PRESSIONE BOTAO");
}

void pulo(){
  if(pypersonagem==1){
    pypersonagem=0;
    lcd.setCursor(1,1);
    lcd.print(" ");
  }
  
  if(pypersonagem==0){
    contador++;
  }
  
  if(contador>2){
    pypersonagem=1;
    contador=0;
    lcd.setCursor(1,0);
    lcd.print(" ");
  }
}

void objetos(){
  x--;
  lcd.setCursor(x+1,1);
  lcd.print(" ");
  lcd.setCursor(x,1);
  lcd.print("0"); 
  if(x==-2) x=16;
}

void pontos(){
  lcd.setCursor(14,0);
  lcd.print(score);
}

void ini (){
  pxpersonagem=31;
  pypersonagem=31;
  x=16;
  score=0;
  start=true;
  vel=300;
}

void gameover(){
  if(pxpersonagem==x && pypersonagem==1){
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("CABECAO");
    lcd.setCursor(4,1);
    lcd.print("YOU LOSE");
    delay(3000);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("CABECAO");
    lcd.setCursor(4,1);
    lcd.print("SCORE: ");
    lcd.print(score);
    delay(3000);
    lcd.clear();
    start=false;
  }
}