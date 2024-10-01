#define BRAKE 0
#define CW 1
#define CCW 2
#define TL 3
#define TR 4
#define CS_THRESHOLD 15 // Definition of safety current (Check: "1.3 
#define MOTOR_1 1
#define MOTOR_2 2
#define MOTOR_A1_PIN 4
#define MOTOR_B1_PIN 9
#define MOTOR_A2_PIN 7
#define MOTOR_B2_PIN 8
#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6
#define EN_PIN_1 A0
#define EN_PIN_2 A1
int x_key = A2;
int y_key = A3;
int x_pos;
int y_pos;
//int motor_speed;
//int motor_speed1;

short usSpeed = 150; //default motor speed
unsigned short usMotor_Status = BRAKE;

void Stop()
{
 usMotor_Status = BRAKE;
 motorGo(MOTOR_1, usMotor_Status, 0);
 motorGo(MOTOR_2, usMotor_Status, 0);
}
void Forward()
{
 usMotor_Status = CW;
 motorGo(MOTOR_1, usMotor_Status, usSpeed);
 motorGo(MOTOR_2, usMotor_Status, usSpeed);
}
void Reverse()
{
 usMotor_Status = CCW;
 motorGo(MOTOR_1, usMotor_Status, usSpeed);
 motorGo(MOTOR_2, usMotor_Status, usSpeed);
}
void TurnLeft()
{
 usMotor_Status = TL;
 motorGo(MOTOR_1, usMotor_Status, usSpeed);
 motorGo(MOTOR_2, usMotor_Status, usSpeed);
}
void TurnRight()
{
 usMotor_Status = TR;
 motorGo(MOTOR_1, usMotor_Status, usSpeed);
 motorGo(MOTOR_2, usMotor_Status, usSpeed);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) 
//Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
 if(motor == MOTOR_1, motor == MOTOR_2)
 {
 if(direct == CW)
 {
 digitalWrite(MOTOR_A1_PIN, HIGH); 
 digitalWrite(MOTOR_B1_PIN, LOW);
 digitalWrite(MOTOR_A2_PIN, HIGH);
 digitalWrite(MOTOR_B2_PIN, LOW);
 }
 else if(direct == CCW)
 {
 digitalWrite(MOTOR_A1_PIN, HIGH);
 digitalWrite(MOTOR_B1_PIN, LOW);
 digitalWrite(MOTOR_A2_PIN, LOW);
 digitalWrite(MOTOR_B2_PIN, HIGH);
 }
 else if(direct == TL)
 {
 digitalWrite(MOTOR_A1_PIN, LOW);
 digitalWrite(MOTOR_B1_PIN, HIGH);
 digitalWrite(MOTOR_A2_PIN, HIGH);
 digitalWrite(MOTOR_B2_PIN, LOW);
 }
 else if(direct == TR)
 {
 digitalWrite(MOTOR_A1_PIN, HIGH);
 digitalWrite(MOTOR_B1_PIN, LOW);
 digitalWrite(MOTOR_A2_PIN, LOW);
 digitalWrite(MOTOR_B2_PIN, HIGH);
 }
 else
 {
 digitalWrite(MOTOR_A1_PIN, LOW);
 digitalWrite(MOTOR_B1_PIN, LOW);
 digitalWrite(MOTOR_A2_PIN, LOW);
 digitalWrite(MOTOR_B2_PIN, LOW);
 }
 
 analogWrite(PWM_MOTOR_1, pwm);
 analogWrite(PWM_MOTOR_2, pwm);
 }
}

void setup() 
{
 pinMode(MOTOR_A1_PIN, OUTPUT);
 pinMode(MOTOR_B1_PIN, OUTPUT);
 pinMode(MOTOR_A2_PIN, OUTPUT);
 pinMode(MOTOR_B2_PIN, OUTPUT);
 pinMode(PWM_MOTOR_1, OUTPUT);
 pinMode(PWM_MOTOR_2, OUTPUT);
 pinMode(EN_PIN_1, OUTPUT);
 pinMode(EN_PIN_2, OUTPUT);
 
 //Initializing the joystick pins as input
 pinMode(x_key, INPUT);
 pinMode(y_key, INPUT);
 Serial.begin(9600); // Initiates the serial to do the monitoring 
}
void loop() 
{
 {digitalWrite(EN_PIN_1, HIGH);
  digitalWrite(EN_PIN_2, HIGH);
  x_pos = analogRead(x_key);
  y_pos = analogRead(y_key);

  if ((x_pos>250 && x_pos <400) && (y_pos>250 && y_pos <400)){
    Stop();
  }
  else if(x_pos < 400 && (y_pos>250 && y_pos <400)){
    TurnRight();
  }
  else if(x_pos > 250 && (y_pos>250 && y_pos <400)){
    TurnLeft();
  }
  else if(y_pos < 400 && (x_pos>250 && x_pos <400)){
    Reverse();
  }
  else if(y_pos > 250 && (x_pos>250 && x_pos <400)){
    Forward();
  }
 }
}