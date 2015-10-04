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
  params.addRequiredParam<RealVectorValue>("point","point on the axis about which the moment is to be computed");
  params.addRequiredParam<RealVectorValue>("axis","axis about which to calculate the moment");
  return params;
}

ReynoldsShearMoment::ReynoldsShearMoment(const InputParameters & parameters) :
  ElementIntegralPostprocessor(parameters),
  _sigma_zx(coupledValue("sigma_zx")),
  _sigma_zy(coupledValue("sigma_zy")),
  _point(getParam<RealVectorValue>("point")),
  _axisIn(getParam<RealVectorValue>("axis")),
  _axis(_axisIn.unit())
{
}

Real
ReynoldsShearMoment::computeQpIntegral()
{
  RealVectorValue relPos = _q_point[_qp] - _point;
  RealVectorValue moment = relPos.cross(RealVectorValue(_sigma_zx[_qp],_sigma_zy[_qp],0));
  Real projectedMoment = moment.contract(_axis);
  return projectedMoment;
}
