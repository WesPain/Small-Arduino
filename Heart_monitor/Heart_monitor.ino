
//define A1 1
//define B1 2
//define C1 3
//define D1 4
//define E1 5
//define F1 6
//define G1 7
//define G3 8
//define A2 9
//define B2 10
//define C2 11
//define D2 12
//define E2 13
//define F2 14
//define G2 15
int puls=0;
int prevPuls=0;
byte TenPlass = 10;
unsigned long timeer;
unsigned long timerS;
unsigned long runder;
unsigned long resete;
unsigned long duration;
boolean StateWhat = false;
int edge =0;
int prevEdge=0;
byte TENseven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                                           { 0,1,1,0,0,0,0 },  // = 1
                                                           { 1,1,0,1,1,0,1 },  // = 2
                                                           { 1,1,1,1,0,0,1 },  // = 3
                                                           { 0,1,1,0,0,1,1 },  // = 4
                                                           { 1,0,1,1,0,1,1 },  // = 5
                                                           { 1,0,1,1,1,1,1 },  // = 6
                                                           { 1,1,1,0,0,0,0 },  // = 7
                                                           { 1,1,1,1,1,1,1 },  // = 8
                                                           { 1,1,1,0,0,1,1 }   // = 9
                                                           };
//this part of the code is 2D array the decides what number should be shown on the LCD by toggeling some of the pins
//the array contains the numbers from 0-9 and the pins needed for the numbers to show on the lcd
//one segment is driven by one pin in this code the drawback is the number of pins needed to drive the lcd.
byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                                           { 0,1,1,0,0,0,0 },  // = 1
                                                           { 1,1,0,1,1,0,1 },  // = 2
                                                           { 1,1,1,1,0,0,1 },  // = 3
                                                           { 0,1,1,0,0,1,1 },  // = 4
                                                           { 1,0,1,1,0,1,1 },  // = 5
                                                           { 1,0,1,1,1,1,1 },  // = 6
                                                           { 1,1,1,0,0,0,0 },  // = 7
                                                           { 1,1,1,1,1,1,1 },  // = 8
                                                           { 1,1,1,0,0,1,1 }   // = 9
                                                           };


                                                           
                                                           
int sensorpin =A5;
int sensorValue=0;
float voltage=0;
int LCDprint =0;
int LCDTENprint =0;
void setup() {
  // put your setup code here, to run once:
  //analogReference(INTERNAL);
  Serial.begin (9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(19,INPUT);
  
  

}
void sevenSegWrite(byte digit) {
  byte pin = 10;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}
//this loop decides what number the lcd should write, so the order of pin is imporant
//the loop wil first start with a pin the digit then decides what "row" digitalWrite should extract information from
//segCount will then decide if the folowing pin should be high or low. digit decides nr while segCount decides segment status (Hi or Lo)
//an exsample: sevenSegWrite(0) means the digitalwrite will begin from pin 10
//then seven_seg_digits[0][0/1/2/3/4/5/6/7] begin interating through row 0 and column 0 to 7, as there are 7 segments

void TENsevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}
void HUNDREsevenSegWrite(int overHundre){
  if(overHundre == 1){
    digitalWrite(17,1);
    digitalWrite(18,1);
  }
  else{
    digitalWrite(17,0);
    digitalWrite(18,0);
  }
    
}

void loop() {
 //the millis function counts elapsed time since the program started
 //the timer is made by setting a variable to millis() then subtracting the variable from millis
 // if the millis()-timerX>= Xval the timer has expired and the program will exicute.
 //ul is to force the 100 to become an unsigned long as this is a requirement for the timer to work properly
 //hvi millis - timer stÃ¸rre enn 100 da har timeren gÃ¥tt ut og det som skjer i iflÃ¸kka blir kjÃ¸rt
  if(millis()-timerS>=120UL){
  timerS=millis(); 
  edge = digitalRead(19);
  }
  //set the digitalRead to avoid bouncing (the signal is read only once)
  
  if(edge){
    if(edge==1){
      puls++;
      StateWhat=false;
      Serial.println("den er high");
      digitalWrite(9,LOW);
    }
  }
  else if(!edge&&!StateWhat){ //if the edge (signal from the ir) is low and the StateWhat is false
    Serial.println("Low, initiating countdown"); //the second parameter is necessary or else this will trigger everytime
    StateWhat=true; //the edge is low. 
    resete=millis();
    digitalWrite(9,LOW);
  }
    
  edge=prevEdge;
  Serial.println(timeer);
 // Serial.println(puls);
  //count for 15 seconds, then print the value of puls*4 to the lcd
 
  if(millis()-timeer>=15000UL){
    Serial.println(puls);
    timeer = millis();
    int hjerteInfarkt = puls*4;
    Serial.println(hjerteInfarkt);
    
    if(hjerteInfarkt>99){
     LCDprint = hjerteInfarkt%10; //The 7 seg lcd only recognizes one nr, this prints to the 1sts
     LCDTENprint = (hjerteInfarkt/10)%10; //this prints to the tenths
     sevenSegWrite(LCDprint);
     TENsevenSegWrite(LCDTENprint);
     HUNDREsevenSegWrite(1);
     puls=0;
    }
    else{ 
     LCDprint = hjerteInfarkt%10; //the firsts
     LCDTENprint = hjerteInfarkt/10;//thenths
     sevenSegWrite(LCDprint);
     TENsevenSegWrite(LCDTENprint);
     HUNDREsevenSegWrite(2);
     puls=0;
    }
   }
  if(millis()-resete>=3000){ //this function resets the timer and the heart rate. 
      Serial.println(puls);
      Serial.println("jeg er ikke berort paa 3 sekunder");
      timeer = millis();
      digitalWrite(9,HIGH);
      sevenSegWrite(0);
      TENsevenSegWrite(0);
      HUNDREsevenSegWrite(2);
      puls=0;
      //Buffere();
   }
}


void Buffere(){
  for(int i =0; i<19;++i){
    digitalWrite(i,0);  
  }
}


