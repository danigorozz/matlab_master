syms d1 d2 d3 Q real

J1 = [0 0; 1 d1; 0 1];
J2 = [0 0; 1 -d1; 0 1];
J3 = [-sin(Q) d2+d3*cos(Q) -d2; cos(Q) d3*sin(Q) 0; 0 1 -1];

% Creación de las matrices A y Jacobiana
A=[eye(3); eye(3); eye(3)];
B=[J1 zeros(3,2) zeros(3,3); zeros(3,2) J2 zeros(3,3); zeros(3,2) zeros(3,2) J3];

syms V1 W1 V2 W2 V3 W3 Wd real
Y = [V1 W1 V2 W2 V3 W3 Wd]';
X = inv(A'*A)*A'*B*Y;
e=omega(A)*B*Y;

disp('Direct model');
pretty(simplify(X));
disp('Non-slippage conditions');
pretty(simplify(e));