function [Q] = InvKinRRR(P,m)
% INVKINRRR Calculo de la cinematica inversa de un manipulador planar de tres
%   articulaciones.
% INPUTS:
%   p   : un vector representando la posicion en X, la posicion en Y y la
%   orientacion del efector final.
%   m   : modo de la solucion. m = 1 para codo abajo, m = -1 para codo
%   arriba, m = 0 para ambas soluciones.
% OUTPUTS:
%   Q   : un vector representando las variables articulares del manipulador.
    
    Q = [];

    if length(P) < 3
        fprintf('\nERROR: Posicion no valida. Tiene que ser un array de 3 elementos [Posicion en X, Posicion en Y, Angulo en el plano].\n');
        return
    end
    
    a=[20,15,10];
    X=P(1); Y=P(2); phi=P(3);
    raiz=sqrt(X^2+Y^2);

    if raiz > (a(1)+a(2)+a(3))
        fprintf('\nERROR: Localizacion fuera de alcance\n');
        return
    end
    
    Xw = X - a(3)*cos(phi);
    Yw = Y - a(3)*sin(phi);
    d = sqrt(Xw^2+Yw^2);
    alpha=acos((a(1)^2+d^2-a(2)^2)/(2*a(1)*d));
    beta=atan2(Yw,Xw);
    gamma = acos((a(1)^2+a(2)^2-d^2)/(2*a(1)*a(2)));
    
    switch(m)
        case -1
            fprintf('\n###### Modo seleccionado: Codo arriba\n');
            q1_1=beta+alpha;
            q2_1=-(pi-gamma);
            q3_1=phi-q2_1-q1_1;
            Q=[q1_1 q2_1 q3_1];
            return
        case 1
            fprintf('\n###### Modo seleccionado: Codo abajo\n');
            q1_2=beta-alpha;
            q2_2=pi-gamma;
            q3_2=phi-q2_2-q1_2;
            Q=[q1_2 q2_2 q3_2];
            return
        case 0
            fprintf('\n###### Modo seleccionado: Ambas soluciones [codo arriba; codo abajo]\n');
            q1_1=beta+alpha;
            q2_1=-(pi-gamma);
            q3_1=phi-q2_1-q1_1;
            q1_2=beta-alpha;
            q2_2=pi-gamma;
            q3_2=phi-q2_2-q1_2;
            Q=[q1_1 q2_1 q3_1; q1_2 q2_2 q3_2];
            return
        otherwise
            fprintf("\nERROR: Modo no valido. Introduce 0, -1 (codo arriba) o 1 (codo abajo).\n")
            return
    end
end

