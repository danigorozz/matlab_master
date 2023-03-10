data = [rand(10,1) 10*rand(10,1)-5 rand(10,1)];
fis = genfis1(data,[3 7],char('pimf','trimf'));
[x,mf] = plotmf(fis,'input',1);
subplot(2,1,1); plot(x,mf);
xlabel('Input 1 (pimf)');
title('Pi-shaped type');
[x,mf] = plotmf(fis,'input',2);
subplot(2,1,2),;plot(x,mf);
xlabel('Input 2 (trimf)');
title('Triangular type');