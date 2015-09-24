clear;
close all;
addpath('../../build/bindings/matlab/fertilized');

n_classes = 3;

[X, Y] = make_spiral(100, n_classes, 0.4);

% make float
X = single(X);

figure;
scatter(X(:, 1), X(:, 2), 20, Y);

s = Soil();

plotX = [-6, 6, 100];
plotY = [-6, 6, 100];

% These were the convenience methods. Lets build a customized forest:
n_trees = 20;
depth = 13;

% minmax array
min_max_vals = [min(X(:,1)), max(X(:, 1)), min(X(:,2)), max(X(:,2))];

for suggestions = [3, 250]
    for dec_name = {'aligned', 'linear', 'quadratic'}
        if strcmp(dec_name, 'aligned')
            feat_sel_prov = s.StandardFeatureSelectionProvider(2, 1, 2, 2, 1);
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
        
        cls = {};
        lm = {};
        for i = 1:n_trees
            % RandomizedClassificationThresholdOptimizer
            shannon = s.ShannonEntropy();
            entropyGain = s.EntropyGain(shannon);
            rcto = s.RandomizedClassificationThresholdOptimizer(suggestions, n_classes, entropyGain, -1, -1, i);

            % ThresholdClassifier
            thresholdClassifier = s.ThresholdDecider(feat_sel_prov, feat_calc, rcto);

            % ClassificationLeafManager
            classificationLeafManager = s.ClassificationLeafManager(n_classes);
            
            cls{i} = thresholdClassifier;
            lm{i} = classificationLeafManager;
        end
        
        nss = s.NoBagging();
        training = s.ClassicTraining(nss);
        f = s.Forest(depth, 1, 2, n_trees, cls, lm, training);

        % fit forest
        f.fit(X, Y);

        % paint prediction plot
        figure;
        point_prob_plot(f, X, Y, plotX, plotY);
        title(strcat(dec_name, ' decider,\Theta_j=', int2str(suggestions * 2))); 
    end
end