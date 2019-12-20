#include <Wire.h>                        // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 1602 I2C용 라이브러리
#include <MsTimer2.h>                 // 타이머 헤더파일
LiquidCrystal_I2C lcd(0x27,16,2);     // 접근주소: 0x3F or 0x27

// 7세그먼트
byte data[]={0x67, 0x7f, 0x07,0x7c,0x6d, 0x66, 0x4F, 0x5B, 0x06, 0x3F};
#define clockPin A1
#define latchPin A2
#define dataPin A3
//

/////////////////배경음악 정의
#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 
int piezoPin = 10;
int tempo = 200; // duration 옵션 값 설정 
int notes[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C }; 
/////////////////배경음악 정의

/////////////////버튼 값들 정의
const int startButton = 6;
const int redButton=3;
const int greenButton=4;
const int blueButton=5;
const int redLed=7;
const int greenLed=8;
const int blueLed=9;
const int whiteButton=12;
const int whiteLed=11;
int startState=0;
int startcount=0;
int roundcount=0;
int win = 0;
/////////////////버튼 값들 정의

/////////////////solution 함수변수정의
int numarray[10]={0,0,0,0,0,0,0,0,0,0};
int compare[10]={0,0,0,0,0,0,0,0,0,0};
int redstate=0;
int bluestate=0;
int greenstate=0;
int whitestate=0;
int redcount=0;
int bluecount=0;
int greencount=0;
int whitecount=0;
int solutioncount=0;
/////////////////solution 함수변수정의

/////////////////problem 함수변수정의
int pronum=0;
int previous;
int whilecount=0;
int round1=1;
int round2=1;
int round3=1;
int round4=1;
/////////////////problem 함수변수정의

/////////////////타이머 함수변수정의
int segindex=0;
int killall = 0;
/////////////////타이머 함수변수정의

void setup()
{
// 7(segment)
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
//

///////////////////////////////////////// 타이머 함수 선언
    MsTimer2::set(1000,kill);
///////////////////////////////////////// 타이머 함수 선언

///////////////////////////////////////// 버튼 셋업
    pinMode(startButton, INPUT); 
    pinMode(redButton, INPUT); 
    pinMode(greenButton, INPUT); 
    pinMode(blueButton, INPUT); 
    pinMode(whiteButton, INPUT); 
///////////////////////////////////////// 버튼 셋업

///////////////////////////////////////// LED 셋업
    pinMode(redLed, OUTPUT); 
    pinMode(greenLed, OUTPUT); 
    pinMode(blueLed, OUTPUT); 
    pinMode(whiteLed,OUTPUT);
///////////////////////////////////////// LED 셋업

///////////////////////////////////////// LCD모듈
    lcd.begin(); //LCD 사용 시작
    lcd.backlight();          
    lcd.setCursor(0, 0);    
    lcd.print("Welcome Game!");            
    lcd.setCursor(0, 1);    
    lcd.print("Get Ready?"); 
///////////////////////////////////////// LCD모듈

/////////////////////////////////////////7세그먼트 셋업
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
/////////////////////////////////////////7세그먼트 셋업

    Serial.begin(9600);
    
///////////////////////////////////// 배경음악
  pinMode (piezoPin, OUTPUT); 
   for (int i = 0; i < 12; i++) { 
    tone (piezoPin, notes[ i ], tempo); 
    delay (300); 
  } 
  delay(700); // 멜로디 중간에 짧게 멈추는 용도 

  for (int i = 12; i < 25; i++) { 
    tone (piezoPin, notes[ i ], tempo); 
    delay(300); 
  } 
/////////////////////////////////// 배경음악
}

void loop()
{
  int temp=0;
  startState = digitalRead(startButton);  
  
//스타트버튼을누르면 스타트 카운트가 증가됌
  if(startState == HIGH){         
    startcount++;   
  } 
  Serial.print("startcount==");
  Serial.println(startcount);
  Serial.print("roundcount==");
  Serial.println(roundcount);
  if(startcount==1&&roundcount==0)
  {
    startcount=0;
    lcd.clear();
    lcd.setCursor(0, 0);    
    lcd.print("Round 1 Start!");             
    lcd.setCursor(0, 1);    
    lcd.print("See Pattern");
    roundcount=1;
    delay(1000);
  }
  else if(startcount==1&&roundcount==1)
  {
    startcount=0;
    lcd.clear();
    lcd.setCursor(0, 0);    
    lcd.print("Round 2 Start!");
    lcd.setCursor(0, 1);    
    lcd.print("See Pattern");
    roundcount=2;
    delay(1000);
  }
  else if(startcount==1&&roundcount==2)
  {
    startcount=0;
    lcd.clear();
    lcd.setCursor(0, 0);    
    lcd.print("Round 3 Start!");             
    lcd.setCursor(0, 1);    
    lcd.print("See Pattern");
    roundcount=3;
    delay(1000);
  }
  else if(startcount==1&&roundcount==3)
  {
    startcount=0;
    lcd.clear();
    lcd.setCursor(0, 0);    
    lcd.print("Round 4 Start!");             
    lcd.setCursor(0, 1);    
    lcd.print("See Pattern");
    roundcount=4;
    delay(1000);
  }

  if(roundcount==1&&round1==1)
  {
    round1=0;
    problem(3);
    whilecount=0;
    solution(3);
  }
  else if(roundcount==2&&round2==1)
  {
    round2=0;
    problem(4);
    whilecount=0;
    solution(4);
  }
  else if(roundcount==3&&round3==1)
  {
    round3=0;
    problem(5);
    whilecount=0;
    solution(5);
  }
  else if(roundcount==4&&round4==1)
  {
    round4=0;
    problem(6);
    whilecount=0;
    solution(6);
    win = 1;
  }

  if(win==1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);    
    lcd.print("YOU WIN YOU WIN");             
    lcd.setCursor(0, 1);    
    lcd.print("YOU WIN YOU WIN");
    return;
  }
}

void problem(int num)
{
  //7세그먼트 끄는 코드.
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, HIGH);
  segindex=0;

  for(int i = 0 ; i < num ; i++)
  {
    pronum = random(4);
    while(whilecount>0)
    {
      if(pronum==previous)
      {
        pronum = random(4);
      }
      else
      {
        break;
      }
    }
    if(pronum==0)
    {
      digitalWrite(redLed,HIGH);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,LOW);
      digitalWrite(whiteLed,LOW);
      delay(1000);
    }
    else if(pronum==1)
    {
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,HIGH);
      digitalWrite(blueLed,LOW);
      digitalWrite(whiteLed,LOW);
      delay(1000);
    }
    else if(pronum==2)
    {
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,HIGH);
      digitalWrite(whiteLed,LOW);
      delay(1000);
    }
    else if(pronum==3)
    {
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,LOW);
      digitalWrite(whiteLed,HIGH);
      delay(1000);
    }
    numarray[i]=pronum;
    previous=pronum;
    whilecount++;
  }
   digitalWrite(redLed,LOW);
   digitalWrite(greenLed,LOW);
   digitalWrite(blueLed,LOW);
   digitalWrite(whiteLed,LOW);
}

void solution(int num)
{
    MsTimer2::start();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press!!!");   
    lcd.setCursor(0, 1);
    lcd.print("Answer!!!");
  while(solutioncount<num)
  {
    if(killall==10)
    {
      for(int i = 0 ; i < 10 ; i++)
      {
        numarray[i]=0;
        compare[i]=0;
      }
      MsTimer2::stop();
      killall=0;
      roundcount=0;
      round1=1;
      round2=1;
      round3=1;
      round4=1;
      pronum=0;
      lcd.clear();
      lcd.setCursor(0, 0);    
      lcd.print("You Lose!!!");             
      lcd.setCursor(0, 1);    
      lcd.print("Time Out!!!");
      return;
    }
    redstate = digitalRead(redButton); 
    bluestate = digitalRead(blueButton); 
    greenstate = digitalRead(greenButton); 
    whitestate = digitalRead(whiteButton); 

    if(redstate==1)
    {
      redcount=0;
      compare[solutioncount]=0;
      solutioncount++;
      digitalWrite(redLed,HIGH);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,LOW);
      digitalWrite(whiteLed,LOW);
      delay(1000);
    }
    else if(greenstate==1)
    {
      greencount=0;
      compare[solutioncount]=1;
      solutioncount++;
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,HIGH);
      digitalWrite(blueLed,LOW);
      digitalWrite(whiteLed,LOW);
      delay(1000);
    }
    else if(bluestate==1)
    {
      bluecount=0;
      compare[solutioncount]=2;
      solutioncount++;
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,HIGH);
      digitalWrite(whiteLed,LOW);
      delay(1000);
    }
    else if(whitestate==0)
    {
      whitecount=0;
      compare[solutioncount]=3;
      solutioncount++;
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,LOW);
      digitalWrite(whiteLed,HIGH);
      delay(1000);
    }
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,LOW);
      digitalWrite(whiteLed,LOW);
  }
    solutioncount=0;
    answer(num);
}

void answer(int num)
{
  MsTimer2::stop();
  killall=0;
  int compare2=0;
  for(int i = 0 ; i<num ; i++)
  {
    if(compare[i]==numarray[i])
    {
      compare2++;
    }
  }
  for(int i = 0 ; i < 10 ; i++)
  {
    numarray[i]=0;
    compare[i]=0;
  }
  if(compare2==num)
  {
    lcd.clear();
    lcd.setCursor(0, 0);    
    lcd.print("Excellent! Let's go");             
    lcd.setCursor(0, 1);    
    lcd.print("Next Round!");
    delay(3000);
  }
  else
  {
    roundcount=0;
    round1=1;
    round2=1;
    round3=1;
    round4=1;
    pronum=0;
    lcd.clear();
    lcd.setCursor(0, 0);    
    lcd.print("You Fail!!! Press");             
    lcd.setCursor(0, 1);    
    lcd.print("Start Button");
    delay(3000);
  }
}

void kill()
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, data[segindex]);
    digitalWrite(latchPin, HIGH);
    segindex++;
    killall++;
}
