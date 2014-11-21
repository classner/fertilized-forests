function [ retpoints ] = to_im_coords( points, im_spec )
  retpoints = double.empty(0,0);
  for point = points'
      scaled = (point - im_spec(1)) / (im_spec(2) - im_spec(1)) * im_spec(3);
      retpoints = [retpoints, scaled];
  end
end

