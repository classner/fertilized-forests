classdef IBaggingStrategy < FertilizedObject
    % Specifies how the samples are distributed amongst the trees.
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
    % - int; int; uint; std::vector<float>; std::vector<float>
    % - float; float; uint; std::vector<float>; std::vector<float>
    % - double; double; uint; std::vector<float>; std::vector<float>
    % - uint8_t; uint8_t; uint; std::vector<float>; std::vector<float>
    % - uint8_t; int16_t; uint; std::vector<float>; std::vector<float>
    % - uint8_t; int16_t; int16_t; std::vector<float>; std::vector<float>
    % - uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
    % - float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
    % - double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
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
    
    methods (Access = {?Soil, ?IBaggingStrategy})
        function this = IBaggingStrategy(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_IBaggingStrategy' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
