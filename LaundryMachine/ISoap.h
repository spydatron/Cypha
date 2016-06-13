#ifndef ISOAP_H
#define ISOAP_H

class ISoap
{
public:
  // Inputs
  virtual boolean GetSoap1Switch() = 0;
  virtual boolean GetSoap2Switch() = 0;
  // Outputs
  virtual void SetSoap2(int level) = 0;
};

#endif


