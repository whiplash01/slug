import subprocess
import numpy as np
import os

# input file
inputFile = 'ex01.i'
numProc = 6

# control for h, the film thickness
min_h = 10e-6 #m
max_h = 1e-3 #m
n_h = 10

# controls for ps, the air bearing supply pressure
ps_min = 10e3 #Pa
ps_max = 10e3 #Pa
n_ps = 1

# controls for p_amb 
pamb_min = 100.0
pamb_max = 100.0
n_pamb = 1

# controls for T, the isothermal temperature in the film
T_min = 300.0
T_max = 300.0
n_T = 1

# controls for sliding velocity (x component)
min_v = 0
max_v = 0
n_v = 1

#controls for alpha
min_alpha = 0
max_alpha = 0
n_alpha = 1

# in nested for loops, create the slug commands to execute

h_array = np.linspace(min_h,max_h,n_h)
ps_array = np.linspace(ps_min,ps_max,n_ps)
pamb_array = np.linspace(pamb_min,pamb_max,n_pamb)
T_array = np.linspace(T_min,T_max,n_T)
v_array = np.linspace(min_v,max_v,n_v)
alpha_array = np.linspace(min_alpha,max_alpha,n_alpha)

commands = []

for h in h_array:
  for ps in ps_array:
    for pamb in pamb_array:
      for T in T_array:
        for v in v_array:
          for alpha in alpha_array:
            commands.append(
                'mpiexec -n {} slug-opt -i {} '.format(numProc,inputFile)
                +'AuxKernels/h/h={} '.format(h)
                +'BCs/inlet/value={} '.format(ps)
                +'BCs/perimeter/value={} '.format(pamb)
                +'GlobalParams/vel_surface=\'{} 0 0\' '.format(v)
                +'Kernels/Pressure/v={} '.format(v)
                +'AuxKernels/h/alpha={} '.format(alpha)
                +'--show-input '
                +'--no-color '
                )

# divy out the jobs (each job is a mpi job, and multiple 
# mpi jobs can go at once.)

num_commands = len(commands)
for i in enumerate(commands):
  print(
    'Beginning solve {} of {}\n'.format((i[0]+1),num_commands)
    +'  command:{}\n'.format(i[1])
  )
  os.system(i[1]
    +'Outputs/exodus/file_base=exodus_{} '.format(i[0])
    +'>&1 > output_{}.log'.format(i[0])
    )
  

