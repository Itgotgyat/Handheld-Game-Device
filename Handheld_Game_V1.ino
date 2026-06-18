#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>
#include <LedControl.h>
#include <LiquidCrystal.h>
#include <OneButton.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

#define DATA_PIN 12
#define CLK_PIN 10
#define CS_PIN 11
#define IR_PIN 2

#define rs 7
#define en A2
#define d4 6
#define d5 4
#define d6 5
#define d7 3

int page = 0;
int lastPage = -1;

LiquidCrystal led(rs, en, d4, d5, d6, d7);

bool gaming = false;
bool go = true;

int s00 = 0; int s03 = 0; int s06 = 0;
int s30 = 0; int s33 = 0; int s36 = 0;
int s60 = 0; int s63 = 0; int s66 = 0;

LedControl lcd(DATA_PIN, CLK_PIN, CS_PIN, 1);

int r = 0;
int c = 0;
int p1 = 0;
int p2 = 0;

int totalTurns;

int chance = 0;

OneButton button(A1, true);
OneButton bRight(A3, true);
OneButton bUp(A4, true);
OneButton bLeft(9, true);
OneButton bDown(A5, true);

void Quit();

int getCurrentSlotOwner() {
  if (r == 0 && c == 0) return s00;
  if (r == 0 && c == 3) return s03;
  if (r == 0 && c == 6) return s06;
  if (r == 3 && c == 0) return s30;
  if (r == 3 && c == 3) return s33;
  if (r == 3 && c == 6) return s36;
  if (r == 6 && c == 0) return s60;
  if (r == 6 && c == 3) return s63;
  if (r == 6 && c == 6) return s66;
  return 0;
}

void setCurrentSlotOwner(int owner) {
  if (r == 0 && c == 0) s00 = owner;
  if (r == 0 && c == 3) s03 = owner;
  if (r == 0 && c == 6) s06 = owner;
  if (r == 3 && c == 0) s30 = owner;
  if (r == 3 && c == 3) s33 = owner;
  if (r == 3 && c == 6) s36 = owner;
  if (r == 6 && c == 0) s60 = owner;
  if (r == 6 && c == 3) s63 = owner;
  if (r == 6 && c == 6) s66 = owner;
}

void clear() {
  if (getCurrentSlotOwner() == 0) {
    lcd.setLed(0, r, c, false);
    lcd.setLed(0, r + 1, c, false);
    lcd.setLed(0, r, c + 1, false);
    lcd.setLed(0, r + 1, c + 1, false);
  }
}

void ticTacToe() {
  int owner = getCurrentSlotOwner();
  if (owner == 0) {
    bool blinkState = (millis() / 300) % 2;
    lcd.setLed(0, r, c, blinkState);
    lcd.setLed(0, r + 1, c, blinkState);
    lcd.setLed(0, r, c + 1, blinkState);
    lcd.setLed(0, r + 1, c + 1, blinkState);
  } else if (owner == 1) {
    lcd.setLed(0, r, c, true);
    lcd.setLed(0, r + 1, c, true);
    lcd.setLed(0, r, c + 1, true);
    lcd.setLed(0, r + 1, c + 1, true);
  } else if (owner == 2) {
    lcd.setLed(0, r, c, true);
    lcd.setLed(0, r + 1, c, false);
    lcd.setLed(0, r, c + 1, false);
    lcd.setLed(0, r + 1, c + 1, true);
  }
  if(s00 == 2 && s03 == 2 && s06 == 2){
    p2+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 2 Wins");
    delay(3000);
    score();
  }
  if(s30 == 2 && s33 == 2 && s36 == 2){
    p2+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 2 Wins");
    delay(3000);
    score();
  }
  if(s60 == 2 && s63 == 2 && s66 == 2){
    p2+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 2 Wins");
    delay(3000);
    score();
  }
  if(s00 == 1 && s03 == 1 && s06 == 1){
    p1+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 1 Wins");
    delay(3000);
    score();
  }
  if(s30 == 1 && s33 == 1 && s36 == 1){
    p1+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 1 Wins");
    delay(3000);
    score();
  }
  if(s60 == 1 && s63 == 1 && s66 == 1){
    p1+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 1 Wins");
    delay(3000);
    score();
  }
  if(s00 == 2 && s30 == 2 && s60 == 2){
    p2+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 2 Wins");
    delay(3000);
    score();
  }
  if(s03 == 2 && s33 == 2 && s63 == 2){
    p2+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 2 Wins");
    delay(3000);
    score();
  }
  if(s06 == 2 && s36 == 2 && s66 == 2){
    p2+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 2 Wins");
    delay(3000);
    score();
  }
  if(s00 == 1 && s30 == 1 && s60 == 1){
    p1+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 1 Wins");
    delay(3000);
    score();
  }
  if(s03 == 1 && s33 == 1 && s63 == 1){
    p1+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 1 Wins");
    delay(3000);
    score();
  }
  if(s06 == 1 && s36 == 1 && s66 == 1){
    p1+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 1 Wins");
    delay(3000);
   score();
  }
  if(s00 == 1 && s33 == 1 && s66 == 1){
    p1+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 1 Wins");
    delay(3000);
    score();
  }
  if(s00 == 2 && s33 == 2 && s66 == 2){
    p2+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 2 Wins");
    delay(3000);
    score();
  }
  if(s06 == 1 && s33 == 1 && s60 ==1){
    p1+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 1 Wins");
    delay(3000);
    score();
  }
  if(s06 == 2 && s33 == 2 && s60 == 2){
    p2+=1;
    led.clear();
    led.setCursor(0, 0); 
    led.print("Player 2 Wins");
    delay(3000);
    score();
  }
  else if(totalTurns >= 9){
    led.clear();
    led.setCursor(0, 0); 
    led.print("TIE");
    delay(3000);
    score();
  }
}

void Quit() {
  lcd.clearDisplay(0);
  led.clear();
  led.setCursor(0, 0);
  led.print("Game Quit");

  gaming = false;
  s00 = s03 = s06 = 0;
  s30 = s33 = s36 = 0;
  s60 = s63 = s66 = 0;
  chance = 0;
  page = 1;
  r = 0;
  c = 0;
  p1 = 0;
  p2 = 0;
  delay(500);
}

void score(){
  lcd.clearDisplay(0);
  led.clear();
  led.setCursor(0, 0);
  led.print("Player 1: ");
  led.print(p1);
  led.setCursor(0, 1);
  led.print("Player 2: ");
  led.print(p2);  
  gaming = false;
  s00 = s03 = s06 = 0;
  s30 = s33 = s36 = 0;
  s60 = s63 = s66 = 0;
  chance = 0;
  page = 1;
  r = 0;
  c = 0;
  delay(5000);
  led.clear();
  led.setCursor(0, 0);
  led.print("Press Select to");
  led.setCursor(0, 1);
  led.print("play again");
  delay(500);
}

void select() {
  if (!gaming) {
    if (page == 1) {
      led.clear();
      led.setCursor(0, 0);
      led.print("Game Confirmed");
      gaming = true;
      totalTurns = 0;
    }
  } else {
    if (getCurrentSlotOwner() == 0) {
      if (chance == 0) {
        setCurrentSlotOwner(1);
        lcd.setLed(0, r, c, true);
        lcd.setLed(0, r + 1, c, true);
        lcd.setLed(0, r, c + 1, true);
        lcd.setLed(0, r + 1, c + 1, true);
        chance = 1;
      } else if (chance == 1) {
        setCurrentSlotOwner(2);
        lcd.setLed(0, r, c, true);
        lcd.setLed(0, r + 1, c, false);
        lcd.setLed(0, r, c + 1, false);
        lcd.setLed(0, r + 1, c + 1, true);
        chance = 0;
      }
    }
    totalTurns +=1;
  }
}

void left() {
  if (!gaming)
    return;
  clear();
  if (c > 0) {
    c -= 3;
  }
}

void right() {
  if (!gaming)
    return;
  clear();
  if (c < 6) {
    c += 3;
  }
}

void up() {
  if (!gaming)
    return;
  clear();
  if (r > 0) {
    r -= 3;
  }
}

void down() {
  if (gaming) {
    clear();
    if (r < 6) {
      r += 3;
    }
  } else {
    page++;
    if (page > 3) page = 1;
  }
}

void setup() {
  Serial.begin(9600);
  button.attachClick(select);
  bUp.attachClick(up);
  bRight.attachClick(right);
  bLeft.attachClick(left);
  bDown.attachClick(down);

  button.setPressMs(4000);
  button.attachLongPressStart(Quit);

  lcd.shutdown(0, false);
  lcd.setIntensity(0, 10);
  lcd.clearDisplay(0);

  led.begin(16, 2);
}

void loop() {
  button.tick();
  bRight.tick();
  bUp.tick();
  bLeft.tick();
  bDown.tick();

  if (page != lastPage && !gaming) {
    led.clear();

    if (page == 0) {
      led.setCursor(0, 0);
      led.print("Welcome");
      led.setCursor(0, 1);
      led.print("Start");
    }
    if (page == 1) {
      led.setCursor(0, 0);
      led.print("1: Tic Tac Toe");
      led.setCursor(0, 1);
      led.print("Next page");
      
    }
    if (page == 2) {
      led.setCursor(0, 0);
      led.print("2: Tetris");
      led.setCursor(0, 1);
      led.print("Next page");
    }
    if (page == 3) {
      led.setCursor(0, 0);
      led.print("3: Settings");
      led.setCursor(0, 1);
      led.print("Next page");
    }

    lastPage = page;
  }

  if (gaming && page == 1) {
    ticTacToe();
  }
}
