int lm1 = 2, lm2 = 3, rm1 = 4, rm2 = 5;
int l, c1, c2, c3, r, m;
int tdelay = 650;
int udelay = 0;

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
  digitalWrite(rm1, 1);
  digitalWrite(rm2, 1);
}


void smallleft()
{
  digitalWrite(lm1, 1);
  digitalWrite(lm2, 1);
  digitalWrite(rm1, 1);
  digitalWrite(rm2, 0);
}


void readsens()
{
  l = digitalRead(6);
  c1 = digitalRead(7);
  c2 = digitalRead(8);
  c3 = digitalRead(10);
  r = digitalRead(11);
  m = digitalRead(12);
}

int eosens()
{
  readsens();
  if (((c1 + c2 + c3) == 1) || ((c1 + c2 + c3) == 2))
    return 1;
  else
    return 0;
}
void inch()
{
  Stop();
  delay(500);
  Forward();
  delay(400);
  Stop();
  delay(500);
  readsens();
}

void setup()
{
  Serial.begin(115200);
  Serial.println("line");
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}


void loop()
{
  readsens();

  //Line Follow
  //fwd
  if ((l == 1) && (c1 == 1) && (c2 == 0) && (c3 == 1) && (r == 1))
  {
    Serial.print("Forward");
    Forward();
    //delay(10);
  }

  //left
  else if (((l == 1) && (c1 == 0) && (c2 == 1) && (c3 == 1) && (r == 1)) || ((l == 1) && (c1 == 0) && (c2 == 0) && (c3 == 1) && (r == 1)))
  {
    Serial.print("Small Left");
    smallleft();
  }
  //Right
  else if (((l == 1) && (c1 == 1) && (c2 == 0) && (c3 == 0) && (r == 1)) || ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 0) && (r == 1)))
  {
    Serial.print("Small Right");
    smallright();
  }

  //Dead end

  else if ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 1) && (r == 1))
  {
    Serial.print("U turn");
    Forward();
    delay(udelay);
  }

  else if (((l == 0) && (c1 == 0)) || ((c3 == 0) && (r == 0)))
  {
    readsens();
    //Right only or str right

    if (((l == 1) && (c1 == 1) && (c2 == 0) && (c3 == 0) && (r == 0)) || ((l == 1) && (c1 == 0) && (c2 == 0) && (c3 == 0) && (r == 0)))
    {
      Serial.print("Rt/Str n Rt?");
      inch();

      if ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 1) && (r == 1))
      {
        Serial.print("right");
        Right();
        delay(tdelay);
      }
      else if ((l == 1) && (r == 1) && (eosens()))
      {
        Serial.print("Right");
        Right();
        delay(tdelay);
      }
    }

    //left or straight and left
    else if (((l == 0) && (c1 == 0) && (c2 == 0) && (c3 == 0) && (r == 1)) || ((l == 0) && (c1 == 0) && (c2 == 0) && (c3 == 1) && (r == 1)))
    {
      Serial.print("Lt/Str n Lt?");
      inch();

      if ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 1) && (r == 1))
      {
        Serial.print("Left");
        Left();
        delay(tdelay);
      }

      else if ((l == 1) && (r == 1) && (eosens()))
      {
        Serial.print("Straight");
        Forward();
        // delay(fdelay);
      }
    }

    //4 way/T-tint/End of maze
    else if ((l == 0) && (c1 == 0) && (c2 == 0) && (c3 == 0) && (r == 0))
    {
      Serial.print("T/END/4");
      inch();
      if ((l == 1) && (r == 1) && (eosens()))
      {
        Serial.print("4 Way");
        Forward();
      }

      else if ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 1) && (r == 1))
      {
        Serial.print("T-int");
        Right();
        delay(tdelay);
      }

      else if ((l == 0) && (c1 == 0) && (c2 == 0) && (c3 == 0) && (r == 0))
      {
          Serial.print("End of maze");
          while(1)
          {
          Stop();
          }
       }
     }
   }
 }

