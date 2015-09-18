#include "ReynoldsMassFlow.h"

template<>
InputParameters validParams<ReynoldsMassFlow>()
{
  InputParameters params = validParams<ReynoldsMeanVelocity>();
  return params;
}

ReynoldsMassFlow::ReynoldsMassFlow(const InputParameters & parameters) :
    ReynoldsMeanVelocity(parameters),
    _rho(getMaterialPropertyByName<Real>("rho"))
{}

Real
ReynoldsMassFlow::computeValue()
{
  return _rho[_qp] * _h[_qp] * ReynoldsMeanVelocity::computeValue();
}
