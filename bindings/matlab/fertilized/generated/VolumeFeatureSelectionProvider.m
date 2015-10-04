classdef VolumeFeatureSelectionProvider < FertilizedObject
    % This selection provider generates random selection combinations
    % from a 3D feature volume.
    % 
    % It may be seeded for reproducible results.
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
    
    methods (Access = {?Soil, ?VolumeFeatureSelectionProvider})
        function this = VolumeFeatureSelectionProvider(dataTypes, libName, ptr, functionFormat)
            position_list = [];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_VolumeFeatureSelectionProvider' tmp];
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
            % - C+_
            % - Python
            % - Matlab
            % 
            % 
            % -----
            % 
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'eq', 'VolumeFeatureSelectionProvider', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function [res] = get_size_x(this) 
            % Get the horizontal patch size.
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
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'get_size_x', 'VolumeFeatureSelectionProvider', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = get_size_y(this) 
            % Get the vertical patch size.
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
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'get_size_y', 'VolumeFeatureSelectionProvider', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = get_size_z(this) 
            % Get the patch depth.
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
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'get_size_z', 'VolumeFeatureSelectionProvider', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = get_n_available_features(this) 
            % Get the total number of of available features.
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
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'get_n_available_features', 'VolumeFeatureSelectionProvider', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
