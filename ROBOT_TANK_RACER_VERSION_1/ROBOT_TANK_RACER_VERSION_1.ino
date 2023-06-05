#define BLUE_LED 16
#define GREEN_LED 17
#define POWER_LED 18
#define STATUS_LED 19
#define BUTTON 7

#define BLUE_INPUT 3
#define BLUE_SENSOR 5
#define GREEN_SENSOR 4
#define GREEN_INPUT 6

#define ENG1_1 8
#define ENG1_2 9
#define ENG1_S 11

#define ENG2_1 12
#define ENG2_2 13
#define ENG2_S 10

#define MIN_SENSOR_VALUE 100
#define TANK_MIN_SPEED 70
#define TANK_MAX_SPEED 150

#define RIGHT 100
#define LEFT 200

bool routine_started;
int direction;
bool running;

void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(POWER_LED, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  pinMode(BLUE_SENSOR, INPUT_PULLUP);
  pinMode(GREEN_SENSOR, INPUT_PULLUP);

  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(POWER_LED, LOW);
  digitalWrite(STATUS_LED, LOW);

  pinMode(ENG1_1, OUTPUT);
  pinMode(ENG1_2, OUTPUT);
  pinMode(ENG2_1, OUTPUT);
  pinMode(ENG2_2, OUTPUT);
  pinMode(ENG1_S, OUTPUT);
  pinMode(ENG2_S, OUTPUT);

  digitalWrite(POWER_LED, HIGH);
  delay(300);
  digitalWrite(POWER_LED, LOW);
  delay(300);
  digitalWrite(POWER_LED, HIGH);

  routine_started = false;
  running = false;
}

void loop() {

  if(routine_started)
  {
    if(!digitalRead(BUTTON))
    {
      routine_started = false;
      digitalWrite(STATUS_LED, LOW);
      stop();
      delay(500);
    }
    else
    {
      if(!running)
      {
        if(direction == RIGHT)
        {
          goRight(35);
          delay(50);
        }
        else
        {
          goLeft(38);
          delay(50);
        }
      }
      
      else
      {
        if(!digitalRead(BLUE_SENSOR)){
          stop();
          direction = RIGHT;
          digitalWrite(BLUE_LED, HIGH);
          delay(300);
          digitalWrite(BLUE_LED, LOW);
          delay(300);
          digitalWrite(BLUE_LED, HIGH);
          delay(300);
          digitalWrite(BLUE_LED, LOW);
          delay(300);
          digitalWrite(BLUE_LED, HIGH);
          delay(300);
          digitalWrite(BLUE_LED, LOW);
          delay(300);
        }
        if(!digitalRead(GREEN_SENSOR)){
          stop();
          direction = LEFT;
          digitalWrite(GREEN_LED, HIGH);
          delay(300);
          digitalWrite(GREEN_LED, LOW);
          delay(300);
          digitalWrite(GREEN_LED, HIGH);
          delay(300);
          digitalWrite(GREEN_LED, LOW);
          delay(300);
          digitalWrite(GREEN_LED, HIGH);
          delay(300);
          digitalWrite(GREEN_LED, LOW);
          delay(300);
        }
      }
    }
  }
  else
  {
    if(!digitalRead(BUTTON))
    {
      digitalWrite(STATUS_LED, HIGH);
      routine_started = true;
      direction = LEFT;
      delay(500);
    }
  }
  delay(20);
  


}

void stop()
{
  running = false;

  digitalWrite(ENG1_1, LOW);
  digitalWrite(ENG1_2, LOW);

  digitalWrite(ENG2_1, LOW);
  digitalWrite(ENG2_2, LOW);
}

void goRight(int speed)
{
  running = true;
  int sp = map(speed, 0, 100, TANK_MIN_SPEED, TANK_MAX_SPEED);

  analogWrite(ENG1_S, sp);
  analogWrite(ENG2_S, sp+10);
  
  digitalWrite(ENG1_1, HIGH);
  digitalWrite(ENG1_2, LOW);

  digitalWrite(ENG2_1, LOW);
  digitalWrite(ENG2_2, HIGH);
}

void goLeft(int speed)
{
  running = true;
  int sp = map(speed, 0, 100, TANK_MIN_SPEED, TANK_MAX_SPEED);

  analogWrite(ENG1_S, sp);
  analogWrite(ENG2_S, sp+10);
  
  digitalWrite(ENG1_1, LOW);
  digitalWrite(ENG1_2, HIGH);

  digitalWrite(ENG2_1, HIGH);
  digitalWrite(ENG2_2, LOW);
}

