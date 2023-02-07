function [T,W]=cubica(q0,qf,tf,res)
% Generación de una trayectoria articular 
%mediante una función cúbica 
% desde q0(1) con velocidad q0(2) hasta qf(1) con 
%velocidad final qf(2) en
% un tiempo tf.
%
% function [T,W]=cubica(q0,qf,tf,res)
%
% q0(1x2): Valor articular y velocidad inicial.
% qf(1x2): Valor articular y velocidad final.
% tf: Tiempo para recorrer la trayectoria.
% res: Tiempo de muestreo de la trayectoria.
%
% T(1xn): Vector de tiempos.
% W(3xn): Trayectoria articular generada.
% Planificación: Definición del polinomio cúbico 
%y sus derivadas.
p=zeros(1,4);
p(4)=q0(1);
p(3)=q0(2);
p(2)=3/tf^2*(qf(1)-q0(1))-2/tf*q0(2)-1/tf*qf(2);
p(1)=-2/tf^3*(qf(1)-q0(1))+1/tf^2*(qf(2)+q0(2));
dp=polyder(p); ddp=polyder(dp);
% Generación de la trayectoria
T=0:res:tf;
W=[polyval(p,T);polyval(dp,T);polyval(ddp,T)];

