classdef StringVector < FertilizedObject
  % Helper object to create std::vector object of std::strings.
  %
  % It should never be necessary to use this object manually! It is
  % automatically used be methods to convert cell arrays of library
  % objects to std::vectors.
  methods
    function self = StringVector()
      self = self@FertilizedObject('', 'matfertilized', calllib('matfertilized', 'createStringVector'), '', 'deleteStringVector');
    end
    function append(self, string)
      calllib(self.LibName, 'appendToStringVector', self.ClassifierPtr, libpointer('cstring', string));
    end
  end
end
