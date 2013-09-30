function [ result ] = imgrad( I )

    [x,y,~] = size(I);

    % Calculate gradient:
    f_gradient = @(I,x,y) ((I(1:(x-2),:,:) - I(3:x,:,:)) / 2);
    result = padarray(f_gradient(I,x,y),[1 0]);

end

