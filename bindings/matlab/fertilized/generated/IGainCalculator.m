classdef IGainCalculator < FertilizedObject
    % Interface for a gain calculator class.
    % 
    % A gain calculator must have an overloaded () operator with the
    % according parameters and an approx function that returns a fast
    % approximation of the gain (can return the original gain if no
    % approximation is available). The approximation is used to find the
    % best split position and only for that the actual gain is computed.
    % 
    % Parameters
    % ==========
    % 
    % counting_dtype : The datatype for counting class members. This might
    %   be a float if sample weights are used.
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
    
    methods (Access = {?Soil, ?IGainCalculator})
        function this = IGainCalculator(dataTypes, libName, ptr, functionFormat)
            tmp = '_f';
            delFuncName = ['delete_IGainCalculator' tmp];
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
