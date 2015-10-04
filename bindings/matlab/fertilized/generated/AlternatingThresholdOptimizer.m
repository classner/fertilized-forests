classdef AlternatingThresholdOptimizer < FertilizedObject
    % Uses two other threshold optimizers and randomly selects one of them at each split.
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
    % - float; float; float
    % - double; double; double
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
    
    methods (Access = {?Soil, ?AlternatingThresholdOptimizer})
        function this = AlternatingThresholdOptimizer(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_AlternatingThresholdOptimizer' tmp];
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
            getter = sprintf('%s%s%s', 'eq', 'AlternatingThresholdOptimizer', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
