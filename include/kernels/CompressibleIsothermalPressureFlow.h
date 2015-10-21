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
#ifndef COMPRESSIBLEISOTHERMALPRESSUREFLOW_H
#define COMPRESSIBLEISOTHERMALPRESSUREFLOW_H

#include "Kernel.h"

class CompressibleIsothermalPressureFlow;

template<>
InputParameters validParams<CompressibleIsothermalPressureFlow>();

class CompressibleIsothermalPressureFlow : public Kernel
{
public:

  CompressibleIsothermalPressureFlow(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

protected:

  const MaterialProperty<Real>& _mu;
  VariableValue & _h;

};

#endif // COMPRESSIBLEISOTHERMALPRESSUREFLOW_H
