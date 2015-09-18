#ifndef REYNOLDSMEANVELOCITY_H
#define REYNOLDSMEANVELOCITY_H

#include "AuxKernel.h"

class ReynoldsMeanVelocity;

template<>
InputParameters validParams<ReynoldsMeanVelocity>();

class ReynoldsMeanVelocity : public AuxKernel
{
public:

  ReynoldsMeanVelocity(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  unsigned _component;
  RealVectorValue _vel_surface;
  const MaterialProperty<Real> & _mu;
  VariableGradient & _grad_p;
  VariableValue & _h;

};

#endif //REYNOLDSMEANVELOCITY_H
