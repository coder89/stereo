function [ img_inv_cov, img_mean ] = imstat( I, epsilon )

    [x,y,z] = size(I);
    I_pad = padarray(I,[1 1],'replicate');
    eU = epsilon * eye(3,3);
    img_mean = zeros(x,y,3);
    img_inv_cov = zeros(3,3,x,y);
    
    mask = zeros(x+2, y+2, z);
    mask = logical(mask);
    for i=1:x
        for j=1:y
            mask(i:(i+2), j:(j+2), :) = 1;

            % Apply mask to image
            X_data = I_pad(mask);
            X_data = reshape(X_data, [length(X_data)/z z]);

            % Compute stats
            img_mean(i,j,:) = mean(X_data);
            img_inv_cov(:,:,i,j) = inv(cov(double(X_data)) + eU);

            mask(i:(i+2), j:(j+2), :) = 0;
        end
    end

end

