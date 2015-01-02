classdef IEntropyFunction < FertilizedObject
    % Interface for an entropy calculation functor.
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
    % - uint
    % 
    % Soil type always:
    % 
    % - float
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
    
    methods (Access = {?Soil, ?IEntropyFunction})
        function this = IEntropyFunction(dataTypes, libName, ptr, functionFormat)
            tmp = '_f';
            delFuncName = ['delete_IEntropyFunction' tmp];
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
