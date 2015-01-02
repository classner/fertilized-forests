classdef UnchangedDataProvider < FertilizedObject
    % Uses the provided data unchanged throughout the training.
    % 
    % It builds its sample database from two pointer on memory arrays with
    % data and annotations. Both must be provided in contiguous layout. The
    % data (but not the annotations!) can be provided row- or column-wise.
    % Column-wise layout is to be preferred, since it has more locality for
    % most optimization processes.
    % 
    % The annotations MUST always be provided in row major order, independent
    % of the provided value for column_wise.
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
    
    methods (Access = {?Soil, ?UnchangedDataProvider})
        function this = UnchangedDataProvider(dataTypes, libName, ptr, functionFormat)
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_UnchangedDataProvider' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
    end
    
end
