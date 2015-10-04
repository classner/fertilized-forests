clear;
close all;
addpath('../../build/bindings/matlab/fertilized');

[X, Y] = make_spiral(100, 2, 0.1);
% Plot configuration [plot start, plot end, number of points]
plotX = [-6, 6, 100];
plotY = [-6, 6, 100];
scatter(X(:, 1), X(:, 2), 20, Y);

soil = Soil();

% create tree...
tree = soil.StandardClassificationTree(2, 2);

% fit tree
tree.fit(X, Y);

% paint prediction plot
figure;
point_prob_plot(tree, X, Y, plotX, plotY);

% create forest...
forest = soil.StandardClassificationForest(2, 2);

% fit forest
forest.fit(X, Y);

% paint prediction plot
figure;
point_prob_plot(forest, X, Y, plotX, plotY);
