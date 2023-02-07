%% Comparativa de incremento de V para dos modos de acondicionamiento:
%  Fuente de corriente
%  Divisor de tension

R1 = 339.63;        % R a 124.9º
R2 = 338.74;        % R a 125º
Rref = 10e3;        % R de referencia del divisor

i = 25e-6           % De la fuente de corriente
Vsource = 1.2       % Del divisor de tension

% Incremento de V en el circuito con fuente de corriente
Vincr_i = i*(R1-R2)

% Incremento de V en el circuito con divisor de tension
Vtalta = Vsource * ( R1/(Rref+R1) );
Vtbaja = Vsource * ( R2/(Rref+R2) );

Vincr_v = Vtalta - Vtbaja

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
ADCres = log10(ADCcounts)/log10(2)      % 15 bits necesarios

%% Apartado 7.2.2
Rref = 10e3;
tolerance = 0.02;
drift = 350e-6;

Tmin = -40;
Tmax = 125;

Rref_dev_m40_1 = Rref + Rref*( -tolerance + drift*(Tmin-25) )
Rref_dev_m40_2 = Rref + Rref*(  tolerance + drift*(Tmin-25) )
Rref_dev_125_1 = Rref + Rref*(  tolerance + drift*(Tmax-25) )
Rref_dev_125_2 = Rref + Rref*( -tolerance + drift*(Tmax-25) )

Rt_m40 = 332093.6;
Rt_125 = 338.74;

RT_dev_m40_1 = Rt_m40*(Rref_dev_m40_1/Rref)
RT_dev_125_1 = Rt_125*(Rref_dev_125_1/Rref)
RT_dev_m40_2 = Rt_m40*(Rref_dev_m40_2/Rref)
RT_dev_125_2 = Rt_125*(Rref_dev_125_2/Rref)

Tm40_dev_1 = (-40-r2t(RT_dev_m40_1))
Tm40_dev_2 = (-40-r2t(RT_dev_m40_2))
T125_dev_1 = (125-r2t(RT_dev_125_1))
T125_dev_2 = (125-r2t(RT_dev_125_2))

%% Apartado 7.2.3
tolerance = 0.02;
Rt_m40 = 332093.6;
Rt_125 = 338.74;

RT_dev_m40_1 = Rt_m40*(1+tolerance);
RT_dev_m40_2 = Rt_m40*(1-tolerance);
RT_dev_125_1 = Rt_125*(1+tolerance);
RT_dev_125_2 = Rt_125*(1-tolerance);

Tm40_dev_1 = (-40-r2t(RT_dev_m40_1))
Tm40_dev_2 = (-40-r2t(RT_dev_m40_2))
T125_dev_1 = (125-r2t(RT_dev_125_1))
T125_dev_2 = (125-r2t(RT_dev_125_2))

%% Apartado 7.2.3.2
Rt_m40 = 332093.6;
Rt_25 = 10e3;
Rt_125 = 338.74;
Rref = 10e3;

C = 2.2e-3;

Vsource = 1.2;

I_m40 = Vsource/(Rt_m40+Rref);
I_25 = Vsource/(Rt_25+Rref);
I_125 = Vsource/(Rt_125+Rref);

eT_m40 = (Rt_m40*(I_m40)^2)/C
eT_25 = (Rt_25*(I_25)^2)/C
eT_125 = (Rt_125*(I_125)^2)/C

%% Funciones

function T = r2t(R)
    A1 = 0.003354016;
    B1 = 0.000256985;
    C1 = 2.62013e-6;
    D1 = 6.38309e-8;

    R25 = 10e3;
    T = 1/(A1 + B1*log(R/R25) + C1*(log(R/R25))^2 + D1*(log(R/R25))^3) -273.15;

end
