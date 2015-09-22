function point_prob_plot(classifier, X, Y, plotX, plotY )
    [n_classes, dummy] = size(unique(Y));
    xmb = linspace(plotX(1), plotX(2), plotX(3));
    ymb = linspace(plotY(1), plotY(2), plotY(3));

    [Xm, Ym] = meshgrid(xmb, ymb);
    
    coltemp = [0,0,0];
    [a, b] = size(Xm);
    Zm = zeros(a, b, 3);
    
    bigpredictarray = [];
    
    for y = 1:a
        for x = 1:b
            predictarr = [Xm(y, x), Ym(y, x)];
            predictarr = single(predictarr);
            bigpredictarray = [bigpredictarray; predictarr];
        end    
    end   
  
    predictionAll = classifier.predict(bigpredictarray);
    

    for y = 1:a
        for x = 1:b
            % calculate index of predicted array...
            idx = (((y-1) * b) + x);
            prediction = predictionAll(idx, :);
            if n_classes == 2
                coltemp(1) = prediction(2); % * 255.0;
            	coltemp(2) = 0;
                coltemp(3) = prediction(1);
            else
                coltemp(1) = prediction(3); % * 255.0;
            	coltemp(2) = prediction(2);
                coltemp(3) = prediction(1);
            end
            
            Zm(y,x,1) = coltemp(1);
            Zm(y,x,2) = coltemp(2);
            Zm(y,x,3) = coltemp(3);
        end    
    end

    % flip dimension to show heatmap correct
    flippedImg = flipdim(Zm, 1); %flipud3d(Zm);
    Xtransformed = to_im_coords( X(:, 1), plotX );
    Ytransformed = to_im_coords( X(:, 2), plotY );
    
    
    % subtract from max value to flip predicted points within plot...
    Ytransformed = plotY(3) - Ytransformed;
    
    % show predicted point colors
    imshow(flippedImg);
    
    % hold image to draw within
    hold on;
    scatter(Xtransformed, Ytransformed, 20, Y);
    hold off;
end

