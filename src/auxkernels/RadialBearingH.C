#include "RadialBearingH.h"

template<>
InputParameters validParams<RadialBearingH>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("c", "diametral clearance");
  params.addParam<Real>("e","eccentricity");
  params.addParam<Real>("circ", "circumference");
  return params;
}

RadialBearingH::RadialBearingH(const InputParameters & parameters) :
    AuxKernel(parameters),
    _c(getParam<Real>("c")),
    _e(getParam<Real>("e")),
    _circ(getParam<Real>("circ"))
{}

Real
RadialBearingH::computeValue()
{
  return _c/2.-_e*std::cos((*_current_node)(0)/_circ*2.*pi);
}
