#include<SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

byte bytegps = 0;
char datagps[100]="";
char hora[15]="";
char lat[15]="";
char lon[15]="";
char NS[5]="";
char WE[5]="";
char sat[5]="";
char alt[20]="";
int comas[15];
int contcomas = 0;
int i=0;
float lat_degInt;
float lat_degDec;
float lat_easy;
float long_degInt;
float long_degDec;
float long_easy;
bool gps_state = false;

void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(13,OUTPUT);
  
}
  
 void loop() {
   
   
   memset(datagps,0,sizeof(datagps));
   gps_state = false;
   
   while(datagps[4] != 'G'){
   gpsloop();
   
   }
   
   Serial.println(datagps);
   
   gpsdatatreatment();
   latlondeg();
   Serial.print("hora:");
   Serial.println(hora);
   Serial.print("latitud:");
   Serial.print(lat_easy,4);
   Serial.println(NS);
   Serial.print("longitud:");
   Serial.print(long_easy,4);
   Serial.println(WE);
  // Serial.print("satelites:");
  //Serial.println(sat);
   Serial.print("altitud:");
   Serial.println(alt);
   
   
   delay(1);
   
   if(!strcmp(NS,"N")){gps_state = true; digitalWrite(13,HIGH);}
   
   clean_all();
   


}

///////////////////////////////////////GPS LOOP
void gpsloop(){
  
 
 mySerial.flush();
 
 mySerial.begin(9600);
 
 memset(datagps,0,sizeof(datagps));
 
 bytegps = 0;
 int i = 1;
 
 while(bytegps != '$'){
 
 bytegps = mySerial.read();  
 
 }
 
 
 datagps[0] = '$';
 bytegps = 0;
 
//   while(bytegps != '*' ){
//   bytegps = mySerial.read();
//   if(bytegps!=255){
//   datagps[i] = bytegps;
//   i++;}
// }
 
 while(bytegps!='$'){
 bytegps = mySerial.read();
 if(bytegps != 255 && bytegps!='$'){
 datagps[i]=bytegps;
 i++;
 }
 
 
 }
 
  
}
///////////////////////////////////////END GPS LOOP


///////////////////////////////////////GPS DATA TREATMENT

void gpsdatatreatment() {
  
  contcomas = 0;
  for (i=7 ; i<sizeof(datagps) ; i++){
  //Serial.println(i);
    if (datagps[i]==','){
    
    comas[contcomas]=i;
    contcomas++;
    
    } // end if
  } // end for
  
  
  for(i=7;i<comas[0]-4;i++){
  hora[i-7]= datagps[i];
  }
  
  for(i=comas[0]+1;i<comas[1];i++){
  lat[i-comas[0]-1]= datagps[i];
  }
 
  for(i=comas[1]-1;i<comas[2];i++){
  NS[i-comas[1]-1]= datagps[i];
  }
  
  for(i=comas[2]+1;i<comas[3];i++){
  lon[i-comas[2]-1]= datagps[i];
  }
  
  for(i=comas[3]+1;i<comas[4];i++){
  WE[i-comas[3]-1]= datagps[i];
  }
  
  for(i=comas[5]+1;i<comas[6];i++){
  sat[i-comas[5]-1]= datagps[i];
  }
  
  for(i=comas[7]+1;i<comas[8];i++){
  alt[i-comas[7]-1]= datagps[i];
  }
  
}

///////////////////////////////////////END GPS DATA TREATMENT

///////////////////////////////////////CLEAN ALL

void clean_all() {

memset(hora,0,sizeof(hora));
memset(lat,0,sizeof(lat));
memset(lon,0,sizeof(lon));
memset(NS,0,sizeof(NS));
memset(WE,0,sizeof(WE));
memset(sat,0,sizeof(sat));
memset(alt,0,sizeof(alt));

}

///////////////////////////////////////END CLEAN ALL

///////////////////////////////////////CAMBIO A GRADOS

void latlondeg() {

lat_degInt = float(int(atof(lat)/100));
lat_degDec = float((atof(lat)-lat_degInt*100)/60);
lat_easy = lat_degInt + lat_degDec;
long_degInt = float(int(atof(lon)/100));
long_degDec = float((atof(lon)-long_degInt*100)/60);
long_easy = long_degInt + long_degDec;

}

///////////////////////////////////////CANVIO A GRADOS

