function [ result ] = cost_volume( I_left, I_right, disparity, alpha, T_c, T_g )
%#codegen

    I_right = imshift(I_right, disparity);
    G_left = gradient(I_left) + 0.5;
    G_right = gradient(I_right) + 0.5;
    imwrite(G_left,'gradTmpl.pgm');
    imwrite(G_right,'gradTmpr.pgm');
    G_left = single(imread('gradTmpl.pgm'))/255;
    G_right = single(imread('gradTmpr.pgm'))/255;
    fx_l_1 = flipdim(G_right,2);
    fx_r_1 = flipdim(G_left,2);

    % G matrix
    aG = sqrt(sum((G_left - G_right) .^ 2, 3));
    
    % M matrix
    aM = sum(abs(I_left - I_right), 3) / 3;
    
    tmp1 = min(T_c, aM);
    tmp2 = min(T_g, aG);
    
    % result
    result = alpha * tmp1 + (1 - alpha) * tmp2;
    
end

