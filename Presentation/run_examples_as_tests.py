import subprocess
import sys
import os

os.chdir('Python')
for tfilename in ['classification.py',
                  'effect_depth.py',
                  'effect_weak_learner_rand.py',
                  'overview.py',
                  'custom.py',
                  'spiral_rf.py',
                  'threshold_classifiers.py',
                  'regression.py']:
  subprocess.check_call(['python',
                         tfilename,
                         'quiet'])
subprocess.check_call(['python',
                       'hough_train.py',
                       sys.argv[1],
                       'quiet'])

subprocess.check_call(['python',
                       'hough_detect.py',
                       sys.argv[1],
                       'quiet'])
os.chdir('..')