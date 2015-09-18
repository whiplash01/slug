#ifndef SLUGAPP_H
#define SLUGAPP_H

#include "MooseApp.h"

class SlugApp;

template<>
InputParameters validParams<SlugApp>();

class SlugApp : public MooseApp
{
public:
  SlugApp(InputParameters parameters);
  virtual ~SlugApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* SLUGAPP_H */
