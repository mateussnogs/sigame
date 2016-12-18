#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Pixy.h>

int ENABLE1 = 3; //PINO ENABLE
int ENABLE2 = 4;
int IN1 = 5; 
int IN2 = 6;
int IN3 = 7; 
int IN4 = 8;


Pixy pixy;

int signature = 0;
int x = 0;
int y = 0;
unsigned int width = 0;
unsigned int height = 0;
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 70;
int Xmax = 200;
int maxArea = 0;
int minArea = 0;
static int i = 0;
int j;
char buf[32];

void setup(){ 

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT); 
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT); 
  pinMode(ENABLE1,OUTPUT); 
  pinMode(ENABLE2,OUTPUT); 
  Serial.begin(9600);
  pixy.init();

}

void loop(){ 

  while(millis()<5000){
    scan();
    area = width * height;
    maxArea = area + 1000;
    minArea = area - 1000;

  }

  scan(); 

  if(signature == 1){
     
    newarea = width * height;
    
    if (x < Xmin){     
      left();
    }
    else if (x > Xmax){
      right();
    }
    else if(newarea < minArea){
      forward(); 
    }
    else if(newarea > maxArea){
      backward(); 
    }      
    else{
      Stop(); 
    } 
  }
   
  else{
    Stop();
  }

}

void backward(){

    //Serial.print("Backwarding\n");    
    digitalWrite(ENABLE1, HIGH); //VELOCIDADE DO MOTOR
    digitalWrite(ENABLE2, HIGH); //VELOCIDADE DO MOTOR
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

}

void forward(){

    //Serial.print("Forwarding\n");
    digitalWrite(ENABLE1, HIGH); //VELOCIDADE DO MOTOR
    digitalWrite(ENABLE2, HIGH); //VELOCIDADE DO MOTOR
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);

}

void right(){

    //Serial.print("Righting\n");
    digitalWrite(ENABLE1, HIGH); //VELOCIDADE DO MOTOR
    digitalWrite(ENABLE2, HIGH); //VELOCIDADE DO MOTOR
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

}

void left(){

    //Serial.print("Lefting\n");
    digitalWrite(ENABLE1, HIGH); //VELOCIDADE DO MOTOR
    digitalWrite(ENABLE2, HIGH); //VELOCIDADE DO MOTOR
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);

}

void Stop(){

    Serial.print("Stopped\n");
    digitalWrite(ENABLE1, 0); //VELOCIDADE DO MOTOR
    digitalWrite(ENABLE2, 0); //VELOCIDADE DO MOTOR}

}
    
void scan(){

  uint16_t blocks;
  blocks = pixy.getBlocks();
  signature = pixy.blocks[i].signature;
  
  x = pixy.blocks[i].x;
  y = pixy.blocks[i].y;
  width = pixy.blocks[i].width;
  height = pixy.blocks[i].height;

}
