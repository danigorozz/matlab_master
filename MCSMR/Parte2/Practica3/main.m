%% Requirements and parameters initialization
clear all;

% Control system requirements and parameters: 
shi=0.4;    % Minimum damping coefficient.
wn=20;      % Natural frequency. 

% System parameters
J=6;    % Inertia.
Ra=0.3; % Resistance of the motor shield.
kt=0.5; % Voltage-torque conversion factor. 
kv=0.5; % Counter-electromotive force constant. 
kTP=1;  % Position feedback gain. 
kTV=1;  % Velocity feedback gain. 

%% PI controller parameters setting

Kv=(2*shi*wn*kv)/kTV;   % Velocity gain.
Kp=(wn^2*kv)/(kTP*Kv);  % Position gain.
Tv=(Ra*J)/(kv*kt);      % Zero for the controller.

%% Joint model with PI controller and joint in internal description
% d(x)=Ax+B. x=[position, velocity, integral]'

A=[0 1 0;...
   -Kv*Tv*kt*kTV*Kp/Ra/J -(kv*kt+Kv*Tv*kt*kTV)/Ra/J kt*Kv/Ra/J;...
   -kTP*Kp -kTV 0];
B=[0 0;-1/J Kv*Tv*kt*Kp/Ra/J;0 Kp];
C=[1 0 0;0 1 0]; % Notice that this defines our output.
D=[0 0; 0 0];

%% State-Space Model construction 

% Get ss model
G=ss(A,B,C,D);

% Plot step response
step(G,1);

%% Following a cubic trajectory

% Create a cubic trajectory
[T,W]=cubica([0,0],[pi/6,0],3,0.1);

% Generate random perturbations along trajectory
%pert = round(randn([size(W,2) 1])*50);
%U=[pert,W(1,:)'];
U=[zeros(size(W,2),1),W(1,:)'];
%U(4,1) = 100;

% Simulation of the trajectory with ss model
[Y,T]=lsim(G,U,T);

% Plot trajectory planned (W) and followed (Y)
figure
plot(T,W(1,:),'-',T,Y(:,1)','-.')
xlabel('Tiempo (sg)');
ylabel('Espacio (rad)');
grid
legend('Planificada','Seguida');


