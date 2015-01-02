classdef ThresholdDecider < FertilizedObject
    % A classifier manager for weak classifiers with a filter function,
    % a feature calculation function and a thresholding.
    % 
    % The classifier design is heavily inspired by "Decision Forests for
    % Classification, Regression, Density Estimation, Manifold Learning and
    % Semi-Supervised Learning" (Criminisi, Shotton and Konukoglu, 2011).
    % With their definition, node classifier parameters :math:`\theta` can
    % be split into three parts:
    % 
    % - :math:`\phi`: a filter function that selects relevant features,
    % - :math:`\psi`: parameters of a function that combines the feature values
    % to a single scalar,
    % - :math:`\tau`: thresholding parameters for the calculated scalar.
    % 
    % With this model, a decision can be made at each node based on whether the
    % calculated scalar lies withing the thresholding bounds.
    % 
    % 
    % -----
    % 
    % Available in:
    % - C++
    % - Python
    % - Matlab
    % 
    % Instantiations:
    % 
    % - int; int; uint
    % - uint8_t; uint8_t; uint
    % - uint8_t; int16_t; uint
    % - float; float; uint
    % - double; double; uint
    % - uint8_t; int16_t; int16_t
    % - float; float; float
    % - double; double; double
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
    
    methods (Access = {?Soil, ?ThresholdDecider})
        function this = ThresholdDecider(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_ThresholdDecider' tmp];
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
            getter = sprintf('%s%s%s', 'eq', 'ThresholdDecider', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
