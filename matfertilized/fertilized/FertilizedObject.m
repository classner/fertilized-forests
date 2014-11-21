classdef FertilizedObject < handle
    % Base type for all library objects.
    %
    % Handles memory management.
    %
    % Author: Christoph Lassner.
    properties (SetAccess = protected, GetAccess = {?FertilizedObject, ?Soil})
        DataTypes;
        ClassifierPtr;
        LibName;
        DestructFunctionName = '';
        TypeSuffix = '';
    end
    
    methods (Access = protected)
        function this = FertilizedObject(dataTypes, libName, ptr, typeSuffix, destr_func_name)
            this.DataTypes = dataTypes;
            this.LibName = libName;
            this.ClassifierPtr = ptr;
            this.TypeSuffix = typeSuffix;
            this.DestructFunctionName = destr_func_name;
        end
    end
    
    methods (Access = public)
        function delete(this)
            % Matlab destuctor function, called when the object goes out of scope.

            % call destructer function in library, which clears the
            % classifier out of the memory...
            calllib(this.LibName, this.DestructFunctionName, this.ClassifierPtr);
        end
    end
end

