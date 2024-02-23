#include <Arduino.h>
#include <TimerOne.h>
#define R1 12
#define G1 13
#define B1 14
#define R2 25
#define G2 26
#define B2 27
#define R3 5
#define G3 18
#define B3 19
#define R4 21
#define G4 22
#define B4 23
#define R5 2
#define G5 0
#define B5 4
//set new rgb pin here

////////////////////////////
#define LED 33
#define Reset_Button 15
#define ButtonY 16
#define ButtonN 17
///////////////////////////////
int state = 1;
int button_state = 0;
int change_allow = 0;
int reset_state = 0;
int r_color = NULL;
int g_color = NULL;
int b_color = NULL;
/////////////////////////////
void RGB_BEEP(int r_pin,int g_pin,int b_pin){
    if(r_color == 0){
      r_color = 200;
      g_color = 50;
      b_color = 0;
    }else{
      r_color = 0;
      g_color = 0;
      b_color = 0;
    }
    analogWrite(r_pin,r_color);
    analogWrite(g_pin,g_color);
    analogWrite(b_pin,b_color);
}

void RESET(){
  reset_state = 1;
}

void BUTTON1(){
  button_state = 1;
}

void BUTTON2(){
  button_state = 2;
}

void RGB_RED(int r_pin ,int g_pin,int b_pin){
  analogWrite(r_pin,255);
  analogWrite(g_pin,0);
  analogWrite(b_pin,0);
}

void RGB_GREEN(int r_pin ,int g_pin,int b_pin){
  analogWrite(r_pin,0);
  analogWrite(g_pin,255);
  analogWrite(b_pin,0);
}

void MAIN_FUNC(){
  // Serial.println("TEST_MAIN");
  if(state == 1){
    reset_state = 0;
    if((button_state == 1)&(change_allow == 0)){
      RGB_GREEN(R1,G1,B1);
      button_state = 0;
      state = 2;
    }else if((button_state == 2)&(change_allow == 0)){
      RGB_RED(R1,G1,B1);
      button_state = 0;
      state = 2;
    }
  }else if(state == 2){
    if((button_state == 1)&(change_allow == 0)){
      RGB_GREEN(R2,G2,B2);
      button_state = 0;
      state = 3;
    }else if((button_state == 2)&(change_allow == 0)){
      RGB_RED(R2,G2,B2);
      button_state = 0;
      state = 3;
    }
  }else if(state == 3){
    if((button_state == 1)&(change_allow == 0)){
      RGB_GREEN(R3,G3,B3);
      button_state = 0;
      state = 4;
    }else if((button_state == 2)&(change_allow == 0)){
      RGB_RED(R3,G3,B3);
      button_state = 0;
      state = 4;
    }
  }else if(state == 4){
    if((button_state == 1)&(change_allow == 0)){
      RGB_GREEN(R4,G4,B4);
      button_state = 0;
      state = 5;
    }else if((button_state == 2)&(change_allow == 0)){
      RGB_RED(R4,G4,B4);
      button_state = 0;
      state = 5;
    }
  }else if(state == 5){
    if((button_state == 1)&(change_allow == 0)){
      RGB_GREEN(R5,G5,B5);
      button_state = 0;
      state = 6;
    }else if((button_state == 2)&(change_allow == 0)){
      RGB_RED(R5,G5,B5);
      button_state = 0;
      state = 6;
    }
  }
  ///////////////////////////
  if(state == 1){
    RGB_BEEP(R1,G1,B1);
  }else if(state == 2){
    RGB_BEEP(R2,G2,B2);
  }else if(state == 3){
    RGB_BEEP(R3,G3,B3);
  }else if(state == 4){
    RGB_BEEP(R4,G4,B4);
  }else if(state == 5){
    RGB_BEEP(R5,G5,B5);
  }

  if(reset_state == 1){
    asm volatile ("  jmp 0");  //asm volatile ("  jmp 0");   if use in mega
  }
}



void setup() {
  Serial.begin(9600);
  pinMode(Reset_Button, INPUT);
  pinMode(ButtonY, INPUT);
  pinMode(ButtonN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(G4, OUTPUT);
  pinMode(B4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(G5, OUTPUT);
  pinMode(B5, OUTPUT);
  ///////////////////////////////////////
  
  attachInterrupt(ButtonY,BUTTON1,HIGH);
  attachInterrupt(ButtonN,BUTTON2,HIGH);
  attachInterrupt(Reset_Button,RESET,HIGH);
/////////////////////MAIN//////////////////////////////
  Timer1.initialize(500000);
  Timer1.attachInterrupt(MAIN_FUNC);
  Timer1.start();

}

void loop() {
  Serial.print("State: ");
  Serial.println(state);
  // Serial.print("Button State: ");
  // Serial.println(button_state);
  // Serial.print("Allow State: ");
  // Serial.println(change_allow);
  // Serial.print("Reset State: ");
  // Serial.println(reset_state);
  delay(500);
}

