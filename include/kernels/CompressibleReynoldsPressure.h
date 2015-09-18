#ifndef COMPRESSIBLEREYNOLDSPRESSURE_H
#define COMPRESSIBLEREYNOLDSPRESSURE_H

#include "Kernel.h"

class CompressibleReynoldsPressure;

template<>
InputParameters validParams<CompressibleReynoldsPressure>();

class CompressibleReynoldsPressure : public Kernel
{
public:

  CompressibleReynoldsPressure(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

protected:

  const MaterialProperty<Real>& _mu;
  RealVectorValue _v;
  VariableValue & _h;
  VariableGradient & _grad_h;

};

#endif // COMPRESSIBLEREYNOLDSPRESSURE_H
