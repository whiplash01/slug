#include "SlugApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

template<>
InputParameters validParams<SlugApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

SlugApp::SlugApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SlugApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SlugApp::associateSyntax(_syntax, _action_factory);
}

SlugApp::~SlugApp()
{
}

// External entry point for dynamic application loading
extern "C" void SlugApp__registerApps() { SlugApp::registerApps(); }
void
SlugApp::registerApps()
{
  registerApp(SlugApp);
}

// External entry point for dynamic object registration
extern "C" void SlugApp__registerObjects(Factory & factory) { SlugApp::registerObjects(factory); }
void
SlugApp::registerObjects(Factory & factory)
{
}

// External entry point for dynamic syntax association
extern "C" void SlugApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { SlugApp::associateSyntax(syntax, action_factory); }
void
SlugApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
