x = (0:0.1:10)';
y = sin(2*x)./exp(x/5);
epoch_n = 20;
in_fis = genfis1([x y],5,'gbellmf');
out_fis = anfis([x y],in_fis,epoch_n);
plot(x,y,x,evalfis(x,out_fis));
legend('Training Data','ANFIS Output');
title('Input - Output comparison')