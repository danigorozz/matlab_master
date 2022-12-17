function [qs,time] = CubicSpline_Interp(q,qd,t,M)
    % Interpolation using cubic spline
    L=length(q);
    time=0;
    qs=q(1,:); % first joint configuration
    for i=1:L-1
        T=t(i+1)-t(i);
        a=q(i,:);
        b=qd(i,:);
        c=(3/T^2)*(q(i+1,:)-q(i,:)) - (1/T)*(qd(i+1,:)+2*qd(i,:));
        d=(-2/T^3)*(q(i+1,:)-q(i,:)) + (1/T^2)*(qd(i+1,:)+qd(i,:));
        temp=linspace(t(i),t(i+1),M);
        temp=temp(2:M);
        time=[time,temp];
        for k=1:M-1
            qtemp(k,:)=a+b*(temp(k)-t(i))+c*(temp(k)-t(i))^2+d*(temp(k)-t(i))^3;
        end
        qs=[qs;qtemp];
    end
end


