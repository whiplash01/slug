#include "ReynoldsMeanVelocity.h"

template<>
InputParameters validParams<ReynoldsMeanVelocity>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("component", "velocity component");
  params.addParam<RealVectorValue>("vel_surface","surface velocity");
  params.addRequiredCoupledVar("p","pressure");
  params.addRequiredCoupledVar("h","film thickness");
  return params;
}

ReynoldsMeanVelocity::ReynoldsMeanVelocity(const InputParameters & parameters) :
    AuxKernel(parameters),
    _component(getParam<Real>("component")),
    _vel_surface(getParam<RealVectorValue>("vel_surface")),
    _mu(getMaterialPropertyByName<Real>("mu")),
    _grad_p(coupledGradient("p")),
    _h(coupledValue("h"))
{}

Real
ReynoldsMeanVelocity::computeValue()
{
  return -pow(_h[_qp],2)/(12.0*_mu[_qp])*_grad_p[_qp](_component)
    + _vel_surface(_component)/2.0;
}
