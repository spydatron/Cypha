#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include "Centipede.h"

#include "IBuzzer.h"
#include "ICoin.h"
#include "ILock.h"
#include "IMotor.h"
#include "IProgram.h"
#include "ISoap.h"
#include "ITemperature.h"
#include "IWater.h"

class HardwareControl : public ICoin, public IProgram
{
  public:
    HardwareControl();
    Centipede centipede;

    // Inputs
    boolean GetClear();
    boolean GetCoin10();
    boolean GetCoin50();
    boolean GetCoin200();
    
    boolean GetStartButton();
    boolean GetProgramButton();
    
    boolean GetLockSwitch();
    boolean GetSoap1Switch();
    boolean GetSoap2Switch();
    boolean GetPressureSwitch();
    int GetMotorSpeed();
    int GetTemperature();
    int GetWaterLevel();

    // Outputs
    void SetClear();
    void SetCoin10(int leds);
    void SetCoin50(int leds);
    void SetCoin200(int leds);
    void SetBuzzer(int level);
    void SetSoap1(boolean level);
    void SetSoap2(boolean level);
    void SetDrain(int level);
    void SetSink(int level);
    void SetDirection(int dir); //0=left 1=right
    void SetMotorSpeed(int value); //0=off 1=slow 2=medium 3=high
    void SetProgramIndicator(int program); //0=off 1=A 2=B 3=C
    void SetLock(int state);
    void SetHeater(int value);

  private:
    void SetKeySelect(int value);
    void SetGroup(unsigned char group);
    void SetData(unsigned char data);
    void Strobe();

    boolean KeySelectButtonPressed(const int* button);
    boolean KeySelectSwitchOn(const int in);
    void SetLeds(int leds, boolean limit);
    int motorSpeed;
};

#endif
