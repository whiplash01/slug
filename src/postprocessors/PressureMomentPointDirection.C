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

#include "PressureMomentPointDirection.h"

template<>
InputParameters validParams<PressureMomentPointDirection>()
{
  InputParameters params = validParams<ElementIntegralPostprocessor>();
  params.addRequiredCoupledVar("pressure","pressure variable");
  params.addRequiredParam<RealVectorValue>("point","vector identifing thepoint on the axis about which the moment is measured");
  params.addRequiredParam<RealVectorValue>("axis","vector identifing the direction of the axis about which the moment is measured");
  params.addParam<RealVectorValue>("normal",RealVectorValue(0,0,1),"Normal direction of the surface to which the pressure is applied");
  return params;
}

PressureMomentPointDirection::PressureMomentPointDirection(const InputParameters & parameters) :
    ElementIntegralPostprocessor(parameters),
    _p(coupledValue("pressure")),
    _point(getParam<RealVectorValue>("point")),
    _axis_param(getParam<RealVectorValue>("axis")),
    _axis(),
    _normal_param(getParam<RealVectorValue>("normal")),
    _normal()
{
  _axis = _axis_param.unit();
  _normal = _normal_param.unit();
}

Real
PressureMomentPointDirection::computeQpIntegral()
{
  RealVectorValue rel_pos = (_q_point[_qp] - _point);
  RealVectorValue raw_moment = rel_pos.cross(_normal*_p[_qp]);
  Real oriented_moment = raw_moment.contract(_axis);
  return oriented_moment;
}

