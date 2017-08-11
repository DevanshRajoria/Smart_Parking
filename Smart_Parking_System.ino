//                                        ************************ENTRY GATE CONTROL***************************

// IR Sensor Pins
int ir_entry_sen1 = 2;
int ir_entry_sen2 = 3;

// Led Pins
int ledpin = 13;
int parking_full_led = 12;

// Motor Pins
int m1_forward;
int m1_backward;

boolean flag = false;
int MAX_SLOTS = 4;
int count = 0;


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
  
  int check_if_can_enter = count;
  if(check_if_can_enter < MAX_SLOTS){
    
    int entry_gate_status; // get the status if the gate needs to be ON of OFF  
  
    entry_gate_status = is_vehicle_at_gate(ir1,ir2);
    if(entry_gate_status == 1){
      gate_on();
    } 
    else if(entry_gate_status == 0){
      gate_off(); 
   }
   else{
      gate_off();
   }  
  }

  else{
    digitalWrite(parking_full_led,1);  
  }
  
}

int is_vehicle_at_gate(int ir1,int ir2){
  
  if(ir1 == 1){ 
    flag = true;
  }
 
  if(ir2 == 1 && flag == true){  
     count = count + 1;
     flag = false;
     return 1; 
  }
  
  return 0;
}

void gate_on(){
  digitalWrite(ledpin,1);
  delay(200);
  digitalWrite(ledpin,0);
}

void gate_off(){
  digitalWrite(ledpin,0);
}
