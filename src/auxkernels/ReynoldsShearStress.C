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

#include "ReynoldsShearStress.h"

template<>
InputParameters validParams<ReynoldsShearStress>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<unsigned>("component","component to compute");
  params.addRequiredCoupledVar("p","pressure variable");
  params.addRequiredCoupledVar("h","film thickness variable");
  params.addRequiredParam<RealVectorValue>("vel_surface","surface velocity");
  return params;
}

ReynoldsShearStress::ReynoldsShearStress(const InputParameters & parameters) :
  AuxKernel(parameters),
  _component(getParam<unsigned>("component")),
  _grad_p(coupledGradient("p")),
  _h(coupledValue("h")),
  _mu(getMaterialPropertyByName<Real>("mu")),
  _vel_surface(getParam<RealVectorValue>("vel_surface"))

{}

Real
ReynoldsShearStress::computeValue()
{
  return _mu[_qp] * ( (_grad_p[_qp](_component)*_h[_qp])/(2.0*_mu[_qp]) + _vel_surface(_component)/_h[_qp] );
}
