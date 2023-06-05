#define ENG1_1 6
#define ENG1_2 7
#define ENG1_S 10

#define ENG2_1 4
#define ENG2_2 5
#define ENG2_S 11

#define LED_STATUS 12
#define LED_ON 13
#define LED_YELLOW 8
#define LED_BLUE 9

#define START_BUTTON A0

#define SENSOR_YELLOW A5
#define SENSOR_BLUE A4
#define INPUT_YELLOW A3
#define INPUT_BLUE A2

#define MIN_SENSOR_VALUE 100
#define TANK_MIN_SPEED 70
#define TANK_MAX_SPEED 100

int STATUS = 0;



void setup() {
  // put your setup code here, to run once:
  pinMode(ENG1_1, OUTPUT);
  pinMode(ENG1_2, OUTPUT);
  pinMode(ENG2_1, OUTPUT);
  pinMode(ENG2_2, OUTPUT);
  pinMode(ENG1_S, OUTPUT);
  pinMode(ENG2_S, OUTPUT);

  pinMode(LED_STATUS, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(SENSOR_YELLOW, INPUT_PULLUP);
  pinMode(SENSOR_BLUE, INPUT_PULLUP);
  pinMode(INPUT_YELLOW, INPUT);
  pinMode(INPUT_BLUE, INPUT);

  digitalWrite(LED_ON, HIGH);
  digitalWrite(LED_STATUS, LOW);
}

void loop() {

  
  if(STATUS == 0)
  {
    stop();
    if(digitalRead(START_BUTTON) == LOW)
    {
      STATUS = 1;
      digitalWrite(LED_STATUS, HIGH);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_BLUE, LOW);
    }
    delay(100);
  }
  else
  {

    if(digitalRead(SENSOR_YELLOW) == LOW)
    {
      stop();
      STATUS = 0;
      digitalWrite(LED_STATUS, LOW);
      digitalWrite(LED_YELLOW, HIGH);
    }
    if(digitalRead(SENSOR_BLUE) == LOW)
    {
      stop();
      STATUS = 0;
      digitalWrite(LED_STATUS, LOW);
      digitalWrite(LED_BLUE, HIGH);
    }
      

    if(STATUS == 1)
    {
      int input_yellow = readInputYellow();
      int input_blue = readInputBlue();

      if(input_yellow == input_blue)
      {
        stop();
      } 
      else
      {
        if(input_yellow > input_blue)
        {
          int dif = input_yellow - input_blue;
          int speed = map(dif, 0, 100, TANK_MIN_SPEED, TANK_MAX_SPEED);
          goRight(speed);                  
        } 
        else
        {
          int dif = input_blue - input_yellow;
          int speed = map(dif, 0, 100, TANK_MIN_SPEED, TANK_MAX_SPEED);
          goLeft(speed);
        }   
      }  
    }

    delay(50);
      
  }

}

int readInputYellow()
{
  int sensorValue = analogRead(INPUT_YELLOW);
  if(sensorValue > MIN_SENSOR_VALUE)
  {
    int percent = map(sensorValue, MIN_SENSOR_VALUE, 1023, 0, 100);
    return percent;
  }
  return 0;
  
}

int readInputBlue()
{
  int sensorValue = analogRead(INPUT_BLUE);
  if(sensorValue > MIN_SENSOR_VALUE)
  {
    int percent = map(sensorValue, MIN_SENSOR_VALUE, 1023, 0, 100);
    return percent;
  }
  return 0;
  
}

void stop()
{
  digitalWrite(ENG1_1, LOW);
  digitalWrite(ENG1_2, LOW);

  digitalWrite(ENG2_1, LOW);
  digitalWrite(ENG2_2, LOW);
}

void goRight(int speed)
{
  analogWrite(ENG1_S, speed);
  analogWrite(ENG2_S, speed);
  
  digitalWrite(ENG1_1, HIGH);
  digitalWrite(ENG1_2, LOW);

  digitalWrite(ENG2_1, LOW);
  digitalWrite(ENG2_2, HIGH);
}

void goLeft(int speed)
{
  analogWrite(ENG1_S, speed);
  analogWrite(ENG2_S, speed);
  
  digitalWrite(ENG1_1, LOW);
  digitalWrite(ENG1_2, HIGH);

  digitalWrite(ENG2_1, HIGH);
  digitalWrite(ENG2_2, LOW);
}

