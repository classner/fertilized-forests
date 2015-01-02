classdef PatchSampleManager < FertilizedObject
    % Manages patch samples for the SubsamlingDataProvider.
    % 
    % Loads patches from the images on-demand and always has only
    % the maximum allowed number of patches in memory. This exception
    % might only be violated at leafs.
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
    % - uint8_t; int16_t
    % - uint8_t; uint
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
    
    methods (Access = {?Soil, ?PatchSampleManager})
        function this = PatchSampleManager(dataTypes, libName, ptr, functionFormat)
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_PatchSampleManager' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
    end
    
end
