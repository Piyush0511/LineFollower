// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#define ldr A9
AF_DCMotor motorL(4);
AF_DCMotor motorR(2);
int b = 46, LS, RS, MS, abc;
void setup()
{
  Serial.begin(115200);           // set up Serial library at 9600 bps
  Serial.println("Line Follower");
  pinMode(46 , OUTPUT);
  pinMode(39, INPUT);
  pinMode(51, INPUT);
  pinMode(43, INPUT);
  pinMode(ldr, INPUT);

  // turn on motor
  motorL.setSpeed(200);
  motorL.run(RELEASE);

  motorR.setSpeed(200);
  motorR.run(RELEASE);
}

void loop()
{
  LS = digitalRead(39);
  RS = digitalRead(51);
  MS = digitalRead(43);
  abc = analogRead(ldr);
  Serial.println(abc);
  digitalWrite(b, LOW);
  if (abc > 720)
  {
    if ((LS == 0) && (RS == 0) && (MS == 1))// frd with no obstacle
    {
      Serial.println("frd with no obst");
      motorL.run(FORWARD);
      motorL.setSpeed(255);
      motorR.run(FORWARD);
      motorR.setSpeed(255);
    }
    else if ((LS == 0) && (RS == 1) && (MS == 1))// rgt with no obstacle
    {
      Serial.println("rgt with no obst");
      motorL.run(FORWARD);
      motorL.setSpeed(250);
      motorR.run(BACKWARD);
      motorR.setSpeed(220);
    }
   else if ((LS == 1) && (RS == 0) && (MS == 1))// lft with no obstacle
    {
      Serial.println("lft with no obst");
      motorL.run(BACKWARD);
      motorL.setSpeed(220);
      motorR.run(FORWARD);
      motorR.setSpeed(250);
    }
    else if ((LS == 1) && (RS == 1) && (MS == 1))// marker with no obstacle
      {
      Serial.println("Marker with no obst");
      motorL.run(FORWARD);
      motorL.setSpeed(255);
      motorR.run(FORWARD);
      motorR.setSpeed(255);
      digitalWrite(b, HIGH);
      delay(200);
      }
    else if ((LS == 0) && (RS == 0) && (MS == 0))// obstacle
    {
      Serial.println("obst");
      motorL.run(RELEASE);
      motorL.setSpeed(255);
      motorR.run(RELEASE);
      motorR.setSpeed(255);
      digitalWrite(b, HIGH);
      delay(200);

    }
  }
  else if (abc < 720)
  {
    if ((LS == 0) && (RS == 0) && (MS == 1))// frd with no obstacle and cave
    {
      Serial.println("frd with no obst and cave");
      motorL.run(FORWARD);
      motorL.setSpeed(190);
      motorR.run(FORWARD);
      motorR.setSpeed(190);
    }
    else if ((LS == 0) && (RS == 1) && (MS == 1))// rgt with no obstacle and cave
    {
      Serial.println("rgt with no obst and cave");
      motorL.run(FORWARD);
      motorL.setSpeed(190);
      motorR.run(BACKWARD);
      motorR.setSpeed(190);
    }
   else if ((LS == 1) && (RS == 0) && (MS == 1))// lft with no obstacle and cave
    {
      Serial.println("lft with no obst cave");
      motorL.run(BACKWARD);
      motorL.setSpeed(190);
      motorR.run(FORWARD);
      motorR.setSpeed(190);
    }
    else if ((LS == 1) && (RS == 1) && (MS == 1))// marker with no obstacle and cave
    {
      Serial.println("Marker with no obst and cave");
      motorL.run(FORWARD);
      motorL.setSpeed(190);
      motorR.run(FORWARD);
      motorR.setSpeed(190);
      digitalWrite(b, HIGH);
      delay(200);
    }
  }
}
