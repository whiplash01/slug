[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmax = 2
[]

[Variables]
  [./p]
  [../]
  [./h]
  [../h]
[]

[Kernels]
  [./diff_p]
    type = Diffusion
    variable = p
  [../]
  [./diff_h]
    type = Diffusion
    variable = h
  [../]
[]

[AuxVariables]
  [./sigma_x]
     order = CONSTANT
     family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./sigma_x]
    type = ReynoldsShearStress
    variable = sigma_x
    component = 0
    p = p
    h = h
    vel_surface = '25 0 0'
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = p
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = p
    boundary = right
    value = 20
  [../]
  [./left_h]
    type = DirichletBC
    variable = h
    boundary = left
    value = 1e-3
  [../]
  [./right_h]
    type = DirichletBC
    variable = h
    boundary = right
    value = 8e-4
  [../]
[]

[Materials]
  [./air]
    type = ReynoldsIdealGas
    block = 0
    temp = 300
    p = p
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  #execute_on = 'timestep_end'
  exodus = true
[]
