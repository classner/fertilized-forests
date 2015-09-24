clear;
close all;
addpath('../../build/bindings/matlab/fertilized');

load('classification_data.mat');

plotX = [-8, 8, 100];
plotY = [-8, 8, 100];

% provide correct datatypes..
X = single(X);
Y = uint32(Y');

figure;
scatter(X(:, 1), X(:, 2), 20, Y);

s = Soil();

% These were the convenience methods. Lets build a customized forest:
n_trees = 200;
stumps = {};

min_max_vals = [min(X(:,1)), max(X(:, 1)), min(X(:,2)), max(X(:,2))];

for i = 1:n_trees
    dec_name = 'aligned';
    if strcmp(dec_name, 'aligned')
        feat_sel_prov = s.StandardFeatureSelectionProvider(2, 1, 2, 2, i);
    else
        feat_sel_prov = s.StandardFeatureSelectionProvider(1, 2, 2, 2);
    end  
    if strcmp(dec_name, 'aligned')
        feat_calc = s.AlignedSurfaceCalculator();
    elseif strcmp(dec_name, 'linear')
        feat_calc = s.LinearSurfaceCalculator(400);
    elseif strcmp(dec_name, 'quadratic')
        feat_calc = s.QuadraticSurfaceCalculator(400, min_max_vals);    
    end

    % RandomizedClassificationThresholdOptimizer
    induced = s.InducedEntropy(2);
    entropyGain = s.EntropyGain(induced);
    rcto = s.RandomizedClassificationThresholdOptimizer(2, 2, entropyGain, -1, -1, i);
    
    % ThresholdClassifier
    thresholdClassifier = s.ThresholdDecider(feat_sel_prov, feat_calc, rcto);
        
    % ClassificationLeafManager
    classificationLeafManager = s.ClassificationLeafManager(2);
    
    stump = s.Tree(1, 1, 2, thresholdClassifier, classificationLeafManager);
    stumps{i} = stump;
    
    % fit stump...
    stump.fit(X,Y);

    % display first 2 stumps   
    if i < 3
        % paint prediction plot
        figure;
        point_prob_plot(stump, X, Y, plotX, plotY);
    end
end

% create forest from first 8 stumps
fft8 = s.CombineTrees(stumps(1:8));

% paint prediction plot
figure;
point_prob_plot(fft8, X, Y, plotX, plotY);

% create forest from stumps
fft = s.CombineTrees(stumps);

% paint prediction plot
figure;
point_prob_plot(fft, X, Y, plotX, plotY);
