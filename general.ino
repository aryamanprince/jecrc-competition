int maxspeedleft = 190; //163
int maxspeedright = 190; //140
int m11 = 10;  //for left tyre moving backward when high
int m12 = 11;  //for left tyre moving forward when high
int m21 = 3;  //for right tyre moving backward when high
int m22 = 9;  //for right tyre moving forward when high
int junc =2;  //junction pulse
long botPosition;
int proportional; // 577 to 440 or 44 to 33   on line
int c=0; //  55==723  and 15==197
int previousproportional;
int derivative,rightSpeed,leftSpeed;
double kp = 0.56;//0.3    4.5
int error,pos;
double kd = 7.0;
int u0=4,u1=5,u2=6,u3=7,u4=A3,u5=13,u6=A1,u7=A2;
double setPoint = 459.8;
void pidCalc() {
       
  proportional = botPosition - setPoint ;
  
  derivative = proportional - previousproportional;
  
  error = (proportional * kp) + (derivative * kd);
  
  previousproportional = proportional;
  
}
void errorAdj()
{
 if(error < -190)
  {
    error = -190;
  }
  if(error > 190)
  {
    error = 190;
  }
  // If error_value is less than zero calculate right turn speed values
  if(error <0)
  {
    rightSpeed = maxspeedright;
    leftSpeed = maxspeedleft+error;
  }
  // If error_value is greater than zero calculate left turn values
  else
  { 
    rightSpeed = maxspeedright-error;
    leftSpeed = maxspeedleft ;
  }
}
void motorRun()
{ // Drive motors according to the calculated values for a turn
  analogWrite(m12, leftSpeed);
  analogWrite(m22, rightSpeed);
 }
void read_leds() {
  botPosition=analogRead(A4);
  Serial.print(botPosition);
  Serial.println();
  pos=botPosition*70/880;
  Serial.print(digitalRead(u0));
  Serial.print(" ");
  Serial.print(digitalRead(u1));
  Serial.print(" ");
  Serial.print(digitalRead(u2));
  Serial.print(" ");
  Serial.print(digitalRead(u3));
  Serial.print(" ");
  Serial.print(digitalRead(u4));
  Serial.print(" ");
  Serial.print(digitalRead(u5));
  Serial.print(" ");
  Serial.print(digitalRead(u6));
  Serial.print(" ");
  Serial.print(digitalRead(u7));
  Serial.println();
}
void setup()
{ pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  pinMode(m21,OUTPUT);
  pinMode(m22,OUTPUT);
  pinMode(A4,INPUT);
  Serial.begin(9600);
  pinMode(junc,INPUT);
  pinMode(u0,INPUT);
  pinMode(u1,INPUT);
  pinMode(u2,INPUT);
  pinMode(u3,INPUT);
  pinMode(u4,INPUT);
  pinMode(u5,INPUT);
  pinMode(u6,INPUT);
  pinMode(u7,INPUT);
}
void right()
  {        Serial.print("right");       
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0);
           delay(100);    
      
        {  analogWrite(m11,0);
           analogWrite(m12,maxspeedleft-100);
           analogWrite(m21,0);
           analogWrite(m22,maxspeedright-100);    
           delay(200);
           read_leds();
        }
   
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0); 
           delay(100);
            
        while(!(pos>30 && pos<40))
         {  analogWrite(m11,0);
            analogWrite(m12,maxspeedleft-100);
            analogWrite(m21,maxspeedright-100);
            analogWrite(m22,0);
            read_leds();    
         }
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0);
           delay(100);
           Pstraight();
  } 
 void specialleft()
 {    Serial.print("special left"); 
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      delay(100);
      analogWrite(m11,0);
      analogWrite(m12,maxspeedleft-100);
      analogWrite(m21,0);
      analogWrite(m22,maxspeedright-100);
      delay(200);  
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      delay(100);
      read_leds();
  if(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH)
  {
    while(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH)
    { analogWrite(m11,maxspeedleft-100);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,maxspeedright-100);  
      read_leds();
    }
    while(!(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
    { analogWrite(m11,maxspeedleft-100);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,maxspeedright-100);     
      read_leds();  
    }
  }
  else if(digitalRead(u0)==HIGH || digitalRead(u1)==HIGH || digitalRead(u2)==HIGH)
   {  while(!(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
      { analogWrite(m11,maxspeedleft-100);
        analogWrite(m12,0);
        analogWrite(m21,0);
        analogWrite(m22,maxspeedright-100);
        read_leds();  
      }
      while(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH)
      { analogWrite(m11,maxspeedleft-100);
        analogWrite(m12,0);
        analogWrite(m21,0);
        analogWrite(m22,maxspeedright-100);  
        read_leds();
      }
      while(!(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
      { analogWrite(m11,maxspeedleft-100);
        analogWrite(m12,0);
        analogWrite(m21,0);
        analogWrite(m22,maxspeedright-100);  
        read_leds(); 
      }
   }
   else 
    {  while(!(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
      { analogWrite(m11,maxspeedleft-100);
        analogWrite(m12,0);
        analogWrite(m21,0);
        analogWrite(m22,maxspeedright-100);  
        read_leds(); 
      }
   }
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0);
           delay(100);
  }
void specialright()
  {   Serial.print("special right");
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      delay(100);
      analogWrite(m11,0);
      analogWrite(m12,maxspeedleft-100);
      analogWrite(m21,0);
      analogWrite(m22,maxspeedright-100);
      delay(200);   
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      delay(100);
      read_leds();
  if(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH)
  {
    while(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH)
    {
      analogWrite(m11,0);
      analogWrite(m12,maxspeedleft-100);
      
      analogWrite(m21,maxspeedright-100);
      analogWrite(m22,0);  
      read_leds();
    }
    while(!(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
    {
      analogWrite(m11,0);
      analogWrite(m12,maxspeedleft-100);
      analogWrite(m21,maxspeedright-100);
      analogWrite(m22,0);     
      read_leds();  
    }
  }
    else if(digitalRead(u5)==HIGH || digitalRead(u6)==HIGH || digitalRead(u7)==HIGH )
   {  while(!(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
      { analogWrite(m11,0);
        analogWrite(m12,maxspeedleft-100);
        analogWrite(m21,maxspeedright-100);
        analogWrite(m22,0);
        read_leds();  
      }
      while((digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
      { analogWrite(m11,0);
        analogWrite(m12,maxspeedleft-100);
        analogWrite(m21,maxspeedright-100);
        analogWrite(m22,0);  
        read_leds();
      }
      while(!(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
      { analogWrite(m11,0);
        analogWrite(m12,maxspeedleft-100);
        analogWrite(m21,maxspeedright-100);
        analogWrite(m22,0);
        read_leds();  
      }
   }
   else
   {  while(!(digitalRead(u3)==HIGH || digitalRead(u4)==HIGH))
      { analogWrite(m11,0);
        analogWrite(m12,maxspeedleft-100);
        analogWrite(m21,maxspeedright-100);
        analogWrite(m22,0);
        read_leds();  
      }
   } 
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0);
           delay(200);
           Pstraight();
  }  
void left()
{      read_leds();
           Serial.print("leftturn");
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0);    
           delay(100);
          
        {  analogWrite(m11,0);
           analogWrite(m12,maxspeedleft-100);
           analogWrite(m21,0);
           analogWrite(m22,maxspeedright-100);   
           delay(200);
           read_leds(); 
        }
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0); 
           delay(100);
        while(!(pos>30 && pos<40))
         {  analogWrite(m11,maxspeedleft-100);
            analogWrite(m12,0);
            analogWrite(m21,0);
            analogWrite(m22,maxspeedright-100); 
            read_leds();   
        }
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0);
           delay(100);
          Pstraight();
  }
void Pstraight(){
 pidCalc();
 errorAdj();
 motorRun();
}
void loop(){
  read_leds();
//  Pstraight();
 if(digitalRead(junc)==HIGH)
 { 
  if((digitalRead(u1)&&digitalRead(u2)&&digitalRead(u3)) || (digitalRead(u0)&&digitalRead(u1)&&digitalRead(u2)) ||
   (digitalRead(u0)&&digitalRead(u1)&&digitalRead(u3)) || (digitalRead(u0)&&digitalRead(u2)&&digitalRead(u3)))
   {
    specialleft();   
   }
  else if((digitalRead(u5)&&digitalRead(u6)&&digitalRead(u7)) || (digitalRead(u4)&&digitalRead(u5)&&digitalRead(u6)) ||
   (digitalRead(u4)&&digitalRead(u6)&&digitalRead(u7)) || (digitalRead(u4)&&digitalRead(u5)&&digitalRead(u7)))
   { 
    specialright();
   }
       
 }
 else if(digitalRead(junc)==LOW)
 { read_leds();
   if(digitalRead(u0)==LOW && digitalRead(u1)==LOW && digitalRead(u2)==LOW && digitalRead(u3)==LOW && digitalRead(u4)==LOW && digitalRead(u5)==LOW && digitalRead(u6)==LOW && digitalRead(u7)==LOW)
   { 
     while(digitalRead(u0)==LOW && digitalRead(u1)==LOW && digitalRead(u2)==LOW && digitalRead(u3)==LOW && digitalRead(u4)==LOW && digitalRead(u5)==LOW && digitalRead(u6)==LOW && digitalRead(u7)==LOW) 
     { analogWrite(m11,0);
       analogWrite(m12,50);
       analogWrite(m21,0);
       analogWrite(m22,50);
       read_leds();
     }
   }
   else
   {
    Pstraight();
    read_leds();
   }
 }
}
