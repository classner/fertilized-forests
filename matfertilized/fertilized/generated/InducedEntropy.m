classdef InducedEntropy < FertilizedObject
    % Computes the induced p entropy.
    % 
    % Works correctly up to a total sum of elements of
    % numeric_limits<input_dtype>::max().
    % 
    % This is the induced p-metric of the vector of :math:`n` class probabilities
    % and the point of maximum unorder (the vector with all entries
    % :math:`\frac{1}{n}`) in the n-dimensional space without applying the root.
    % It is equal to the Gini-measure for :math:`p=2`.
    % 
    % The definition for :math:`c` classes:
    % 
    % .. math::
    %   \sum_{i=1}^{c} \left\Vert p_i - 0.5\right\Vert ^p
    % .
    % 
    % The differential entropy for a normal distribution with covariance
    % matrix :math:`\Sigma` in :math:`n` dimensions is defined as:
    % 
    % .. math::
    %   \frac{1}{\sqrt{p^n}}\cdot\left(\sqrt{2\pi}^n\cdot\sqrt{\left|\Sigma\right|}\right)^{-(p-1)}
    % 
    % 
    % In the differential normal case, the most useful values for :math:`p` are
    % very close to 1 (e.g. 1.00001)! :math:`p=2` is already equivalent to the
    % infinite norm!
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
    
    methods (Access = {?Soil, ?InducedEntropy})
        function this = InducedEntropy(dataTypes, libName, ptr, functionFormat)
            tmp = '_f';
            delFuncName = ['delete_InducedEntropy' tmp];
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
            % class_member_numbers : Vector  The class member counts (class histogram).
            % 
            % fsum : float The total of the class_member_numbers Vector.
            %   \return The calculated entropy value.
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'apply', 'InducedEntropy', suffix);
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
            getter = sprintf('%s%s%s', 'eq', 'InducedEntropy', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
