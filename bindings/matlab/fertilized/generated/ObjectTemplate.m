classdef ObjectTemplate < FertilizedObject
    % Object template.
    % 
    % After having described the object, add a section like the following
    % to specify in which interfaces the object should be available, and, if it
    % is templated, which instantiations of the object. The instantiations are
    % ;-separated lists of the C++ types to use.
    % 
    % To start and end this section, use exactly -----. End the lists with a dot
    % and add an empty line after the last list. This is not due to our parser,
    % but due to doxygen. It is required to get a meaningful rendering for the
    % documentation.
    % 
    % Use exactly the library template names `input_dtype`, `feature_dtype`,
    % `annotation_dtype`, `leaf_return_dtype`, `forest_dtype` for your
    % objects as necessary (you may omit unnecessary ones). If your class is
    % templated differently, only one possible
    % template instantiation can be used for the interfaces. In that case, you
    % have to specify this with a parser list "Soil type always:". You can find
    % an example for this in impurities/shannonentropy.h.
    % 
    % The specification of the "Serialization generation:" is important if you
    % want to serialize your object and remain compatible to older versions
    % of the library. Specify the number as the version number of the library
    % in hundreds format (e.g., 1.00 as 100) plus one
    % (e.g., if the current library version is 1.01, use 102). Your self-
    % compiled library version with the additional object will be backwards
    % compatible with all lower library versions. Increase the library version in
    % the file 'global.h' to the same value!
    % 
    % IMPORTANT: you HAVE to adjust the `Serializaton generation:` version number
    % and the library version in 'global.h' to serialize your object and
    % maintain backwards compatibility!
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
    % 
    % Serialization generation: 100
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
    
    methods (Access = {?Soil, ?ObjectTemplate})
        function this = ObjectTemplate(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_ObjectTemplate' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
    end
    
end
