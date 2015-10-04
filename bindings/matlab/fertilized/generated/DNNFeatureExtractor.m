classdef DNNFeatureExtractor < FertilizedObject
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
    
    methods (Access = {?Soil, ?DNNFeatureExtractor})
        function this = DNNFeatureExtractor(dataTypes, libName, ptr, functionFormat)
            position_list = [];
            tmp = '';
            for i = position_list
                tmp = strcat(tmp, '_', dataTypes(i));
            end
            if iscell(tmp)
              tmp = tmp{1};
            end
            delFuncName = ['delete_DNNFeatureExtractor' tmp];
            this = this@FertilizedObject(dataTypes, libName, ptr, tmp, delFuncName); 
            this.FunctionFormat = functionFormat;
        end
    end

    methods (Access = public)
        function [res] = extract(this, images, subtract_mean) 
            % Extract DNN features with this extractor.
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
            % images : vector(Array<float, 3, 3>)
            %   This vector of C contiguous float arrays contains the images to
            %   extract the features from in OpenCV (BGR) format.
            % 
            % 
            % subtract_mean : bool
            %   Whether to subtract the mean before extracting the features. Can
            %   only be used, if the mean file for this extractor has been loaded.
            % 
            % \return An Array, with dimensions: n_images x n_filters x height x width.
            if ~exist('subtract_mean', 'var') || subtract_mean == -1
                subtract_mean = 1;
            end
            suffix = this.TypeSuffix;
            getter = sprintf('%s%s%s', 'extract', 'DNNFeatureExtractor', suffix);
            ptr = calllib(this.LibName, getter, this.ClassifierPtr, images, subtract_mean);

            res = ptr;
        end
    end
    
end
