classdef EntropyGain < FertilizedObject
    % Calculates the gain as difference of current entropy and the
    % weighted sum of subgroup entropies.
    % 
    % Works correctly up to a total sum of elements of
    % min(numeric_limits<float>::max(), numeric_limits<input_dtype>::max())
    % and the limitations of the selected entropy function.
    % Speed optimized function that does no checks in release mode!
    % 
    % Parameters
    % ==========
    % 
    % input_dtype : The datatype for counting class members. This might
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
    
    methods (Access = {?Soil, ?EntropyGain})
        function this = EntropyGain(dataTypes, libName, ptr, functionFormat)
            tmp = '_f';
            delFuncName = ['delete_EntropyGain' tmp];
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
            getter = sprintf('%s%s%s', 'eq', 'EntropyGain', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
