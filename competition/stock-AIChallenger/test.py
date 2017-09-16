import pandas as pd
import numpy as np
import matplotlib as plt

initdir = '/home/sigma/singleprj/stock/data/'
train = pd.read_csv(initdir + "train.csv")
#test = pd.read_csv(initdir + "test.csv")

train.sort_values(by='era').plot(x='era', y='label', kind='line', figsize=(50, 25))
