# Authors: Philipp Harzig, Christoph Lassner.
from SingleFileParser import SingleFileParser
from os import listdir
from os.path import isfile, join, isdir, splitext, basename

parsed_classes = []
parsed_functions = []
using_relations_str = []
lib_headers = []
mypath = "../fertilized/"

onlysubdirs = ['.'] + [ f for f in listdir(mypath) if isdir(join(mypath,f)) ]

for subdir in onlysubdirs:
    if subdir == 'ndarray' or subdir == 'offloading' or subdir == 'serialization':
        continue
    if subdir == '.':
        package = 'rootdir'
    else:
        package = subdir
    subdir = subdir + "/"
    #headers = ['forest.h'] #alternatingthresholdoptimizer.h']
    headers = [ f for f in listdir(join(mypath,subdir)) if \
                  isfile(join(mypath,subdir,f)) and splitext(f)[1] == ".h" and\
                  (basename(f) != 'ndarray.h' and \
                   basename(f) != 'ndarray_fwd.h' and \
                   basename(f) != 'fertilized.h' and \
                   basename(f) != 'fertilized_fwd.h' and \
                   basename(f) != 'soil.h' and \
                   basename(f) != 'default_values.h' and \
                   basename(f) != 'types.h' and \
                   basename(f) != 'global.h')]
    for header in headers:
        if subdir != './':
          lib_headers.append('.' + '/' + subdir + header)
        else:
          lib_headers.append(subdir + header)
        filename = join(mypath, subdir, header)
        sfp = SingleFileParser(filename, package)
        cls, funcs, using_rels = sfp.ParseToIntermediateObject()
        parsed_classes.extend(cls)
        parsed_functions.extend(funcs)
        using_relations_str.extend(using_rels)
