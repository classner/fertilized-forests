classdef Result_Types
  % An enumeration of available library result types.
  %
  % Author: Christoph Lassner.
  properties
     name
  end
  methods
      function self = Result_Types(name)
         self.name = name; 
      end
  end
  enumeration
     probabilities ('probabilities')
     hough_map ('hough_map')
     regression ('regression')
  end
end
