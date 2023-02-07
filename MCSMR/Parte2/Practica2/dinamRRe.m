function dx=dinamRRe(t,x,flag,m1,m2,L1,L2,F,tau,g)

c=cos(x); s=sin(x); c12=cos(x(1)+x(2));
B=[m1*L1^2+m2*L2^2+2*m2*L2*L1*c(2)+m2*L1^2, m2*L2^2+m2*L2*L1*c(2); m2*L2^2+m2*L2*L1*c(2), m2*L2^2];
C=[-m2*L2*L1*s(2)*(2*x(3)+x(4))*x(4); x(3)^2*m2*L2*L1*s(2)];
G=[m1*g*c(1)*L1+m2*g*(c12*L2+c(1)*L1);m2*g*c12*L2];
dx=[x(3);x(4);inv(B)*(tau-C-G-F*[x(3);x(4)])];

end

