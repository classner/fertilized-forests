classdef Forest < FertilizedObject
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
    
    methods (Access = {?Soil, ?Forest})
        function this = Forest(dataTypes, libName, ptr, functionFormat)
            position_list = [1,2,3,4,5];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_Forest' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
        function fit(this, data, annotations, num_threads) 
            % Fits the forest on the given data.
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
            % num_threads : uint>0
            %   The number of threads to use for fitting.
            if ~exist('num_threads', 'var') || num_threads == -1
                num_threads = 1;
            end
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'fit', 'Forest', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, data, annotations, num_threads);

            res = ptr;
        end
        function fit_dprov(this, fdata_provider, execution_strategy) 
            % The fitting function for a forest.
            % 
            % Fits this forest to the data given by the data provider.
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
            % data_provider : shared(IForestDataProvider)
            %   The data provider for the fitting process.
            % 
            % execution_strategy : IExecutionStrategy*
            %   The execution strategy to use.
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'fit_dprov', 'Forest', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, fdata_provider.ClassifierPtr, execution_strategy.ClassifierPtr);

            res = ptr;
        end
        function [res] = predict(this, data) 
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
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'predict', 'Forest', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, data);

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
            getter = sprintf('%s%s%s', 'predict_image', 'Forest', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, image, step_size, reduce_to_patch_positions, p1, p2);

            res = ptr;
        end
        function [res] = get_input_data_dimensions(this) 
            % Gets the required input data dimenstion.
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
            getter = sprintf('%s%s%s', 'get_input_data_dimensions', 'Forest', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = get_tree_weights(this) 
            % Gets all tree weights.
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
            getter = sprintf('%s%s%s', 'get_tree_weights', 'Forest', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr);

            res = ptr;
        end
        function [res] = eq(this, rhs) 
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
            getter = sprintf('%s%s%s', 'eq', 'Forest', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, rhs.ClassifierPtr);

            res = ptr;
        end
        function save(this, filename) 
            % Saves the forest to a file with the specified name.
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
            %   The filename to use.
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'save', 'Forest', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, filename);

            res = ptr;
        end
        function [res] = ne(this, other)
            res = ~this.eq(other);
        end
    end
    
end
