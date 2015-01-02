classdef StandardFeatureSelectionProvider < FertilizedObject
    % This selection provider generates random selection combinations.
    % 
    % It may be seeded for reproducible results. It can be configured to only
    % use a part of the available data dimensions. It only uses then the first
    % that are registered as used.
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
    
    methods (Access = {?Soil, ?StandardFeatureSelectionProvider})
        function this = StandardFeatureSelectionProvider(dataTypes, libName, ptr, functionFormat)
            position_list = [];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_StandardFeatureSelectionProvider' tmp];
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
            getter = sprintf('%s%s%s', 'eq', 'StandardFeatureSelectionProvider', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
