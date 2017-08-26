//                                        ************************ENTRY GATE CONTROL***************************
#include<LiquidCrystal.h>


LiquidCrystal lcd(12,11,5,4,3,2);

// IR Sensor Pins
int ir_sen1 = 23;
int ir_sen2 = 22;

// Led Pins
int ledpin = 32;
int parking_full_led = 31;
int parking_empty_led = 30;

int MAX_SLOTS = 2;      // Maximum Parking Slots Available

int count = -1;        
boolean entry_flag1 = false;
boolean exit_flag1 = false;

boolean temp1 = false;
boolean temp2 = false;

void setup(){
  
  // Initialize IR Entry Sensor pins
  pinMode(ir_sen1,INPUT);
  pinMode(ir_sen2,INPUT);
  
  // Initialize Led pin
  pinMode(ledpin,OUTPUT);
  pinMode(parking_full_led,OUTPUT);
  pinMode(parking_empty_led,OUTPUT);

  lcd.begin(16,2);
  
  Serial.begin(9600);
}

void loop(){
  // Reading IR sensors
  int ir1 = digitalRead(ir_sen1);
  int ir2 = digitalRead(ir_sen2);

  if((ir1 == 1 && temp2 == false) || temp1 == true){
    temp1 = true;
    entry_gate(ir1,ir2);
    delay(500);
  }
  else if((ir2 == 1 && temp1 == false) || temp2 == true){
    temp2 = true;
    exit_gate(ir1,ir2);
    delay(500);  
  }
}

void entry_gate(int ir1,int ir2){       // Function for entry
 if(count < MAX_SLOTS - 1){
    digitalWrite(parking_empty_led,0);
    lcd_display_Welcome();

    if(ir1 == 1){
      entry_flag1 = true;
      gate_open();    
    }
    if(ir2 == 1 && entry_flag1 == true){
      temp1 = false;
      entry_flag1 = false;
      count = count + 1;
      gate_closed();      
    }
    Serial.println("ENTRY :");
    Serial.println(count);
    
 }
 else{
    temp1 = false;
    lcd_display_full();
    digitalWrite(parking_full_led,1);
 }
}

void exit_gate(int ir1,int ir2){        // Function for exit
 if(count == -1){
    lcd_display_Welcome();
    digitalWrite(parking_empty_led,1);
    temp2 = false;
 }
 else{
  if(ir2 == 1){
    exit_flag1 = true;
    gate_open();
   }
  if(ir1 == 1 && exit_flag1 == true){
    temp2 = false;
    exit_flag1 = false;
    count = count - 1;
    gate_closed();
   }
    digitalWrite(parking_full_led,0);
    Serial.println("EXIT :");
    Serial.println(count);
 }
}

void gate_open(){             // Parking Gate Open
  digitalWrite(ledpin,1);
  delay(100);
  digitalWrite(ledpin,0);
}

void gate_closed(){           // Parking Gate Closed
  digitalWrite(ledpin,1);
  delay(100);
  digitalWrite(ledpin,0);
}

void lcd_display_Welcome(){
  lcd.clear();   
  lcd.print("Welcome To Smart");
  lcd.setCursor(0,1);
  lcd.print("Parking");
}

void lcd_display_full(){
  lcd.clear();
  lcd.print("Parking Full");  
}
