clear;
close all;
addpath('../../build/bindings/matlab/fertilized');

% generate 2D samples from a polynomial function
n_samples = 45;
annot_dim = 1;
input_dim = 1;
samplesX = (rand(n_samples, 1) * 12) - 6; % make random distribution between -6 and 6
samplesY = samplesX.*samplesX - 0.2*samplesX - 1;
noise_var = 2.3;
random_noise = randn(n_samples, 1) * noise_var;
samplesY = samplesY + random_noise;

% make float
samplesX = single(samplesX);
samplesY = single(samplesY);

% define the plotted space
minX = min(samplesX);
maxX = max(samplesX);
deltaX = (maxX - minX);
plotX = [(minX -0.2*deltaX), (maxX +0.2*deltaX), 50];

s = Soil('f', 'f', 'f', Result_Types.regression);

n_trees = 5;
max_depth = 2;
n_thresholds = 2;
forest = s.StandardRegressionForest(input_dim, max_depth, input_dim, n_thresholds, n_trees);
forest.fit(samplesX, samplesY);

% predict the whole interval (minX, maxX)
predictX = single(linspace(plotX(1), plotX(2), plotX(3)))';
forest_result = forest.predict(predictX);

figure;
plot(samplesX, samplesY, 'o', predictX, forest_result(:, 1), 'LineSmoothing', 'on');