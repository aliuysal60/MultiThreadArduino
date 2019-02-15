const int RELAY1 = 12;
const int RELAY2 = 11;
const int RELAY3 = 10;

const int BUTTON1 = 2;
const int BUTTON2 = 3;
const int BUTTON3 = 4;

boolean lastButton1 = LOW;
boolean currentButton1 = LOW;
boolean relayOn1 = true;
boolean lastButton2 = LOW;
boolean currentButton2 = LOW;
boolean relayOn2 = true;
boolean lastButton3 = LOW;
boolean currentButton3 = LOW;
boolean relayOn3 = true;

boolean b1Start = false;
int b1Stage = -1;
unsigned long b1P1WorkingMillis = 0;


boolean b2Start = false;
int b2Stage = -1;
unsigned long b2P1WorkingMillis = 0;


boolean b3Start = false;
int b3Stage = -1;
unsigned long b3P1WorkingMillis = 0;

const long p1WorkingInterval = 3000;


void setup(){
  Serial.begin(9600); // See the connection status in Serial Monitor
  pinMode(RELAY1, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(BUTTON3, INPUT);

  digitalWrite(RELAY1, true);
  digitalWrite(RELAY2, true);
  digitalWrite(RELAY3, true);
}

boolean debounce1(boolean last1) {
  boolean current1 = digitalRead(BUTTON1);
  if(last1 != current1) {
    delay(5);
    current1 = digitalRead(BUTTON1);
  }
  return current1;
}
boolean debounce2(boolean last2) {
  boolean current2 = digitalRead(BUTTON2);
  if(last2 != current2) {
    delay(5);
    current2 = digitalRead(BUTTON2);
  }
  return current2;
}
boolean debounce3(boolean last3) {
  boolean current3 = digitalRead(BUTTON3);
  if(last3 != current3) {
    delay(5);
    current3 = digitalRead(BUTTON3);
  }
  return current3;
}

void loop()
{
  B1Function();
  B2Function();
  B3Function();
}

void B1Function()
{
  unsigned long nowMillis = 0;
  
  currentButton1 = debounce1(lastButton1);
  if(lastButton1 == LOW && currentButton1 == HIGH) {
    if (!b1Start)
    {
      b1Start = true;
      b1Stage = 0;
    }
  }
  lastButton1 = currentButton1;
  
  if (b1Start)
  {
    switch (b1Stage)
    {
      case 0:
        b1Stage = 1;
        digitalWrite(RELAY1, false);
        Serial.println("1.Röle Çekildi");
        b1P1WorkingMillis = millis();
        break;
      case 1:
        nowMillis = millis();
        if (nowMillis - b1P1WorkingMillis >= p1WorkingInterval)
        {
          b1Stage = -1;
          b1Start = false;
          Serial.println("1. Röle Kapandı!");
          digitalWrite(RELAY1, true);
        }
  
    }  
  }
}

void B2Function()
{
  unsigned long nowMillis = 0; 
  currentButton2 = debounce2(lastButton2);
  if(lastButton2 == LOW && currentButton2 == HIGH) {
    if (!b2Start)
    {
      b2Start = true;
      b2Stage = 0;
    }
  }
  lastButton2 = currentButton2;
  
  if (b2Start)
  {
    switch (b2Stage)
    {
      case 0:
        b2Stage = 1;
        digitalWrite(RELAY2, false);
        Serial.println("2. Röle Çekildi");
        b2P1WorkingMillis = millis();
        break;
      case 1:
        nowMillis = millis();
        if (nowMillis - b2P1WorkingMillis >= p1WorkingInterval)
        {
          b2Stage = -1;
          b2Start = false;
          Serial.println("2. Röle Kapandı!");
          digitalWrite(RELAY2, true);
        }
    }  
  }
}


void B3Function()
{
  unsigned long nowMillis = 0; 
  currentButton3 = debounce3(lastButton3);
  if(lastButton3 == LOW && currentButton3 == HIGH) {
    if (!b3Start)
    {
      b3Start = true;
      b3Stage = 0;
    }
  }
  lastButton3 = currentButton3;
  
  if (b3Start)
  {
    switch (b3Stage)
    {
      case 0:
        b3Stage = 1;
        digitalWrite(RELAY3, false);
        Serial.println("3. Röle Çekildi");
        b3P1WorkingMillis = millis();
        break;
      case 1:
        nowMillis = millis();
        if (nowMillis - b3P1WorkingMillis >= p1WorkingInterval)
        {
          b3Stage = -1;
          b3Start = false;
          Serial.println("3. Röle Kapandı!");
          digitalWrite(RELAY3, true);
        }
    }  
  }
}
