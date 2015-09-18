#ifndef REYNOLDSMASSFLOW_H
#define REYNOLDSMASSFLOW_H

#include "ReynoldsMeanVelocity.h"

class ReynoldsMassFlow;

template<>
InputParameters validParams<ReynoldsMassFlow>();

class ReynoldsMassFlow : public ReynoldsMeanVelocity
{
public:

  ReynoldsMassFlow(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  const MaterialProperty<Real> & _rho;

};

#endif //REYNOLDSMASSFLOW_H
