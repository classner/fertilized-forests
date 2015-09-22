
classdef Soil
    % Convenience factory class for creating forest objects of specified types.
    %
    % You can create a `Soil` once with a given set of types that you want to
    % work with. All following objects constructed by the soil objects work
    % with according types, so that you don't have to worry about this detail.
    %
    % Take into account, that not all objects can be created by a `Soil` of a
    % specific type! Calling the respective functions throws an exception.
    %
    % The datatype strings are translated into an internal string representation,
    % so they can be specified quite freely, e.g. specyfing `f` or `float` is
    % both understood as `float`. Take into account, that these datatypes are
    % interpreted like the C++ datatypes, i.e. `float` is (usually) a 32-bit
    % floating point number, and `double` is (usually) the 64-bit counterpart.
    %
    % There is the enum `Result_Types` available in this package, that provides
    % access to the different result types.
    %
    % Example usage:
    %
    % >>> soil = Soil(result_type=Result_Types.probabilities)
    % >>> leaf_manager = soil.ClassificationLeafManager(2)
    %
    % A leaf manager working with the proper types (in this case
    % `float` and `unsigned int`) has been created.
    %
        % Author: Christoph Lassner.
    %
    % This is an automatically generated file!
    %
    properties (SetAccess = private)
        LibName = 'matfertilized';
        MainHeader = 'matlab.h';
        AdditionalHeaders = { 'objectvector-nonmsvc.h', 'stringvector-nonmsvc.h', '__bagging.h', '__boosting.h', '__data_providers.h', '__deciders.h', '__execution_strategies.h', '__feature_extraction.h', '__features.h', '__gains.h', '__impurities.h', '__leafs.h', '__regression.h', '__rootdir.h', '__threshold_optimizers.h', '__trainings.h', '__functions_standard_forests.h', '__functions_standard_trees.h', '__functions_feature_extraction.h' };
        
        % DataTypes order: input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype 
        inp_str = 'f';
        feat_str = 'f';
        ann_str = 'uint';
        res_type = Result_Types.probabilities
        tres = 'fv';
        fres = 'fv';
        dtype_str_translation = containers.Map;
        res_type_str_translation = containers.Map;
    end

    methods (Static = true)
        function [res] = DEFAULT_ENTROPY_P1_2()
          res = single([2, 1]);
        end

        function [res] = DEFAULT_ENTROPY_VEC_2()
          res = {'induced', 'induced'};
        end
    end

    methods
        function this = Soil(input_dtype,...
                             feature_dtype,...
                             annotation_dtype,...
                             result_type)
            this.dtype_str_translation('std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>') = 'vprpff';
            this.dtype_str_translation('int') = 'i';
            this.dtype_str_translation('float') = 'f';
            this.dtype_str_translation('char') = 'int8';
            this.dtype_str_translation('int16_t') = 'int16';
            this.dtype_str_translation('std::vector<double>') = 'dv';
            this.dtype_str_translation('ui16') = 'uint16';
            this.dtype_str_translation('uint8_t') = 'uint8';
            this.dtype_str_translation('uchar') = 'uint8';
            this.dtype_str_translation('uint16') = 'uint16';
            this.dtype_str_translation('std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>') = 'rpd';
            this.dtype_str_translation('std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>') = 'vprpfd';
            this.dtype_str_translation('int16') = 'int16';
            this.dtype_str_translation('unsigned char') = 'uint8';
            this.dtype_str_translation('uint8') = 'uint8';
            this.dtype_str_translation('std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>') = 'rpf';
            this.dtype_str_translation('std::vector<std::pair<float,std::shared_ptr<std::vector<int16_t>>>>') = 'vhp';
            this.dtype_str_translation('uint') = 'uint';
            this.dtype_str_translation('std::vector<float>') = 'fv';
            this.dtype_str_translation('ui8') = 'uint8';
            this.dtype_str_translation('unsigned int') = 'uint';
            this.dtype_str_translation('c') = 'int8';
            this.dtype_str_translation('d') = 'd';
            this.dtype_str_translation('f') = 'f';
            this.dtype_str_translation('i') = 'i';
            this.dtype_str_translation('double') = 'd';
            this.dtype_str_translation('i16') = 'int16';
            this.dtype_str_translation('ui') = 'uint';
            this.dtype_str_translation('std::pair<float,std::shared_ptr<std::vector<int16_t>>>') = 'hp';
            this.dtype_str_translation('uint16_t') = 'uint16';
            this.dtype_str_translation('uc') = 'uint8';
            this.res_type_str_translation(Result_Types.probabilities.name) = {'fv' ;'fv'};
            this.res_type_str_translation(Result_Types.hough_map.name) = {'hp'; 'vhp'};
            this.res_type_str_translation(Result_Types.regression.name) = {'rp'; 'vprpf'};
            %if libisloaded(this.LibName)
            %    unloadlibrary(this.LibName);
            %end
            % add the generated folder to the path if necessary
            genpath = strcat(fileparts(mfilename('fullpath')), filesep, 'generated;');
            if isempty(strfind(path, genpath))
              addpath(genpath);
            end    
            if ~libisloaded(this.LibName)
                % create additional loadlibray arguments...
                args = {};
                for header = this.AdditionalHeaders
                    args = [args, 'addheader'];
                    args = [args, strcat('headers', ...
                                         filesep, ...
                                         header)];
                end

                mainheader = strcat(fileparts(mfilename('fullpath')), ...
                                    filesep, ...
                                    'headers', ...
                                    filesep, ...
                                    this.MainHeader);
            
                if strcmp(getenv('OS'), 'Windows_NT')
                    dllsuff = '.dll';
                else
                    dllsuff = '.so';
                end
                dllName = strcat(fileparts(mfilename('fullpath')), ...
                                 filesep, ...
                                 this.LibName, ...
                                 dllsuff);
                [notfound,warnings] = loadlibrary(dllName, mainheader, args{:});
            end
            % Initialize values.
            if exist('input_dtype', 'var')
              if find(ismember(keys(this.dtype_str_translation), input_dtype))
                this.inp_str = this.dtype_str_translation(input_dtype);
              else
                throw(MException('fertilized:soil_inp_dtype_wrong', 'Unknown input dtype!'));
              end
            end
            if exist('feature_dtype', 'var')
              if find(ismember(keys(this.dtype_str_translation), feature_dtype))
                this.feat_str = this.dtype_str_translation(feature_dtype);
              else
                throw(MException('fertilized:soil_feat_dtype_wrong', 'Unknown feature dtype!'));
              end
            end
            if exist('annotation_dtype', 'var')
              if find(ismember(keys(this.dtype_str_translation), annotation_dtype))
                this.ann_str = this.dtype_str_translation(annotation_dtype);
              else
                throw(MException('fertilized:soil_ann_dtype_wrong', 'Unknown annotation dtype!'));
              end
            end
            if exist('result_type', 'var')
              this.res_type = result_type;
              tmp_rest = this.res_type_str_translation(result_type.name);
              if this.res_type == Result_Types.regression
                this.tres = strcat(tmp_rest{1}, this.inp_str);
                this.fres = strcat(tmp_rest{2}, this.inp_str);
              else
                if this.res_type == Result_Types.probabilities ||...
                   this.res_type == Result_Types.hough_map
                  this.tres = tmp_rest{1};
                  this.fres = tmp_rest{2};
                else
                  throw(MException('fertilized:soil_ret_dtype_wrong', 'Unknown return dtype!'));
                end
              end
            end
        end

        function [out] = getDataTypes(this, index)
            % Gets a cell array with the data type strings of this soil object.
            out = {this.inp_str, this.feat_str, this.ann_str, this.tres, this.fres};
            if exist('index', 'var')
              out = out{index};
            end
        end
       
        function listLibFunctions(this)
            % Prints all library functions of the underlying C library module.
            libfunctions(this.LibName);
        end

        % start generated methods
        function [res] = Forest(this, max_tree_depth, min_samples_at_leaf, min_samples_at_node, n_trees, deciders, leaf_managers, training)
            % Class information:
            % ==================
            % 
            % Standard forest class of the library.
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
            % - uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
            % - float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
            % - double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % max_tree_depth : uint > 0
            %   The maximum tree depth, including leafs (up to including).
            % 
            % min_samples_at_leaf : uint > 0
            %   The minimum number of samples at a leaf (from including).
            % 
            % min_samples_at_node : uint>=2*min_samples_at_leaf
            %   The minimum number of samples at a node (from including).
            % 
            % n_trees : uint>1
            %   The number of trees.
            % 
            % deciders : vector(shared(IDecider))
            %   The deciders for each tree.
            % 
            % leaf_managers : vector(shared(ILeafManager))
            %   The leaf managers for each tree.
            % 
            % training : ITraining
            %   The training to use.
            tmp_deciders = ObjectVector();
            for tmp_deciders_idx = 1:length(deciders)
              tmp_deciders.append(deciders{tmp_deciders_idx});
            end
            deciders = tmp_deciders.ClassifierPtr;
            tmp_leaf_managers = ObjectVector();
            for tmp_leaf_managers_idx = 1:length(leaf_managers)
              tmp_leaf_managers.append(leaf_managers{tmp_leaf_managers_idx});
            end
            leaf_managers = tmp_leaf_managers.ClassifierPtr;
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'Forest', tmp);
            ptr = calllib(this.LibName, getter, max_tree_depth, min_samples_at_leaf, min_samples_at_node, n_trees, deciders, leaf_managers, training.ClassifierPtr);
            res = Forest(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ForestFromTrees(this, trees, training)
            % Class information:
            % ==================
            % 
            % Standard forest class of the library.
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
            % - uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
            % - float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
            % - double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Combines UNTRAINED trees to a forest.
            % 
            % -----
            % 
            % Available in:
            % 
            % - C++
            % - Python
            % - Matlab
            % 
            % Exported name: ForestFromTrees
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % trees : vector(shared(Tree))
            %   The untrained trees.
            % 
            % training : ITraining
            %   The training to use.
            tmp_trees = ObjectVector();
            for tmp_trees_idx = 1:length(trees)
              tmp_trees.append(trees{tmp_trees_idx});
            end
            trees = tmp_trees.ClassifierPtr;
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'ForestFromTrees', tmp);
            ptr = calllib(this.LibName, getter, trees, training.ClassifierPtr);
            res = Forest(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = CombineTrees(this, trees)
            % Class information:
            % ==================
            % 
            % Standard forest class of the library.
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
            % - uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
            % - float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
            % - double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Combines TRAINED trees to a forest. !! Training is not possible any more !!
            % 
            % -----
            % 
            % Available in:
            % 
            % - C++
            % - Python
            % - Matlab
            % 
            % Exported name: CombineTrees
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % trees : vector(shared(Tree))
            %   The trained trees to combine.
            tmp_trees = ObjectVector();
            for tmp_trees_idx = 1:length(trees)
              tmp_trees.append(trees{tmp_trees_idx});
            end
            trees = tmp_trees.ClassifierPtr;
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'CombineTrees', tmp);
            ptr = calllib(this.LibName, getter, trees);
            res = Forest(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ForestFromFile(this, filename)
            % Class information:
            % ==================
            % 
            % Standard forest class of the library.
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
            % - uint8_t; int16_t; int16_t; std::pair<float, std::shared_ptr<std::vector<int16_t>>>; std::vector<std::pair<float, std::shared_ptr<std::vector<int16_t>>>>
            % - float; float; float; std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<float>>,std::shared_ptr<std::vector<float>>>,float>>
            % - double; double; double; std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>; std::vector<std::pair<std::pair<std::shared_ptr<std::vector<double>>,std::shared_ptr<std::vector<double>>>,float>>
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Deserializing constructor to load a forest from a file.
            % 
            % -----
            % 
            % Available in:
            % 
            % - C++
            % - Python
            % - Matlab
            % 
            % Exported name: ForestFromFile
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % filename : string
            %   The file to load the forest from.
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'ForestFromFile', tmp);
            ptr = calllib(this.LibName, getter, filename);
            res = Forest(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = Tree(this, max_depth, min_samples_at_leaf, min_samples_at_node, decider, leaf_manager)
            % Class information:
            % ==================
            % 
            % The main tree class for the fertilized framework.
            % 
            % This class is the core element of the framework. It can be used as a
            % standalone tree or to form a forest. It is highly customizable by
            % providing the IClassifierManager and ILeafManager.
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
            % Constructor:
            % ============
            % 
            % The standard constructor for the fertilized trees.
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
            % max_depth : uint > 0
            %   The maximum tree depth, including leafs (up to including).
            % 
            % min_samples_at_leaf : uint > 0
            %   The minimum number of samples at a leaf (from including).
            % 
            % min_samples_at_node : uint>=2*min_samples_at_leaf
            %   The minimum number of samples at a node (from including).
            % 
            % decider : IDecider
            %   The decider that stores, optimizes and applies the decision rules
            %   for each inner tree node.
            % 
            % leaf_manager : The leaf manager generates, stores and handles
            %   the return values of the leaf nodes.
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'Tree', tmp);
            ptr = calllib(this.LibName, getter, max_depth, min_samples_at_leaf, min_samples_at_node, decider.ClassifierPtr, leaf_manager.ClassifierPtr);
            res = Tree(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = TreeFromFile(this, filename)
            % Class information:
            % ==================
            % 
            % The main tree class for the fertilized framework.
            % 
            % This class is the core element of the framework. It can be used as a
            % standalone tree or to form a forest. It is highly customizable by
            % providing the IClassifierManager and ILeafManager.
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
            % Constructor:
            % ============
            % 
            % Deserialization constructor for the fertilized trees.
            % 
            % -----
            % 
            % Available in:
            % 
            % - C++
            % - Python
            % - Matlab
            % 
            % Exported name: TreeFromFile
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % filename : string
            %   The filename to deserialize the tree from.
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'TreeFromFile', tmp);
            ptr = calllib(this.LibName, getter, filename);
            res = Tree(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ObjectTemplate(this, example_param)
            % Class information:
            % ==================
            % 
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
            % Constructor:
            % ============
            % 
            % For every method, including the constructor, you can specify a
            % list of interfaces in which the method should be exported. Add the
            % description of the parameters after the specification (this is again
            % just to get nice doxygen results). Parameter conversion code for method
            % arguments is generated automatically for
            % 
            % - all plain C++ types,
            % - vectors of these types,
            % - 'Array's,
            % - vectors of 'Array's,
            % - library objects,
            % - vectors of library objects.
            % 
            % Return types may be
            % - all plain C++ types,
            % - vectors of these types,
            % - 'Array's,
            % - library objects (not available for Matlab!),
            % - vectors of library objects (not available for Matlab!).
            % 
            % Remember to run `scons --generate-interfaces` to update all language
            % interfaces after a change to your class specification. This also requires
            % compilation.
            % 
            % -----
            % 
            % Available in:
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
            % example_param : uint > 0
            %   An example parameter to illustrate the documentation.
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'ObjectTemplate', tmp);
            ptr = calllib(this.LibName, getter, example_param);
            res = ObjectTemplate(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = LocalExecutionStrategy(this, num_threads)
            % Class information:
            % ==================
            % 
            % Executes the training on the local machine.
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
            % Constructor:
            % ============
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
            % num_threads : int>0
            %   The number of threads to use for parallelism on forest training level.
            %   Note that this multiplies with the parallelism applied for training
            %   steps, such as for IDecider optimization! Default: 1.
            if ~exist('num_threads', 'var') || num_threads == -1
                num_threads = 1;
            end    
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'LocalExecutionStrategy', tmp);
            ptr = calllib(this.LibName, getter, num_threads);
            res = LocalExecutionStrategy(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ThresholdDecider(this, selection_provider, feature_calculator, threshold_optimizer, n_valid_features_to_use, num_threads, use_hough_heuristic, hough_heuristic_ratio, hough_heuristic_maxd, allow_early_stopping)
            % Class information:
            % ==================
            % 
            % A classifier manager for weak classifiers with a filter function,
            % a feature calculation function and a thresholding.
            % 
            % The classifier design is heavily inspired by "Decision Forests for
            % Classification, Regression, Density Estimation, Manifold Learning and
            % Semi-Supervised Learning" (Criminisi, Shotton and Konukoglu, 2011).
            % With their definition, node classifier parameters :math:`\theta` can
            % be split into three parts:
            % 
            % - :math:`\phi`: a filter function that selects relevant features,
            % - :math:`\psi`: parameters of a function that combines the feature values
            % to a single scalar,
            % - :math:`\tau`: thresholding parameters for the calculated scalar.
            % 
            % With this model, a decision can be made at each node based on whether the
            % calculated scalar lies withing the thresholding bounds.
            % 
            % 
            % -----
            % 
            % Available in:
            % - C++
            % - Python
            % - Matlab
            % 
            % Instantiations:
            % 
            % - int; int; uint
            % - uint8_t; uint8_t; uint
            % - uint8_t; int16_t; uint
            % - float; float; uint
            % - double; double; uint
            % - uint8_t; int16_t; int16_t
            % - float; float; float
            % - double; double; double
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % selection_provider : shared(IFeatureSelectionProvider)
            %   It suggests tuples
            %   for the optimization of :math:`\phi`. It must be compatible
            %   to the feature calculator.
            % 
            % feature_calculator : shared(ISurfaceCalculator)
            %   The feature calculation function. Its
            %   parameters are :math:`\psi`, and it combines the data
            %   dimensions to a single scalar feature.
            % 
            % threshold_optimizer : shared(IThresholdOptimizer)
            %   Optimizes :math:`\tau`.
            % 
            % n_valid_features_to_use : size_t
            %   The threshold optimizer may hint that
            %   a selected feature may be completely inappropriate for the
            %   currently searched split. If the feature selection provider
            %   does provide  sufficiently many features, the classifier may
            %   use the next one and "not count" the inappropriate one.
            %   This is the maximum number of "valid" features that are
            %   used per split. If 0, ignore the flag returned by the
            %   optimizer and always use all suggested feature combinations
            %   provided by the feature selection provider. Default: 0.
            % 
            % num_threads : size_t>0
            %   The number of threads to use for threshold optimization.
            %   Independent of the number of threads, the result is
            %   guaranteed to be the same. Default: 1.
            % 
            % use_hough_heuristic : bool
            %   Whether or not to use a heuristic for hough
            %   forests introduced by Juergen Gall
            %   (http://www.vision.ee.ethz.ch/~gallju/projects/houghforest/houghforest.html)
            %   Can be used only with an AlternatingThresholdOptimizer.
            %   If used, the AlternatingThresholdOptimizer will guaranteed
            %   use opt2 if the ratio of negative samples is < hough_heuristic_ratio or
            %   depth >= hough_heuristic_maxd. opt2 must be a
            %   VarianceClassificationThresholdOptimizer (check this
            %   manually!). Default: false.
            % 
            % hough_heuristic_ratio : float>=0.f
            %   Default: 0.05f.
            % 
            % hough_heuristic_maxd : uint
            %   Default: 0.
            % 
            % allow_early_stopping : bool
            %   Allows the threshold optimizer to stop training if, e.g., all samples
            %   are of the same class in a classification setting. This is currently
            %   only supported by the classification threshold optimizers for 1D
            %   class annotations. Default: false.
            if ~exist('n_valid_features_to_use', 'var') || n_valid_features_to_use == -1
                n_valid_features_to_use = 0;
            end    
            if ~exist('num_threads', 'var') || num_threads == -1
                num_threads = 1;
            end    
            if ~exist('use_hough_heuristic', 'var') || use_hough_heuristic == -1
                use_hough_heuristic = 0;
            end    
            if ~exist('hough_heuristic_ratio', 'var') || hough_heuristic_ratio == -1
                hough_heuristic_ratio = 0.05;
            end    
            if ~exist('hough_heuristic_maxd', 'var') || hough_heuristic_maxd == -1
                hough_heuristic_maxd = 0;
            end    
            if ~exist('allow_early_stopping', 'var') || allow_early_stopping == -1
                allow_early_stopping = 0;
            end    
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'ThresholdDecider', tmp);
            ptr = calllib(this.LibName, getter, selection_provider.ClassifierPtr, feature_calculator.ClassifierPtr, threshold_optimizer.ClassifierPtr, n_valid_features_to_use, num_threads, use_hough_heuristic, hough_heuristic_ratio, hough_heuristic_maxd, allow_early_stopping);
            res = ThresholdDecider(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = NoCopyPatchSampleManager(this, images, patch_descs, n_positives, patch_size_z, patch_size_y, patch_size_x, patches_luc)
            % Class information:
            % ==================
            % 
            % A sample manager for Hough forests that limits the number of
            % patches for one node, but does not copy anything but uses direct access
            % tricks.
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
            % - uint8_t; int16_t
            % - uint8_t; uint
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % images : vector(Array<input_dtype>, 3D, row-major contiguous)
            %   Images of shape (n_features, height, width).
            % 
            % patch_descs : Array<annotation_dtype, 3D, row-major contiguous)
            %   2D array in row major format with
            %   the patch descriptions. A patch description consists of 5 values:
            %   image id, position x, y, offset x, y (from the object to detect,
            %   so that position x + offset x = object x).
            % 
            % n_positives : size_t>0
            %   The first n_positive examples are interpreted as
            %   positives, the rest as negatives (they get an according annotation).
            % 
            % patch_size_z : size_t>0
            %   Patch depth.
            % 
            % patch_size_y : size_t>0
            %   Patch height.
            % 
            % patch_size_x : size_t>0
            %   Patch width.
            % 
            % patches_luc : bool
            %   If true, it is assumed that the patch descriptions
            %   contain the _L_eft _U_pper _C_orners of the patches. Otherwise, it
            %   it assumed they contain the center points. In the luc case, the patch
            %   goes from (including) position{x,y} to (excluding)
            %   position{x,y}+{width, height}. In the center case, the patch goes
            %   from (including) position{x,y}-{width//2, height//2} up to (excluding)
            %   position{x,y}-{(width//2-width), (height//2-height)}. Default: false.
            if ~exist('patches_luc', 'var') || patches_luc == -1
                patches_luc = 0;
            end    
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'NoCopyPatchSampleManager', tmp);
            ptr = calllib(this.LibName, getter, images, patch_descs, n_positives, patch_size_z, patch_size_y, patch_size_x, patches_luc);
            res = NoCopyPatchSampleManager(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = SubsamplingDataProvider(this, max_samples_per_node, sample_manager, random_seed)
            % Class information:
            % ==================
            % 
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
            % Constructor:
            % ============
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
            % max_samples_per_node : size_t>0
            %   The maximum number of samples to use for split optimization.
            % 
            % sample_manager : shared(ISampleManager)
            %   The ISampleManager to use to handle the samples.
            % 
            % random_seed : uint>0
            %   The seed for the RNG.
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'SubsamplingDataProvider', tmp);
            ptr = calllib(this.LibName, getter, max_samples_per_node, sample_manager.ClassifierPtr, random_seed);
            res = SubsamplingDataProvider(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = UnchangedFDataProvider(this, data_array, annotation_array)
            % Class information:
            % ==================
            % 
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
            % Constructor:
            % ============
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
            % Parameters
            % ==========
            % 
            % data_array : Array<input_dtype>, 2D, row-major contiguous.
            %   The data to use, with one data sample per row.
            % 
            % annotation_array : Array<annotation_dtype>, 2D, row-major contiguous.
            %   The annotations to use, with one annotation per row.
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'UnchangedFDataProvider', tmp);
            ptr = calllib(this.LibName, getter, data_array, annotation_array);
            res = UnchangedFDataProvider(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = UnchangedDataProvider(this, data, annotations)
            % Class information:
            % ==================
            % 
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
            % Constructor:
            % ============
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
            % Parameters
            % ==========
            % 
            % data_array : Array<input_dtype>, 2D, row-major contiguous.
            %   The data to use, with one data sample per row.
            % 
            % annotation_array : Array<annotation_dtype>, 2D, row-major contiguous.
            %   The annotations to use, with one annotation per row.
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'UnchangedDataProvider', tmp);
            ptr = calllib(this.LibName, getter, data, annotations);
            res = UnchangedDataProvider(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = PatchSampleManager(this, images, patch_descs, n_positives, patch_size_z, patch_size_y, patch_size_x, patches_luc)
            % Class information:
            % ==================
            % 
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
            % Constructor:
            % ============
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
            % images : vector(Array<input_dtype>, 3D, row-major contiguous)
            %   Images of shape (n_features, height, width).
            % 
            % patch_descs : Array<annotation_dtype, 3D, row-major contiguous)
            %   2D array in row major format with
            %   the patch descriptions. A patch description consists of 5 values:
            %   image id, position x, y, offset x, y (from the object to detect,
            %   so that position x + offset x = object x).
            % 
            % n_positives : size_t>0
            %   The first n_positive examples are interpreted as
            %   positives, the rest as negatives (they get an according annotation).
            % 
            % patch_size_z : size_t>0
            %   Patch depth.
            % 
            % patch_size_y : size_t>0
            %   Patch height.
            % 
            % patch_size_x : size_t>0
            %   Patch width.
            % 
            % patches_luc : bool
            %   If true, it is assumed that the patch descriptions
            %   contain the _L_eft _U_pper _C_orners of the patches. Otherwise, it
            %   it assumed they contain the center points. In the luc case, the patch
            %   goes from (including) position{x,y} to (excluding)
            %   position{x,y}+{width, height}. In the center case, the patch goes
            %   from (including) position{x,y}-{width//2, height//2} up to (excluding)
            %   position{x,y}-{(width//2-width), (height//2-height)}. Default: false.
            if ~exist('patches_luc', 'var') || patches_luc == -1
                patches_luc = 0;
            end    
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'PatchSampleManager', tmp);
            ptr = calllib(this.LibName, getter, images, patch_descs, n_positives, patch_size_z, patch_size_y, patch_size_x, patches_luc);
            res = PatchSampleManager(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = NoBagging(this)
            % Class information:
            % ==================
            % 
            % As the name suggests, performs no bagging and uses all samples for all trees.
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
            % Constructor:
            % ============
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
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'NoBagging', tmp);
            ptr = calllib(this.LibName, getter);
            res = NoBagging(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = EqualDistBagging(this)
            % Class information:
            % ==================
            % 
            % Equal distribution bagging.
            % 
            % The samples are distributed equally amongst the trees. Each sample belongs
            % to exactly one tree. Note that this behaviour destroys the max-margin
            % property of decision forests.
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
            % Constructor:
            % ============
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
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'EqualDistBagging', tmp);
            ptr = calllib(this.LibName, getter);
            res = EqualDistBagging(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = LinearRegressionCalculator(this, force_numerical_stability, numerical_zero_threshold)
            % Class information:
            % ==================
            % 
            % Calculator for linear regression.
            % 
            % This regression calculator uses a linear combination of the input dimensions
            % to predict the output value. Therefore it does not provide a constant prediction
            % or a constant prediction covariance matrix.
            % If there are multiple output values to be predicted, each output is produced
            % using its own linear model.
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
            % - double
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Constructor for a LinearRegressionCalculator
            % 
            % Costructs a LinearRegressionCalculator.
            % If numberical stability is not forced, the linear models
            % in low dimensional cases are computed using a closed form.
            % This is faster but less accurate.
            % Otherwise, always matrix decomposition is used which provides
            % more accurate and stable solutions.
            % In order to prevent numerical issues, a threshold can be specified
            % to denote the smallest number that is distinct to zero.
            % Using the default value -1, this threshold is determined automatically
            % based on the data samples.
            % 
            % Parameters
            % ==========
            % 
            % force_numerical_stability : Denotes, numerical stability is forced or not.
            % 
            % numerical_zero_threshold : The threshold for the smallest number distinguished from zero.
            %   \returns A new LinearRegressionCalculator.
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
            % 
            % force_numerical_stability : bool
            %   Whether to enforce numerical stability or allow instable solutions. Default: true.
            % 
            % numerical_zero_threshold : input_dtype >=0||-1
            %   Everything below this threshold is treated as zero. If set to -1.f,
            %   use the value proposed by Eigen. Default: -1.f
            if ~exist('force_numerical_stability', 'var') || force_numerical_stability == -1
                force_numerical_stability = 1;
            end    
            if ~exist('numerical_zero_threshold', 'var') || numerical_zero_threshold == -1
                numerical_zero_threshold = static_cast<input_dtype>(-1);
            end    
            position_list = [1];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'LinearRegressionCalculator', tmp);
            ptr = calllib(this.LibName, getter, force_numerical_stability, numerical_zero_threshold.ClassifierPtr);
            res = LinearRegressionCalculator(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ConstantRegressionCalculator(this)
            % Class information:
            % ==================
            % 
            % Calculator for constant regression.
            % 
            % This regression calculator uses a constant value to predict the output value.
            % Therefore, it provides a constant prediction and a constant prediction covariance matrix.
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
            % - double
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            position_list = [1];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'ConstantRegressionCalculator', tmp);
            ptr = calllib(this.LibName, getter);
            res = ConstantRegressionCalculator(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = InducedEntropy(this, p)
            % Class information:
            % ==================
            % 
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
            % Constructor:
            % ============
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
            % p : float>0.f
            %   The entropy parameter value.
            tmp = '_f';
            getter = sprintf('%s%s%s', 'get', 'InducedEntropy', tmp);
            ptr = calllib(this.LibName, getter, p);
            res = InducedEntropy(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = RenyiEntropy(this, alpha)
            % Class information:
            % ==================
            % 
            % Computes the Renyi entropy.
            % 
            % Works correctly up to a total sum of elements of
            % numeric_limits<input_dtype>::max().
            % 
            % This is the Renyi entropy, as introduced by Alfred Renyi
            % (see http://en.wikipedia.org/wiki/R%C3%A9nyi_entropy).
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
            % Constructor:
            % ============
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
            % alpha : float>0.f
            %   The entropy parameter.
            tmp = '_f';
            getter = sprintf('%s%s%s', 'get', 'RenyiEntropy', tmp);
            ptr = calllib(this.LibName, getter, alpha);
            res = RenyiEntropy(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ShannonEntropy(this)
            % Class information:
            % ==================
            % 
            % Computes the classical Shannon-Entropy.
            % 
            % Works correctly up to a total sum of elements of
            % numeric_limits<input_dtype>::max().
            % 
            % For classes :math:`C={c_1, \ldots, c_n}`, the Shannon entropy is defined as
            % 
            % .. math::
            %   -\sum_{c\in C}p_z\cdot \log_2 p_z.
            % 
            % 
            % The differential Shannon entropy for a normal distribution with covariance
            % matrix :math:`\Sigma` in :math:`n` dimensions is defined as
            % 
            % .. math::
            %   \frac{1}{2}\log\left((2\pi e)^n\left|\Sigma\right|\right).
            % 
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
            % Constructor:
            % ============
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
            tmp = '_f';
            getter = sprintf('%s%s%s', 'get', 'ShannonEntropy', tmp);
            ptr = calllib(this.LibName, getter);
            res = ShannonEntropy(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ClassificationError(this)
            % Class information:
            % ==================
            % 
            % Computes the classification error as 1-\max(p_i).
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
            % Constructor:
            % ============
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
            tmp = '_f';
            getter = sprintf('%s%s%s', 'get', 'ClassificationError', tmp);
            ptr = calllib(this.LibName, getter);
            res = ClassificationError(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = TsallisEntropy(this, q)
            % Class information:
            % ==================
            % 
            % Computes the Tsallis entropy.
            % 
            % Works correctly up to a total sum of elements of
            % numeric_limits<input_dtype>::max().
            % 
            % This is the Tsallis entropy, as introduced by Constantino Tsallis
            % (see http://en.wikipedia.org/wiki/Tsallis_entropy).
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
            % -----
            % 
            % Constructor:
            % ============
            % 
            % -----
            % 
            % Available in:
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
            % q : float>0.f
            %   The entropy parameter.
            tmp = '_f';
            getter = sprintf('%s%s%s', 'get', 'TsallisEntropy', tmp);
            ptr = calllib(this.LibName, getter, q);
            res = TsallisEntropy(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = RandomizedClassificationThresholdOptimizer(this, n_thresholds, n_classes, gain_calculator, gain_threshold, annotation_step, random_seed)
            % Class information:
            % ==================
            % 
            % Optimizes a threshold by selecting the best of few random values.
            % 
            % Supports only classification annotations (unsigned int) with annotation
            % values in [0, ..., n_classes[.
            % The threshold optimizer draws n_thresholds random values between
            % the minimum and maximum observed feature value and returns the best
            % one.
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
            % - int; int; uint
            % - int; float; uint
            % - float; int; uint
            % - uint8_t; int; uint
            % - uint8_t; uint8_t; uint
            % - uint8_t; float; uint
            % - uint8_t; int16_t; uint
            % - float; float; uint
            % - double; double; uint
            % - uint8_t; int16_t; int16_t
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Standard constructor.
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
            % n_thresholds : size_t>0
            %   The number of thresholds to test per node.
            % 
            % n_classes : size_t>1
            %   The number of classes. All annotations must be within
            %   [0, ..., n_classes[.
            % 
            % gain_calculator : IGainCalculator
            %   The gain calculator to use.
            % 
            % gain_threshold : float >= 0f
            %   The minimum gain that must be reached to continue splitting. Optional.
            % 
            % annotation_step : size_t>0
            %   The memory step from one annotation value to the next. Optional.
            % 
            % random_seed : uint>0
            %   The random seed to initialize the RNG. Optional.
            if ~exist('gain_threshold', 'var') || gain_threshold == -1
                gain_threshold = 1E-7;
            end    
            if ~exist('annotation_step', 'var') || annotation_step == -1
                annotation_step = 1;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'RandomizedClassificationThresholdOptimizer', tmp);
            ptr = calllib(this.LibName, getter, n_thresholds, n_classes, gain_calculator.ClassifierPtr, gain_threshold, annotation_step, random_seed);
            res = RandomizedClassificationThresholdOptimizer(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = VarianceClassificationThresholdOptimizer(this, n_thresholds, n_classes, offset_dim, gain_threshold, random_seed)
            % Class information:
            % ==================
            % 
            % Optimizes a threshold by selecting the best some random values with respect to the variance of example offsets.
            % 
            % The annotations are assumed to be a class label followed by its offset
            % values. Since all these values must be of the same datatype, the only supported type
            % is (signed) int in this case (to allow for negative offsets). The class labels
            % must still be in [0; n_classes - 1].
            % 
            % This threshold optimizer draws n_thresholds random values between
            % the minimum and maximum observed feature value and returns the best
            % one.
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
            % - int; int; uint
            % - int; float; uint
            % - float; int; uint
            % - uint8_t; int; uint
            % - uint8_t; uint8_t; uint
            % - uint8_t; float; uint
            % - uint8_t; int16_t; uint
            % - float; float; uint
            % - double; double; uint
            % - uint8_t; int16_t; int16_t
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Standard constructor.
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
            % n_thresholds : size_t>0
            %   The number of thresholds to evaluate per split.
            % 
            % n_classes : size_t>1
            %   The number of classes in the data. Currently only 2 are supported! Default: 2.
            % 
            % offset_dim : size_t>0
            %   The dimensionality of the offset annotation (usually 2). Default: 2.
            % 
            % gain_threshold : float
            %   The minimum gain to accept a split as valid. Default: 0.f.
            % 
            % random_seed : unsigned int>0
            %   The seed for the RNG. Must be greater 0. Default: 1.
            if ~exist('n_classes', 'var') || n_classes == -1
                n_classes = 2;
            end    
            if ~exist('offset_dim', 'var') || offset_dim == -1
                offset_dim = 2;
            end    
            if ~exist('gain_threshold', 'var') || gain_threshold == -1
                gain_threshold = 0;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'VarianceClassificationThresholdOptimizer', tmp);
            ptr = calllib(this.LibName, getter, n_thresholds, n_classes, offset_dim, gain_threshold, random_seed);
            res = VarianceClassificationThresholdOptimizer(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = RegressionThresholdOptimizer(this, n_thresholds, regression_calculator, entropy_function, gain_threshold, annotation_step, random_seed)
            % Class information:
            % ==================
            % 
            % Optimizes the threshold for splitting a dataset, to ensure optimal
            % regression results on the splits.
            % 
            % This threshold optimizer draws n_thresholds random values between
            % the minimum and maximum observed feature value and returns the best
            % one.
            % Multiple annotations (and therefore multiple output regression) are allowed.
            % The splits are evaluated using a provided regression calculator.
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
            % - float; float
            % - double; double
            % 
            % 
            % -----
            % 
            % 
            % Constructor:
            % ============
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
            % n_thresholds : size_t>0
            %   Number of randomly drawn threshold values that are asessed.
            % 
            % regression_calculator : shared(IRegressionCalculator)
            %   The regression calculator used to evaluate possible splits.
            % 
            % entropy_function : shared(IEntropyFunction)
            %   The entropy function used on the regression results.
            % 
            % gain_threshold : float >=0.f
            %   The minimum information gain a split has to achieve.
            % 
            % annotation_step : size_t >0
            %   The memory layout of sample annotations.
            % 
            % random_seed : uint >0
            %   The random seed.
            %   \returns A new RegressionThresholdOptimizer.
            if ~exist('gain_threshold', 'var') || gain_threshold == -1
                gain_threshold = 1E-7;
            end    
            if ~exist('annotation_step', 'var') || annotation_step == -1
                annotation_step = 1;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [1,2];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'RegressionThresholdOptimizer', tmp);
            ptr = calllib(this.LibName, getter, n_thresholds, regression_calculator.ClassifierPtr, entropy_function.ClassifierPtr, gain_threshold, annotation_step, random_seed);
            res = RegressionThresholdOptimizer(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = TwoSideClassificationThresholdOptimizer(this, use_fast_search_approximation, n_classes, gain_calculator, gain_threshold, annotation_step)
            % Class information:
            % ==================
            % 
            % Optimizes two sided classifcation thresholds very efficiently.
            % 
            % Supports only classification annotations (unsigned int) with annotation
            % values in {0, ..., n_classes - 1}.
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
            % - int; int; uint
            % - int; float; uint
            % - float; int; uint
            % - uint8_t; int; uint
            % - uint8_t; uint8_t; uint
            % - uint8_t; float; uint
            % - uint8_t; int16_t; uint
            % - float; float; uint
            % - double; double; uint
            % - uint8_t; int16_t; int16_t
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Standard constructor.
            % 
            % use_fast_search_approximation is an interesting option to speed up the
            % optimization process. In any case, the elements are sorted in
            % feature order. If use_fast_search_approximation is set to true, the
            % gain is only calculated at positions, where the currently considered
            % element is from a different class than the last one AND if the
            % feature value changed. The approximation does a greedy search,
            % whereas all threshold combinations are evaluated for exact search
            % (requires :math:`O(n^2)` time, where :math:`n` is n_examples)!
            % 
            % This is a true approximation (i.e. the optimal gain can be at a
            % position where the current element is from the same class than the
            % last), but this hardly ever occurs for the usual gain calculation
            % functions.
            % 
            % A necessary, but not sufficient criterion for the approximation to
            % be equal to the optimal value is the following:
            % Assuming the (weighted) histogram values at position :math:`k` are
            % :math:`k_{li}` for the left hand-side histogram and :math:`k_{ri}` for the
            % right hand-side histogram, :math:`i\in[0,n\_classes-1]`. Then the gain
            % function :math:`g(.)` must have the property
            % 
            % .. math::
            %   \forall j\forall k_{li},k_{ri}: g(\{k_{li}\},\{k_{ri}\})<
            % g(\{k_{li}\}_{i\backslash j}\cup\{k_{lj}+1\},
            % \{k_{ri}\}_{i\backslash j}\cup\{k_{rj}-1\}) \vee
            % g(\{k_{li}\}_{i\backslash j}\cup\{k_{lj}-1\},
            % \{k_{ri}\}_{i\backslash j}\cup\{k_{rj}+1\})
            % .
            % 
            % This does not hold in general, but for the standard information gain
            % based measures, cases where it doesn't hold occur very rarely and even
            % if so, the found positions aren't a lot worse than the theoretical
            % optimum.
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
            % use_fast_search_approximation : bool
            %   Behaviour as described above.
            % 
            % n_classes : size_t>1
            %   The number of classes in the data.
            % 
            % ent_calc : shared(IGainCalculator<float>)
            %   The gain calculator to use to estimate the gain.
            % 
            % gain_threshold : float>=0.f
            %   The minimum gain to accept a split as valid. Default: 1E-7f.
            % 
            % annotation_step : size_t>0
            %   The step size in memory for the annotations.
            if ~exist('gain_threshold', 'var') || gain_threshold == -1
                gain_threshold = 1E-7;
            end    
            if ~exist('annotation_step', 'var') || annotation_step == -1
                annotation_step = 1;
            end    
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'TwoSideClassificationThresholdOptimizer', tmp);
            ptr = calllib(this.LibName, getter, use_fast_search_approximation, n_classes, gain_calculator.ClassifierPtr, gain_threshold, annotation_step);
            res = TwoSideClassificationThresholdOptimizer(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ClassificationThresholdOptimizer(this, use_fast_search_approximation, n_classes, gain_calculator, gain_threshold, annotation_step)
            % Class information:
            % ==================
            % 
            % Optimizes one threshold very efficiently.
            % 
            % Supports only classification annotations (unsigned int) with annotation
            % values ranging in [0; n_classes - 1]. Searches the perfect threshold to
            % split the data.
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
            % - int; int; uint
            % - int; float; uint
            % - float; int; uint
            % - uint8_t; int; uint
            % - uint8_t; uint8_t; uint
            % - uint8_t; float; uint
            % - uint8_t; int16_t; uint
            % - float; float; uint
            % - double; double; uint
            % - uint8_t; int16_t; int16_t
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Standard constructor.
            % 
            % use_fast_search_approximation is an interesting option to speed up the
            % optimization process. In general, the elements are considered in sorted
            % feature order. If use_fast_search_approximation is set to true, the
            % gain is only calculated at positions, where the currently considered
            % element is from a different class than the last one AND if the
            % feature value changed.
            % 
            % This is a true approximation (i.e. the optimal gain can be at a
            % position where the current element is from the same class than the
            % last), but this hardly ever occurs for the usual gain calculation
            % functions.
            % 
            % A necessary, but not sufficient criterion for the approximation to
            % be equal to the optimal value is the following:
            % Assuming the (weighted) histogram values at position :math:`k` are
            % :math:`k_{li}` for the left hand-side histogram and :math:`k_{ri}` for the
            % right hand-side histogram, :math:`i\in[0,n\_classes-1]`. Then the gain
            % function :math:`g(.)` must have the property
            % 
            % .. math::
            %   \forall j\forall k_{li},k_{ri}: g(\{k_{li}\},\{k_{ri}\})<
            % g(\{k_{li}\}_{i\backslash j}\cup\{k_{lj}+1\},
            % \{k_{ri}\}_{i\backslash j}\cup\{k_{rj}-1\}) \vee
            % g(\{k_{li}\}_{i\backslash j}\cup\{k_{lj}-1\},
            % \{k_{ri}\}_{i\backslash j}\cup\{k_{rj}+1\})
            % .
            % 
            % This does not hold in general, but for the standard information gain
            % based measures, cases where it doesn't hold occur very rarely and even
            % if so, the found positions aren't a lot worse than the theoretical
            % optimum.
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
            % use_fast_search_approximation : bool
            %   Whether to use the approximation described above or not.
            % 
            % n_classes : size_t >1
            %   The number of classes. All annotations must be in [0, ..., n_classes[.
            % 
            % gain_calculator : IGainCalculator
            %   The gain calculator to estimate the gain at each split.
            % 
            % gain_threshold : float>=0f
            %   The minimum gain that must be reached to continue splitting. Default: 1E-7f.
            % 
            % annotation_step : size_t>0
            %   The memory step size for the annotation data. Default: 1.
            if ~exist('gain_threshold', 'var') || gain_threshold == -1
                gain_threshold = 1E-7;
            end    
            if ~exist('annotation_step', 'var') || annotation_step == -1
                annotation_step = 1;
            end    
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'ClassificationThresholdOptimizer', tmp);
            ptr = calllib(this.LibName, getter, use_fast_search_approximation, n_classes, gain_calculator.ClassifierPtr, gain_threshold, annotation_step);
            res = ClassificationThresholdOptimizer(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = AlternatingThresholdOptimizer(this, opt1, opt2, random_seed)
            % Class information:
            % ==================
            % 
            % Uses two other threshold optimizers and randomly selects one of them at each split.
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
            % - float; float; float
            % - double; double; double
            % - int; int; uint
            % - int; float; uint
            % - float; int; uint
            % - uint8_t; int; uint
            % - uint8_t; uint8_t; uint
            % - uint8_t; float; uint
            % - uint8_t; int16_t; uint
            % - float; float; uint
            % - double; double; uint
            % - uint8_t; int16_t; int16_t
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % opt1 : shared(IThresholdOptimizer)
            %   The first threshold optimizer to alternate in between.
            % 
            % opt2 : shared(IThresholdOptimizer)
            %   The second threshold optimizer to alternate in between.
            % 
            % random_seed : uint>0
            %   The random seed for the RNG. Default: 1.
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'AlternatingThresholdOptimizer', tmp);
            ptr = calllib(this.LibName, getter, opt1.ClassifierPtr, opt2.ClassifierPtr, random_seed);
            res = AlternatingThresholdOptimizer(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = EntropyGain(this, entropy_function)
            % Class information:
            % ==================
            % 
            % Calculates the gain as difference of current entropy and the
            % weighted sum of subgroup entropies.
            % 
            % Works correctly up to a total sum of elements of
            % min(numeric_limits<float>::max(), numeric_limits<input_dtype>::max())
            % and the limitations of the selected entropy function.
            % Speed optimized function that does no checks in release mode!
            % 
            % Parameters
            % ==========
            % 
            % input_dtype : The datatype for counting class members. This might
            %   be a float if sample weights are used.
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
            % Constructor:
            % ============
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
            % 
            % entropy_function : shared(IEntropyFunction<float>)
            %   The entropy to use for gain calculation.
            tmp = '_f';
            getter = sprintf('%s%s%s', 'get', 'EntropyGain', tmp);
            ptr = calllib(this.LibName, getter, entropy_function.ClassifierPtr);
            res = EntropyGain(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = DNNFeatureExtractor(this, use_cpu, device_id, net_layout_file, net_weights_file, net_outlayer, load_mean, mean_file)
            % Class information:
            % ==================
            % 
            % Extracts DNN features using a pretrained caffe network.
            % 
            % To obtain reproducible results, you have to remove the dropout layers
            % from the network specification file (this has been done for the default
            % AlexNet). During extraction, always the full batch size is used. This
            % means, that if you repeatedly only extract features from one image with
            % the extract method, most of the batch will be unused. You should observe
            % large speed gains by reducing the batch size in the model specification
            % file to a batch size of one in that case.
            % 
            % The mean image must be subtracted from any image before
            % using the feature extractor. This can be done within the `extract` method,
            % or, if you want to use many samples from an image, you can do that before.
            % The default mean image is the one of the ImageNet dataset. The mean image
            % format is a text file with a very simple layout:
            % 
            % 
            % - the first line consists of the number of rows,
            % - the second line consists of the columns,
            % - the third line consists of the number of channels,
            % - the fourth line contains all pixel values, in OpenCV memory layout
            % (rows, columns, channels, where channels are contiguous).
            % 
            % -----
            % 
            % Available in:
            % - C++
            % - Python
            % - Matlab
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Standard constructor.
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
            % use_cpu : bool
            %   Whether to only use the CPU or use the GPU. Default: false.
            % 
            % 
            % device_id : int>=0
            %   The CUDA device id. Only relevant, if `use_cpu` is false. Default: 0.
            % 
            % 
            % net_layout_file : string
            %   The protobuf file describing the network layout. Default: "".
            %   This reserved value is resolved to the path
            %   to the AlexNet installed to the directory specified during
            %   compilation as `--caffe-model-dir`.
            % 
            % 
            % net_weights_file : string
            %   Filename of the pretrained network weights file. Default: "".
            %   This reserved value is resolved to the
            %   AlexNet weights file installed to the directory specified during
            %   compilation as `--caffe-model-dir`.
            % 
            % 
            % net_outlayer : string
            %   The name of the blob and layer from which to read. Default: "pool5".
            % 
            % 
            % load_mean : bool
            %   If set to true, loads the mean image specified by `mean_file`.
            %   Default: true.
            % 
            % 
            % mean_file : string
            %   The filename of the mean image file to use. For a file
            %   format description, see the documentation of this class. Default: "".
            %   This reserved value is resolved to the ImageNet mean file installed
            %   to the `--caffe-model-dir`.
            if ~exist('use_cpu', 'var') || use_cpu == -1
                use_cpu = 0;
            end    
            if ~exist('device_id', 'var') || device_id == -1
                device_id = 0;
            end    
            if ~exist('net_layout_file', 'var') || net_layout_file == -1
                net_layout_file = '';
            end    
            if ~exist('net_weights_file', 'var') || net_weights_file == -1
                net_weights_file = '';
            end    
            if ~exist('net_outlayer', 'var') || net_outlayer == -1
                net_outlayer = '';
            end    
            if ~exist('load_mean', 'var') || load_mean == -1
                load_mean = 1;
            end    
            if ~exist('mean_file', 'var') || mean_file == -1
                mean_file = '';
            end    
            position_list = [];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'DNNFeatureExtractor', tmp);
            ptr = calllib(this.LibName, getter, use_cpu, device_id, net_layout_file, net_weights_file, net_outlayer, load_mean, mean_file);
            res = DNNFeatureExtractor(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = StandardFeatureSelectionProvider(this, n_selections_per_node, selection_dimension, how_many_available, max_to_use, random_seed)
            % Class information:
            % ==================
            % 
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
            % Constructor:
            % ============
            % 
            % Standard constructor.
            % 
            % Additional constraints on the methods arguments apply to guarantee good
            % random selection speed:
            % 
            % .. math::
            %   {{how\_many\_available}\choose{selection\_dimension}}\ge
            % n\_selections\_per\_node\cdot 2,
            % 
            % 
            % .. math::
            %   {{max\_to\_use}\choose{selection\_dimension}}\ge
            % n\_selections\_per\_node\cdot 2.
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
            % Parameters
            % ==========
            % 
            % n_selections_per_node : size_t>0
            %   How many selection proposals are created for each node.
            % 
            % selection_dimension : size_t>0
            %   How many data dimensions are selected per
            %   proposal. Must be > 0 and < how_many_available.
            % 
            % how_many_available : size_t>0
            %   How many data dimensions are available.
            % 
            % max_to_use : size_t
            %   How many data dimensions may be used. If set to zero, use how_many_available.
            %   Default: 0.
            % 
            % random_seed : uint>0
            %   A random seed for the random number generator. Must
            %   be greater than 0. Default: 1.
            if ~exist('max_to_use', 'var') || max_to_use == -1
                max_to_use = 0;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'StandardFeatureSelectionProvider', tmp);
            ptr = calllib(this.LibName, getter, n_selections_per_node, selection_dimension, how_many_available, max_to_use, random_seed);
            res = StandardFeatureSelectionProvider(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = DifferenceSurfaceCalculator(this)
            % Class information:
            % ==================
            % 
            % Calculates a feature as the difference between two data dimensions
            % of inputs.
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
            % - int; int; uint
            % - uint8_t; int16_t; uint
            % - float; float; uint
            % - float; float; float
            % - double; double; uint
            % - double; double; double
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'DifferenceSurfaceCalculator', tmp);
            ptr = calllib(this.LibName, getter);
            res = DifferenceSurfaceCalculator(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = VolumeFeatureSelectionProvider(this, selection_dimension, size_x, size_y, size_z, how_many_per_node, random_seed)
            % Class information:
            % ==================
            % 
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
            % Constructor:
            % ============
            % 
            % Standard constructor.
            % 
            % Additional constraints on the methods arguments apply to guarantee good
            % random selection speed:
            % 
            % .. math::
            %   {{how\_many\_available}\choose{selection\_dimension}}\ge
            % n\_selections\_per\_node\cdot 2,
            % 
            % 
            % .. math::
            %   {{max\_to\_use}\choose{selection\_dimension}}\ge
            % n\_selections\_per\_node\cdot 2.
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
            % Parameters
            % ==========
            % 
            % selection_dimension : size_t>0
            %   How many data dimensions are selected per
            %   proposal. Must be > 0 and <= size_x*size_y*size_z.
            % 
            % size_x : size_t>0
            %   Horizontal patch size.
            % 
            % size_y : size_t>0
            %   Vertical patch size.
            % 
            % size_z : size_t>0
            %   Patch depth.
            % 
            % how_many_per_node : size_t>0
            %   How many selection proposals are created for each node.
            % 
            % random_seed : A random seed for the random number generator. Must
            %   be greater than 0.
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'VolumeFeatureSelectionProvider', tmp);
            ptr = calllib(this.LibName, getter, selection_dimension, size_x, size_y, size_z, how_many_per_node, random_seed);
            res = VolumeFeatureSelectionProvider(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = LinearSurfaceCalculator(this, n_params_per_feat_sel, n_comb_dims, random_seed)
            % Class information:
            % ==================
            % 
            % Calculates a feature as linear combination of inputs.
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
            % - int; uint
            % - uint8_t; uint
            % - float; uint
            % - float; float
            % - double; double
            % - double; uint
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % n_params_per_feat_sel : size_t>0
            %   The number of linear configurations to evaluate per feature selection.
            % 
            % n_comb_dims : size_t>0
            %   The dimensionality of the linear surface. Default: 2.
            % 
            % random_seed : uint>0
            %   Seed for the RNG. Default: 1.
            if ~exist('n_comb_dims', 'var') || n_comb_dims == -1
                n_comb_dims = 2;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'LinearSurfaceCalculator', tmp);
            ptr = calllib(this.LibName, getter, n_params_per_feat_sel, n_comb_dims, random_seed);
            res = LinearSurfaceCalculator(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = DirectPatchDifferenceSurfCalculator(this, psx, psy, psz, luc)
            % Class information:
            % ==================
            % 
            % Calculates a feature as the difference between two data dimensions
            % of inputs.
            % 
            % In contrast to the DifferenceSurfaceCalculator, works with patches
            % in images directly. It only works together with a SubsamplingDataProvider
            % with a NoCopyPatchSampleManager, because they provide the images
            % in the correct format.
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
            % - uint8_t; int16_t; uint
            % - uint8_t; int16_t; int16_t
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % psx : size_t>0
            %   Horizontal patch size.
            % 
            % psy : size_t>0
            %   Vertical patch size.
            % 
            % psz : size_t>0
            %   Patch depth.
            % 
            % luc : bool
            %   Whether the Left Upper Corner of a patch is used when specifying
            %   positions or its center.
            position_list = [1,2,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'DirectPatchDifferenceSurfCalculator', tmp);
            ptr = calllib(this.LibName, getter, psx, psy, psz, luc);
            res = DirectPatchDifferenceSurfCalculator(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = AlignedSurfaceCalculator(this)
            % Class information:
            % ==================
            % 
            % Forwards the data as features.
            % 
            % Does not require any parameters.
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
            % - int; uint
            % - uint8_t; uint
            % - float; uint
            % - float; float
            % - double; uint
            % - double; double
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'AlignedSurfaceCalculator', tmp);
            ptr = calllib(this.LibName, getter);
            res = AlignedSurfaceCalculator(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = QuadraticSurfaceCalculator(this, n_params_per_feat_sel, min_max_vals, random_seed)
            % Class information:
            % ==================
            % 
            % Calculates a feature as the response value of a quadratic
            % surface (see CriminisiShotton 2013, p. 15). Currently only supports two
            % feature dimensions.
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
            % - int; uint
            % - uint8_t; uint
            % - float; uint
            % - float; float
            % - double; uint
            % - double; double
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % n_params_per_feat_sel : size_t>0
            %   The number of surfaces to evaluate per feature selection.
            % 
            % min_max_vals : vector<float>
            %   The relevant range for each feature dimension.
            % 
            % random_seed : uint>0
            %   Seed for the RNG.
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'QuadraticSurfaceCalculator', tmp);
            ptr = calllib(this.LibName, getter, n_params_per_feat_sel, min_max_vals, random_seed);
            res = QuadraticSurfaceCalculator(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ClassificationLeafManager(this, n_classes)
            % Class information:
            % ==================
            % 
            % Stores the probability distributions for n_classes at a leaf.
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
            % - int; uint
            % - float; uint
            % - double; uint
            % - uint8_t; uint
            % - uint8_t; int16_t
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % n_classes : uint>1
            %   The number of classes.
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'ClassificationLeafManager', tmp);
            ptr = calllib(this.LibName, getter, n_classes);
            res = ClassificationLeafManager(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = HoughLeafManager(this, n_classes, annot_dim)
            % Class information:
            % ==================
            % 
            % Stores the offset vectors for positive samples and their
            % probabilities in the leafs.
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
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % n_classes : uint>1
            %   The number of classes. Currently only 2 are supported. Default: 2.
            % 
            % annot_dim : size_t>0
            %   The number of offset dimensions. Default: 2.
            if ~exist('n_classes', 'var') || n_classes == -1
                n_classes = 2;
            end    
            if ~exist('annot_dim', 'var') || annot_dim == -1
                annot_dim = 2;
            end    
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'HoughLeafManager', tmp);
            ptr = calllib(this.LibName, getter, n_classes, annot_dim);
            res = HoughLeafManager(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = RegressionLeafManager(this, selection_provider, n_valids_to_use, regression_calculator, entropy_function, use_fallback_constant_regression, num_threads, summary_mode)
            % Class information:
            % ==================
            % 
            % Manages the leaf nodes of regression trees.
            % 
            % This leaf manager creates leaf nodes and stores a probabilistic regression model at each leaf.
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
            % - double
            % 
            % 
            % -----
            % 
            % Constructor:
            % ============
            % 
            % Constructor for a RegressionLeafManager
            % 
            % Costructs a RegressionLeafManager.
            % For each leaf, a number of dimension selections used as regressors is asessed.
            % The selection resulting in the regression model with the lowest entropy is used.
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
            % selection_provider : ISelectionProvider
            %   Selection provider creating random feature selections.
            %   It specifies, how many regressors are used.
            % 
            % n_valids_to_use : size_t>0
            %   How many valid selections are asessed, until the selection process is
            %   stopped.
            % 
            % regression_calculator : IRegressionCalculator
            %   The regression calculator that is used to generate a regression model for each leaf.
            % 
            % entropy_function : IEntropyFunction
            %   The entropy function used to evaluate the regression models.
            % 
            % use_fallback_constant_regression : bool
            %   When no valid dimension selections can be found and this flag is set to true,
            %   a ConstantRegressionCalculator (independent from regressor selections) is used instead.
            %   Otherwise, this case results in a runtime exception. Default: false.
            % 
            % num_threads : int>0
            %   The number of threads used when evaluating different selections.
            %   Default: 1.
            % 
            % summary_mode : uint<3
            %   Determines the meaning of the values in the 2D prediction matrix of
            %   a forest (the output of the convenience `predict` method of a forest).
            %   Case 0: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the expected variances for each
            %   regressor (second half of its entries). To estimate the joint
            %   variance, a gaussian is fitted over the multimodal distribution
            %   defined by all trees.
            %   Case 1: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the mean of the expected variances of
            %   each tree. This has no direct semantic meaning, but can give
            %   better results in active learning applications.
            %   Case 2: Each row contains the prediction for each regressor and
            %   the variance estimate for each regressor for each tree, e.g.,
            %   (r11, r12, v11, v12, r21, r22, v21, v22, ...), with `r` and `v`
            %   denoting regressor prediction and variance respectively, the
            %   first index the tree and the second index the regressor index.
            %   \returns A new RegressionLeafManager.
            if ~exist('use_fallback_constant_regression', 'var') || use_fallback_constant_regression == -1
                use_fallback_constant_regression = 0;
            end    
            if ~exist('num_threads', 'var') || num_threads == -1
                num_threads = 1;
            end    
            if ~exist('summary_mode', 'var') || summary_mode == -1
                summary_mode = 0;
            end    
            position_list = [1];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'RegressionLeafManager', tmp);
            ptr = calllib(this.LibName, getter, selection_provider.ClassifierPtr, n_valids_to_use, regression_calculator.ClassifierPtr, entropy_function.ClassifierPtr, use_fallback_constant_regression, num_threads, summary_mode);
            res = RegressionLeafManager(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = BoostingLeafManager(this, n_classes)
            % Class information:
            % ==================
            % 
            % Allows the boosting strategies to set their own tree functions to influence the combined result.
            % 
            % Using thes LeafManager may lead to better classifcation results.
            % 
            % Note that the output does not represent probabilites and may vary when using different IBoostingStrategies
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
            % - int; uint
            % - float; uint
            % - double; uint
            % - uint8_t; uint
            % - uint8_t; int16_t
            % 
            % Serialization generation: 101
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % n_classes : uint>1
            %   The number of classes.
            position_list = [1,3];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'BoostingLeafManager', tmp);
            ptr = calllib(this.LibName, getter, n_classes);
            res = BoostingLeafManager(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = AdaBoost(this)
            % Class information:
            % ==================
            % 
            % AdaBoost.M2 boosting algorithm implementation
            % 
            % Implements the original AdaBoost algorithm proposed by Freund and Schapire
            % 
            % See "A decision-theoretic generalization of on-line learning and an application to boosting". Journal of Computer and System Sciences 55. 1997
            % 
            % To support multi-class classification, the AdaBoost.M2 algorithm is used
            % 
            % Output when using BoostingLeafManager is estimator_probability*std::log(1.f/beta)
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
            % 
            % Serialization generation: 101
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'AdaBoost', tmp);
            ptr = calllib(this.LibName, getter);
            res = AdaBoost(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = Samme_R(this, learning_rate)
            % Class information:
            % ==================
            % 
            % SAMME.R real boosting algorithm implementation
            % 
            % Implements the SAMME.R real boosting algorithm proposed by J. Zhu, H. Zou, S. Rosset and T. Hastie
            % 
            % See Zhu, H. Zou, S. Rosset, T. Hastie, "Multi-class AdaBoost", 2009
            % 
            % One can set the learning rate which specifies the contribution of each classifier
            % 
            % Output when using BoostingLeafManager is log(p_k^m(x))-1/K*sum_k(log(p_k^m(x)))
            % 
            % with x the sample to classify, K the number of classes, k the classIndex, m the estimatorIndex and p the estimator probability
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
            % 
            % Serialization generation: 101
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            if ~exist('learning_rate', 'var') || learning_rate == -1
                learning_rate = 1;
            end    
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'Samme_R', tmp);
            ptr = calllib(this.LibName, getter, learning_rate);
            res = Samme_R(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = Samme(this, learning_rate)
            % Class information:
            % ==================
            % 
            % SAMME boosting algorithm implementation
            % 
            % Implements the SAMME boosting algorithm proposed by J. Zhu, H. Zou, S. Rosset and T. Hastie
            % 
            % See Zhu, H. Zou, S. Rosset, T. Hastie, "Multi-class AdaBoost", 2009
            % 
            % One can set the learning rate which specifies the contribution of each classifier
            % 
            % Output when using BoostingLeafManager is estimator_probability*estimator_weight
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
            % 
            % Serialization generation: 101
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            if ~exist('learning_rate', 'var') || learning_rate == -1
                learning_rate = 1;
            end    
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'Samme', tmp);
            ptr = calllib(this.LibName, getter, learning_rate);
            res = Samme(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = ClassicTraining(this, bagging_strategy)
            % Class information:
            % ==================
            % 
            % Implements the vanilla decision forest training.
            % 
            % Trains all trees independent of each other as allowed by the
            % IExecutionStrategy, possibly exploiting parallelism, etc.
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
            % Constructor:
            % ============
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
            % bagging_strategy : IBagginStrategy
            %   The bagging strategy to use to distribute samples amongst trees.
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'ClassicTraining', tmp);
            ptr = calllib(this.LibName, getter, bagging_strategy.ClassifierPtr);
            res = ClassicTraining(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = BoostedTraining(this, boosting_strategy)
            % Class information:
            % ==================
            % 
            % Implements a boosted training that uses a boosting implementation defined by an IBoostingStrategy
            % 
            % Trains all trees using a given boosting algorithm implementation
            % Use a BoostingLeafManager to let the boosting strategies decide their weight functions
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
            % 
            % Serialization generation: 101
            % 
            % -----
            % 
            % Constructor:
            % ============
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
            % bagging_strategy : IBagginStrategy
            %   The bagging strategy to use to distribute samples amongst trees.
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', this.getDataTypes(i));
            end
            getter = sprintf('%s%s%s', 'get', 'BoostedTraining', tmp);
            ptr = calllib(this.LibName, getter, boosting_strategy.ClassifierPtr);
            res = BoostedTraining(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = StandardClassificationForest (this, n_classes, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, n_trees, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, threshold_optimization_threads)
            % Constructs a default decision forest for classification.
            % 
            % The forest uses axis-aligned threshold deciders. The default values for
            % each of the parameters lead to the parameter choice by various
            % heuristics. The results should be similar to those of the
            % ClassificationForest object of scikit-learn.
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
            % - int
            % - float
            % - double
            % - uint8_t
            % 
            % Exported name: StandardClassificationForest
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % n_classes : uint>1
            %   The number of classes. All annotation labels must be in
            %   [0, ..., n_classes[.
            % 
            % n_features : size_t>0
            %   The number of features available.
            % 
            % max_depth : uint>=0
            %   The maximum tree depth. If 0, it is set to UINT_MAX to allow for
            %   maximally large trees. Default: 0.
            % 
            % test_n_features_per_node : size_t>=0
            %   The number of features to evaluate as split criteria at each tree
            %   node. If 0, it is set to sqrt(n_features). Default: 0.
            % 
            % n_thresholds_per_features : size_t>=0
            %   The number of thresholds to evaluate per feature. If set to zero,
            %   search for the perfect split. Default: 0.
            % 
            % n_trees : uint>1
            %   The number of trees to use. Default: 10.
            % 
            % min_samples_per_leaf : uint>0
            %   The minimum number of samples at a leaf node.  Default: 1.
            % 
            % min_samples_per_split : uint>2*min_samples_per_leaf
            %   The minimum number of samples to continue splitting. Default: 2.
            % 
            % min_gain_threshold
            %   The minimum gain that must be reached to continue splitting. Default: 1E-7.
            % 
            % allow_redraw : bool
            %   If set to true, allows to try a new feature when optimizing for a
            %   split, when for a feature no split could be found that satisfied
            %   the minimum number of samples per leaf for each subgroup. This may be
            %   done until all features have been checked. Default: true.
            % 
            % random_seed : uint>=1
            %   The random seed to initialize the RNG. Default: 1.
            % 
            % entropy_name : string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
            %   The entropy type to use. For the specification of induced entropy,
            %   see the "Publications" page. Default: 'induced'.
            % 
            % entropy_p1 : float
            %   The entropy parameter. Might be unused (e.g. for the Shannon entropy).
            %   Default: 2.
            % 
            % threshold_optimization_threads : uint>0
            %   The number of threads to use for threshold optimization. Default: 1.
            if ~exist('max_depth', 'var') || max_depth == -1
                max_depth = 0;
            end    
            if ~exist('test_n_features_per_node', 'var') || test_n_features_per_node == -1
                test_n_features_per_node = 0;
            end    
            if ~exist('n_thresholds_per_feature', 'var') || n_thresholds_per_feature == -1
                n_thresholds_per_feature = 0;
            end    
            if ~exist('n_trees', 'var') || n_trees == -1
                n_trees = 10;
            end    
            if ~exist('min_samples_per_leaf', 'var') || min_samples_per_leaf == -1
                min_samples_per_leaf = 1;
            end    
            if ~exist('min_samples_per_split', 'var') || min_samples_per_split == -1
                min_samples_per_split = 2;
            end    
            if ~exist('min_gain_threshold', 'var') || min_gain_threshold == -1
                min_gain_threshold = 1E-7;
            end    
            if ~exist('allow_redraw', 'var') || allow_redraw == -1
                allow_redraw = 1;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            if ~exist('entropy_name', 'var') || entropy_name == -1
                entropy_name = 'induced';
            end    
            if ~exist('entropy_p1', 'var') || entropy_p1 == -1
                entropy_p1 = 2;
            end    
            if ~exist('threshold_optimization_threads', 'var') || threshold_optimization_threads == -1
                threshold_optimization_threads = 1;
            end    
            suffix = strcat('_', this.inp_str);
            getter = sprintf('%s%s', 'StandardClassificationForest', suffix);
            ptr = calllib(this.LibName, getter, n_classes, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, n_trees, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, threshold_optimization_threads);

            res = Forest(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = StandardClassificationTree (this, n_classes, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, threshold_optimization_threads)
            % Constructs a default decision tree for classification.
            % 
            % It uses an axis aligned decider.
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
            % - int
            % - float
            % - double
            % - uint8_t
            % 
            % Exported name: StandardClassificationTree
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % n_classes : uint>1
            %   The number of classes. All annotation labels must be in
            %   [0, ..., n_classes[.
            % 
            % n_features : size_t>0
            %   The number of features available.
            % 
            % max_depth : uint>=0
            %   The maximum tree depth. If 0, it is set to UINT_MAX to allow for
            %   maximally large trees. Default: 0.
            % 
            % test_n_features_per_node : size_t>=0
            %   The number of features to evaluate as split criteria at each tree
            %   node. If 0, it is set to sqrt(n_features). Default: 0.
            % 
            % n_thresholds_per_feature : size_t>=0
            %   The number of thresholds to evaluate per feature. If set to zero,
            %   search for the perfect split. Default: 0.
            % 
            % min_samples_per_leaf : uint>0
            %   The minimum number of samples at a leaf node. Default: 1.
            % 
            % min_samples_per_split : uint>2*min_samples_per_leaf
            %   The minimum number of samples to continue splitting. Default: 2.
            % 
            % min_gain_threshold
            %   The minimum gain that must be reached to continue splitting. Default: 1E-7.
            % 
            % allow_redraw : bool
            %   If set to true, allows to try a new feature when optimizing for a
            %   split, when for a feature no split could be found that satisfied
            %   the minimum number of samples per leaf for each subgroup. This may be
            %   done until all features have been checked. Default: true.
            % 
            % random_seed : uint>=1
            %   The random seed to initialize the RNG. Default: 1.
            % 
            % entropy_name : string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
            %   The entropy type to use. For the specification of induced entropy,
            %   see the "Publications" page. Default: 'induced'.
            % 
            % entropy_p1 : float
            %   The entropy parameter. Might be unused (e.g. for the Shannon entropy).
            %   Default: 2.
            % 
            % threshold_optimization_threads : uint>0
            %   The number of threads to use for threshold optimization. Default: 1.
            if ~exist('max_depth', 'var') || max_depth == -1
                max_depth = 0;
            end    
            if ~exist('test_n_features_per_node', 'var') || test_n_features_per_node == -1
                test_n_features_per_node = 0;
            end    
            if ~exist('n_thresholds_per_feature', 'var') || n_thresholds_per_feature == -1
                n_thresholds_per_feature = 0;
            end    
            if ~exist('min_samples_per_leaf', 'var') || min_samples_per_leaf == -1
                min_samples_per_leaf = 1;
            end    
            if ~exist('min_samples_per_split', 'var') || min_samples_per_split == -1
                min_samples_per_split = 2;
            end    
            if ~exist('min_gain_threshold', 'var') || min_gain_threshold == -1
                min_gain_threshold = 1E-7;
            end    
            if ~exist('allow_redraw', 'var') || allow_redraw == -1
                allow_redraw = 1;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            if ~exist('entropy_name', 'var') || entropy_name == -1
                entropy_name = 'induced';
            end    
            if ~exist('entropy_p1', 'var') || entropy_p1 == -1
                entropy_p1 = 2;
            end    
            if ~exist('threshold_optimization_threads', 'var') || threshold_optimization_threads == -1
                threshold_optimization_threads = 1;
            end    
            suffix = strcat('_', this.inp_str);
            getter = sprintf('%s%s', 'StandardClassificationTree', suffix);
            ptr = calllib(this.LibName, getter, n_classes, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, threshold_optimization_threads);

            res = Tree(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = FastRegressionForest (this, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, n_trees, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, numerical_zero_threshold, threshold_optimization_threads, summary_mode)
            % Constructs a fast decision forest for regression.
            % 
            % It uses an axis aligned decider and uses constant regression at split
            % and linear regression at leaf nodes.
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
            % - double
            % 
            % Exported name: FastRegressionForest
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % n_features : size_t>0
            %   The number of features available.
            % 
            % max_depth : uint>=0
            %   The maximum tree depth. If 0, it is set to UINT_MAX to allow for
            %   maximally large trees. Default: 0.
            % 
            % test_n_features_per_node : size_t>=0
            %   The number of features to evaluate as split criteria at each tree
            %   node. If 0, it is set to sqrt(n_features). Default: 0.
            % 
            % n_thresholds_per_feature : size_t>0
            %   The number of thresholds to evaluate per feature. Default: 10.
            % 
            % n_trees : size_t>1
            %   The number of trees. Default: 10.
            % 
            % min_samples_per_leaf : uint>0
            %   The minimum number of samples at a leaf node.  Default: 3.
            % 
            % min_samples_per_split : uint>2*min_samples_per_leaf
            %   The minimum number of samples to continue splitting. Default: 6.
            % 
            % min_gain_threshold
            %   The minimum gain that must be reached to continue splitting. Default: 1E-7.
            % 
            % allow_redraw : bool
            %   If set to true, allows to try a new feature when optimizing for a
            %   split, when for a feature no split could be found that satisfied
            %   the minimum number of samples per leaf for each subgroup. This may be
            %   done until all features have been checked. Default: true.
            % 
            % random_seed : uint>=1
            %   The random seed to initialize the RNG. Default: 1.
            % 
            % entropy_name : string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
            %   The entropy type to use. For the specification of induced entropy,
            %   see the "Publications" page. Default: 'shannon'.
            % 
            % entropy_p1 : float
            %   The entropy parameter. Might be unused (e.g. for the Shannon entropy).
            %   Default: 1E-7.
            % 
            % numerical_zero_threshold : float>=0.f || -1.f
            %   The threshold below of which all values are treated as zeros.
            %   If set to -1.f, use the value suggested by Eigen. Default: -1.f.
            % 
            % threshold_optimization_threads : uint>0
            %   The number of threads to use for threshold optimization. Default: 1.
            % 
            % summary_mode : uint<3
            %   Determines the meaning of the values in the prediction matrix of
            %   the forest (the output of the convenience `predict` method of a forest).
            %   Case 0: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the expected variances for each
            %   regressor (second half of its entries). To estimate the joint
            %   variance, a gaussian is fitted over the multimodal distribution
            %   defined by all trees.
            %   Case 1: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the mean of the expected variances of
            %   each tree. This has no direct semantic meaning, but can give
            %   better results in active learning applications.
            %   Case 2: Each row contains the prediction for each regressor and
            %   the variance estimate for each regressor for each tree, e.g.,
            %   (r11, r12, v11, v12, r21, r22, v21, v22, ...), with `r` and `v`
            %   denoting regressor prediction and variance respectively, the
            %   first index the tree and the second index the regressor index.
            %   Default: 0.
            if ~exist('max_depth', 'var') || max_depth == -1
                max_depth = 0;
            end    
            if ~exist('test_n_features_per_node', 'var') || test_n_features_per_node == -1
                test_n_features_per_node = 0;
            end    
            if ~exist('n_thresholds_per_feature', 'var') || n_thresholds_per_feature == -1
                n_thresholds_per_feature = 10;
            end    
            if ~exist('n_trees', 'var') || n_trees == -1
                n_trees = 10;
            end    
            if ~exist('min_samples_per_leaf', 'var') || min_samples_per_leaf == -1
                min_samples_per_leaf = 3;
            end    
            if ~exist('min_samples_per_split', 'var') || min_samples_per_split == -1
                min_samples_per_split = 6;
            end    
            if ~exist('min_gain_threshold', 'var') || min_gain_threshold == -1
                min_gain_threshold = 1E-7;
            end    
            if ~exist('allow_redraw', 'var') || allow_redraw == -1
                allow_redraw = 1;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            if ~exist('entropy_name', 'var') || entropy_name == -1
                entropy_name = 'shannon';
            end    
            if ~exist('entropy_p1', 'var') || entropy_p1 == -1
                entropy_p1 = 2;
            end    
            if ~exist('numerical_zero_threshold', 'var') || numerical_zero_threshold == -1
                numerical_zero_threshold = -1;
            end    
            if ~exist('threshold_optimization_threads', 'var') || threshold_optimization_threads == -1
                threshold_optimization_threads = 1;
            end    
            if ~exist('summary_mode', 'var') || summary_mode == -1
                summary_mode = 0;
            end    
            suffix = strcat('_', this.inp_str);
            getter = sprintf('%s%s', 'FastRegressionForest', suffix);
            ptr = calllib(this.LibName, getter, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, n_trees, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, numerical_zero_threshold, threshold_optimization_threads, summary_mode);

            res = Forest(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = FastRegressionTree (this, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, numerical_zero_threshold, threshold_optimization_threads, summary_mode)
            % Constructs a fast decision tree for regression.
            % 
            % It uses an axis aligned decider and uses constant regression at split
            % and linear regression at leaf nodes.
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
            % - double
            % 
            % Exported name: FastRegressionTree
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % n_features : size_t>0
            %   The number of features available.
            % 
            % max_depth : uint>=0
            %   The maximum tree depth. If 0, it is set to UINT_MAX to allow for
            %   maximally large trees.
            % 
            % test_n_features_per_node : size_t>=0
            %   The number of features to evaluate as split criteria at each tree
            %   node. If 0, it is set to sqrt(n_features). Default: 0.
            % 
            % n_thresholds_per_feature : size_t>0
            %   The number of thresholds to evaluate per feature. Default: 10.
            % 
            % min_samples_per_leaf : uint>0
            %   The minimum number of samples at a leaf node.  Default: 3.
            % 
            % min_samples_per_split : uint>2*min_samples_per_leaf
            %   The minimum number of samples to continue splitting. Default: 6.
            % 
            % min_gain_threshold
            %   The minimum gain that must be reached to continue splitting. Default: 1E-7.
            % 
            % allow_redraw : bool
            %   If set to true, allows to try a new feature when optimizing for a
            %   split, when for a feature no split could be found that satisfied
            %   the minimum number of samples per leaf for each subgroup. This may be
            %   done until all features have been checked. Default: true.
            % 
            % random_seed : uint>=1
            %   The random seed to initialize the RNG. Default: 1.
            % 
            % entropy_name : string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
            %   The entropy type to use. For the specification of induced entropy,
            %   see the "Publications" page. Default: 'shannon'.
            % 
            % entropy_p1 : float
            %   The entropy parameter. Might be unused (e.g. for the Shannon entropy).
            %   Default: 2.
            % 
            % numerical_zero_threshold : float>=0.f || -1.f
            %   The threshold below of which all values are treated as zeros.
            %   If set to -1.f, use the value suggested by Eigen. Default: -1.f.
            % 
            % threshold_optimization_threads : uint>0
            %   The number of threads to use for threshold optimization. Default: 1.
            % 
            % summary_mode : uint<3
            %   Determines the meaning of the values in the prediction matrix of
            %   the forest (the output of the convenience `predict` method of a forest).
            %   Case 0: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the expected variances for each
            %   regressor (second half of its entries). To estimate the joint
            %   variance, a gaussian is fitted over the multimodal distribution
            %   defined by all trees.
            %   Case 1: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the mean of the expected variances of
            %   each tree. This has no direct semantic meaning, but can give
            %   better results in active learning applications.
            %   Case 2: Each row contains the prediction for each regressor and
            %   the variance estimate for each regressor for each tree, e.g.,
            %   (r11, r12, v11, v12, r21, r22, v21, v22, ...), with `r` and `v`
            %   denoting regressor prediction and variance respectively, the
            %   first index the tree and the second index the regressor index.
            %   Default: 0.
            if ~exist('max_depth', 'var') || max_depth == -1
                max_depth = 0;
            end    
            if ~exist('test_n_features_per_node', 'var') || test_n_features_per_node == -1
                test_n_features_per_node = 0;
            end    
            if ~exist('n_thresholds_per_feature', 'var') || n_thresholds_per_feature == -1
                n_thresholds_per_feature = 10;
            end    
            if ~exist('min_samples_per_leaf', 'var') || min_samples_per_leaf == -1
                min_samples_per_leaf = 3;
            end    
            if ~exist('min_samples_per_split', 'var') || min_samples_per_split == -1
                min_samples_per_split = 6;
            end    
            if ~exist('min_gain_threshold', 'var') || min_gain_threshold == -1
                min_gain_threshold = 1E-7;
            end    
            if ~exist('allow_redraw', 'var') || allow_redraw == -1
                allow_redraw = 1;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            if ~exist('entropy_name', 'var') || entropy_name == -1
                entropy_name = 'shannon';
            end    
            if ~exist('entropy_p1', 'var') || entropy_p1 == -1
                entropy_p1 = 2;
            end    
            if ~exist('numerical_zero_threshold', 'var') || numerical_zero_threshold == -1
                numerical_zero_threshold = -1;
            end    
            if ~exist('threshold_optimization_threads', 'var') || threshold_optimization_threads == -1
                threshold_optimization_threads = 1;
            end    
            if ~exist('summary_mode', 'var') || summary_mode == -1
                summary_mode = 0;
            end    
            suffix = strcat('_', this.inp_str);
            getter = sprintf('%s%s', 'FastRegressionTree', suffix);
            ptr = calllib(this.LibName, getter, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, numerical_zero_threshold, threshold_optimization_threads, summary_mode);

            res = Tree(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = StandardHoughTree (this, patch_dimensions, n_thresholds_per_split, n_splits_per_node, max_depth, min_sample_counts, random_seed, min_gain_thresholds, patch_annot_luc, allow_redraw, num_threads, entropy_names, entropy_p1, use_hough_heuristic, hough_heuristic_ratio, hough_heuristic_maxd)
            % Constructs a default Hough tree.
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
            % - uint8_t; int16_t; int16_t
            % 
            % Exported name: StandardHoughTree
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % patch_dimensions : vector<size_t>0>, three elements
            %   The patch size in x, y, z.
            % 
            % n_thresholds_per_split : size_t>=0
            %   The number of thresholds to evaluate per feature.
            % 
            % n_splits_per_node : size_t>0
            %   The number of features to evaluate as split criteria at each tree
            %   node.
            % 
            % max_depth : uint>=0
            %   The maximum tree depth. If 0, it is set to UINT_MAX to allow for
            %   maximally large trees.
            % 
            % min_sample_counts : vector<uint>0>, two elements.
            %   The min samples per leaf, and min samples per split. The second value
            %   must be >= 2 * the first value.
            % 
            % random_seed : uint>=1
            %   The random seed to initialize the RNG.
            % 
            % min_gain_thresholds : vector<float>=0.f>, two elements.
            %   The minimum gains for classification and regression.
            % 
            % patch_annot_luc : bool
            %   Whether the patch annotations contain patch position for the patch
            %   left upper corner or patch center. Default: false.
            % 
            % allow_redraw : bool
            %   If set to true, allows to try a new feature when optimizing for a
            %   split, when for a feature no split could be found that satisfied
            %   the minimum number of samples per leaf for each subgroup. This may be
            %   done until all features have been checked. Default: true.
            % 
            % num_threads : uint>0
            %   The number of threads to use for optimizing the split nodes.
            %   Default: 1.
            % 
            % entropy_names : vector<string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]>, two elements.
            %   The entropy type to use for classification and regression.
            %   Default: ["shannon", "shannon"]
            % 
            % entropy_p1 : vector<float>0.f>, two elements.
            %   The entropy parameters. Might be unused (e.g. for the Shannon entropy).
            %   Default: [2, 2]
            % 
            % use_hough_heuristic : bool
            %   Whether or not to use a heuristic for hough
            %   forests introduced by Juergen Gall
            %   (http://www.vision.ee.ethz.ch/~gallju/projects/houghforest/houghforest.html)
            %   Can be used only with an AlternatingThresholdOptimizer.
            %   If used, the AlternatingThresholdOptimizer will guaranteed
            %   use opt2 if the ratio of negative samples is < hough_heuristic_ratio or
            %   depth >= hough_heuristic_maxd. opt2 must be a
            %   VarianceClassificationThresholdOptimizer (check this
            %   manually!). Default: true.
            % 
            % hough_heuristic_ratio : float>=0.f
            %   Default: 0.05f.
            % 
            % hough_heuristic_maxd : uint
            %   Default: 0.
            if ~exist('patch_annot_luc', 'var') || patch_annot_luc == -1
                patch_annot_luc = 0;
            end    
            if ~exist('allow_redraw', 'var') || allow_redraw == -1
                allow_redraw = 1;
            end    
            if ~exist('num_threads', 'var') || num_threads == -1
                num_threads = 1;
            end    
            if ~exist('entropy_names', 'var') || entropy_names == -1
                entropy_names = Soil.DEFAULT_ENTROPY_VEC_2;
            end    
            tmp_entropy_names = StringVector();
            for tmp_entropy_names_idx = 1:length(entropy_names)
              tmp_entropy_names.append(entropy_names{tmp_entropy_names_idx});
            end
            entropy_names = tmp_entropy_names.ClassifierPtr;
            if ~exist('entropy_p1', 'var') || entropy_p1 == -1
                entropy_p1 = Soil.DEFAULT_ENTROPY_P1_2;
            end    
            if ~exist('use_hough_heuristic', 'var') || use_hough_heuristic == -1
                use_hough_heuristic = 1;
            end    
            if ~exist('hough_heuristic_ratio', 'var') || hough_heuristic_ratio == -1
                hough_heuristic_ratio = 0.05;
            end    
            if ~exist('hough_heuristic_maxd', 'var') || hough_heuristic_maxd == -1
                hough_heuristic_maxd = 0;
            end    
            suffix = strcat('_', this.inp_str, '_', this.feat_str, '_', this.ann_str);
            getter = sprintf('%s%s', 'StandardHoughTree', suffix);
            ptr = calllib(this.LibName, getter, patch_dimensions, n_thresholds_per_split, n_splits_per_node, max_depth, min_sample_counts, random_seed, min_gain_thresholds, patch_annot_luc, allow_redraw, num_threads, entropy_names, entropy_p1, use_hough_heuristic, hough_heuristic_ratio, hough_heuristic_maxd);

            res = Tree(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = StandardRegressionForest (this, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, n_trees, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, numerical_zero_threshold, threshold_optimization_threads, summary_mode)
            % Constructs a default decision forest for regression.
            % 
            % It uses an axis aligned decider and uses linear regression at split
            % and leaf nodes.
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
            % - double
            % 
            % Exported name: StandardRegressionForest
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % n_features : size_t>0
            %   The number of features available.
            % 
            % max_depth : uint>=0
            %   The maximum tree depth. If 0, it is set to UINT_MAX to allow for
            %   maximally large trees. Default: 0.
            % 
            % test_n_features_per_node : size_t>=0
            %   The number of features to evaluate as split criteria at each tree
            %   node. If 0, it is set to sqrt(n_features). Default: 0.
            % 
            % n_thresholds_per_feature : size_t>0
            %   The number of thresholds to evaluate per feature. Default: 10.
            % 
            % n_trees : size_t>1
            %   The number of trees to use. Default: 10.
            % 
            % min_samples_per_leaf : uint>0
            %   The minimum number of samples at a leaf node.  Default: 3.
            % 
            % min_samples_per_split : uint>2*min_samples_per_leaf
            %   The minimum number of samples to continue splitting. Default: 6.
            % 
            % min_gain_threshold
            %   The minimum gain that must be reached to continue splitting. Default: 1E-7.
            % 
            % allow_redraw : bool
            %   If set to true, allows to try a new feature when optimizing for a
            %   split, when for a feature no split could be found that satisfied
            %   the minimum number of samples per leaf for each subgroup. This may be
            %   done until all features have been checked. Default: true.
            % 
            % random_seed : uint>=1
            %   The random seed to initialize the RNG. Default: 1.
            % 
            % entropy_name : string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
            %   The entropy type to use. For the specification of induced entropy,
            %   see the "Publications" page. Default: 'shannon'.
            % 
            % entropy_p1 : float
            %   The entropy parameter. Might be unused (e.g. for the Shannon entropy).
            %   Default: 2.
            % 
            % numerical_zero_threshold : float>=0.f || -1.f
            %   The threshold below of which all values are treated as zeros.
            %   If set to -1.f, use the value suggested by Eigen. Default: -1.f.
            % 
            % threshold_optimization_threads : uint>0
            %   The number of threads to use for threshold optimization. Default: 1.
            % 
            % summary_mode : uint<3
            %   Determines the meaning of the values in the prediction matrix of
            %   the forest (the output of the convenience `predict` method of a forest).
            %   Case 0: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the expected variances for each
            %   regressor (second half of its entries). To estimate the joint
            %   variance, a gaussian is fitted over the multimodal distribution
            %   defined by all trees.
            %   Case 1: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the mean of the expected variances of
            %   each tree. This has no direct semantic meaning, but can give
            %   better results in active learning applications.
            %   Case 2: Each row contains the prediction for each regressor and
            %   the variance estimate for each regressor for each tree, e.g.,
            %   (r11, r12, v11, v12, r21, r22, v21, v22, ...), with `r` and `v`
            %   denoting regressor prediction and variance respectively, the
            %   first index the tree and the second index the regressor index.
            %   Default: 0.
            if ~exist('max_depth', 'var') || max_depth == -1
                max_depth = 0;
            end    
            if ~exist('test_n_features_per_node', 'var') || test_n_features_per_node == -1
                test_n_features_per_node = 0;
            end    
            if ~exist('n_thresholds_per_feature', 'var') || n_thresholds_per_feature == -1
                n_thresholds_per_feature = 10;
            end    
            if ~exist('n_trees', 'var') || n_trees == -1
                n_trees = 10;
            end    
            if ~exist('min_samples_per_leaf', 'var') || min_samples_per_leaf == -1
                min_samples_per_leaf = 3;
            end    
            if ~exist('min_samples_per_split', 'var') || min_samples_per_split == -1
                min_samples_per_split = 6;
            end    
            if ~exist('min_gain_threshold', 'var') || min_gain_threshold == -1
                min_gain_threshold = 1E-7;
            end    
            if ~exist('allow_redraw', 'var') || allow_redraw == -1
                allow_redraw = 1;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            if ~exist('entropy_name', 'var') || entropy_name == -1
                entropy_name = 'shannon';
            end    
            if ~exist('entropy_p1', 'var') || entropy_p1 == -1
                entropy_p1 = 2;
            end    
            if ~exist('numerical_zero_threshold', 'var') || numerical_zero_threshold == -1
                numerical_zero_threshold = -1;
            end    
            if ~exist('threshold_optimization_threads', 'var') || threshold_optimization_threads == -1
                threshold_optimization_threads = 1;
            end    
            if ~exist('summary_mode', 'var') || summary_mode == -1
                summary_mode = 0;
            end    
            suffix = strcat('_', this.inp_str);
            getter = sprintf('%s%s', 'StandardRegressionForest', suffix);
            ptr = calllib(this.LibName, getter, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, n_trees, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, numerical_zero_threshold, threshold_optimization_threads, summary_mode);

            res = Forest(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = StandardRegressionTree (this, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, numerical_zero_threshold, threshold_optimization_threads, summary_mode)
            % Constructs a default decision tree for regression.
            % 
            % It uses an axis aligned decider and uses linear regression at split
            % and leaf nodes.
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
            % - double
            % 
            % Exported name: StandardRegressionTree
            % 
            % -----
            % 
            % 
            % Parameters
            % ==========
            % 
            % n_features : size_t>0
            %   The number of features available.
            % 
            % max_depth : uint>=0
            %   The maximum tree depth. If 0, it is set to UINT_MAX to allow for
            %   maximally large trees. Default: 0.
            % 
            % test_n_features_per_node : size_t>=0
            %   The number of features to evaluate as split criteria at each tree
            %   node. If 0, it is set to sqrt(n_features). Default: 0.
            % 
            % n_thresholds_per_feature : size_t>0
            %   The number of thresholds to evaluate per feature. Default: 10.
            % 
            % min_samples_per_leaf : uint>0
            %   The minimum number of samples at a leaf node. Default: 3.
            % 
            % min_samples_per_split : uint>2*min_samples_per_leaf
            %   The minimum number of samples to continue splitting. Default: 6.
            % 
            % min_gain_threshold
            %   The minimum gain that must be reached to continue splitting. Default: 1E-7.
            % 
            % allow_redraw : bool
            %   If set to true, allows to try a new feature when optimizing for a
            %   split, when for a feature no split could be found that satisfied
            %   the minimum number of samples per leaf for each subgroup. This may be
            %   done until all features have been checked. Default: true.
            % 
            % random_seed : uint>=1
            %   The random seed to initialize the RNG. Default: 1.
            % 
            % entropy_name : string in ["induced", "classification_error", "renyi", "tsallis", "shannon"]
            %   The entropy type to use. For the specification of induced entropy,
            %   see the "Publications" page. Default: 'shannon'.
            % 
            % entropy_p1 : float
            %   The entropy parameter. Might be unused (e.g. for the Shannon entropy).
            %   Default: 2.
            % 
            % numerical_zero_threshold : float>=0.f || -1.f
            %   The threshold below of which all values are treated as zeros.
            %   If set to -1.f, use the value suggested by Eigen. Default: -1.f.
            % 
            % threshold_optimization_threads : uint>0
            %   The number of threads to use for threshold optimization. Default: 1.
            % 
            % summary_mode : uint<3
            %   Determines the meaning of the values in the prediction matrix of
            %   the forest (the output of the convenience `predict` method of a forest).
            %   Case 0: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the expected variances for each
            %   regressor (second half of its entries). To estimate the joint
            %   variance, a gaussian is fitted over the multimodal distribution
            %   defined by all trees.
            %   Case 1: Each row contains the prediction for each regressor (the first
            %   half of its entries) and the mean of the expected variances of
            %   each tree. This has no direct semantic meaning, but can give
            %   better results in active learning applications.
            %   Case 2: Each row contains the prediction for each regressor and
            %   the variance estimate for each regressor for each tree, e.g.,
            %   (r11, r12, v11, v12, r21, r22, v21, v22, ...), with `r` and `v`
            %   denoting regressor prediction and variance respectively, the
            %   first index the tree and the second index the regressor index.
            %   Default: 0.
            if ~exist('max_depth', 'var') || max_depth == -1
                max_depth = 0;
            end    
            if ~exist('test_n_features_per_node', 'var') || test_n_features_per_node == -1
                test_n_features_per_node = 0;
            end    
            if ~exist('n_thresholds_per_feature', 'var') || n_thresholds_per_feature == -1
                n_thresholds_per_feature = 10;
            end    
            if ~exist('min_samples_per_leaf', 'var') || min_samples_per_leaf == -1
                min_samples_per_leaf = 3;
            end    
            if ~exist('min_samples_per_split', 'var') || min_samples_per_split == -1
                min_samples_per_split = 6;
            end    
            if ~exist('min_gain_threshold', 'var') || min_gain_threshold == -1
                min_gain_threshold = 1E-7;
            end    
            if ~exist('allow_redraw', 'var') || allow_redraw == -1
                allow_redraw = 1;
            end    
            if ~exist('random_seed', 'var') || random_seed == -1
                random_seed = 1;
            end    
            if ~exist('entropy_name', 'var') || entropy_name == -1
                entropy_name = 'shannon';
            end    
            if ~exist('entropy_p1', 'var') || entropy_p1 == -1
                entropy_p1 = 2;
            end    
            if ~exist('numerical_zero_threshold', 'var') || numerical_zero_threshold == -1
                numerical_zero_threshold = -1;
            end    
            if ~exist('threshold_optimization_threads', 'var') || threshold_optimization_threads == -1
                threshold_optimization_threads = 1;
            end    
            if ~exist('summary_mode', 'var') || summary_mode == -1
                summary_mode = 0;
            end    
            suffix = strcat('_', this.inp_str);
            getter = sprintf('%s%s', 'StandardRegressionTree', suffix);
            ptr = calllib(this.LibName, getter, n_features, max_depth, test_n_features_per_node, n_thresholds_per_feature, min_samples_per_leaf, min_samples_per_split, min_gain_threshold, allow_redraw, random_seed, entropy_name, entropy_p1, numerical_zero_threshold, threshold_optimization_threads, summary_mode);

            res = Tree(this.getDataTypes(), this.LibName, ptr, '%s%s');    
        end
        function [res] = extract_hough_forest_features (this, image, full)
            % Extract the Hough forest features. If `full` is set, uses the
            % 32 feature channels used by Juergen Gall in his original publications,
            % else use 15 feature channels as used by Matthias Dantone.
            % 
            % The image must be in OpenCV (BGR) channel format!
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
            % image : Array<uint8_t>, row-major contiguous
            %   The source image.
            % 
            % full : bool
            %   Whether to return the full feature set (32 layers) or not (15 layers).
            %   Default: false.
            if ~exist('full', 'var') || full == -1
                full = 0;
            end    
            suffix = '';
            getter = sprintf('%s%s', 'extract_hough_forest_features', suffix);
            ptr = calllib(this.LibName, getter, image, full);

            res = ptr;
        end
        % end generated methods         
    end % methods    
end % class