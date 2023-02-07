close all; clearvars;

% Get images from a folder
train_images = read_imgs('train_digits');
test_images = read_imgs('test_digits');

nimages = length(train_images);
[nrows, ncolumns, ~] = size(train_images{1});
size_of_vector = nrows*ncolumns;
X = zeros(size_of_vector, nimages);


for i=1:nimages
    % Binarize imges to black/white and transform 0 to -1
    aux = double(im2bw(train_images{i}));
    aux(aux == 0) = -1;
    train_images{i} = aux;
    aux = double(im2bw(test_images{i}));
    aux(aux == 0) = -1;
    test_images{i} = aux;

    % Reshape images matrix in vectors
    train_images{i} = reshape(train_images{i}, [1,size_of_vector]);
    test_images{i} = reshape(test_images{i}, [1,size_of_vector]);

    % Put vector in columns in a matrix X
    X(:,i) = train_images{i};
end

%% Get Hopfield net
net = newhop(X);

%% Get output with a input pattern xc
xc = test_images{5};
num_iter = 500; % Define the number of iterations
Y=sim(net,{1 num_iter},{},xc'); % Get outputs

% Transform the output to watch image
match_iter = 500; % i.e. we take the last iteration
output = Y{match_iter}; % Recovered pattern
output = reshape(output, nrows, ncolumns); % Reshape to image dimensions
output(output == -1) = 0; % Transform -1 to 0

% Plot input and output image
figure;
tiledlayout(1,2,'TileSpacing','Compact');
axis off; grid off;
nexttile;
input = reshape(xc, nrows, ncolumns);
input(input == -1) = 0;
imshow(input);
title("INPUT", 'FontSize', 16);
nexttile;
imshow(output);
title("OUTPUT", 'FontSize', 16);


