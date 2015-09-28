[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmin = 1
  xmax = 2
  ymin = 1
  ymax = 2
[]

[Variables]
  [./u]
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[Postprocessors]
  [./Mx]
    type = PressureMomentPointDirection
    pressure = u
    point = '1.5 1.5 0'
    axis = '1 0 0'
    normal = '0 0 1'
  [../]
  [./My]
    type = PressureMomentPointDirection
    pressure = u
    point = '1.5 1.5 0'
    axis = '0 1 0'
    normal = '0 0 1'
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
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
