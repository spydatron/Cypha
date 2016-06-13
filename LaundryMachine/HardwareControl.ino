#define OUT_GROUP2      0
#define OUT_GROUP1      1
#define OUT_STROBE      2
#define OUT_KEYSELECT   3
#define OUT_BUZZER      4
#define OUT_HEATER      5
#define OUT_SPEED2      6
#define OUT_SPEED1      7
#define OUT_DATAC       8
#define OUT_DATAB       9
#define OUT_DATAA       10
#define OUT_MOTOR_RL    11
#define OUT_SOAP1       12
#define OUT_SINK        13
#define OUT_DRAIN       14
#define OUT_LOCK        15
#define IN_W2           16
#define IN_W1           17
#define IN_T2           18
#define IN_T1           19
#define IN_IN3          20
#define IN_IN2          21
#define IN_IN1          22
#define IN_IN0          23

HardwareControl::HardwareControl()
{
  Wire.begin(); // start I2C
  centipede.initialize(); // set all registers to default
  for (int i = 0; i <= 15; i++) 
  {
    centipede.pinMode(i, OUTPUT);
  }
  centipede.digitalWrite(OUT_GROUP2, LOW);
  centipede.digitalWrite(OUT_GROUP1, LOW);
  centipede.digitalWrite(OUT_STROBE, LOW);
  centipede.digitalWrite(OUT_KEYSELECT, HIGH);
  centipede.digitalWrite(OUT_BUZZER, HIGH);
  centipede.digitalWrite(OUT_HEATER, HIGH);
  centipede.digitalWrite(OUT_SPEED2, HIGH);
  centipede.digitalWrite(OUT_SPEED1, HIGH);
  centipede.digitalWrite(OUT_DATAC, LOW);
  centipede.digitalWrite(OUT_DATAB, LOW);
  centipede.digitalWrite(OUT_DATAA, LOW);
  centipede.digitalWrite(OUT_MOTOR_RL, LOW);
  centipede.digitalWrite(OUT_SOAP1, LOW);
  centipede.digitalWrite(OUT_SINK, LOW);
  centipede.digitalWrite(OUT_DRAIN, LOW);
  centipede.digitalWrite(OUT_LOCK, LOW);
}

static const int Button10[] = {
  LOW, LOW, LOW, HIGH};
static const int Button50[] = {
  LOW, LOW, HIGH, LOW};
static const int Button200[] = {
  LOW, HIGH, LOW, LOW};
static const int ButtonStart[] = {
  HIGH, LOW, LOW, LOW};
static const int ButtonClear[] = {
  LOW, HIGH, HIGH, HIGH};
static const int ButtonProgram[] = {
  HIGH, LOW, LOW, HIGH};

//-----------------------------------------------------------------------------------

boolean HardwareControl::KeySelectSwitchOn(const int in)
{
  SetKeySelect(0);
  return (centipede.digitalRead(in) == HIGH);
}

boolean HardwareControl::KeySelectButtonPressed(const int* button)
{
  SetKeySelect(1);
  return ((centipede.digitalRead(IN_IN3) == button[3]) &&
    (centipede.digitalRead(IN_IN2) == button[2]) &&
    (centipede.digitalRead(IN_IN1) == button[1]) &&
    (centipede.digitalRead(IN_IN0) == button[0]));
}

//-----------------------------------------------------------------------------------

boolean HardwareControl::GetClear()
{
  return KeySelectButtonPressed(ButtonClear);
}

boolean HardwareControl::GetCoin10()
{
  return KeySelectButtonPressed(Button10);
}

boolean HardwareControl::GetCoin50()
{
  return KeySelectButtonPressed(Button50);
}

boolean HardwareControl::GetCoin200()
{
  return KeySelectButtonPressed(Button200);
}

boolean HardwareControl::GetStartButton()
{
  return KeySelectButtonPressed(ButtonStart);
}

boolean HardwareControl::GetProgramButton()
{
  return KeySelectButtonPressed(ButtonProgram);
}

//-----------------------------------------------------------------------------------

boolean HardwareControl::GetLockSwitch()
{
  return KeySelectSwitchOn(IN_IN3);
}

boolean HardwareControl::GetSoap1Switch()
{
  return KeySelectSwitchOn(IN_IN1);
}

boolean HardwareControl::GetSoap2Switch()
{
  return KeySelectSwitchOn(IN_IN2);
}

boolean HardwareControl::GetPressureSwitch()
{
  return KeySelectSwitchOn(IN_IN0);
}

//-----------------------------------------------------------------------------------

int HardwareControl::GetMotorSpeed()
{
  return 0;
}

int HardwareControl::GetTemperature()
{
  return ( centipede.digitalRead(IN_T2) << 1 ) + ( centipede.digitalRead(IN_T1) );
}
int HardwareControl::GetWaterLevel()
{
  return ( centipede.digitalRead(IN_W2) << 1 ) + ( centipede.digitalRead(IN_W1) );
}

//-----------------------------------------------------------------------------------

void HardwareControl::SetLeds(int leds, boolean limit)
{
  switch(leds)
  {
  case 0:
    SetData(0);
    break;
  case 1:
    SetData(0b100);
    break;
  case 2:
    SetData(0b110);
    break;
  case 3:
    if ( !limit )
      SetData(0b111);
    break;
  }
}

void HardwareControl::SetCoin10(int leds) //0 = 0 leds on,...,3 = 3 leds on.
{
  SetGroup(0b00);
  SetLeds(leds, false);
}

void HardwareControl::SetCoin50(int leds)
{
  SetGroup(0b10);
  SetLeds(leds, false);
}

void HardwareControl::SetCoin200(int leds)
{
  SetGroup(0b01);
  SetLeds(leds, true);
}

void HardwareControl::SetProgramIndicator(int program)
{
  SetGroup(0b11);
  SetData(0b100 >> program);
}

void HardwareControl::SetClear()
{
  SetCoin10(0);
  SetCoin50(0);
  SetCoin200(0);
}
//-----------------------------------------------------------------------------------

void HardwareControl::SetBuzzer(int level)
{
  centipede.digitalWrite(OUT_BUZZER, level);
}

void HardwareControl::SetSoap1(boolean level)
{
  centipede.digitalWrite(OUT_SOAP1, level);
}

void HardwareControl::SetSoap2(boolean level)
{
  SetGroup(0b01);
  if(level)
    SetData(0b1);
  else
    SetData(0b0);
}

//-----------------------------------------------------------------------------------

void HardwareControl::SetDrain(int level)
{
  centipede.digitalWrite(OUT_DRAIN, level);
}

void HardwareControl::SetSink(int level)
{
  centipede.digitalWrite(OUT_SINK, level);
}

void HardwareControl::SetDirection(int dir)
{
  centipede.digitalWrite(OUT_MOTOR_RL, dir);
}

void HardwareControl::SetMotorSpeed(int value)
{
  switch(value)
  {
    case 1:
      centipede.digitalWrite(OUT_SPEED2, 1);
      centipede.digitalWrite(OUT_SPEED1, 1);
      break;
    case 2:
      centipede.digitalWrite(OUT_SPEED2, 1);
      centipede.digitalWrite(OUT_SPEED1, 0);
      break;
    case 3:
      centipede.digitalWrite(OUT_SPEED2, 0);
      centipede.digitalWrite(OUT_SPEED1, 1);
      break;
    case 4:
      centipede.digitalWrite(OUT_SPEED2, 0);
      centipede.digitalWrite(OUT_SPEED1, 0);
      break;
  }
}

void HardwareControl::SetLock(int state)
{
  centipede.digitalWrite(OUT_LOCK, state);
}

void HardwareControl::SetHeater(int value)
{
  centipede.digitalWrite(OUT_HEATER, value);
}

//-----------------------------------------------------------------------------------

void HardwareControl::SetKeySelect(int value)
{
  centipede.digitalWrite(OUT_KEYSELECT, value);
}

void HardwareControl::SetGroup(unsigned char group)
{
  Strobe();
  centipede.digitalWrite(OUT_GROUP2, group & 0b01);
  centipede.digitalWrite(OUT_GROUP1, group & 0b10);
}

void HardwareControl::SetData(unsigned char data)
{
  centipede.digitalWrite(OUT_DATAC, data & 0b001);
  centipede.digitalWrite(OUT_DATAB, data & 0b010);
  centipede.digitalWrite(OUT_DATAA, data & 0b100);
}

void HardwareControl::Strobe()
{
  centipede.digitalWrite(OUT_STROBE, LOW);
  delay(80);
  centipede.digitalWrite(OUT_STROBE, HIGH);
  delay(10);
  centipede.digitalWrite(OUT_STROBE, LOW);
}

