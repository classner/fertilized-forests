# -*- coding: utf-8 -*-
"""
Created on Sun Apr 06 15:29:28 2014

@author: lassnech
"""
import os
import sys
sys.path.insert(0, os.path.join('..', '..', 'pyfertilized'))
if len(sys.argv) > 1:
  print 'Quiet mode. Plot display disabled.'
  INTERACTIVE = False
else:
  INTERACTIVE = True

import fertilized as f
import matplotlib.pyplot as plt
import sklearn.metrics
import numpy as np
from plottools import make_spiral, point_prob_plot
np.random.seed(1)
#plt.rc('text', usetex=True)
#plt.rc('font', family='serif')

#%% Prepare...
n_classes = 3
n_trees = 400
ploty = [-6, 6, 100]
plotx = [-6, 6, 100]
X, Y = make_spiral(n_arms=n_classes, noise=.4)

#%%
soil = f.Soil('float', 'float', 'uint', f.Result_Types.probabilities)
depth = 13
rs=1
for suggestions in [3, 250]:
  for dec_name in ['aligned', 'linear', 'quadratic']:
    if dec_name == 'aligned':
      feat_sel_prov = soil.StandardFeatureSelectionProvider(2, 1, 2, 2, random_seed=rs)
    else:
      feat_sel_prov = soil.StandardFeatureSelectionProvider(1, 2, 2, 2)
    if dec_name == 'aligned':
      feat_calc = soil.AlignedSurfaceCalculator()
    elif dec_name == 'linear':
      feat_calc = soil.LinearSurfaceCalculator(2, random_seed=rs)
    elif dec_name == 'quadratic':
      feat_calc = soil.QuadraticSurfaceCalculator(2,
                                                  np.array([X[:, 0].min(),
                                                            X[:, 0].max(),
                                                            X[:, 1].min(),
                                                            X[:, 1].max()],
                                                          dtype='float32'),
                                                  random_seed=rs)
    cls = []
    lm = []
    for i in xrange(n_trees):
      cls.append(soil.ThresholdDecider(   feat_sel_prov,
                                          feat_calc,
                                          soil.RandomizedClassificationThresholdOptimizer(
                                            suggestions,
                                            n_classes,
                                            soil.EntropyGain(soil.ShannonEntropy()),
                                            random_seed=rs)))
      lm.append(soil.ClassificationLeafManager(n_classes))
    forest = soil.Forest(depth,
                         1,
                         2,
                         n_trees,
                         cls,
                         lm,
                         soil.ClassicTraining(soil.NoBagging()))
    forest.fit(X, Y, 1)
    plt.figure()
    assert sklearn.metrics.accuracy_score(Y, np.argmax(forest.predict(X), axis=1)) > 0.95
    point_prob_plot(forest, X, Y, plotx, ploty)
    plt.title('%s decider, $|\Theta_j|=%d$' %(dec_name, suggestions * 2))
    plt.savefig('effect_wl%s_rand_%d.png' % (dec_name, suggestions * 2))
    if INTERACTIVE:
        plt.show()