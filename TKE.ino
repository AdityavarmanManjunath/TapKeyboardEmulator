#include "Keyboard.h"

//charecter set for right hand
char charsetr[4][11]=
{
  //when mpins config is {0,0,0}
  {NULL,'a','c','e','g','i','k','m','o','q',' '},
  //when mpins config is {0,0,1}
  {NULL,'s','u','w','y',215,218,'@','|',',','.'},
  //when mpins config is {0,1,0}
  {NULL,'0','1','2','3','4','5','6','7','8','9'},
  //when mpins config is {1,¬,¬}
  {NULL,216,218,217,215,193,'5','6','7','8','9'}
};
//charecter set for left hand
char charsetl[3][11]=
{
  //when mpins config is {0,0,0}
  {NULL,'b','d','f','h','j','l','n','p','r',178},
  //when mpins config is {0,0,1}
  {NULL,'t','v','x','z',216,217,'!','#','"','?'},
  //when mpins config is {0,1,0}
  {NULL,'+','-','*','/','^','%','(',')','~','='},
};

//right hand config pins
int rpins[]={6,5,4,3};
//left hand config pins
int lpins[]={10,9,8,7};
//map enable config pins
int mpins[]={11,2,12};
//right hand enable matrix
int rconf[11][4]=
{
    {0,0,0,0},
    {1,0,0,0},//1
    {0,1,0,0},//2
    {0,0,1,0},//3
    {0,0,0,1},//4
    {1,1,0,0},//5      
    {0,1,1,0},//6
    {0,0,1,1},//7
    {1,1,1,0},//8
    {0,1,1,1},//9
    {1,1,1,1},//10    
};
//left hand enable matrix
int lconf[11][4]=
{
    {0,0,0,0},
    {0,0,0,1},//1
    {0,0,1,0},//2
    {0,1,0,0},//3
    {1,0,0,0},//4
    {0,0,1,1},//5      
    {0,1,1,0},//6
    {1,1,0,0},//7
    {0,1,1,1},//8
    {1,1,1,0},//9
    {1,1,1,1},//10    
};
//temporary storage variables and arrays
int tempr;
int templ;
int temparr[4];
char tempchar[11];
char tempchal[11];
//

//input configuration arryas

//right hand
int inpr[4];
//left hand
int inpl[4];
//enable pins (little fingers, folding)
int inpm[2];

//pinMode initialization
void setup()
{
  for(int i=0;i<4;i++)
  {
    pinMode(rpins[i],INPUT);
    pinMode(lpins[i],INPUT);
    pinMode(mpins[i],INPUT);
  }
  Serial.begin(9600);
  Keyboard.begin();
}

void loop()
{
  moin();
  
  if (Serial.available() > 0) 
  {
    // read incoming serial data:
    char inChar = Serial.read();
    // Type the next ASCII value from what you received:
    Keyboard.write(inChar);
  }
}
void moin()
{
  rest();
  reader();
  //char ack
  templ=arrary(inpl,lconf);
  tempr=arrary(inpr,rconf);
  if(templ<11&&tempr<11)
  {
    printer(); 
    delay(1000);
  }
  rest();
}
void rest()
{
  for(int i=0;i<4;i++)
  {
    digitalWrite(rpins[i],0);
    digitalWrite(lpins[i],0);
    }
   
  for(int i=0;i<3;i++)
  {
    digitalWrite(mpins[i],0);
    }
}
void printer()
{
  switch(templ)
  {
    case 0:
    break;
    default:
    Serial.println(tempchal[templ]);
    break;
  }
  switch(tempr)
  {
    case 0:
    break;
    default:
    Serial.println(tempchar[tempr]);
    break;
  }
}
int arrary(int mp[4],int kol[11][4])
{
  int booga, flag, k;
  for(k=0;k<11;k++)
  {
    for(int j=0;j<4;j++)
      temparr[j]=kol[k][j];
    booga=compareArray(mp,temparr,4);
    if(booga==0)
    {
      flag=k;
      break;
    }
    else
      continue;
  }
  return flag;
}
//charmaps
void map00()
{
    for(int t=0;t<11;t++)
      tempchar[t]=charsetr[0][t];
    for(int t=0;t<11;t++)
      tempchal[t]=charsetl[0][t];
}
void map01()
{
    for(int t=0;t<11;t++)
      tempchar[t]=charsetr[1][t];
    for(int t=0;t<11;t++)
      tempchal[t]=charsetl[1][t];
}
void map10()
{
    for(int t=0;t<11;t++)
      tempchar[t]=charsetr[2][t];
    for(int t=0;t<11;t++)
      tempchal[t]=charsetl[2][t];
}
//

void reader()
{
  for(int i=0;i<4;i++)
  {
    inpr[i]=0;
    inpl[i]=0;
  }
  for(int redr=0;redr<4;redr++)
  {
    inpr[redr]=digitalRead(rpins[redr]);
    inpl[redr]=digitalRead(lpins[redr]);
  }
  for(int redm=0;redm<3;redm++)
    inpm[redm]=digitalRead(mpins[redm]);
  
  if(inpm[2]==0)
  {
    for(int t=0;t<11;t++)
      tempchar[t]=charsetr[3][t];
    for(int t=0;t<11;t++)
      tempchal[t]=NULL;
  }
  else
  {
  switch(inpm[0])
  {
    case 0:
    switch(inpm[1])
    {
      case 0:
      map00();
      //Serial.println("map00");
      break;
      case 1:
      map01();
      //Serial.println("map01");
      break;
    }
    break;
    case 1:
    map10();
    //Serial.println("map10");
    break;
  }
  }
}
int compareArray(int a[],int b[],int size)  {
  int i;
  for(i=0;i<size;i++){
    if(a[i]!=b[i])
      return 1;
  }
  return 0;
}
