classdef UnchangedFDataProvider < FertilizedObject
    % Uses unchanged data providers for each tree.
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
    % - float; uint
    % - int; uint
    % - uint8_t; uint
    % - uint8_t; int16_t
    % - double; uint
    % - double; double
    % - float; float
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
    
    methods (Access = {?Soil, ?UnchangedFDataProvider})
        function this = UnchangedFDataProvider(dataTypes, libName, ptr, functionFormat)
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_UnchangedFDataProvider' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
    end
    
end
