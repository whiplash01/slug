#ifndef REYNOLDSIDEALGAS_H
#define REYNOLDSIDEALGAS_H

#include "Material.h"

class ReynoldsIdealGas;

template<>
InputParameters validParams<ReynoldsIdealGas>();

class ReynoldsIdealGas : public Material
{
public:
  ReynoldsIdealGas(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

private:
  MaterialProperty<Real> & _mu;
  MaterialProperty<Real> & _rho;
  Real _T;
  VariableValue & _p;
};

#endif //REYNOLDSIDEALGAS_H
