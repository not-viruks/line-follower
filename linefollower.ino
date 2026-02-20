// ===== MOTORS =====
int mr2=8;
int mr1=9;
int ml2=10;
int ml1=11;

int enl=5;
int enr=6;  


// ===== SENSORS =====
int sl2=2;
int sl1=3;
int smid=4;
int sr1=7;
int sr2=12;

int svl2, svl1, svm, svr1, svr2;

int speedR;
int speedL;

int pattern;

void setup() {
  pinMode(mr1,OUTPUT);
  pinMode(mr2,OUTPUT);
  pinMode(ml1,OUTPUT);
  pinMode(ml2,OUTPUT);
  pinMode(enr,OUTPUT);
  pinMode(enl,OUTPUT);

  pinMode(sl2,INPUT_PULLUP);
  pinMode(sl1,INPUT_PULLUP);
  pinMode(smid,INPUT_PULLUP);
  pinMode(sr1,INPUT_PULLUP);
  pinMode(sr2,INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("START");
}

void loop() {
  
  speedL=255;
  speedR=255;
  pattern = fpattern();
  
  Serial.println(pattern);
  
  while(pattern != 100){
    speedR=5;
    speedL=5;
    int state = 0;
    if(pattern > 111 && pattern < 10100)
    {
      speedR*=2;
      speedL*=2;
      move(speedL,speedR, 0,1,0,1);
      state = -1;
    }
    else if(pattern <= 1111 && pattern > 0)
    {
      speedL*=2;
      speedR*=2;
      move(speedL,speedR, 1,0,1,0);
      state = 1;
    }
    else
    {
      if(state==-1){
        move(40, 40, 0,1,0,1);
      }
      else if(state==1){
        move(40, 40, 1,0,1,0);
      }
      else{
        move(40, 40, 1,0,0,1);
      }
    }
    pattern = fpattern();
  }
  move(speedL,speedR, 1,0,0,1);
  
}

int fpattern()
{
  svl2 = digitalRead(sl2) == HIGH? 10000:0;
  svl1 = digitalRead(sl1) == HIGH? 1000:0;
  svm  = digitalRead(smid) == HIGH? 100:0;
  svr1 = digitalRead(sr1) == HIGH? 10:0;
  svr2 = digitalRead(sr2) == HIGH? 1:0;
  int pattern = svl2+svl1+svm+svr1+svr2;
  return pattern;
}

void move(int speedL, int speedR, bool mlf, bool mlb, bool mrf, bool mrb)
{
  digitalWrite(mr1, mrf);
  digitalWrite(mr2, mrb);
  digitalWrite(ml1, mlf);
  digitalWrite(ml2, mlb);

  analogWrite(enr, speedR);
  analogWrite(enl, speedL);
}