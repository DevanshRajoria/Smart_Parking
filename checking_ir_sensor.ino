int ir1 = 2;
int ir2 = 3;
int ledpin = 13;
void setup()
{
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ledpin,OUTPUT);
}
void loop()
{
  int ir_1 = digitalRead(ir1);
  int ir_2 = digitalRead(ir2);
  
  if(ir_1 == 1){
     digitalWrite(ledpin,1); 
     delay(200);
     digitalWrite(ledpin,0);
  }
  if(ir_2 == 1){
     digitalWrite(ledpin,1); 
     delay(200);
     digitalWrite(ledpin,0);
  } 
  else{
    digitalWrite(ledpin,0);
  }
  
}
