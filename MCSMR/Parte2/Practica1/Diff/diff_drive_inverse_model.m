syms d1 d2 real

J1 = [0 0; 1 d1; 0 1];
J2 = [0 0; 1 -d2; 0 1];

A = [eye(3); eye(3)];
B = [J1 zeros(3,2); zeros(3,2) J2];

syms Vx Vy Wc real

VC = [Vx Vy Wc]';
VR = inv(B'*B)*B'*A*VC;
e = omega(B)*A*VC;

disp('Inverse model');
pretty(simplify(VR));
disp('Non-slippage conditions');
pretty(simplify(e));