clear;
close all;
addpath('../../build/bindings/matlab/fertilized');

[X, Y] = make_spiral(100, 2, 0.1);

% make float
X = single(X);

% Y = uint32(randi([0 1],200,1));
scatter(X(:, 1), X(:, 2), 20, Y);

plotX = [-6, 6, 100];
plotY = [-6, 6, 100];
soil = Soil();

% create tree...
tree = soil.StandardClassificationTree(2, 2, 6, 2, 2);

% fit tree
tree.fit(X, Y);
filename = strcat('test_tree.ft');
tree.save(filename);

clear tree;

treefromfile = soil.TreeFromFile(filename);

% paint prediction plot
figure;
point_prob_plot(treefromfile, X, Y, plotX, plotY);