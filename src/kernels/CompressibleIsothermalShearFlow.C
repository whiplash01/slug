/* -------------------------------------------------------------------------------
    slug - a finite element solver for simulation of lubrication films
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

#include "CompressibleIsothermalShearFlow.h"

template<>
InputParameters validParams<CompressibleIsothermalShearFlow>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("h","lubricating film thickness");
  params.addRequiredParam<RealVectorValue>("vel_surface","sliding velocity");
  return params;
}

CompressibleIsothermalShearFlow::CompressibleIsothermalShearFlow(const InputParameters &parameters) :

  Kernel(parameters),
  _mu(getMaterialPropertyByName<Real>("mu")),
  _v(getParam<RealVectorValue>("vel_surface")),
  _h(coupledValue("h"))
{
}

Real CompressibleIsothermalShearFlow::computeQpResidual()
{
  return -_grad_test[_i][_qp]*6.0*_mu[_qp]*_h[_qp]*_u[_qp]*_v;
}

Real CompressibleIsothermalShearFlow::computeQpJacobian()
{
  return -_grad_test[_i][_qp]*6.0*_mu[_qp]*_h[_qp]*_phi[_j][_qp]*_v;
}
