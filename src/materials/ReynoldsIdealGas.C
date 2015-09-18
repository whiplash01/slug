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
