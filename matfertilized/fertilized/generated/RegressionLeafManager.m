classdef RegressionLeafManager < FertilizedObject
    % Manages the leaf nodes of regression trees.
    % 
    % This leaf manager creates leaf nodes and stores a probabilistic regression model at each leaf.
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
    % - float
    % - double
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
    
    methods (Access = {?Soil, ?RegressionLeafManager})
        function this = RegressionLeafManager(dataTypes, libName, ptr, functionFormat)
            position_list = [1];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_RegressionLeafManager' tmp];
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
            getter = sprintf('%s%s%s', 'eq', 'RegressionLeafManager', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
