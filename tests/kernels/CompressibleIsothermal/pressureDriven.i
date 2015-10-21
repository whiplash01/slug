[Mesh]
  type = FileMesh
  file = simpleAirBearingMesh.unv
  uniform_refine = 2
[]

[Variables]
  [./p]
    order =  FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = ConstantIC
      value = 100.0
    [../]
  [../]
[]

[AuxVariables]
  [./h]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./PressureFlow]
   type = CompressibleIsothermalPressureFlow
   variable = p
   h = h
  [../]
[]

[AuxKernels]
  [./h]
    type = AlphaBetaH
    variable = h
    alpha = 0
    beta = 0
    h = 1e-3 
    execute_on = initial
  [../]
[]

[Postprocessors]
[]

[BCs]
  [./outer]
    type = DirichletBC
    variable = p
    boundary = 'outer'
    value = 100
  [../]
  [./trailingEdge]
    type = DirichletBC
    variable = p
    boundary = 'inner'
    value = 10e3
  [../]

[]

[Materials]
  [./air]
    type = ReynoldsIdealGas
    block = 0
    temp = 300 #K
    p = p
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Steady
  l_max_its = 25
  nl_max_its = 100
  nl_rel_step_tol = 1e-3
  #nl_rel_tol = 1e-12
  l_tol = 1e-15
[]

[Outputs]
  execute_on = 'initial failed timestep_end'
  [./console] 
    type = Console
  [../]
  [./exodus]
    type = Exodus
    #execute_on = 'initial nonlinear'
    elemental_as_nodal = true
  [../]
[]
