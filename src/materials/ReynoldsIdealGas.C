#include "ReynoldsIdealGas.h"

template<>
InputParameters validParams<ReynoldsIdealGas>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<Real>("temp","gas temperature");
  params.addRequiredCoupledVar("p","pressure");
  return params;
}

ReynoldsIdealGas::ReynoldsIdealGas(const InputParameters &parameters):
  Material(parameters),
  _mu(declareProperty<Real>("mu")),
  _rho(declareProperty<Real>("rho")),
  _T(getParam<Real>("temp")),
  _p(coupledValue("p"))
{}

void
ReynoldsIdealGas::computeQpProperties()
{
  _mu[_qp] = 1.75e-5; // N*s/m^2
  _rho[_qp] = _p[_qp]/(287.0*_T);
}
