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
# include "CompressibleIsothermalPressureFlow.h"

template<>
InputParameters validParams<CompressibleIsothermalPressureFlow>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("h","lubricating film thickness");
  return params;
}

CompressibleIsothermalPressureFlow::CompressibleIsothermalPressureFlow(const InputParameters &parameters) :

  Kernel(parameters),
  _mu(getMaterialPropertyByName<Real>("mu")),
  _h(coupledValue("h"))

{
}

Real CompressibleIsothermalPressureFlow::computeQpResidual()
{
  return _grad_test[_i][_qp]*pow(_h[_qp],3)*_u[_qp]*_grad_u[_qp];
}

Real CompressibleIsothermalPressureFlow::computeQpJacobian()
{
  return _grad_test[_i][_qp]*pow(_h[_qp],3)*_phi[_j][_qp]*_grad_phi[_j][_qp];
}
