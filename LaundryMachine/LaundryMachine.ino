#include <Wire.h>
#include <Centipede.h>

#include "IBuzzer.h"
#include "ICoin.h"
#include "ILock.h"
#include "IMotor.h"
#include "IProgram.h"
#include "ISoap.h"
#include "ITemperature.h"
#include "IWater.h"

#include "HardwareControl.h"
#include "CoinWallet.h"
#include "ProgramSelect.h"
#include "ProgramSettings.h"
#include "ProgramExecutor.h"

static HardwareControl * mControl;
static IBuzzer * mBuzzer;
static ICoin * mCoin;
static IMotor * mMotor;
static ILock * mLock;
static IProgram * mProgram;
static ISoap * mSoap;
static ITemperature * mTemperature;
static IWater * mWater;
static CoinWallet * mCoinWallet;
static ProgramSelect * mProgramSelect;
static ProgramSettings * mProgramSettings;
static ProgramExecutor * mProgramExecutor;
static int now=0, later=0,i=1;
void setup()
{
  Serial.begin(9600);
  mControl = new HardwareControl();

}
void test()
{
  now=millis();
  if(now-later>=500)
  {
    if(mControl->GetCoin10())
    {
      if(i<4)
        i++;
      else
        i=1;
      later=now;
    }
  }
  mControl->SetDirection(1);
  mControl->SetMotorSpeed(i);
}

void loop()
{
  if(mControl->GetLockSwitch())
    mControl->SetLock(1);
  else
    mControl->SetLock(0);
  if(mControl->GetSoap1Switch())
    mControl->SetSoap1(1);
  else
    mControl->SetSoap1(0);
  if(mControl->GetSoap2Switch())
    mControl->SetSoap2(1);
  else
    mControl->SetSoap2(0);
}
