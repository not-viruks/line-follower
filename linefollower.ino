/*motors*/
int mr1=8;  //motor right 1
int mr2=9;  //motor right 2
int ml1=10;   //motor left 1
int ml2=11; //motor left 2
int enr=6; //A-enable/speed
int enl=5; //B-enable/speed

/*sensors*/
int sl2=2;   //sensor left2
int sl1=3;   //sensor left
int smid=4;   //sensor middle
int sr1=7;   //sensor right
int sr2=12;   //sensor right2

int led=13; //led

/*values*/
int vspeed=100;    
int tspeed=255;
int tdelay=20;

int svl2, svl1, svm, svr1, svr2 = 0; //sensors values


void setup()
{
  pinMode(mr1,OUTPUT);
  pinMode(mr2,OUTPUT);
  pinMode(ml1,OUTPUT);
  pinMode(ml2,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(sl2,INPUT);
  pinMode(sl1,INPUT);
  pinMode(smid,INPUT);
  pinMode(sr1,INPUT);
  pinMode(sr2,INPUT);
   
  delay(5000);
}

void loop()
{
  svl2=digitalRead(sl2);
  svl1=digitalRead(sl1);
  svm=digitalRead(smid);
  svr1=digitalRead(sr1);
  svr2=digitalRead(sr2);

  int pattern =
  (svl2 << 4) |
  (svl1 << 3) |
  (svm << 2) |
  (svr1 << 1) |
  (svr2);

  switch (pattern) {
    case 0b00100: forward(); break;
    case 0b01000: left(); break;
    case 0b00010: right(); break;
    case 0b00000: stop(); break;
  }


  /*if(pattern == 0b00000)
  {
    forward(); //continue
  }

  if(pattern == 0b00000)
  {
    left(); //turn left
  }
  else if(pattern == 0b00000)
  {
    right(); //turn right
  }
  else if(pattern == 0b00000)
  {
    stop(); //stop
  }*/
}

void forward()
  {
    digitalWrite(mr1,HIGH);
    digitalWrite(mr2,LOW);
    digitalWrite(ml1,HIGH);
    digitalWrite(ml2,LOW);
    analogWrite(enr,vspeed);
    analogWrite(enl,vspeed);
  } 

void backward()
  {
    digitalWrite(mr1,LOW);
    digitalWrite(mr2,HIGH);
    digitalWrite(ml1,LOW);
    digitalWrite(ml2,HIGH);
    analogWrite(enr,vspeed);
    analogWrite(enl,vspeed);
  }

void right()
  {
   digitalWrite(mr1,LOW);
   digitalWrite(mr2,HIGH);
   digitalWrite(ml1,HIGH);
   digitalWrite(ml2,LOW);
   analogWrite(enr,tspeed);
   analogWrite(enl,tspeed);
   delay(tdelay);
  } 

void left()
  {
   digitalWrite(mr1,HIGH);
   digitalWrite(mr2,LOW);
   digitalWrite(ml1,LOW);
   digitalWrite(ml2,HIGH);
   analogWrite(enr,tspeed);
   analogWrite(enl,tspeed);
   delay(tdelay);
  }  

void stop()
  {
    analogWrite(enr,0);
    analogWrite(enl,0);
  }