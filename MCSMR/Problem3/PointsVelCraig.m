function qd = PointsVelCraig(q,t)
    % Computing joint velocities of via points using Craig criteria.
    % Input data size
    num_joints = size(q,2); num_points = size(q,1);
    % Zero initialization of joint velocities
    qd = zeros(size(q));
    for j=1:num_joints
        for i=2:num_points-1
            if (sign(q(i,j)-q(i-1,j))~=sign(q(i+1,j)-q(i,j))) && (q(i-1,j)==q(i,j)) && (q(i,j)==q(i+1,j))
                qd(i,j)=0;
            else
                qd(i,j)=(1/2)*((q(i+1,j)-q(i,j))/(t(i+1)-t(i)) + (q(i,j)-q(i-1,j))/(t(i)-t(i-1)));
            end
        end
    end
end

