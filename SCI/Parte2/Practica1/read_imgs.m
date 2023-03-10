function images = read_imgs(imgs_directory)
    
    directory = strcat(imgs_directory,'/*.png');
    imagefiles = dir(directory);
    nfiles = length(imagefiles);
    
    for i = 1:nfiles
        directory = strcat(imgs_directory,'/', imagefiles(i).name);
        images{i} = imread(directory);
    end

end

