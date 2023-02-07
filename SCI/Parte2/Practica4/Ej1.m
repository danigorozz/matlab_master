P=[1 1 0 0; 
   1 0 1 0]; %patrones de entrada
T=[1 1 1 0]; %salidas deseadas para esos patrones
red=newp(minmax(P),1,'hardlim'); %creación del perceptrón simple con una neurona binaria
red=train(red,P,T); %entrenamiento de la red
S=sim(red,P); %salidas para los patrones de entrenamiento

w=red.IW{1};%se asignan los pesos a la variable w
b=red.b{1}; %se asigna el umbral a la variable b
plotpv(P,T); %gráfico de entradas frente a salidas
hold on; %se mantiene la gráfica anterior
plotpc(w,b); %se muestra la recta de separación