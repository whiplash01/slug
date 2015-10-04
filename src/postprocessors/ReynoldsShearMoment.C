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

#include "ReynoldsShearMoment.h"

template<>
InputParameters validParams<ReynoldsShearMoment>()
{
  InputParameters params = validParams<ElementIntegralPostprocessor>();
  params.addRequiredCoupledVar("sigma_zx","shear stress component");
  params.addRequiredCoupledVar("sigma_zy","shear stress component");
  params.addRequiredParam<RealVectorValue>("point","a point on the moment axis (will be projected on z = 0)");
  return params;
}

ReynoldsShearMoment::ReynoldsShearMoment(const InputParameters & parameters) :
  ElementIntegralPostprocessor(parameters),
  _sigma_zx(coupledValue("_sigma_zx")),
  _sigma_zy(coupledValue("_sigma_zy")),
  _pointIn(getParam<RealVectorValue>("point"))

{
  _point = RealVectorValue(_pointIn(0),_pointIn(1),0);
}

Real
ReynoldsShearMoment::computeQpIntegral()
{
  RealVectorValue relPos = _q_point[_qp] - _point;
  RealVectorValue moment = relPos.cross(RealVectorValue(_sigma_zx[_qp],_sigma_zy[_qp],0));
  return moment(2);
}
