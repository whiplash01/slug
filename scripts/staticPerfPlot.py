import pandas as pd
import matplotlib.pyplot as plt
import os
import re


#find all the postprocessor outputfiles and
# and read each in to a dataframe
p = re.compile(r'postprocessor_([0-9])*\.csv')
#p = re.compile(r'output_[0-9]*\.log')
dfs = []
for directory,directories,files in os.walk('.'):
  for f in files:
    m = p.match(f)
    if m:
      dfd = pd.read_csv(directory+'/'+f)
      num = m.expand(r'\1')
      dfi = pd.read_csv(directory+'/indep_{}.csv'.format(num))
      for col in dfi.columns:
        dfd[col] = dfi[col][0]

      dfs.append(dfd)

df = pd.concat(dfs)
df = df[df.index==0]
