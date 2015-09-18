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
#include "RadialBearingH.h"

template<>
InputParameters validParams<RadialBearingH>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("c", "diametral clearance");
  params.addParam<Real>("e","eccentricity");
  params.addParam<Real>("circ", "circumference");
  return params;
}

RadialBearingH::RadialBearingH(const InputParameters & parameters) :
    AuxKernel(parameters),
    _c(getParam<Real>("c")),
    _e(getParam<Real>("e")),
    _circ(getParam<Real>("circ"))
{}

Real
RadialBearingH::computeValue()
{
  return _c/2.-_e*std::cos((*_current_node)(0)/_circ*2.*pi);
}
