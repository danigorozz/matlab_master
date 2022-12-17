%% Subject: Modelado y Control de Sistemas Mecatrónicos y Robots. 2021-22.
%% Deliverable 2: Jacobian Matrix

clearvars;
close all;

%% IRB120 DH1 parameters
syms alpha a theta d real
T=despZ(d)*rotZ(theta)*despX(a)*rotX(alpha);

% Standard Denavit-Hartemberg parameters (DH1)
di=[0.290 0 0 0.302 0 0.072];
ai=[0 0.270 0.070 0 0 0];
alphai=[-pi/2 0 -pi/2 pi/2 -pi/2 0];
syms q1 q2 q3 q4 q5 q6 real
qi=[q1 q2 q3 q4 q5 q6];

T01=subs(T,{a,alpha,d,theta},{ai(1),alphai(1),di(1),qi(1)});
T12=subs(T,{a,alpha,d,theta},{ai(2),alphai(2),di(2),qi(2)});
T23=subs(T,{a,alpha,d,theta},{ai(3),alphai(3),di(3),qi(3)});
T34=subs(T,{a,alpha,d,theta},{ai(4),alphai(4),di(4),qi(4)});
T45=subs(T,{a,alpha,d,theta},{ai(5),alphai(5),di(5),qi(5)});
T56=subs(T,{a,alpha,d,theta},{ai(6),alphai(6),di(6),qi(6)});

%T01 computed before.
T02=simplify(T01*T12);
T03=simplify(T02*T23);
T04=simplify(T03*T34);
T05=simplify(T04*T45);
T06=simplify(T05*T56);

% IRB120 symbolic Jacobian
%joint vectors (zi)
zL=[0 0 1]';
z0=zL;
z1=T01(1:3,1:3)*z0;
z2=T02(1:3,1:3)*z0;
z3=T03(1:3,1:3)*z0;
z4=T04(1:3,1:3)*z0;
z5=T05(1:3,1:3)*z0;
%position vectors (pi); they are the position part of the homogeneus
%transformation matrices (position of the origin of the reference frame)
p0=[0 0 0]';
p1=T01(1:3,4);
p2=T02(1:3,4);
p3=T03(1:3,4);
p4=T04(1:3,4);
p5=T05(1:3,4);
p6=T06(1:3,4);
%Columns according to the algorithm (J=[JP;JO]); we are left with the three
%first elements of each pi vector
J1=simplify([cross(z0,(p6(1:3)-p0(1:3)));z0]);
J2=simplify([cross(z1,(p6-p1));z1]);
J3=simplify([cross(z2,(p6-p2));z2]);
J4=simplify([cross(z3,(p6-p3));z3]);
J5=simplify([cross(z4,(p6-p4));z4]);
J6=simplify([cross(z5,(p6-p5));z5]);
JPO=simplify([J1 J2 J3 J4 J5 J6]);


% Point A
Ta=[1 0 0 0; 0 -1 0 0.302; 0 0 -1 0.558; 0 0 0 1];
qa=IRB120_IK(Ta,ai,di,T03);
% Point B
Tb=[1 0 0 0; 0 -1 0 0.302; 0 0 -1 0.358; 0 0 0 1];
qb=IRB120_IK(Tb,ai,di,T03);

% Position vector in the trajectory
n=20;
z_i=linspace(Ta(3,4),Tb(3,4),n);
pos_i=[Ta(1,4)*ones(1,n); Ta(2,4)*ones(1,n); z_i];
% End-effector velocity
ve=[0;0;-0.01;0;0;0];  

t=0:1:n-1;
t=t/10;
rg=180/pi;

out_ws=0;
% Trajectory in joint space
T=Ta;
for k=1:n
    T(3,4)=z_i(k);
    q(k,:)=IRB120_IK(T,ai,di,T03);
    if isinf(q(k,:)) % if a position out of range
        out_ws=1; 
    end
end

% STARTING HERE FOR PROBLEM 3

% Plotting joint configurations in via points
figure(1); hold on;
scatter(t,q(:,1)*rg,'*'); 
scatter(t,q(:,2)*rg,'*');
scatter(t,q(:,3)*rg,'*');
scatter(t,q(:,4)*rg,'*');
scatter(t,q(:,5)*rg,'*');
scatter(t,q(:,6)*rg,'*'); 
xlabel('time (s)'); ylabel('joint angle (º)');
xlim([0 2.5]);
legend('q1','q2','q3','q4','q5','q6'); title('Joint configurations in via points'); grid;

qd=[];
if out_ws==1
    disp('There is a position out of workspace');
else

    % Geetting velocities in via points with Craig criteria
    qd = PointsVelCraig(q,t);
    
    % Plotting joint velocities in via points
    figure(2); hold on;
    scatter(t,qd(:,1)*rg, '*');
    scatter(t,qd(:,2)*rg, '*');
    scatter(t,qd(:,3)*rg, '*');
    scatter(t,qd(:,4)*rg, '*');
    scatter(t,qd(:,5)*rg, '*');
    scatter(t,qd(:,6)*rg, '*'); 
    xlabel('time (s)'); ylabel('joint velocities (º/s)');
    xlim([0 2.5]);
    legend('dq1','dq2','dq3','dq4','dq5','dq6'); title('Joint velocities in via points'); grid;
    
    % Getting spline with M=100
    M=100;
    [qs, time] = CubicSpline_Interp(q,qd,t,M);

    % Plotting joint configurations
    figure(3); hold on;
    scatter(t,q(:,1)*rg,'o'); 
    scatter(t,q(:,2)*rg,'o');
    scatter(t,q(:,3)*rg,'o');
    scatter(t,q(:,4)*rg,'o');
    scatter(t,q(:,5)*rg,'o');
    scatter(t,q(:,6)*rg,'o'); 
    xlabel('time (s)'); ylabel('joint angle (º)');
    xlim([0 2.5]);
    plot(time,qs(:,1)*rg,time,qs(:,2)*rg,time,qs(:,3)*rg,time,qs(:,4)*rg,time,qs(:,5)*rg,time,qs(:,6)*rg);
    legend('q1','q2','q3','q4','q5','q6'); title('Joint configurations'); grid;

    % Getting velocities at each point of spline
    qds=qs(1,:)/time(1);
    for i = 1:length(time)-1
        temp = (qs(i+1,:) - qs(i,:))/(time(i+1)-time(i));
        qds = [qds; temp];
    end

    % Plotting joint velocities
    figure(4); hold on;
    scatter(t,qd(:,1)*rg, 'o');
    scatter(t,qd(:,2)*rg, 'o');
    scatter(t,qd(:,3)*rg, 'o');
    scatter(t,qd(:,4)*rg, 'o');
    scatter(t,qd(:,5)*rg, 'o');
    scatter(t,qd(:,6)*rg, 'o'); 
    xlabel('time (s)'); ylabel('joint velocities (º/s)');
    xlim([0 2.5]);
    plot(time,qds(:,1)*rg,time,qds(:,2)*rg,time,qds(:,3)*rg,time,qds(:,4)*rg,time,qds(:,5)*rg,time,qds(:,6)*rg);
    legend('dq1','dq2','dq3','dq4','dq5','dq6'); title('Joint velocities'); grid;

    % Getting joint accelerations
    qdds=qds(1,:)/time(1);
    for i = 1:length(time)-1
        temp = (qds(i+1,:) - qds(i,:))/(time(i+1)-time(i));
        qdds = [qdds; temp];
    end

    % Plotting joint accelerations
    figure(5); hold on;
    xlabel('time (s)'); ylabel('joint accelerations (º/s^{2})');
    xlim([0 2.5]);
    plot(time,qdds(:,1)*rg,time,qdds(:,2)*rg,time,qdds(:,3)*rg,time,qdds(:,4)*rg,time,qdds(:,5)*rg,time,qdds(:,6)*rg);
    legend('ddq1','ddq2','ddq3','ddq4','ddq5','ddq6'); title('Joint accelerations'); grid;

    
    % End-effector position -> Direct Kinematic Model
    % End-effector velocity -> Jacobian Matrix 
    pe = Ta(1:3,4)';
    ve= [0 0 -0.1 0 0 0];
    for i = 1:length(time)-1
        temp = subs(T06, {q1,q2,q3,q4,q5,q6},{qs(i,1),qs(i,2),qs(i,3),qs(i,4),qs(i,5),qs(i,6)});
        temp = temp(1:3,4)';
        pe = [pe; temp];

        tempJ = subs(JPO, {q1,q2,q3,q4,q5,q6},{qs(i,1),qs(i,2),qs(i,3),qs(i,4),qs(i,5),qs(i,6)});
        temp = tempJ*qds(i,:)';
        ve = [ve; temp'];
    end

    % Plotting end-effector position
    figure(6); hold on;
    plot(pe(:,2), pe(:,3));
    plot([0.302 0.302], [0.358 0.558]);
    xlabel('Axis Y (m)'); ylabel('Axis Z (m)');
    legend('Real end-effector position','Target position'); title('Position of the end-effector'); grid;

    % Plotting end-effector velocity
    figure(7);
    subplot(2,1,1);
    plot(time, ve(:,2));
    xlabel('time (s)'); ylabel('Velocity in axis Y (m/s)');
    title('End-effector velocity'); grid;
    subplot(2,1,2);
    plot(time, ve(:,3));
    xlabel('time (s)'); ylabel('Velocity in axis Z (m/s)'); grid;

    % End-effector acceleration -> Diff(velocity)/Diff(time)
    ae=ve(1,:)/time(1);
    for i = 1:length(time)-1
        temp = (ve(i+1,:) - ve(i,:))/(time(i+1)-time(i));
        ae = [ae; temp];
    end

    % Plotting end-effector acceleration
    figure(8);
    subplot(2,1,1);
    plot(time, ae(:,2));
    xlabel('time (s)'); ylabel('Acceleration in axis Y (m/s^{2})');
    title('End-effector acceleration'); grid;
    subplot(2,1,2);
    plot(time, ae(:,3));
    xlabel('time (s)'); ylabel('Acceleration in axis Z (m/s^{2})'); grid;

end

