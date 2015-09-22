classdef Tree < FertilizedObject
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
    
    methods (Access = {?Soil, ?Tree})
        function this = Tree(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_Tree' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
        function make_node(this, data_provider, append_on_different) 
            % Handle the creation of one tree node.
            % 
            % Takes the next one of the list of marked nodes and fits it to the
            % data. If necessary, creates two child nodes and a split criterion,
            % otherwise makes it a leaf.
            % 
            % The function is always using the frontmost mark in the todo-list.
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
            % data_provider : shared(IDataProvider)
            %   The data provider to use.
            % 
            % append_on_different : bool
            %   Where to append the produced node-marks in
            %   the deque "todo-list". Appending the nodes on the
            %   same side they're read from leads to performing a
            %   DFS, while appending them on the different end
            %   leads to performing a BFS.
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'make_node', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, data_provider.ClassifierPtr, append_on_different);

            res = ptr;
        end
        function [res] = depth(this) 
            % Get the tree depth.
            % 
            % The depth is defined to be 0 for an "empty" tree (only a leaf/root node)
            % and as the amount of edges on the longest path in the tree otherwise.
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
            getter = sprintf('%s%s%s', 'depth', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function fit(this, data, annotations, complete_dfs) 
            % Standard fitting function.
            % 
            % Fits this tree to the data given by the data provider. If
            % complete_dfs is true, the tree is completely fitted to the data
            % Otherwise, just a node todo for the root node is added and the tree
            % may be performed step-by-step by calling the BFS or DFS
            % functions.
            % 
            % Releases the GIL in Python!
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
            % data : Array<input_dtype>, 2D, row-major contiguous
            %   Row-wise data points.
            % 
            % annotations : Array<annotation_dtype>, 2D, row-major contiguous
            %   Row-wise annotations.
            % 
            % complete_dfs : bool
            %   If set to true, finishes training the tree. Otherwise, the training
            %   is just set up, and make_node must be called. Default: true.
            if ~exist('complete_dfs', 'var') || complete_dfs == -1
                complete_dfs = 1;
            end
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'fit', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, data, annotations, complete_dfs);

            res = ptr;
        end
        function fit_dprov(this, data_provider, complete_dfs) 
            % The fitting function for a single tree.
            % 
            % Fits this tree to the data given by the data provider. If
            % complete_dfs is true, the tree is completely fitted to the data
            % Otherwise, just a node todo for the root node is added and the tree
            % may be performed step-by-step by calling the BFS or DFS
            % functions.
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
            % data_provider : shared(IDataProvider)
            %   The data provider for the fitting process.
            % 
            % complete_dfs : bool
            %   If true, complete the fitting process.
            if ~exist('complete_dfs', 'var') || complete_dfs == -1
                complete_dfs = 1;
            end
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'fit_dprov', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, data_provider.ClassifierPtr, complete_dfs);

            res = ptr;
        end
        function [res] = predict(this, data, num_threads) 
            % Predicts new data points.
            % 
            % Releases the GIL in Python!
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
            % data : Array<input_data>, 2D, row-major contiguous
            %   The data predict with one sample per row.
            % 
            % 
            % num_threads : int>0
            %   The number of threads to use for prediction. The number of
            %   samples should be at least three times larger than the number
            %   of threads to observe very good parallelization behaviour.
            if ~exist('num_threads', 'var') || num_threads == -1
                num_threads = 1;
            end
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'predict', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, data, num_threads);

            res = ptr;
        end
        function [res] = predict_image(this, image, step_size, reduce_to_patch_positions, p1, p2) 
            % Predicts an entire image.
            % 
            % This method will iterate pixel per pixel over the image and tries to
            % predict it. This method is only supported for certain setups:
            % 
            % 
            % - Leaf Manager: ClassificationLeafManager or HoughLeafManager.
            % - Decider: ThresholdDecider.
            % - Feature Selection Provider: VolumeFeatureSelectionProvider.
            % 
            % Releases the GIL in Python!
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
            % image : Array<input_dtype>, 3D, row-major-contiguous
            %   The feature image to predict.
            % 
            % step_size : size_t>0
            %   Step size in pixels between predictions (horizontal and vertical). Default: 1.
            % 
            % reduce_to_patch_positions : bool
            %   A reduced result image grid is used, matching exactly the required size.
            %   This has implications for the use with the HoughLeafManager, because
            %   the offset vectors must also be added on the reduced grid.
            % 
            % p1 : float>0.f
            %   The ratio of x to y axis for the HoughLeafManager.
            % 
            % p2 : float>=0.f
            %   The minimum probability to add a vector for the HoughLeafManager.
            if ~exist('step_size', 'var') || step_size == -1
                step_size = 1;
            end
            if ~exist('reduce_to_patch_positions', 'var') || reduce_to_patch_positions == -1
                reduce_to_patch_positions = 0;
            end
            if ~exist('p1', 'var') || p1 == -1
                p1 = 1;
            end
            if ~exist('p2', 'var') || p2 == -1
                p2 = 0;
            end
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'predict_image', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, image, step_size, reduce_to_patch_positions, p1, p2);

            res = ptr;
        end
        function [res] = get_weight(this) 
            % The tree weight.
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
            getter = sprintf('%s%s%s', 'get_weight', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = get_n_nodes(this) 
            % The number of tree nodes.
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
            getter = sprintf('%s%s%s', 'get_n_nodes', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function set_weight(this, new_weight) 
            % Sets the tree weight.
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
            getter = sprintf('%s%s%s', 'set_weight', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, new_weight);

            res = ptr;
        end
        function [res] = get_input_data_dimensions(this) 
            % The data dimension that is required by this tree.
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
            getter = sprintf('%s%s%s', 'get_input_data_dimensions', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = compute_feature_importances(this) 
            % Computes a feature importance vector.
            % 
            % The vector is normalized to sum to 1.0. It contains the relative
            % frequencies of the feature occurences. Its length is the number
            % of available features.
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
            getter = sprintf('%s%s%s', 'compute_feature_importances', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = get_samples_stored(this) 
            % The number of samples stored in leafs.
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
            getter = sprintf('%s%s%s', 'get_samples_stored', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = eq(this, rhs) 
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
            getter = sprintf('%s%s%s', 'eq', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function save(this, filename) 
            % Saves the tree to a textfile.
            % 
            % This method can be used platform and system independent (e.g. Matlab -
            % C++).
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
            % filename : string
            %   The filename of the file to store the tree in.
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'save', 'Tree', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, filename);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
