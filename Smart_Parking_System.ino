//                                        ************************ENTRY GATE CONTROL***************************

// IR Sensor Pins
int ir_entry_sen1;
int ir_entry_sen2;

// Motor Pins
int m1_forward;
int m2_forward;

void begin(){
  
  // Initialize IR Entry Sensor pins
  pinMode(ir1_entry_sen1,INPUT);
  pinMode(ir2_entry_sen2,INPUT);
  
  // Initialize motor pins
  

}

void loop(){
  
  int ir1=digitalRead(ir1_entry_sen1);
  int ir2=digitalRead(ir2_entry_sen2);
    
  
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

int is_vehicle_at_gate(int ir1,int ir2){
  
  boolean temp = false;
  
  while(ir1 != 1); // wait for entry ir sen1 to give 1
  
  if(ir1 == 1){
    temp = true;
  }
  
  while(ir2 != 1); // wait for entry ir sen2 to give 1
  
  else if(ir2 == 1 && temp == true){  
     return 1; 
  }
  
  return 0;
}
