classdef RandomizedClassificationThresholdOptimizer < FertilizedObject
    % Optimizes a threshold by selecting the best of few random values.
    % 
    % Supports only classification annotations (unsigned int) with annotation
    % values in [0, ..., n_classes[.
    % The threshold optimizer draws n_thresholds random values between
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
    
    methods (Access = {?Soil, ?RandomizedClassificationThresholdOptimizer})
        function this = RandomizedClassificationThresholdOptimizer(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_RandomizedClassificationThresholdOptimizer' tmp];
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
            getter = sprintf('%s%s%s', 'eq', 'RandomizedClassificationThresholdOptimizer', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
