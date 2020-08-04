

#include <NewTone.h>
#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremoteInt.h>
#include <IRremote.h>


//Codes der Fernbedienung
    //16753245  1
    //16736925  2
    //16769565  3
    //16720605  4
    //16712445  5
    //16761405  6
    //16769055  7
    //16754775  8
    //16748655  9
    //16718055 Pfeil nach oben
    //16730805 Pfeil nach unten
    //16716015 Pfeil nach links
    //16734885 Pfeil nach rechts
    //16726215 OK
    //16738455 *
    //16756815 #
    //16750695 0
/*************************************************
 * Public Constants
 *************************************************/
 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
 

//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

//Mario main theme tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

    

/*int greenled = 4;*/
int redled = A0;
int greenled = A1;
int blueled = A2;
int ledGND = A3;

int laser = 2;

int buzzer = 4;
int freq= 1200; // 31-65535

int motA =10;
int dirA = 12;

int motB =11;
int dirB = 13;

int IRGND=7;
int IRVCC=6;
int RECV_PIN = 5;

int infra1_left = 3;
int infra2_right= A5;

IRrecv irrecv(RECV_PIN);
decode_results results;

int remote = 1;

void setup() {
  // put your setup code here, to run once:

  //öffnet die Kommunikationskanäle
  Serial.begin(9600); //USB Kabel Serial Interface

  //pinMode konfiguriert die Pins als Ausgang
  pinMode(buzzer, OUTPUT);//buzzer
  
  pinMode(greenled, OUTPUT);
  digitalWrite(greenled, LOW);//digitalwrite schreibt ein Signal HIGH(5V) oder LOW(0V) auf den Pin
  
  pinMode(blueled, OUTPUT);
  digitalWrite(blueled, LOW);
  
  pinMode(redled, OUTPUT);
  digitalWrite(redled, LOW);

  pinMode(ledGND,OUTPUT);
  digitalWrite(ledGND,LOW);

  pinMode(laser, OUTPUT);
  digitalWrite(laser, LOW);
  
  pinMode(motA, OUTPUT);
  pinMode(motB, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);

  irrecv.enableIRIn(); //Empfänger gestartet
  pinMode(IRGND, OUTPUT);
  digitalWrite(IRGND, LOW);
  pinMode(IRVCC, OUTPUT);
  digitalWrite(IRVCC, HIGH);

  //pinMode konfiguriert die Pins als Ausgang/Eingang
  pinMode(infra1_left, INPUT);//links vom auto aus
  pinMode(infra2_right, INPUT);//rechts

}


void loop() {

  if (remote == 0)
  {
    blinken();
    remote++;
  
    sing();
    delay(2000);
    laseron();
    mario_sound();
    delay(2000);
    laseroff();
    delay(1000);
    goX(2000);
    left(2000);
    backX(2000);
    right(2000);
    halt();
  }
  else
  {
    if(irrecv.decode(&results))
    {
      //Serial.println(results.value);
      switch (results.value) {
      case 16718055:
        Serial.println("go");  
        go();    
        break;
      case 16730805:
        Serial.println("back");
        back();      
        break;
      case 16734885:
        Serial.println("right");  
        right(400);    
        break;
      case 16716015:
        Serial.println("left"); 
        left(400);     
        break;
      case 16726215:
        Serial.println("halt");
        halt();      
        break;
      case 16738455:
        Serial.println("blink");
        blinken();      
        break;        
      case 16756815:
        Serial.println("sing");   
        sing();   
        break;
      case 16750695:
        Serial.println("follow");   
        follow();   
        break;
      default:
        Serial.println(results.value);
        break;
      }
      //Serial.println(results.value);
      irrecv.resume();
    }    
  
  }
  

}//loop

void follow()
{

while(true)
  {
    if(digitalRead(infra1_left) == LOW && digitalRead(infra2_right) == LOW)
    {
      back();
    }
    else if(digitalRead(infra1_left) == HIGH && digitalRead(infra2_right) == LOW)
    {
      left(100);
    }
    else if(digitalRead(infra1_left) == LOW && digitalRead(infra2_right) == HIGH)
    {
      right(100);
    } 
    else if(digitalRead(infra1_left) == HIGH && digitalRead(infra2_right) == HIGH)
    {
      go();
    }   
  }
}

void blinken()
{
  digitalWrite(blueled,HIGH);
  digitalWrite(greenled,LOW);
  digitalWrite(redled,LOW);
  delay (500);
  digitalWrite(blueled,LOW);
  digitalWrite(greenled,HIGH);
  digitalWrite(redled,LOW);
  delay (500);
  digitalWrite(blueled,LOW);
  digitalWrite(greenled,LOW);
  digitalWrite(redled,HIGH);
  delay (500);
  digitalWrite(blueled,LOW);
  digitalWrite(greenled,LOW);
  digitalWrite(redled,LOW);
}

//nicht in Verwendung
/*void laseron ()
{
  digitalWrite(laser,HIGH);  
}

void laseroff ()
{
  digitalWrite(laser,LOW);  
}*/


void sing()//Funktionsdefinition
{
  NewTone(buzzer, freq, 300); //pin, frequenz, länge
  delay (600);//Pause dazwischen
  NewTone(buzzer, freq, 300);
  delay (600);//Pause dazwischen
  NewTone(buzzer, freq, 300);
  delay (600);//Pause dazwischen
  NewTone(buzzer, freq/2, 2000);
  delay (2000);
  noNewTone(buzzer); 
  
}

void halt()
{
  digitalWrite(motA, LOW);
  digitalWrite(motB, LOW);  
  delay (200);  
}


void right(int x){
  digitalWrite(dirA, LOW);
  digitalWrite(dirB, HIGH);
  digitalWrite(motA, HIGH);
  digitalWrite(motB, HIGH);
  delay(x);
  //halt();
}

void left(int x){
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, LOW);
  digitalWrite(motA, HIGH);
  digitalWrite(motB, HIGH);
  delay(x);
  //halt();
}
void goX(int x){
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, HIGH);
  digitalWrite(motA, HIGH);
  digitalWrite(motB, HIGH);
  delay(x);
}

void backX(int x){
  digitalWrite(dirA, LOW);
  digitalWrite(dirB, LOW);
  digitalWrite(motA, HIGH);
  digitalWrite(motB, HIGH);
  delay(x);
}

void go(){
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, HIGH);
  digitalWrite(motA, HIGH);
  digitalWrite(motB, HIGH);
}

void back(){
  digitalWrite(dirA, LOW);
  digitalWrite(dirB, LOW);
  digitalWrite(motA, HIGH);
  digitalWrite(motB, HIGH);
}

void accelerate()
{
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, HIGH);
  for (int speed = 255; speed>0;speed--)
  {
    analogWrite(motA,speed);
    analogWrite(motB,speed);  
    delay(50);
  }
  
}


void buzz(int targetPin, long frequency, long length) {
  
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}
  
void mario_sound() {
  // iterate over the notes of the melody:

      int size = sizeof(melody) / sizeof(int);
      for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];
 
      buzz(buzzer, melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(buzzer, 0, noteDuration);
    }//end for


  }//end mario_sound







