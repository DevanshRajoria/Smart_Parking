//                                    ************************ENTRY-EXIT GATE CONTROL***************************

// IR Sensor Pins
int ir_entry_sen1 = 2;
int ir_entry_sen2 = 3;

// Led Pins
int ledpin = 13;
int parking_full_led = 12;

// Motor Pins
int m1_forward;
int m1_backward;

int MAX_SLOTS = 4;
int count = -1;

boolean entry_flag1 = false;
boolean exit_flag1 = false;

void setup(){
  
  // Initialize IR Entry Sensor pins
  pinMode(ir_entry_sen1,INPUT);
  pinMode(ir_entry_sen2,INPUT);
  
  // Initialize Led pin
  pinMode(ledpin,OUTPUT);
  pinMode(parking_full_led,OUTPUT);

}

void loop(){
  
  int ir1=digitalRead(ir_entry_sen1);
  int ir2=digitalRead(ir_entry_sen2);
  
    
    int entry_gate_status; // get the status if the gate needs to be ON of OFF  
  
    entry_gate_status = is_vehicle_at_gate(ir1,ir2);
    if(entry_gate_status == 1){
      gate_on();
    } 
    else if(entry_gate_status == 0){
      gate_off(); 
   }
  
}

int is_vehicle_at_gate(int ir1,int ir2){
 
  if(ir1 == 1){
    entry_flag1 = true;
  }
  if(ir2 == 1 && entry_flag1 == true){
    if(count >= MAX_SLOTS - 1){
      digitalWrite(parking_full_led,1);
      return 0;
    }
    digitalWrite(parking_full_led,0);
    count = count + 1;
    entry_flag1 = false;
    return 1;
  }

  if(ir2 == 1){
    exit_flag1 = true;
  }
  if(ir1 == 1 && exit_flag1 == true){
    if(count < 0){
      digitalWrite(parking_full_led,1);
      return 0;
    }
    digitalWrite(parking_full_led,0);
    count = count - 1;
    exit_flag1 = false;
    return 1;
  }
  
  return 0;

}

void gate_on(){
  digitalWrite(ledpin,1);
  delay(100);
  digitalWrite(ledpin,0);
}

void gate_off(){
  digitalWrite(ledpin,0);
}

