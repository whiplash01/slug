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

  [./sigma_zx_yo]
  [../]

  [./sigma_zy_yo]
  [../]

[]

[Kernels]

  [./diff_sigma_zx_yo]
    type = Diffusion
    variable = sigma_zx_yo
  [../]

  [./diff_sigma_zy_yo]
    type = Diffusion
    variable = sigma_zy_yo
  [../]

[]

[Postprocessors]

  [./MCenter]
    type = ReynoldsShearMoment
    sigma_zx = sigma_zx_yo
    sigma_zy = sigma_zy_yo
    point = '1.5 1.5 0' 
    axis = '0 0 1'
  [../]

  [./MOutOfPlaneX]
    type = ReynoldsShearMoment
    sigma_zx = sigma_zx_yo
    sigma_zy = sigma_zy_yo
    point = '1.5 1.5 10' 
    axis = '1 0 0'
  [../]

  [./MOutOfPlaneY]
    type = ReynoldsShearMoment
    sigma_zx = sigma_zx_yo
    sigma_zy = sigma_zy_yo
    point = '1.5 1.5 10' 
    axis = '0 1 0'
  [../]

  [./MOutOfPlaneZ]
    type = ReynoldsShearMoment
    sigma_zx = sigma_zx_yo
    sigma_zy = sigma_zy_yo
    point = '1.5 1.5 10' 
    axis = '0 0 1'
  [../]

  [./MLowerRight]
    type = ReynoldsShearMoment
    sigma_zx = sigma_zx_yo
    sigma_zy = sigma_zy_yo
    point = '2 1 0' 
    axis = '0 0 1'
  [../]

[]

[BCs]
  [./left]
    type = DirichletBC
    variable = sigma_zx_yo
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = sigma_zx_yo
    boundary = right
    value = 1
  [../]

  [./top]
    type = DirichletBC
    variable = sigma_zy_yo
    boundary = bottom
    value = 0
  [../]
  [./bottom]
    type = DirichletBC
    variable = sigma_zy_yo
    boundary = top
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
