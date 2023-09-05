#include <CayenneMQTTESP8266.h>
#include"ssid_pass.h"
#define Bed 1
#define Red_Desk 2
#define Green_Desk 3
#define Blue_Desk 4
#define Clock 5
#define Sound 6
#define Scull 7
#define Book_shelf 8
#define Desk 9
#define RGB 10


//put this in ssid_pass.h
//char ssid[] = "";
//char wifiPassword[] = "";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "24945d20-0246-11e9-b82d-f12a91579eed";
char password[] = "93a679bfb9868772251b1c9aa659005265f68bf3";
char clientID[] = "75ba0d50-3690-11eb-a2e4-b32ea624e442";

int Bed_light_value, new_Bed_light_value;
int Book_shelf_light_value, new_Book_shelf_light_value;
int Desk_light_value, new_Desk_light_value;
int Desk_R_light_value, new_Desk_R_light_value;
int Desk_G_light_value, new_Desk_G_light_value;
int Desk_B_light_value, new_Desk_B_light_value;

int Clock_value, new_Clock_value;
int Sound_value, new_Sound_value;
int Scull_value, new_Scull_value;
int RGB_animacija, new_RGB_animacija;




bool new_data=false;

void package_form_and_send(){
  char data[10];
  data[0]='U';//0101 0101
  data[1]=new_Desk_R_light_value;
  data[2]=new_Desk_G_light_value;
  data[3]=new_Desk_B_light_value;
  data[4]=new_Desk_light_value;
  data[5]=new_Book_shelf_light_value;
  data[6]=new_Bed_light_value;
  
  
  
  data[7]=0;
  data[7]+=new_Scull_value;
  data[7]+=new_Sound_value*2;
  data[7]+=new_Clock_value*4;
  data[7]+=new_RGB_animacija*8;
  
  data[8]=data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7];
  data[9]='j';//0101 0101
  
  int i=0;
  while(Serial.available()>0) Serial.read();
  while(1){
    for(int j=0;j<=9;j++){
      Serial.print(data[j]);
    }
    
    long unsigned int timer=millis();
    while(Serial.available()>0){
      if(Serial.read()=='O'){
        digitalWrite(2,1);
        delay(100);
        digitalWrite(2,0);
        return;
      }
    }
    i++;
    delay(10);
    //if(millis()-timer>100) return;
    if(i>30) return;
  }
}

void setup()
{
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(2, OUTPUT);
  digitalWrite(2,0);
}

void loop()
{
  Cayenne.loop();
  if(new_data=true){
    new_data=false;

    if(Bed_light_value!=new_Bed_light_value) package_form_and_send();
    if(Book_shelf_light_value!=new_Book_shelf_light_value) package_form_and_send();
    if(Desk_light_value!=new_Desk_light_value) package_form_and_send();
    
    if(Desk_R_light_value!=new_Desk_R_light_value) package_form_and_send();
    if(Desk_G_light_value!=new_Desk_G_light_value) package_form_and_send();
    if(Desk_B_light_value!=new_Desk_B_light_value) package_form_and_send();
    
    if(Clock_value!=new_Clock_value) package_form_and_send();
    if(Sound_value!=new_Sound_value) package_form_and_send();
    if(Scull_value!=new_Scull_value) package_form_and_send();
    if(RGB_animacija!=new_RGB_animacija) package_form_and_send();

    Bed_light_value=new_Bed_light_value;
    Book_shelf_light_value=new_Book_shelf_light_value;
    Desk_light_value=new_Desk_light_value;
    Desk_R_light_value=new_Desk_R_light_value;
    Desk_G_light_value=new_Desk_G_light_value;
    Desk_B_light_value=new_Desk_B_light_value;
    Clock_value=new_Clock_value;
    Sound_value=new_Sound_value;
    Scull_value=new_Scull_value;
    RGB_animacija=new_RGB_animacija;
  }
}







CAYENNE_IN(Bed){
  new_Bed_light_value = getValue.asInt(); // 0 to 1
  new_data=true;
}
CAYENNE_IN(Book_shelf){
  new_Book_shelf_light_value = getValue.asInt(); // 0 to 1
  new_data=true;
}
CAYENNE_IN(Desk){
  new_Desk_light_value = getValue.asInt(); // 0 to 25
  new_data=true;
}
CAYENNE_IN(Red_Desk){
  new_Desk_R_light_value = getValue.asInt(); // 0 to 1
  new_data=true;
}
CAYENNE_IN(Green_Desk){
  new_Desk_G_light_value = getValue.asInt(); // 0 to 1
  new_data=true;
}
CAYENNE_IN(Blue_Desk){
  new_Desk_B_light_value = getValue.asInt(); // 0 to 1
  new_data=true;
}


CAYENNE_IN(Clock){
  new_Clock_value = getValue.asInt(); // 0 to 1
  new_data=true;
}
CAYENNE_IN(Sound){
  new_Sound_value = getValue.asInt(); // 0 to 1
  new_data=true;
}
CAYENNE_IN(Scull){
  new_Scull_value = getValue.asInt(); // 0 to 1
  new_data=true;
}
CAYENNE_IN(RGB){
  new_RGB_animacija = getValue.asInt(); // 0 to 1
  new_data=true;
}
