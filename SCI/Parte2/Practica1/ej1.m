

x1 = [1 1 1 -1];
x2 = [-1 -1 -1 1];

X = [x1' x2'];

red_hopfield = newhop(X);

num_iter = 250;
%xc = [1 1 1 -1]; % Se estabiliza en la iteración 1
%xc = [-1 -1 -1 -1]; % Se estabiliza en la iteración 5
%xc = [1 1 1 1]; % Se estabiliza en la iteración 5

xc = [1 -1 1 1]; % Se estabiliza en la 239

Y=sim(red_hopfield,{1 num_iter},{},xc');
