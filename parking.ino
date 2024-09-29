#define BLYNK_TEMPLATE_ID "TMPL3DvBHUTUX"
#define BLYNK_TEMPLATE_NAME "Smart Parking system"96
#define BLYNK_AUTH_TOKEN "qXQXh-jf77j9l8OFifLJSrttLUeGbWNO"
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

int ir_pin1 = 34;
int ir_pin2 = 35;
int ir_pin3 = 36;
int ir_pin6 = 39;

int ir_pin4 = 27;
int ir_pin5 = 33;

int led_red1 = 13;
int led_red2 = 12;
int led_green1 = 14;
int led_green2 = 32;

int buzz = 25;

int servo_pin = 15;
int servo_pin2 = 5;
LiquidCrystal_I2C lcd(0x27, 20, 4);

bool s1 = true;
bool s2 = true;
bool s3 = true;
bool s4 = true;

Servo myservo;
Servo myservo2;

char ssid[] = "Avijit";
char pass[] = "12345678";
 
#define SS_PIN 2
#define RST_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);

String card_holder_name;
const String sheet_url = "https://script.google.com/macros/s/AKfycbxly1tbfSD39sSc1-KgENEiAxQfvW39qwY5rjUtQEJQV3bdBCB9fUrDtqggUZDl9pIc/exec?name=";

bool chk = true;
bool chk2 = true;

BLYNK_WRITE(V4)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1 && chk == true)
  {
    for(int i = 0 ; i <= 90 ; i++){
      myservo.write(i);
      delay(10);
    }
    chk = false;

    String requestURL = sheet_url + "Avijit_Biswas";
    Serial.println("Sending to Google Sheets: " + requestURL);
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    https.begin(client, requestURL);
    https.GET();
    https.end();
    
    digitalWrite(led_green1,HIGH);
    digitalWrite(led_red1,LOW);
  }
  
  if(value == 0 && chk == false)
  {
    digitalWrite(led_green1,LOW);
    digitalWrite(led_red1,HIGH);
    delay(200);
    for(int i = 90 ; i>=0 ;i--) {
      myservo.write(i);
      delay(10);
    } 
    chk = true;
  }
}


void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(ir_pin1,INPUT);
  pinMode(ir_pin2,INPUT);
  pinMode(ir_pin3,INPUT);
  pinMode(ir_pin6,INPUT);

  pinMode(ir_pin4,INPUT);
  pinMode(ir_pin5,INPUT);

  pinMode(buzz,OUTPUT);

  pinMode(led_red1,OUTPUT);
  pinMode(led_red2,OUTPUT);
  pinMode(led_green1,OUTPUT);
  pinMode(led_green2,OUTPUT);

  myservo.attach(servo_pin);
  myservo2.attach(servo_pin2);

  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  digitalWrite(led_red1,HIGH);
  digitalWrite(led_red2,HIGH);
}

void loop() {

  lcd.setCursor(3,0);
  lcd.print("SMART  PARKING");

  int ir1 = digitalRead(ir_pin1);
  int ir2 = digitalRead(ir_pin2);
  int ir3 = digitalRead(ir_pin3);
  int ir4 = digitalRead(ir_pin4);
  int ir5 = digitalRead(ir_pin5); 
  int ir6 = digitalRead(ir_pin6); 

  if(ir4 == 0 && chk2 == true){
    Serial.println("backgate open");
    for(int i = 0 ; i <= 90 ; i++){
      myservo2.write(i);
      delay(10);
    }
    chk2 = false;
    digitalWrite(led_green2,HIGH);
    digitalWrite(led_red2,LOW);    
  }
  else if(ir4 == 1 && chk2 == false){
    delay(3000);
    digitalWrite(led_green2,LOW);
    digitalWrite(led_red2,HIGH);
    delay(200);
    Serial.println("backgate close");
    for(int i = 90 ; i >= 0 ; i--){
      myservo2.write(i);
      delay(10);
    }
    chk2 = true;
  }

  if(ir1 == 1){
    lcd.setCursor(0,2);
    lcd.print("S-1:EMPTY");
    Serial.println("slot 1 is empty");
    Blynk.virtualWrite(V0, 0);
    s1 = true;
  }
  else{
    lcd.setCursor(0,2);
    lcd.print("S-1:BOOK ");
    Serial.println("Slot 1 is full");
    Blynk.virtualWrite(V0, 1);
    s1 = false;
  }

  if(ir2 == 1){ 
    lcd.setCursor(0,3);
    lcd.print("S-2:EMPTY");
    Serial.println("slot 2 is empty");
    Blynk.virtualWrite(V1, 0);
    s2 = true;
  }
  else{ 
    lcd.setCursor(0,3);
    lcd.print("S-2:BOOK ");
    Serial.println("Slot 2 is full");
    Blynk.virtualWrite(V1, 1);
    s2 = false;
  }

  if(ir3 == 1){ 
    lcd.setCursor(10,2);
    lcd.print("S-3:EMPTY");
    Serial.println("slot 3 is empty");
    Blynk.virtualWrite(V2, 0);
    s3 = true;
  }
  else{ 
    lcd.setCursor(10,2);
    lcd.print("S-3:BOOK ");
    Serial.println("Slot 3 is full");
    Blynk.virtualWrite(V2, 1);
    s3 = false;
  }

  if(ir6 == 1){ 
    lcd.setCursor(10,3);
    lcd.print("S-4:EMPTY");
    Serial.println("slot 4 is empty");
    Blynk.virtualWrite(V3, 0);
    s4 = true;
  }
  else{ 
    lcd.setCursor(10,3);
    lcd.print("S-4:BOOK ");
    Serial.println("Slot 4 is full");
    Blynk.virtualWrite(V3, 1);
    s4 = false;
  } 

  if((ir5 == 0 && chk == false)){
    digitalWrite(led_green1,LOW);
    digitalWrite(led_red1,HIGH);

    delay(200);
    Serial.println("off by ir");
    for(int i = 90 ; i>=0 ;i--) {
      myservo.write(i);
      delay(10);
    } 
    chk = true;
    Blynk.virtualWrite(V4, 0);
    digitalWrite(buzz,LOW);
  }
  if(!chk){
    digitalWrite(buzz,HIGH);
    delay(200);
    digitalWrite(buzz,LOW);
    delay(200);
  }

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    Serial.println("ABC");
    return;
  }
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  

  if(((content.substring(1) == "E3 C9 55 A7" || content.substring(1) == "C3 7B 71 A8" || content.substring(1) == "70 7D C2 1B" || content.substring(1) == "E3 09 43 A8" ) && chk == true) && (s1 == true || s2 == true || s3 == true || s4 == true)){
    String uid = content.substring(1);
    String card_data = "";

    Serial.println("open by rfid");

    for(int i = 0 ; i <= 90 ; i++){
      myservo.write(i);
      delay(10);
    }
    
    chk = false;
    Blynk.virtualWrite(V4, 1);

    if(uid == "E3 C9 55 A7") card_data = "Avijit_Biswas";
    else if(uid == "C3 7B 71 A8") card_data = "Bikram_Paul";
    else if(uid == "70 7D C2 1B") card_data = "Abhijit_Maity";
    else if(uid == "E3 09 43 A8") card_data = "Archisman_Kundu";
    
    String requestURL = sheet_url + card_data;
    Serial.println("Sending to Google Sheets: " + requestURL);
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    https.begin(client, requestURL);
    https.GET();
    https.end();
    
    digitalWrite(led_green1,HIGH);
    digitalWrite(led_red1,LOW);
  }
  Blynk.run();
}

