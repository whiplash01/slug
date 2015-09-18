[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 4
  ny = 4
  xmin = -0.010
  xmax = 0.010
  ymax = -0.005
  ymax = 0.005
  elem_type = QUAD4
  block_id = 0
  block_name = film
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

  [./vel_x]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./vel_y]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./mass_x]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./mass_y]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./Pressure]
    type = CompressibleReynoldsPressure
    variable = p
    h = h
    v = 44.707
  [../]
[]

[AuxKernels]
  [./h]
    type = AlphaBetaH
    variable = h
    alpha = 8.0e-5 # ~ 0.05 deg
    beta = 0
    h = 25e-6 
    execute_on = initial
  [../]

  [./vel_x]
    type = ReynoldsMeanVelocity
    variable = vel_x
    component = 0
    vel_surface = '44.707 0 0'
    p = p
    h = h
  [../]

  [./vel_y]
    type = ReynoldsMeanVelocity
    variable = vel_y
    component = 1
    vel_surface = '44.707 0 0'
    p = p
    h = h
  [../]

  [./mass_x]
    type = ReynoldsMassFlow
    variable = mass_x
    component = 0
    vel_surface = '44.707 0 0'
    p = p
    h = h
  [../]

  [./mass_y]
    type = ReynoldsMassFlow
    variable = mass_y
    component = 1
    vel_surface = '44.707 0 0'
    p = p
    h = h
  [../]
[]

[BCs]
  [./perimeter]
    type = DirichletBC
    variable = p
    boundary = 'left top bottom'
    value = 100
  [../]
  [./trailingEdge]
    type = NeumannBC
    variable = p
    boundary = right
  [../]

[]

[Materials]
  [./air]
    type = ReynoldsIdealGas
    block = film
    temp = 300 #K
    p = p
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Steady
  l_max_its = 25
  nl_max_its = 100
  nl_rel_step_tol = 5e-4
  #nl_rel_tol = 1e-12
  l_tol = 1e-15
[]

[Outputs] 
  [./console] 
    type = Console
  [../]
  [./exodus]
    type = Exodus
    execute_on = 'initial nonlinear'
    elemental_as_nodal = true
  [../]
[]
