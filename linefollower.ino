// ===== MOTORS =====
int mr1=8;
int mr2=9;
int ml1=10;
int ml2=11;
int enr=6;
int enl=5;

// ===== SENSORS =====
int sl2=2;
int sl1=3;
int smid=4;
int sr1=7;
int sr2=12;

int svl2, svl1, svm, svr1, svr2;
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
  svl2 = digitalRead(sl2) == LOW;
  svl1 = digitalRead(sl1) == LOW;
  svm  = digitalRead(smid) == LOW;
  svr1 = digitalRead(sr1) == LOW;
  svr2 = digitalRead(sr2) == LOW;

  pattern = (svl2 << 4) |
            (svl1 << 3) |
            (svm  << 2) |
            (svr1 << 1) |
            (svr2);

  Serial.print("Pattern BIN: ");
  Serial.println(pattern, BIN);

  switch (pattern) {
    case 0b00100: move(255, 255, 1,0,1,0); break; // forward

    case 0b01100: move(255, 255, 0,1,1,0); break; //left
    case 0b11100: move(255, 255, 0,1,1,0); break;
    case 0b11000: move(255, 255, 0,1,1,0); break;
    case 0b10000: move(255, 255, 0,1,1,0); break;

    case 0b00110: move(255, 255, 1,0,0,1); break; //right
    case 0b00010: move(255, 255, 1,0,0,1); break;
    case 0b00110: move(255, 255, 1,0,0,1); break;
    case 0b00110: move(255, 255, 1,0,0,1); break;

    case 0b00000: move(255, 255, 0,1,0,1); break; //back
    default: move(255, 255, 1,0,1,0); break; //def
  }
}

void move(int speedL, int speedR, bool mrf, bool mrb, bool mlf, bool mlb)
{
  digitalWrite(mr1, mrf);
  digitalWrite(mr2, mrb);
  digitalWrite(ml1, mlf);
  digitalWrite(ml2, mlb);

  analogWrite(enr, speedR);
  analogWrite(enl, speedL);
}
