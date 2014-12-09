# -*- coding: utf-8 -*-
# Author: Christoph Lassner
# Platform independent serialization.
import os
import sys
sys.path.insert(0, os.path.join('..', '..', 'pyfertilized'))

import numpy as np
from fertilized import *

soil = Soil('d', 'd', 'd', Result_Types.regression)
# Deserialize tree serialized on Windows.
tree_win = soil.TreeFromFile("tree_windows.ft")
# Deserialize tree serialized on Linux.
tree_lin = soil.TreeFromFile("tree_linux.ft")

prediction = tree_win.predict(np.array([[0.]]))
assert prediction[0,0] == 500.
assert prediction[0,1] == 500000.

prediction = tree_lin.predict(np.array([[0.]]))
assert prediction[0,0] == 500.
assert prediction[0,1] == 500000.
