// Jon Turnquist OTR/L
// St Ambrose University
// turnquistjonc@sau.edu
// uses a uno shield to read a sparkfun analog joystick
// and then control two DC motors via two REV spark motor controllers

//view output using the serial monitor

#include <Servo.h> 
Servo myservoS1;
Servo myservoS2;


int potpinS1 = 0;  //analog input pin A0
int potpinS2 = 1;

int newvalS1;
int newvalS2;
int EXvalS1;
int EXvalS2;
int  D1;
int  D2;
int Delta;
int cop;
int MC =1;
int LL = 66;    //set limits
int HL = 115;

void setup() 
{
  Serial.begin(9600);  
 myservoS1.attach(9, 1000, 2000);  
 myservoS2.attach(10, 1000, 2000);
//digitalWrite(4, LOW); 
//digitalWrite(6, HIGH); 


pinMode(3, INPUT);           // set pin to input
digitalWrite(3, HIGH);       
 
pinMode(4, INPUT);           // set pin to input
digitalWrite(4, HIGH);      

pinMode(5, INPUT);           // set pin to input
digitalWrite(5, HIGH);   

pinMode(6, INPUT);           // set pin to input
digitalWrite(6, HIGH);         

 Serial.println("Joystick AD output");   
 
}


 
   
void loop() 
{ 
  newvalS1 = analogRead(potpinS1);     // adjust upper map number to match other joystick axis      
  newvalS1 = map(newvalS1, 0, 1023, 0, 180); // adjust here or there for pot adjustment
delay (100);
newvalS2 = analogRead(potpinS2);
newvalS2 = map(newvalS2, 0, 1023, 0, 175);  // adjust here or there for pot adjustment
int Pin3 = digitalRead(3);
int Pin4 = digitalRead(4);
int Pin5 = digitalRead(5);
int Pin6 = digitalRead(6);

  Serial.print("MC= ");
  Serial.println(MC);
  
  Serial.print("Pin3 = ");
  Serial.println(Pin3);
  Serial.print("Pin4 = ");
  Serial.println(Pin4);
  Serial.print("Pin5 = ");
  Serial.println(Pin5);
  Serial.print("Pin6 = ");
  Serial.println(Pin6);
  

if (Pin3 == 0) // slowest: change numbers for fast (HL) and slow (LL) limits
{
  LL = 70;      // all stop is 86 and the farther from this 86 (total range 0 to 171 ) is faster 
  HL = 110;
}
 
if (Pin4 == 0)// mid slow: 
{
  LL = 65;
  HL = 115;
}

if (Pin5 == 0)// mid: 
{
  LL = 60;
  HL = 120;
}

if (Pin6 == 0) //fastest : change numbers for fast (HL) and slow (LL) limits
{
  LL = 55;
  HL = 125;
}


Serial.print("LL = ");
  Serial.println(LL);
  Serial.print("HL = ");
  Serial.println(HL);


//newvalS2 = constrain(newvalS2, 66, 115);  old one speed only
//newvalS1 = constrain(newvalS1, 66, 115);

  newvalS2 = constrain(newvalS2, LL, HL);  
  newvalS1 = constrain(newvalS1, LL, HL);
 
  if ((newvalS2)>82 && (newvalS2) <87 && (newvalS1) >85 &&(newvalS1) <89) 
 {
 MC =1; // no movement
 D1 = 86;   //motor 1 Right full stop
 D2 = 86;   //motor 2 Left full stop
 }

if  ((newvalS1) > 90  && (newvalS2) >82  &&(newvalS2) <88) // adjust numbers to change joystick sen.
{ 
   MC = 8; // Forward
}

 if  ((newvalS1) <84  && (newvalS2) >83  &&(newvalS2) <88) // right spin
{ 
   MC = 5; //rev
}

if  ((newvalS2) >88 && (newvalS1) >85 &&(newvalS1) <89) // left
{ 
   MC = 2;  // left
}
  
if ((newvalS2)<81  && (newvalS1) >85 &&(newvalS1) <89) 
{ 
   MC = 3; // right
}
if ((newvalS1)<80 && (newvalS2) >89) 
 {
    MC =4;     // slight left reverse
 }
  
if ((newvalS2)<80  && (newvalS1) <83) 
{ 
   MC = 6; //silght right reverse
}

if ((newvalS2) > 89  && (newvalS1) > 91) 
{ 
   MC = 7; //silght left  forward
}

if ((newvalS2)< 83  && (newvalS1) > 89) 
{ 
   MC = 9; //silght right  forward
}

switch (MC) {
     case 1: //all off
 myservoS1.write(newvalS1);  //motor 1
 myservoS2.write(newvalS2);  //motor 2 
EXvalS2 = D2;
EXvalS1 = D1;
cop = 0;
Serial.print("ALL STOP");
  Serial.println("   ");
 Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
   
       break;     

case 2: // left

// 2 = 110 - 70

if (cop == 4)
{
  myservoS1.write(D1);  //motor 1 stop for pause from forward to reverse first time through
  myservoS2.write(D2); 
  delay (500);
}

cop = 3;

Delta = (newvalS2 - D2);
//Delta = (Delta - 10); to have greater movement??
EXvalS2 = ( D2 - Delta );
 
if (EXvalS2 < 70)
{
 EXvalS2 = 70;
}
   
  myservoS2.write(EXvalS2);  
  //myservoS2.write(EXvalS2);  //motor 1 Left
  myservoS1.write(newvalS2);  //motor 2 right

Serial.print("DELTA =");
   Serial.println(Delta);

Serial.print("EXvalS2 =");
   Serial.println(EXvalS2);

 Serial.print("LEFT ");
   Serial.println("   ");

 Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
       break;

 case 9://Right & Forward 

 myservoS2.write(newvalS1);  //motor 2 is left ; stopped
 myservoS1.write(D1);  //motor 1 is right is forward
   Serial.print("Right & Forward");
 Serial.println("   ");
  Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);      
       break;
       
  case 3:// right

if (cop == 3)
{
  myservoS1.write(D1);  //motor 1 stop for pause from forward to reverse first time through
  myservoS2.write(D2); 
  delay (500);
}

cop = 4;

Delta = ( D2 - newvalS2);
Delta = (Delta +8);
EXvalS2 = ( D2 + Delta );
 
if (EXvalS2 >110)
{
 EXvalS2 = 110;
}
   //  EXvalS1 = 108;
  myservoS2.write(EXvalS2);  
  //myservoS2.write(EXvalS2);  //motor 1 Left
  myservoS1.write(newvalS2);  //motor 2 right
  // myservoS2.write(newvalS1); // left motor forward

Serial.print("DELTA =");
   Serial.println(Delta);

Serial.print("EXvalS2 =");
   Serial.println(EXvalS2);

  Serial.print("Right ");
 Serial.println("   ");
 Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
 Serial.print("2EX- ");    
 Serial.println(EXvalS2);   
 Serial.print("DELTA- ");    
 Serial.println(Delta); 
         break;
    
case 8:// Forward 

if (cop == 2)// if straight from reverse a delay will happen
{
  myservoS1.write(D1);  //motor 1 stop for pause from forward to reverse first time through
  myservoS2.write(D2); 
  delay (500);
}

cop = 1;
 EXvalS1 = newvalS1;
   
 myservoS1.write(newvalS1);  //motor 1 is now right
 myservoS2.write(EXvalS1);  //motor 2  is now left

 Serial.print(" Forward");
 Serial.println("");
Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
Serial.print("2EX- ");    
 Serial.println(EXvalS1);

       break;
       
  case 7://left forward 

 delay (20);
 myservoS2.write(D2); 
 
  myservoS1.write(newvalS2); 
 
 Serial.print(" Left & Forward");
  Serial.println("   ");
 
  Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);           
       break;
 
case 6://Right reverse slight


myservoS2.write(D2);  
 myservoS1.write(newvalS1); 
 Serial.print("Right reverse slight");
 Serial.println("   ");

Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
      
       break;


 case 5: //Rev


Serial.print("Cop =  ");
Serial.println(cop);

if (cop == 1)
{
  myservoS1.write(D1);  //motor 1 stop for pause from forward to reverse first time through
  myservoS2.write(D2); 
  delay (500);
}
 cop = 2;  
EXvalS1 = newvalS1; 
Serial.print("Reverse ");
Serial.println("   ");
 
  Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
Serial.print("2EX- ");    
 Serial.println(EXvalS1);


  myservoS1.write(newvalS1);  //motor 2
  myservoS2.write(EXvalS1);  //motor 1  copies motor 2
 
       break;

case 4://Reverse Left 


 myservoS1.write(D1);  
 myservoS2.write(newvalS1); 
Serial.print("Reverse and Left slight");
Serial.println("   ");

Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
  
       break;

       
     default: 
       // if nothing else matches, do the default
       // default is optional
     break;
   }

delay (200);
  
  }




