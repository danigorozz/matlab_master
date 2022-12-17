
mu = 100;
sig = 300.79;
x = linspace(0,900,900);
y = gaussmf(x,[mu,sig]);
plot(x, y, 'LineWidth',3, 'DisplayName','Prob. Distribution')
hold on
plot(833, 0, 'r.', 'MarkerSize', 20, 'DisplayName','Deadline')
plot(576.1, 0, 'k.', 'MarkerSize', 20, 'DisplayName','WCET')
plot(300.79, 0, 'g.', 'MarkerSize', 20, 'DisplayName','ACET')
legend()
%%
figure()
mu = 100;
sig = 600;
x = linspace(0,900,900);
y = gaussmf(x,[mu,sig]);
plot(x, y, 'LineWidth',3, 'DisplayName','Prob. Distribution')
hold on
plot(833, 0, 'r.', 'MarkerSize', 20, 'DisplayName','Deadline')
%plot(576.1, 0, 'k.', 'MarkerSize', 20, 'DisplayName','WCET')
plot(600, 0, 'g.', 'MarkerSize', 20, 'DisplayName','ACET')
legend()
%%
figure() 
hax=axes; 
x=0:1:833;
ylim([0 1.5])
hold on 
SP=833; %your point goes here 
h(1) = line([SP SP],[0 1],'Color',[0 1 0], 'LineWidth', 3, 'DisplayName', 'Utility Function');
h(2) = line([0 SP],[1 1],'Color',[0 1 0], 'LineWidth', 3);
h(3) = plot(833, 0, 'r.', 'MarkerSize', 20, 'DisplayName','Deadline');
legend([h(1) h(3)])