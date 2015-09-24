clear;
close all;
addpath('../../build/bindings/matlab/fertilized');

n_classes = 3;

[X, Y] = make_spiral(100, n_classes, 0.4);

% make float
X = single(X);

figure;
scatter(X(:, 1), X(:, 2), 20, Y);
title('Raw data');

s = Soil();

plotX = [-6, 6, 100];
plotY = [-6, 6, 100];

% These were the convenience methods. Lets build a customized forest:
n_trees = 200;
min_max_vals = [min(X(:,1)), max(X(:, 1)), min(X(:,2)), max(X(:,2))];

for depth = [3, 6, 15]
    cls = {};
    lm = {};
    for i = 1:n_trees
        % StandardFeatureSelectionProvider
        stdFeatureSelect = s.StandardFeatureSelectionProvider(1, 2, 2, 2);

        % LinearSurfaceCalculator
        surface = s.QuadraticSurfaceCalculator(400, min_max_vals, 1+i);

        % ClassificationThresholdOptimizer
        shannon = s.ShannonEntropy();
        entropyGain = s.EntropyGain(shannon);
        cto = s.ClassificationThresholdOptimizer(1, n_classes, entropyGain);

        % ThresholdClassifier
        tClassifier = s.ThresholdDecider(stdFeatureSelect, surface, cto);

        % ClassificationLeafManager
        leafMgr = s.ClassificationLeafManager(n_classes);

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
    title(strcat('Depth ', int2str(depth))); 
end