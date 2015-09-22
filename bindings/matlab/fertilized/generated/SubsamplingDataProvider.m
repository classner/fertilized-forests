classdef SubsamplingDataProvider < FertilizedObject
    % Uses at maximum a certain amount of samples for node optimization.
    % 
    % Tracks the loaded samples during training and adds new samples if possible.
    % For leafs, all samples are loaded, even if its more than the maximum
    % number of samples for split optimization.
    % 
    % 
    % Can only be used for DFS (!!) for efficiency reasons.
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
    
    methods (Access = {?Soil, ?SubsamplingDataProvider})
        function this = SubsamplingDataProvider(dataTypes, libName, ptr, functionFormat)
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_SubsamplingDataProvider' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
    end
    
end
