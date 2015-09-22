classdef ObjectVector < FertilizedObject
  % Helper object to create std::vector objects of library objects.
  %
  % It should never be necessary to use this object manually! It is
  % automatically used be methods to convert cell arrays of library
  % objects to std::vectors.
  %
  % Author: Christoph Lassner.
  methods
    function self = ObjectVector()
      self = self@FertilizedObject('', 'matfertilized', calllib('matfertilized', 'createObjectVector'), '', 'deleteObjectVector');
    end
    function append(self, object)
      calllib(self.LibName, 'appendToObjectVector', self.ClassifierPtr, object.ClassifierPtr);
    end
  end
end