#ifndef ILOCK_H
#define ILOCK_H

class ILock
{
public:
  // Inputs
  virtual boolean GetLockSwitch() = 0;
  // Outputs
  virtual void SetLock(int state) = 0;
};

#endif


