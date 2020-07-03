int maxspeedleft = 190;
int maxspeedright = 190;
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
double kp = 0.60;
int error,pos;
double kd = 7.0;
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
}
void setup()
{ pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  pinMode(m21,OUTPUT);
  pinMode(m22,OUTPUT);
  pinMode(A4,INPUT);
  Serial.begin(9600);
  pinMode(junc,INPUT);
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
           delay(150);
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
  void RIGHT()
  {  Serial.print("right");       
           analogWrite(m11,0);
           analogWrite(m12,0);
           analogWrite(m21,0);
           analogWrite(m22,0);
           delay(100);    
      
        {  analogWrite(m11,0);
           analogWrite(m12,maxspeedleft-100);
           analogWrite(m21,0);
           analogWrite(m22,maxspeedright-100);    
           delay(300);
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
  void LEFT()
  {  read_leds();
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
           delay(300);
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
      delay(150);  
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      delay(100);
      read_leds();
  if(pos>30 && pos<40)
  {
    while(pos>30 && pos<40)
    { analogWrite(m11,maxspeedleft-100);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,maxspeedright-100);  
      read_leds();
    }
    while(!(pos>30 && pos<40))
    { analogWrite(m11,maxspeedleft-100);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,maxspeedright-100);     
      read_leds();  
    }
  }
  else if(pos<=30 && pos>=0)
   {  while(!(pos>30 && pos<40))
      { analogWrite(m11,maxspeedleft-100);
        analogWrite(m12,0);
        analogWrite(m21,0);
        analogWrite(m22,maxspeedright-100);
        read_leds();  
      }
      while(pos>30 && pos<40)
      { analogWrite(m11,maxspeedleft-100);
        analogWrite(m12,0);
        analogWrite(m21,0);
        analogWrite(m22,maxspeedright-100);  
        read_leds();
      }
      while(!(pos>30 && pos<40))
      { analogWrite(m11,maxspeedleft-100);
        analogWrite(m12,0);
        analogWrite(m21,0);
        analogWrite(m22,maxspeedright-100);  
        read_leds(); 
      }
   }
   else 
    {  while(!(pos>30 && pos<40))
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
           Pstraight();
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
      delay(150);   
      analogWrite(m11,0);
      analogWrite(m12,0);
      analogWrite(m21,0);
      analogWrite(m22,0);
      delay(100);
      read_leds();
  if(pos>30 && pos<40)
  {
    while(pos>30 && pos<40)
    { analogWrite(m11,0);
      analogWrite(m12,maxspeedleft-100);
      analogWrite(m21,maxspeedright-100);
      analogWrite(m22,0);  
      read_leds();
    }
    while(!(pos>30 && pos<40))
    { analogWrite(m11,0);
      analogWrite(m12,maxspeedleft-100);
      analogWrite(m21,maxspeedright-100);
      analogWrite(m22,0);     
      read_leds();  
    }
  }
    else if(pos<=30 && pos>=0)
   {  while(!(pos>30 && pos<40))
      { analogWrite(m11,0);
        analogWrite(m12,maxspeedleft-100);
        analogWrite(m21,maxspeedright-100);
        analogWrite(m22,0);
         read_leds();  
      }
   }
   else
   {  while(!(pos>30 && pos<40))
      { analogWrite(m11,0);
        analogWrite(m12,maxspeedleft-100);
        analogWrite(m21,maxspeedright-100);
        analogWrite(m22,0);
        read_leds();  
      }
      while((pos>30 && pos<40))
      { analogWrite(m11,0);
        analogWrite(m12,maxspeedleft-100);
        analogWrite(m21,maxspeedright-100);
        analogWrite(m22,0);  
        read_leds();
      }
      while(!(pos>30 && pos<40))
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
           delay(100);
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
           delay(150);
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
 /* analogWrite(m11,0);
    analogWrite(m12,200);
    analogWrite(m21,0);
    analogWrite(m22,200);
*/
if(digitalRead(junc)==HIGH)
{ c++;
if(c==4)
 { while(digitalRead(junc)==HIGH)
 Pstraight();
 }
else if(c==1||c==2||c==3||c==5||c==6||c==7||c==8||c==10||c==11||c==13||c==14||c==17)
right();    
else if(c==4|| c==10 || c==11)
specialleft();
else if(c==5)
specialright();
else if(c==7||c==9||c==12||c==16)
left();
//else if(c)
//RIGHT();
//else if(c)
//LEFT();
 else
  {
   while(digitalRead(junc)==HIGH)
    { Pstraight();
      read_leds();
    }
  }
}
else
 { 
    Pstraight();
    read_leds();
  
 }
}
