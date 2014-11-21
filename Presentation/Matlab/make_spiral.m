function [ points, ids ] = make_spiral( n_samples_per_arm, n_arms, noise )
    starting_angles = (0:n_arms-1) * 2.0 * pi / n_arms;
    points = single(zeros(n_arms * n_samples_per_arm, 2));
    ids = uint32(zeros(n_arms * n_samples_per_arm, 1));
    maxpifac = 1.7;
    for arm_id = 1:n_arms;
        angle = starting_angles(arm_id);
        
        for point_id = 1:n_samples_per_arm
            angle_add = rand(1) * maxpifac; %np.random.uniform(low=0., high=maxpifac)
            position = point_on_circle(angle + angle_add * pi, 1. + 2. * angle_add);
            tmp = noise * angle_add * randn([1,2]);
            position = position + tmp;
            
            idx = (arm_id - 1) * n_samples_per_arm + point_id;
            points(idx, 1) = position(1);
            points(idx, 2) = position(2);
            
            ids(idx) = arm_id - 1;
        end
    end
end


function [res] = point_on_circle(phi, r)
    tmp = [cos(phi), sin(phi)];
    res = r * tmp;
 % return r *   np.array([np.cos(phi), np.sin(phi)])
end