classdef IDataProvider < FertilizedObject
    % The data provider for the training of one tree.
    % 
    % 
    % Data providers work with Samples and sample ids. They are allowed to
    % add additional samples during training on the fly. The method
    % optimize_set_for_node is called before a classifier is fitted for
    % a decision node, so that the data provider can alter the set of samples
    % that are used.
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
    
    methods (Access = {?Soil, ?IDataProvider})
        function this = IDataProvider(dataTypes, libName, ptr, functionFormat)
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_IDataProvider' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
    end
    
end
