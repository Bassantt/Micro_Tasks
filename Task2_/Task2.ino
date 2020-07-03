unsigned long previousMillis=0;
unsigned long sensor=0;
unsigned long previousMillisAlarmthatbeingon=0;
bool canmoveforward=true;
bool checktoturnonfan=false;
bool Activefan=false;
void setup() {
   for(int i=0;i<4;i++){
     pinMode(i,INPUT);
     }
  for(int i=4;i<14;i++){
     pinMode(i,OUTPUT);
     }
       pinMode(A0,INPUT);
       pinMode(A1,OUTPUT);
       pinMode(A2,OUTPUT);
       pinMode(A3,OUTPUT);
       pinMode(A4,OUTPUT);
       
       attachInterrupt(digitalPinToInterrupt(3),isMOreThanhalfsecond,RISING);     
}

void loop() {
  unsigned long currentMillis=millis();
  if((unsigned)(currentMillis-previousMillis)>=1000){
   digitalWrite(13,!digitalRead(13));
   previousMillis=millis();
  }
if(digitalRead(A0))
{
    if(checktoturnonfan&&(unsigned)(currentMillis-previousMillisAlarmthatbeingon)>=500){
       Activefan=true;
    }
  if(Activefan){
      moveforward(A1,A2,A3,A4);
      }
  else{    
        if(getdistance(0)>10 && canmoveforward){
                moveforward(5,6,7,8);
                moveforward(9,10,11,12); 
         }
         else{
                if(getdistance(1)>10){
                returnandcheckforword(9,10,11,12);
                
                }
                    else{
                          if(getdistance(2)>10){
                              returnandcheckforword(5,6,7,8);
              
                          }    
                           else{
                             moveback();
                             canmoveforward=false;
                            }  
                          }
                 }
       }
}   
} 

void returnandcheckforword(int b0,int b1, int b2, int b3){
                              moveforward(b0,b1,b2,b3);
                               moveforward(b0,b1,b2,b3);
                             canmoveforward=true;
                             if(getdistance(0)>10 && canmoveforward){
                           moveforward(5,6,7,8);
                          moveforward(9,10,11,12); 
                             }
  
  }

void moveforward(int bin0,int bin1,int bin2,int bin3){
        digitalWrite(bin0, HIGH);
        digitalWrite(bin1, LOW);
        digitalWrite(bin2, LOW);
        digitalWrite(bin3, HIGH);

        digitalWrite(bin0, HIGH);
        digitalWrite(bin1, HIGH);
        digitalWrite(bin2, LOW);
        digitalWrite(bin3, LOW);
       
        digitalWrite(bin0, LOW);
        digitalWrite(bin1, HIGH);
        digitalWrite(bin2,HIGH );
        digitalWrite(bin3, LOW);
 
        digitalWrite(bin0, LOW);
        digitalWrite(bin1, LOW);
        digitalWrite(bin2, HIGH);
        digitalWrite(bin3, HIGH);
        }

void moveback(){
  for (int i=5;i<12;i+=4)
        {
        digitalWrite(i, HIGH);
        digitalWrite(i+1, LOW);
        digitalWrite(i+2, HIGH);
        digitalWrite(i+3, LOW);
        }
         // 0110
        for (int i=5;i<12;i+=4)
        {
        digitalWrite(i, LOW);
        digitalWrite(i+1, HIGH);
        digitalWrite(i+2, HIGH);
        digitalWrite(i+3, LOW);
        }
       //0101
       for (int i=5;i<12;i+=4)
        {
        digitalWrite(i, LOW);
        digitalWrite(i+1, HIGH);
        digitalWrite(i+2, LOW);
        digitalWrite(i+3, HIGH);
        }
        //1001
        for (int i=5;i<12;i+=4)
        {
         digitalWrite(i, HIGH);
        digitalWrite(i+1, LOW);
        digitalWrite(i+2, LOW);
        digitalWrite(i+3, HIGH);
        }
  
  }
        
long getdistance(int pinNum){
  sensor=0;
  digitalWrite(4, LOW);
 unsigned long currentMillis=millis();
  if((unsigned)(currentMillis-sensor)<0.002){
   sensor=millis();
  }
  digitalWrite(4, HIGH);
  sensor=0;
  currentMillis=millis();
  if((unsigned)(currentMillis-sensor)<0.02){
   sensor=millis();
  }
  digitalWrite(4, LOW);

  long duration = pulseIn(pinNum, HIGH,55000);
  long cm = (duration)/ 29  / 2;
  return cm;
  }
        
void isMOreThanhalfsecond(){
  previousMillisAlarmthatbeingon =millis();
  if(checktoturnonfan==false){
    checktoturnonfan=true;
    }
  else{
    Activefan=false;
    }  
  }
