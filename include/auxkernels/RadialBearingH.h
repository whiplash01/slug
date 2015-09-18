#ifndef RADIALBEARINGHH_H
#define RADIALBEARINGHH_H

#include "AuxKernel.h"

class RadialBearingH;

template<>
InputParameters validParams<RadialBearingH>();

class RadialBearingH : public AuxKernel
{
public:

  RadialBearingH(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  Real _c;
  Real _e;
  Real _circ;
};

#endif //RADIALBEARING_H
