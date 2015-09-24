clear;
close all;
addpath('../../build/bindings/matlab/fertilized');

N_CLASSES = 3;

[X, Y] = make_spiral(100, N_CLASSES, 0.1);

% make float
X = single(X);

figure;
scatter(X(:, 1), X(:, 2), 20, Y);

s = Soil();

plotX = [-6, 6, 100];
plotY = [-6, 6, 100];

% These were the convenience methods. Lets build a customized forest:
depth = 6;
n_trees = 200;

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
    rcto = s.RandomizedClassificationThresholdOptimizer(1, N_CLASSES, entropyGain, 0, 1, 1+i);

    % ThresholdDecider
    tClassifier = s.ThresholdDecider(stdFeatureSelect, linSurface, rcto);

    % ClassificationLeafManager
    leafMgr = s.ClassificationLeafManager(N_CLASSES);
    
    cls{i} = tClassifier;
    lm{i} = leafMgr;
end

nss = s.NoBagging();
training = s.ClassicTraining(nss);

f = s.Forest(depth, 1, 2, n_trees, cls, lm, training);

% fit forest
f.fit(X, Y);

% paint prediction plot
figure;
point_prob_plot(f, X, Y, plotX, plotY);