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
byte TenPlass = 10; 
//Bytes holding the bit data for the different segments on the LCD display
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
  //pinMode(A5,OUTPUT);
  pinMode(16,OUTPUT);
  //pinMode(8, OUTPUT);
  pinMode(15,OUTPUT);
  
  

}
void sevenSegWrite(byte digit) { //writes for 0-9
  byte pin = 10;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}
void TENsevenSegWrite(byte digit) { //writes the thents
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}
void loop() {
  
 int sensorValue = analogRead(sensorpin); //forklare
  float voltage = (sensorValue * (5.0 / 1024))*100; //forlkare
  LCDprint = (int) voltage%10;  //This operation is needed to extract the remineder of deviding by 10
  LCDTENprint = (int)voltage/10; 
  delay(10);
  sevenSegWrite(LCDprint);
  TENsevenSegWrite(LCDTENprint);
  delay(10);
  //Buffere();
  // print out the value you read:
  Serial.println(voltage);
  //Serial.println(LCDprint);
  
   
 /*  for (byte count = 10; count > 0; --count){
   delay(1000);
   sevenSegWrite(count - 1);
   TENsevenSegWrite(TenPlass - 1);
   //*if(count-1==0){
   TenPlass--;
  }
  delay(4000);*/

}

void Buffere(){
  for(int i =0; i<17;++i){
    digitalWrite(i,0);  
  }
}

