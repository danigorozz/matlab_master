% ##################### CONSIDERATIONS #####################
% m1 y m2: Link masses (Kg)
% d1 y d2: Link Lengths (m)
% F=[f1 0;f2 0]: Viscous friction for each joint (Nm/rad/sg)
% tau=[tau1 tau2]: Joint torques (Nm)
% g: Gravity (m/s^2)
% Tf: Simulation time (s)
% g2r: Constant for converting degrees into radians
% r2g: Constant for converting radians into degrees
% ##########################################################

% Constants
m1=5; m2=2; d1=1; d2=0.6;
F=[4.5 0;0 3.5]; tau=[0;0];
g=9.8; Tf=30;
g2r=pi/180; r2g=180/pi;

% Initial conditions.
X0=[0;0;0;0]*g2r;

% Simulation
[T,Q]=ode45('dinamRRe',[0 Tf],X0,[],m1,m2,d1,d2,F,tau,g);

% Visualization
subplot(2,1,1); % Positions
plot(T,Q(:,1)*r2g,'-',T,Q(:,2)*r2g,'-.');
legend('q1','q2');
grid; title('Joint Positions');
xlabel('seconds'); ylabel('deg');
subplot(2,1,2); % Joint velocities
plot(T,Q(:,3)*r2g,'-',T,Q(:,4)*r2g,'-.');
legend('dq1','dq2');
grid; title('Joint Velocities');
xlabel('seconds'); ylabel('deg/s');