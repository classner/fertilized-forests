classdef RegressionThresholdOptimizer < FertilizedObject
    % Optimizes the threshold for splitting a dataset, to ensure optimal
    % regression results on the splits.
    % 
    % This threshold optimizer draws n_thresholds random values between
    % the minimum and maximum observed feature value and returns the best
    % one.
    % Multiple annotations (and therefore multiple output regression) are allowed.
    % The splits are evaluated using a provided regression calculator.
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
    % - float; float
    % - double; double
    % 
    % 
    % -----
    % 
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
    
    methods (Access = {?Soil, ?RegressionThresholdOptimizer})
        function this = RegressionThresholdOptimizer(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_RegressionThresholdOptimizer' tmp];
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
            getter = sprintf('%s%s%s', 'eq', 'RegressionThresholdOptimizer', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
