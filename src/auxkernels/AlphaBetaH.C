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
#include "AlphaBetaH.h"

template<>
InputParameters validParams<AlphaBetaH>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("alpha", "wedge angle");
  params.addParam<Real>("beta","transverse wedge angle");
  params.addParam<Real>("h", "gap height at origin");
  return params;
}

AlphaBetaH::AlphaBetaH(const InputParameters & parameters) :
    AuxKernel(parameters),
    _alpha(getParam<Real>("alpha")),
    _beta(getParam<Real>("beta")),
    _h(getParam<Real>("h"))
{}

Real
AlphaBetaH::computeValue()
{
  Real x = (*_current_node)(0);
  Real y = (*_current_node)(1);
  return -x*std::sin(_alpha) + y*std::sin(_beta) + _h;
}
