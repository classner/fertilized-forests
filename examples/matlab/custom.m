clear;
close all;
addpath('../../build/bindings/matlab/fertilized');

% load('testdata.mat');
% Y = uint32(randi([0 1],200,1));
X = [];
Y = [];

for x = -6: .1 : 6;
    y = cos(x) * tan(x + 1);
    X = [X; [x, y]];
    Y = [Y; tan(x + 1)<0];
end

X = single(X);
Y = uint32(Y);

figure;
scatter(X(:, 1), X(:, 2), 20, Y);

s = Soil();

plotX = [-6, 6, 100];
plotY = [-6, 6, 100];

% Lets build a customized forest:
depth = 12;
n_trees = 200;
% These variables will contain the classifiers and leaf managers for each
% tree.
cls = {};
lm = {};

for i = 1:n_trees
    % StandardFeatureSelectionProvider
    stdFeatureSelect = s.StandardFeatureSelectionProvider(1, 2, 2, 2, 1+i);

    % LinearSurfaceCalculator
    linSurface = s.LinearSurfaceCalculator(400, 2, 1+i);

    % RandomizedClassificationThresholdOptimizer
    shannon = s.ShannonEntropy();
    entropyGain = s.EntropyGain(shannon);
    rcto = s.RandomizedClassificationThresholdOptimizer(1, 2, entropyGain, 0, 1, 1+i);

    % ThresholdDecider
    tClassifier = s.ThresholdDecider(stdFeatureSelect, linSurface, rcto);

    % ClassificationLeafManager
    leafMgr = s.ClassificationLeafManager(2);

    cls{i} = tClassifier;
    lm{i} = leafMgr;
end


nb = s.NoBagging();
training = s.ClassicTraining(nb);

f = s.Forest(depth, 1, 2, n_trees, cls, lm, training);

% fit forest
f.fit(X, Y);

% paint prediction plot
figure;
point_prob_plot(f, X, Y, plotX, plotY);
