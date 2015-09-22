classdef ShannonEntropy < FertilizedObject
    % Computes the classical Shannon-Entropy.
    % 
    % Works correctly up to a total sum of elements of
    % numeric_limits<input_dtype>::max().
    % 
    % For classes :math:`C={c_1, \ldots, c_n}`, the Shannon entropy is defined as
    % 
    % .. math::
    %   -\sum_{c\in C}p_z\cdot \log_2 p_z.
    % 
    % 
    % The differential Shannon entropy for a normal distribution with covariance
    % matrix :math:`\Sigma` in :math:`n` dimensions is defined as
    % 
    % .. math::
    %   \frac{1}{2}\log\left((2\pi e)^n\left|\Sigma\right|\right).
    % 
    % 
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
    
    methods (Access = {?Soil, ?ShannonEntropy})
        function this = ShannonEntropy(dataTypes, libName, ptr, functionFormat)
            tmp = '_f';
            delFuncName = ['delete_ShannonEntropy' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
        function [res] = apply(this, class_members_numbers, fsum) 
            % The method is supposed to be fast and hence no checking for the validity
            % of fsum is done in release mode!
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
            % Parameters
            % ==========
            % 
            % class_member_numbers : Vector
            %   The class member counts (class histogram).
            % 
            % fsum : float
            %   The total of the class_member_numbers Vector.
            %   \return The calculated entropy value.
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'apply', 'ShannonEntropy', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, class_members_numbers, fsum);

            res = ptr;
        end
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
            getter = sprintf('%s%s%s', 'eq', 'ShannonEntropy', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
