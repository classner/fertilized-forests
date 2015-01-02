classdef VarianceClassificationThresholdOptimizer < FertilizedObject
    % Optimizes a threshold by selecting the best some random values with respect to the variance of example offsets.
    % 
    % The annotations are assumed to be a class label followed by its offset
    % values. Since all these values must be of the same datatype, the only supported type
    % is (signed) int in this case (to allow for negative offsets). The class labels
    % must still be in [0; n_classes - 1].
    % 
    % This threshold optimizer draws n_thresholds random values between
    % the minimum and maximum observed feature value and returns the best
    % one.
    % 
    % 
    % -----
    % 
    % Available in:
    % 
    % - C++
    % - Python
    % - Matlab
    % 
    % Instantiations:
    % 
    % - int; int; uint
    % - int; float; uint
    % - float; int; uint
    % - uint8_t; int; uint
    % - uint8_t; uint8_t; uint
    % - uint8_t; float; uint
    % - uint8_t; int16_t; uint
    % - float; float; uint
    % - double; double; uint
    % - uint8_t; int16_t; int16_t
    % 
    % 
    % -----
    % 
    %
    % This object can only be constructed by using a `Soil` object!
    %
    % Author: Christoph Lassner.
    %
    % This is an automatically generated file!
    %
    properties (Access = private)
        FunctionFormat = '';
    end 
    
    methods (Access = {?Soil, ?VarianceClassificationThresholdOptimizer})
        function this = VarianceClassificationThresholdOptimizer(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_VarianceClassificationThresholdOptimizer' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
        function [res] = eq(this, rhs) 
            % -----
            % 
            % Available in:
            % 
            % - C++
            % - Python
            % - Matlab
            % 
            % 
            % -----
            % 
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'eq', 'VarianceClassificationThresholdOptimizer', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
