int ir1 = 2;
//int ir2 = 7;
//m1f=12 ,m1b=13 ,m2f=3 ,m2b=2 ;
void setup()
{
  pinMode(ir1,INPUT);
  /*pinMode(ir2,INPUT);
  pinMode(m1f,OUTPUT);
  pinMode(m1f,OUTPUT);
  pinMode(m1f,OUTPUT);
  pinMode(m1f,OUTPUT);
*/
  Serial.begin(9600); 
}
void loop()
{
  ir1=digitalRead(ir1);
  
  if(ir1 == 1){
     digitalWrite(ledpin,1); 
     delay(200);
     digitalWrite(ledpin,0);
  }
  else{
    digitalWrite(ledpin,0);
  }
  
}

