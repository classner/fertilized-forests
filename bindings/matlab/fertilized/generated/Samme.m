classdef Samme < FertilizedObject
    % SAMME boosting algorithm implementation
    % 
    % Implements the SAMME boosting algorithm proposed by J. Zhu, H. Zou,
    % S. Rosset and T. Hastie ("Multi-class AdaBoost", 2009).
    % 
    % One can set the learning rate which specifies the contribution of each
    % classifier.
    % 
    % Output when using BoostingLeafManager is
    % estimator_probability*estimator_weight.
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
    % - int; int; uint; std::vector<float>; std::vector<float>
    % - float; float; uint; std::vector<float>; std::vector<float>
    % - double; double; uint; std::vector<float>; std::vector<float>
    % - uint8_t; uint8_t; uint; std::vector<float>; std::vector<float>
    % - uint8_t; int16_t; uint; std::vector<float>; std::vector<float>
    % - uint8_t; int16_t; int16_t; std::vector<float>; std::vector<float>
    % 
    % Serialization generation: 101
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
    
    methods (Access = {?Soil, ?Samme})
        function this = Samme(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_Samme' tmp];
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
            getter = sprintf('%s%s%s', 'eq', 'Samme', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
