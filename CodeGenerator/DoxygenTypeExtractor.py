# Authors: Philipp Harzig, Christoph Lassner.
import re
from TypeTranslations import _dtype_str_translation
from helper_classes import InstantiationTypes

class DoxygenTypeExtractor(object):
    """Extracts types and available interfaces from a doxygen class comment."""
    
    def __init__(self, doxygenComment):
        self.DoxygenComment = doxygenComment

    def ExtractExportedName(self):
        if self.DoxygenComment == None:
            return [], None

        lines = self.DoxygenComment.splitlines()

        didExportedNamePartStartAlready = False
        lineMatchPattern = "^.*?- (.*?)$"
        availableIn = []
        exportedName = None
        isExtractingAvailableIn = False
        for line in lines:
            # search for the machine readable beginning of the comment
            if re.compile("^.*?-----$").match(line):
                if didExportedNamePartStartAlready == False:
                    didExportedNamePartStartAlready = True
                else:
                    break

            if re.compile("^.*?Available in:$").match(line):
                isExtractingAvailableIn = True
            lineMatch = re.search(lineMatchPattern, line)
            if lineMatch and isExtractingAvailableIn:
                availableIn.append(lineMatch.group(1).strip())
            
            match = re.compile("^.*?Exported name:\s*([a-zA-Z0-9]*).*$").match(line)
            if match:
                exportedName = match.group(1)
        return availableIn, exportedName

    def Extract(self):
        if self.DoxygenComment == None:
            return [], None, None, None

        lines = self.DoxygenComment.splitlines()

        didTypePartStartAlready = False
        isExtractingAvailableIn = False
        isExtractingInstantiations = False
        isExtractingSoilUsage = False

        lineMatchPattern = "^.*?- (.*?)$"
        availableIn = []
        instantiations = []
        instantiationsTmp = []
        serialization_generation = None
        soilUsage = None

        for line in lines:
            # search for the machine readable beginning of the comment
            if re.compile("^.*?-----$").match(line):
                if didTypePartStartAlready == False:
                    didTypePartStartAlready = True
                else:
                    break
            
            if re.compile("^.*?Available in:$").match(line):
                isExtractingAvailableIn = True
                isExtractingInstantiations = False
                isExtractingSoilUsage = False
                
            if re.compile("^.*?Instantiations:$").match(line):
                isExtractingAvailableIn = False
                isExtractingInstantiations = True
                isExtractingSoilUsage = False

            if re.compile("^.*?Soil type always:$").match(line):
                isExtractingSoilUsage = True
                isExtractingAvailableIn = False
                isExtractingInstantiations = False
                
            lineMatch = re.search(lineMatchPattern, line)
            if lineMatch and isExtractingAvailableIn:
                availableIn.append(lineMatch.group(1).strip())
            elif lineMatch and isExtractingInstantiations:
                instantiationsTmp.append(lineMatch.group(1))
            elif lineMatch and isExtractingSoilUsage:
                soilUsage = lineMatch.group(1)
            # Look for the serialization generation.
            sergen = re.search("\* ?Serialization generation: ?(\d+)\s*", line.strip())
            if not sergen is None:
              if not serialization_generation is None:
                raise Exception("Found multiple specifications of the " +\
                  "serialization generation!")
              else:
                serialization_generation = int(sergen.group(1))
        if serialization_generation is None:
          # default.
          serialization_generation = 0
        
        # Split instantiation types
        for i in instantiationsTmp:
            types = re.split(";[\s]+", i)
            result = [x.strip(' ') for x in types]
            instantiations.append(InstantiationTypes(result))
        
        if soilUsage != None:
          assert soilUsage in instantiationsTmp, 'The soil usage type must be '+\
            'an instantiation type!'
          types = re.split(";[\s]+", soilUsage)
          result = [x.strip(' ') for x in types]
          soilUsage = InstantiationTypes(result)

        if instantiations.count == 0:
            return availableIn, None, soilUsage, serialization_generation
        else:
            return availableIn, instantiations, soilUsage, serialization_generation
