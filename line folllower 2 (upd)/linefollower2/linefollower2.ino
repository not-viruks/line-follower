// ===== MOTORS =====
int mr2=8;
int mr1=9;
int ml2=10;
int ml1=11;

int enl=5;
int enr=6;  


// ===== SENSORS =====
  int svl2;
  int svl1;
  int svm;
  int svr1;
  int svr2;

#define NUM_SENSORS 8

int sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5, A6, A7};
int sensorValues[NUM_SENSORS];
int lineFound[NUM_SENSORS];


int threshold = 500;

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

  Serial.begin(9600);
  Serial.println("START");
}

void loop() {
  speedL=255;
  speedR=255;
  pattern = fpattern();
  
  
  while(pattern != 100){
    speedR=5;
    speedL=5;
    int state = 0;
    if(pattern > 111 && pattern < 10100)
    {
      speedR*=2;
      speedL*=2;
      move(speedL,speedR, 1,0,1,0);
      state = -1;
    }
    else if(pattern <= 1111 && pattern > 0)
    {
      speedL*=2;
      speedR*=2;
      move(speedL,speedR, 0,1,0,1);
      state = 1;
    }
    else
    {
      if(state==-1){
        move(40, 40, 1,0,1,0);
      }
      else if(state==1){
        move(40, 40, 0,1,0,1);
      }
      else{
        move(40, 40, 0,1,1,0);
      }
    }
    pattern = fpattern();
    analogRead(sensorPins[2]);
  }
  move(speedL,speedR, 0,1,1,0);
  Serial.println(pattern);
}

int fpattern()
{
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);

    if (sensorValues[i] < threshold) { 
       lineFound[i] = 1;
    }
  }

  svl2 = lineFound[0] == HIGH? 10000:0;
  svl1 = lineFound[1] == HIGH? 1000:0;
  svm  = lineFound[2] == HIGH? 100:0;
  svr1 = lineFound[3] == HIGH? 10:0;
  svr2 = lineFound[4] == HIGH? 1:0;

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