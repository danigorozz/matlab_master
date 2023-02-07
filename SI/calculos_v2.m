temp = [-40:0.1:125];
rt = load('rt.mat');
rt = rt.rt';

%% Comparativa de incremento de V para dos modos de acondicionamiento:

Rref = 10e3;        % R de referencia del divisor
i = 25e-6;          % De la fuente de corriente
Vsource = 1.2;      % Del divisor de tension

%%%  Fuente de corriente
Vi = i*rt;

% Incremento de V en el circuito con fuente de corriente
Vincr_i = abs(Vi(end) - Vi(end-1));

%%%  Divisor de tension
Vv = Vsource * ( rt ./ (rt + Rref) );

% Incremento de V en el circuito con divisor de tension
Vincr_v = abs(Vv(end) - Vv(end-1));

% Ploteamos tensiones obtenidas de las dos formas
figure(1)
subplot(2,1,1);
plot(temp,Vi, 'LineWidth', 2);
xlim([-40 125]); title('V_{therm} del circuito con fuente de corriente');
xlabel('Temperatura'); ylabel('Tensión');
subplot(2,1,2);
plot(temp,Vv, 'LineWidth', 2);
xlim([-40 125]); title('V_{therm} del circuito con divisor de tensión');
xlabel('Temperatura'); ylabel('Tensión');

%% Apartado 7.1, determinacion de numero de bits
Tres = 0.1;
Tmax = 125;

R1 = 339.63;        % R a 124.9º
R2 = 338.74;        % R a 125º
Rref = 10e3;        % R de referencia del divisor
Vbias = 1.2;        % V de alimentacion

% Incremento de V
Vtalta = Vsource * ( R1/(Rref+R1) );
Vtbaja = Vsource * ( R2/(Rref+R2) );

Vincr = Vtalta - Vtbaja;
Vincr_semi = Vincr/2;

% Caida de V en Rref maxima (a -40º)
Rm40 = 332093.6;
VRref_max = Vsource * ( 1 - Rref/(Rref+Rm40) );

% Cuentas necesarias
ADCcounts = VRref_max/Vincr_semi;

% Resolucion necesaria
ADCres = log10(ADCcounts)/log10(2);     % 15 bits necesarios

%% Apartado 7.2.2
Rref = 10e3;        % Resistencia de referencia
tolerance = 0.01;   % Tolerancia de Rref
drift = 50e-6;     % Deriva de Rref

% Calculamos el error en Rref
dRref_mas = Rref + Rref.*(tolerance + drift .* (temp - 25));
dRref_menos = Rref + Rref.*(-tolerance + drift .* (temp - 25));

% Calculamos el error en termistor
dRt_mas = (rt ./ Rref) .* dRref_mas;
dRt_menos = (rt ./ Rref) .* dRref_menos;

% Calculamos el error en la temperatura
dT_mas = temp - r2t(dRt_mas);
dT_menos = temp - r2t(dRt_menos);

% Ploteamos
plot(temp, dT_mas, temp, dT_menos);
hold on;
plot(temp, (dT_mas+dT_menos)/2, 'k--');
xlabel('Temperatura'); ylabel('Error (ºC)');
title('Error debido a R_{ref} (deriva y tolerancia)');
legend('+tolerance', '-tolerance'); xlim([-40 125]);

%% Apartado 7.2.3
tolerance = 0.02;   % Tolerancia del termistor

% Calculamos el error en el termistor
dRt_mas = rt .* (1 + tolerance);
dRt_menos = rt .* (1 - tolerance);

% Calculamos el error en la temperatura
dT_mas = temp - r2t(dRt_mas);
dT_menos = temp - r2t(dRt_menos);

% Ploteamos
plot(temp, dT_mas, temp, dT_menos);
hold on;
plot(temp, (dT_mas+dT_menos)/2, 'k--');
xlabel('Temperatura'); ylabel('Error (ºC)');
title('Error debido a R_{T} (tolerancia)');
legend('+tolerance', '-tolerance'); xlim([-40 125]);

%% Apartado 7.2.3.2

Rref = 10e3;    % Resistencia de referencia
C = 2.2e-3;     % Constante de disipación térmica
Vsource = 1.2;  % Tensión de alimentación

% Calculamos corriente
I = Vsource ./ (rt + Rref);

% Calculamos el error en tempatura err=P/C
eT = ( rt .* I.^2 ) ./ C;

% Ploteamos
plot(temp, eT);
xlabel('Temperatura'); ylabel('Error (ºC)');
title('Error debido al autocalentamiento de  R_{T}');
xlim([-40 125]);


%% Funciones

function T = r2t(R)
    A1 = 0.003354016;
    B1 = 0.000256985;
    C1 = 2.62013e-6;
    D1 = 6.38309e-8;

    R25 = 10e3;
    T = 1./(A1 + B1.*log(R./R25) + C1.*(log(R./R25)).^2 + D1.*(log(R./R25)).^3) -273.15;

end
