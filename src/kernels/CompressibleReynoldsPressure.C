#include "CompressibleReynoldsPressure.h"

template<>
InputParameters validParams<CompressibleReynoldsPressure>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("h","lubricating gap thickness");
  params.addRequiredParam<Real>("v","perpheriphal speed");
  return params;
}

CompressibleReynoldsPressure::CompressibleReynoldsPressure(const InputParameters &parameters) :

  Kernel(parameters),
  _mu(getMaterialPropertyByName<Real>("mu")),
  _v(getParam<Real>("v"),0,0),
  _h(coupledValue("h")),
  _grad_h(coupledGradient("h"))
{

}

Real CompressibleReynoldsPressure::computeQpResidual()
{
  return _test[_i][_qp]*6.*_mu[_qp]*_v*(_u[_qp]*_grad_h[_qp]+_h[_qp]*_grad_u[_qp])
         -_test[_i][_qp]*_grad_u[_qp]*(std::pow(_h[_qp],3)*_grad_u[_qp]+_u[_qp]*3.*std::pow(_h[_qp],2)*_grad_h[_qp])
         +(
           _test[_i][_qp]*std::pow(_h[_qp],3)*_grad_u[_qp]
           +_test[_i][_qp]*_u[_qp]*3.*std::pow(_h[_qp],2)*_grad_h[_qp]
           +std::pow(_h[_qp],3)*_u[_qp]*_grad_test[_i][_qp]
         )*_grad_u[_qp];
}

Real CompressibleReynoldsPressure::computeQpJacobian()
{
  return  
    _test[_i][_qp]*6.*_mu[_qp]*_v*(_phi[_j][_qp]*_grad_h[_qp]+_h[_qp]*_grad_phi[_j][_qp])
    -_test[_i][_qp]*_grad_u[_qp]*(std::pow(_h[_qp],3)*_grad_phi[_j][_qp]+_phi[_j][_qp]*3.*std::pow(_h[_qp],2)*_grad_h[_qp])
    -_test[_i][_qp]*_grad_phi[_j][_qp]*(std::pow(_h[_qp],3)*_grad_u[_qp]+_u[_qp]*3.*std::pow(_h[_qp],2)*_grad_h[_qp])
    +_grad_phi[_j][_qp]*(
      _test[_i][_qp]*std::pow(_h[_qp],3)*_grad_u[_qp]
      +_test[_i][_qp]*_u[_qp]*3.*std::pow(_h[_qp],2)*_grad_h[_qp]
      +std::pow(_h[_qp],3)*_u[_qp]*_grad_test[_i][_qp]
    )
    +_grad_u[_qp]*(
      _test[_i][_qp]*std::pow(_h[_qp],3)*_grad_phi[_j][_qp]
      +_test[_i][_qp]*_phi[_j][_qp]*3.*std::pow(_h[_qp],2)*_grad_h[_qp]
      +std::pow(_h[_qp],3)*_phi[_j][_qp]*_grad_test[_i][_qp]
    );
}
