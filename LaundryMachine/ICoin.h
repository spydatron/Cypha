#ifndef ICOIN_H
#define ICOIN_H

class ICoin
{
public:
  // Inputs
  virtual boolean GetCoin10() = 0;
  virtual boolean GetCoin50() = 0;
  virtual boolean GetCoin200() = 0;
  virtual boolean GetClear() = 0;
  // Outputs
  virtual void SetCoin10(int leds) = 0;
  virtual void SetCoin50(int leds) = 0;
  virtual void SetCoin200(int leds) = 0;
  virtual void SetClear() = 0;
};

#endif


