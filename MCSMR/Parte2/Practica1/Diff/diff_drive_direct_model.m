syms d1 d2 real

J1 = [0 0; 1 d1; 0 1];
J2 = [0 0; 1 -d2; 0 1];

A = [eye(3); eye(3)];
B = [J1 zeros(3,2); zeros(3,2) J2];

syms V1 W1 V2 W2 real
Y = [V1 W1 V2 W2]';
X = inv(A'*A)*A'*B*Y;
e=omega(A)*B*Y;

disp('Direct model');
pretty(simplify(X));
disp('Non-slippage conditions');
pretty(simplify(e));