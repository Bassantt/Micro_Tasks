int bit0,bit1,bit2,bit3;
void setup(){
for(int i=2;i<9;i++) {
pinMode(i,OUTPUT);
}
for(int i=9;i<13;i++) {
pinMode(i,INPUT);
}}
void loop(){
for(int i=2;i<9;i++) {
  digitalWrite(i,LOW);} 
bit0=digitalRead(12);
bit1=digitalRead(11);
bit2=digitalRead(10);
bit3=digitalRead(9);
if((bit3||bit2||bit1||!bit0)&&(bit3||!bit2||bit1||bit0)&&(!bit3||!bit2||bit1||!bit0)&&(!bit3||bit2||!bit1||!bit0)){digitalWrite(2,HIGH);}
if((!bit3||!bit2||bit0)&&(!bit3||!bit1||!bit0)&&(bit3||!bit2||bit1||!bit0)&&(!bit2||!bit1||bit0)){digitalWrite(3,HIGH);}
if((!bit3||!bit2||bit0)&&(!bit3||!bit2||!bit1||!bit0)&&(bit3||bit2||!bit1||bit0)){digitalWrite(5,HIGH);}
if((!bit2||!bit1||!bit0)&&(!bit3||bit2||!bit1||bit0)&&(bit3||bit2||bit1||!bit0)&&(bit3||!bit2||bit1||bit0)){digitalWrite(6,HIGH);}
if((bit3||!bit0)&&(bit2||bit1||!bit0)&&(bit3||!bit2||bit1)){digitalWrite(7,HIGH);}
if((!bit3||!bit2||bit1||!bit0)&&(bit3||!bit1||!bit0)&&(bit3||bit2||!bit0)&&(bit3||bit2||!bit1)){digitalWrite(8,HIGH);}
if((bit3||bit2||bit1)&&(bit3||!bit2||!bit1||!bit0)&&(!bit3||!bit2||bit1||bit0)){digitalWrite(4,HIGH);}
delay(30);
}
