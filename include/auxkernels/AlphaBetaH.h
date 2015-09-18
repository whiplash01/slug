#ifndef ALPHABETAH_H
#define ALPHABETAH_H

#include "AuxKernel.h"

class AlphaBetaH;

template<>
InputParameters validParams<AlphaBetaH>();

class AlphaBetaH : public AuxKernel
{
public:

  AlphaBetaH(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  Real _alpha;
  Real _beta;
  Real _h;
};

#endif //ALPHABETAH_H
