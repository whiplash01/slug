/* -------------------------------------------------------------------------------
    slug - a finite element solver for lubrication films
    Copyright (C) 2015 Adam Lange

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
  ----------------------------------------------------------------------------- */
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
