#include "AlphaBetaH.h"

template<>
InputParameters validParams<AlphaBetaH>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("alpha", "wedge angle");
  params.addParam<Real>("beta","transverse wedge angle");
  params.addParam<Real>("h", "gap height at origin");
  return params;
}

AlphaBetaH::AlphaBetaH(const InputParameters & parameters) :
    AuxKernel(parameters),
    _alpha(getParam<Real>("alpha")),
    _beta(getParam<Real>("beta")),
    _h(getParam<Real>("h"))
{}

Real
AlphaBetaH::computeValue()
{
  Real x = (*_current_node)(0);
  Real y = (*_current_node)(1);
  return -x*std::sin(_alpha) + y*std::sin(_beta) + _h;
}
