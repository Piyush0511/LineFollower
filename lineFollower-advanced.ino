
int lm1 = 2, lm2 = 3, rm1 = 4, rm2 = 5;
int l, c1, c2, c3, r;
int a, b, c, d, e, x, y;


void Forward()
  {
    digitalWrite(lm1, 1);
    digitalWrite(lm2, 0);
    digitalWrite(rm1, 1);
    digitalWrite(rm2, 0);
  }

void Stop()
  {
    digitalWrite(lm1, 0);
    digitalWrite(lm2, 0);
    digitalWrite(rm1, 0);
    digitalWrite(rm2, 0);
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

int eosens()
  {
    readsens();
    if (((c1 + c2 + c3) == 1) || ((c1 + c2 + c3) == 2))
      return 1;
    else
      return 0;
  }

void clearval()
  {
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    x = 0;
    y = 0;
  }

void readsens()
  {
    l = digitalRead(6);
    c1 = digitalRead(7);
    c2 = digitalRead(8);
    c3 = digitalRead(10);
    r = digitalRead(11);
  }
  
void readval()
{
  
  if(l == 0)
    {
      a = 2;
    }
  if(c1 == 0)
    {
      b = 1;
    }
  if(c2 == 0)
    {
      c = 0;
    }
  if(c3 == 0)
    {
      d = 1;
    }
  if(r == 0)
    {
      e = 2;
    }

  x = a + b;
  
  y = d + e;
  
}


int hello()
  {
    
    readsens();
    if ((l == 1)&& eosens() &&(r == 1))
      {
        return 0; 
      }
    else
      return 1; 
  
  }
void inch()
  {
    Stop();
    delay(500);
    Forward();
    delay(100);
    Stop();
    delay(500);
    readsens();
  }



//LINE FOLLOWER PATH




void setup()
  {
    Serial.begin(9600);
    Serial.print("LINE FOLLOWER");
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
  
    //Forward
    if ((l == 1) && (c1 == 1) && (c2 == 0) && (c3 == 1) && (r == 1))
      {
        
         Serial.println("forward");
         Forward();
         delay(15);
         Stop();
         delay(1);

      }
    

   //smallleft
    else if (((l == 1) && (c1 == 0) && (c2 == 1) && (c3 == 1) && (r == 1)) || ((l == 1) && (c1 == 0) && (c2 == 0) && (c3 == 1) && (r == 1)))
      {
        
        Serial.println("smallleft");
        smallleft();
    
      }


    //smallright
    else if (((l == 1) && (c1 == 1) && (c2 == 0) && (c3 == 0) && (r == 1)) || ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 0) && (r == 1)))
      {
        
        Serial.println("smallright");
        smallright();

      }
      
   //no line
    else if ((l == 1) && (c1 == 1) && (c2 == 1) && (c3 == 1) && (r == 1))
      {
        
       Forward();
                
      }

   //black line  
    else if ((l == 0) && (c1 == 0) && (c2 == 0) && (c3 == 0) && (r == 0))
      {
        
       Forward(); 
           
      }

    else 
      {
        clearval();
        readsens();
        readval();

        //Serial.print(x);
        //Serial.print(y);
        //Serial.println();
         if(x > y)
          {
            Stop();
            delay(50);
            while(hello())
              {
                
                Serial.print("left");
                Left();
       
              }
          } 
          
        //Right
        else if(x < y)
          {
            Stop();
            delay(50);
            while(hello())
              { 
                
               Serial.println("right");
               Right();
               
              }
          }
      }   
 } 



