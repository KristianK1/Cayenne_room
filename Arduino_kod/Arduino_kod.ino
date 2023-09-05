#include <SoftwareSerial.h>
#include<math.h>
SoftwareSerial Serial1(2, 4);

#define R_pin 3
#define G_pin 10
#define B_pin 11
#define Bed_pin 6
#define Desk_pin 5
#define Clock_pin 12
#define Scull_pin 7
#define Book_pin 9

#define Sound_pin 15

#define Power_pin 14




char recive[10];
int svjetlina[26]={0,1,2,3,4,5,6,7,8,9,10,11,14,18,22,28,35,43,54,67,84,105,131,163,204,255};

int Bed_light_value=0;
int Book_shelf_light_value=0;
int Desk_light_value=0;
int Desk_R_light_value=0;
int Desk_G_light_value=0;
int Desk_B_light_value=0;

int Clock_value=0;
int Sound_value=0;
int Scull_value=1;
int RGB_animacija=0;



int Desk_light_value_real=0;
int Desk_R_light_value_real=0;
int Desk_G_light_value_real=0;
int Desk_B_light_value_real=0;
int Book_shelf_light_value_real=20;
int Bed_light_value_real=0;

bool new_data=true;


void Data(){
    if(Serial1.available()>0){
    for(int i=0;i<=9;i++){
      recive[i]=0;
    }
    for(int i=0;i<10&&recive[0]!='U';i++)
    recive[0]=Serial1.read();
    
    recive[1]=Serial1.read();
    recive[2]=Serial1.read();
    recive[3]=Serial1.read();
    recive[4]=Serial1.read();
    recive[5]=Serial1.read();
    recive[6]=Serial1.read();
    recive[7]=Serial1.read();
    recive[8]=Serial1.read();
    recive[9]=Serial1.read();
    
    for(int i=0;i<=9;i++){
      Serial.print((int)recive[i]); Serial.print(" ");
    }
    Serial.println();

    
    if(recive[0]=='U' && recive[9]=='j' && recive[8]==(recive[1]+recive[2]+recive[3]+recive[4]+recive[5]+recive[6]+recive[7])){
      new_data=true;
      Serial1.print("OOOOOOOOOOOOO");
      Serial.println("Uspjeh");
      
      Desk_R_light_value=recive[1];
      Desk_R_light_value_real=svjetlina[Desk_R_light_value];

      Desk_G_light_value=recive[2];
      Desk_G_light_value_real=svjetlina[Desk_G_light_value];

      Desk_B_light_value=recive[3];
      Desk_B_light_value_real=svjetlina[Desk_B_light_value];

      
      Desk_light_value=recive[4];
      Desk_light_value_real=svjetlina[Desk_light_value];

      Book_shelf_light_value=recive[5];
      Book_shelf_light_value_real=svjetlina[Book_shelf_light_value];

      Bed_light_value=recive[6];
      Bed_light_value_real=svjetlina[Bed_light_value];



      Scull_value=recive[7]%2;
      Sound_value=recive[7]/2%2;
      Clock_value=recive[7]/4%2;
      RGB_animacija=recive[7]/8%2;
      Serial.println("----------");
      Serial.println(Desk_R_light_value_real);
      Serial.println(Desk_G_light_value_real);
      Serial.println(Desk_B_light_value_real);
      Serial.println(Desk_light_value_real);
      Serial.println(Book_shelf_light_value_real);
      Serial.println(Bed_light_value_real);
      
      Serial.println(RGB_animacija);
      Serial.println(Clock_value);
      Serial.println(Sound_value);
      Serial.println(Scull_value);
      Serial.println("----------");
      
    }
    else Serial.println("neuspjeh");
  }
}

void Output(){
  if(new_data==true){
    digitalWrite(Power_pin, Sound_value||Clock_value||Scull_value||Desk_R_light_value_real||Desk_G_light_value_real||Desk_B_light_value_real||Desk_light_value_real||Bed_light_value_real||Book_shelf_light_value_real||RGB_animacija);
    digitalWrite(Clock_pin, Clock_value||Sound_value);
    digitalWrite(Scull_pin, Scull_value);
    analogWrite(Bed_pin, Bed_light_value_real);
    analogWrite(Book_pin, Book_shelf_light_value_real);
    
    if(RGB_animacija==0){
      analogWrite(R_pin,Desk_R_light_value_real);
      analogWrite(G_pin,Desk_G_light_value_real);
      analogWrite(B_pin,Desk_B_light_value_real);
      analogWrite(Desk_pin,Desk_light_value_real);
    }
  }
}

#define baza 7
#define pi 3.141592654

long unsigned int timer;
int T_R=5;
int T_G=6;
int T_B=7;

int Rmax=252, Gmax=130, Bmax=130;
int T=7;
double omega=2*pi/T;

int value_duty;

void Animation(){
  if(RGB_animacija==1){
    //analogWrite(Desk_pin,0);
    if(millis()-timer>20){
      double vrijeme=1.0*millis()/1000;
      timer=millis();
      //value_duty=(int)(127+127*sin(2*3.14159/T_R*millis()/1000)); //0 stup
      value_duty=3+round((pow(baza,1+sin(omega*vrijeme))-1)*Rmax/(baza*baza-1));
      //Serial.println(value_duty);
      analogWrite(R_pin,value_duty);
      //value_duty=(int)(127+127*sin(2*3.14159/T_G*millis()/1000+3.14159*2/3)); //120 stup
      value_duty=3+round((pow(baza,1+sin(omega*vrijeme+2*pi/3))-1)*Gmax/(baza*baza-1));
      analogWrite(G_pin,value_duty);
      //value_duty=(int)(127+127*sin(2*3.14159/T_B*millis()/1000+3.14159*4/3)); //240 stup
      value_duty=3+round((pow(baza,1+sin(omega*vrijeme+4*pi/3))-1)*Bmax/(baza*baza-1));
      analogWrite(B_pin,value_duty);
    }
  }
}
long unsigned int timer1;
void Sound(){
  if(Sound_value==1){
    if(millis()/500%2==0)
    if(micros()-timer>=250){
      timer=micros();
      digitalWrite(Sound_pin, digitalRead(Sound_pin)^1);  
    }
  }
  else{
    digitalWrite(Sound_pin, LOW); 
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(R_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
  pinMode(Bed_pin, OUTPUT);
  pinMode(Desk_pin, OUTPUT);
  pinMode(Clock_pin, OUTPUT);
  pinMode(Scull_pin, OUTPUT);
  pinMode(Book_pin, OUTPUT);
  pinMode(Sound_pin, OUTPUT);
  pinMode(Power_pin, OUTPUT);

    if(new_data==true){
    digitalWrite(Power_pin, Clock_value||Scull_value||Desk_R_light_value_real||Desk_G_light_value_real||Desk_B_light_value_real||Desk_light_value_real||Bed_light_value_real||Book_shelf_light_value_real||RGB_animacija);
    digitalWrite(Clock_pin, Clock_value||Sound_value);
    digitalWrite(Scull_pin, Scull_value);
    analogWrite(Bed_pin, Bed_light_value_real);
    analogWrite(Book_pin, Book_shelf_light_value_real);
    
    if(RGB_animacija==0){
      analogWrite(R_pin,Desk_R_light_value_real);
      analogWrite(G_pin,Desk_G_light_value_real);
      analogWrite(B_pin,Desk_B_light_value_real);
      analogWrite(Desk_pin,Desk_light_value_real);
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  Data();
  Output();
  Animation();
  Sound();
}
