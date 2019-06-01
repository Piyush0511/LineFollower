
int lm1 = 2, lm2 = 3, rm1 = 4, rm2 = 5;
int l, c1, c2, c3, r, m = 44;
int i = 9;
void Forward()
{
  digitalWrite(lm1, 1);
  digitalWrite(lm2, 0);
  digitalWrite(rm1, 1);
  digitalWrite(rm2, 0);
}


void Stop()
{
  digitalWrite(lm1, 1);
  digitalWrite(lm2, 1);
  digitalWrite(rm1, 1);
  digitalWrite(rm2, 1);
}


void Reverse()
{
  digitalWrite(lm1, 0);
  digitalWrite(lm2, 1);
  digitalWrite(rm1, 0);
  digitalWrite(rm2, 1);
}


void Right()
{
  digitalWrite(lm1, 1);
  digitalWrite(lm2, 0);
  digitalWrite(rm1, 0);
  digitalWrite(rm2, 1);
}


void Left()
{
  digitalWrite(lm1, 0);
  digitalWrite(lm2, 1);
  digitalWrite(rm1, 1);
  digitalWrite(rm2, 0);
}

void smallright()
{
  digitalWrite(lm1, 1);
  digitalWrite(lm2, 0);
  digitalWrite(rm1, 0);
  digitalWrite(rm2, 0);
}


void smallleft()
{
  digitalWrite(lm1, 0);
  digitalWrite(lm2, 0);
  digitalWrite(rm1, 1);
  digitalWrite(rm2, 0);
}

void readsens()
{
  l = digitalRead(30);
  c1 = digitalRead(32);
  c2 = digitalRead(34);
  c3 = digitalRead(36);
  r = digitalRead(38);
  m = digitalRead(44);
}



void setup()
{
  Serial.begin(115200);
  Serial.println("line");
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(38, INPUT);
  pinMode(30, INPUT);
  pinMode(32, INPUT);
  pinMode(34, INPUT);
  pinMode(36, INPUT);
  pinMode(44, INPUT);
  pinMode(9, OUTPUT);
}


void loop()
{

  readsens();

  //Line Follow
  //fwd
 // if (m == 1)
 // {
    if ((l == 1) && (c1 == 1) && (c2 == 0) && (c3 == 1) && (r == 1))
    {
      Serial.println("Forward");
      Forward();

    }

    //smallleft
    else if (((l == 1) && (c1 == 0) && (c2 == 1) && (c3 == 1) && (r == 1)) || ((l == 1) && (c1 == 0) && (c2 == 0) && (c3 == 1) && (r == 1)))
    {
      Serial.println("smallleft");
      smallleft();

    }
    //smallRight
    else if (((l == 1) && (c1 == 1) && (c2 == 0) && (c3 == 0) && (r == 1)) || ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 0) && (r == 1)))
    {
      Serial.println("smallright");
      smallright();

    }
    //right
    else if (((l == 1) && (c1 == 1) && (c2 == 0) && (c3 == 0) && (r == 0)) || ((l == 1) && (c1 == 0) && (c2 == 0) && (c3 == 0) && (r == 0)))
    {
      Right();
    }
    //left
    else if (((l == 0) && (c1 == 0) && (c2 == 0) && (c3 == 0) && (r == 1)) || ((l == 0) && (c1 == 0) && (c2 == 0) && (c3 == 1) && (r == 1)))
    {
      Left();
    }
    //marker
    else if ((l == 0) && (c1 == 0) && (c2 == 0) && (c3 == 0) && (r == 0))
    {
      Forward();
      digitalWrite(i, 1);
      delay(500);

    }
    if ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 1) && (r == 1))
    {
      Stop();
    }
  }
 // else if (m == 0)
 // {
 //   Stop();
//    digitalWrite(i, 1);

 //   Serial.print("obstalce");
 // }




