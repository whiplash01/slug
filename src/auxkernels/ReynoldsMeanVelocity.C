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
