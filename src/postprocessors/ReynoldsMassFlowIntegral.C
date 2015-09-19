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

#include "ReynoldsMassFlowIntegral.h"

template<>
InputParameters validParams<ReynoldsMassFlowIntegral>()
{
  InputParameters params = validParams<SideIntegralPostprocessor>();
  params.addRequiredCoupledVar("cross_film_m_dot_x","x component of cross film mass flow");
  params.addRequiredCoupledVar("cross_film_m_dot_y","y component of cross film mass flow");
  return params;
}

ReynoldsMassFlowIntegral::ReynoldsMassFlowIntegral(const InputParameters & parameters) :
    SideIntegralPostprocessor(parameters),
    _m_dot_x(coupledValue("cross_film_m_dot_x")),
    _m_dot_y(coupledValue("cross_film_m_dot_y"))
{}

Real
ReynoldsMassFlowIntegral::computeQpIntegral()
{
  RealVectorValue vec(_m_dot_x[_qp],_m_dot_y[_qp]);
  return vec*_normals[_qp];
}

