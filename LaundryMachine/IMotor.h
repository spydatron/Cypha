#ifndef IMOTOR_H
#define IMOTOR_H

class IMotor
{
public:
  // Inputs
  virtual int GetMotorSpeed() = 0;
  // Outputs
  virtual void SetDirection(int dir) = 0;
  virtual void SetMotorSpeed(int value) = 0;
};

#endif


