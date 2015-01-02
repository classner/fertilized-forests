classdef FeatCalcParamSet < FertilizedObject
    % Can be specialized to any necessary parameters used by a feature
    % calculator.
    % 
    % This was planned as an implementable interface, however it must be a
    % single, plain POD object, since it might be transferred forth and back
    % between host and MIC device.
    % 
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
    
    methods (Access = {?Soil, ?FeatCalcParamSet})
        function this = FeatCalcParamSet(dataTypes, libName, ptr, functionFormat)
            position_list = [];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_FeatCalcParamSet' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
