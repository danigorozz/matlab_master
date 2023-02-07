%% Creating datasets

% Generation of 51 points in interval [-1, 1]
numPts = 51;
x = linspace(-1, 1, numPts)';

% Generate data output by a function
y = 0.6*sin(pi*x) + 0.3*sin(3*pi*x) + 0.1*sin(5*pi*x);
data = [x y];

% Get training a validation datasets
trndata = data(1:2:numPts,:); % Odd indexes for training
chkdata = data(2:2:numPts,:); % Even indexes for validation

% Plot training anda validation data
plot(trndata(:,1),trndata(:,2),'o',chkdata(:,1), chkdata(:,2),'x');
legend('Training data', 'Validation data');
title('Training and validation data')

%% Configuration of the fuzzy system

% Define the number of MF and its type
numMFs=5;
mfType = 'gbellmf';

% Generate FIS-matrix and plot MFs
fismat = genfis1(trndata, numMFs, mfType);
[x, mf] = plotmf(fismat,'input',1);
plot(x,mf);
title('Membership Functions with gbell shape')

%% ANFIS training

% Define number of epochs/episodes/rounds
numEpochs = 40;

% Train
[fismat1, trnErr, ss, fismat2, chkErr] = anfis(trndata, fismat, numEpochs, NaN, chkdata);
fprintf('\n\n TRAINING PROCESS COMPLETED\n\n\n');

%% Validation

% Get RMSE of training and validation predictions
trnOut = evalfis(fismat1, trndata(:,1));
trnRMSE = norm(trnOut-trndata(:,2))/sqrt(length(trnOut));
trn_label = sprintf('\nTraining error = %.4f\n', trnRMSE);
chkOut = evalfis(fismat2, chkdata(:,1));
chkRMSE = norm(chkOut-chkdata(:,2))/sqrt(length(chkOut));
chk_label = sprintf('Validation error = %.4f\n', chkRMSE);

% Plot error curves
epoch = 1:numEpochs;
%plot(epoch,trnErr,'o',epoch,chkErr,'x');
%hold on;
plot(epoch,[trnErr chkErr]);
%hold off;
legend('Training error', 'Validation error');
title('Error curves')
text(20,0.05,trn_label);
text(20,0.045,chk_label);

%% Ploting interesting features

% Evolution of step size
figure()
plot(epoch,ss,'-',epoch,ss,'x');
title('Evolution of step size during training')

% MFs before and after training
figure();
subplot(2,1,1);
[x,mf] = plotmf(fismat,'input',1);
plot(x,mf);
title('MFs before training');
subplot(2,1,2);
[x,mf] = plotmf(fismat1, 'input',1);
plot(x,mf);
title('MFs after training');

% Output and data comparation
figure();
anfis_y = evalfis(x(:,1),fismat1);
plot(trndata(:,1),trndata(:,2),'o',chkdata(:,1), chkdata(:,2),'x',x,anfis_y,'-');
legend('Training data', 'Validation data', 'Output');
title('Comparaison between training and validation data and output')