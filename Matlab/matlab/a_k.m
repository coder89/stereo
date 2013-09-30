function [ result ] = a_k( I, f, r, covariance, mean )

    w = ones(r);
    sumW = sum(sum(w));
    [x,y,z] = size(I);
    I_pad = padarray(I, [r r], 'replicate');
    f_pad = padarray(f, [r r], 'replicate');
    
    result = zeros(x,y,z);
    for i=1:x
       for j=1:y
           
           k = [i, j];
           Ii = I_pad((k(1)):(k(1)+2*r),(k(2)):(k(2)+2*r),:);
           fi = f_pad((k(1)):(k(1)+2*r),(k(2)):(k(2)+2*r),:);
           fmean = (1 / sumW) * sum(sum(fi));
           fIsum = [sum(sum(Ii(:,:,1) .* fi)) 
                    sum(sum(Ii(:,:,2) .* fi)) 
                    sum(sum(Ii(:,:,3) .* fi))];
           uf = reshape(mean(1,1,:), [3 1]) * fmean;
           result(k(1), k(2), :) = covariance(:,:,k(1),k(2)) * ((1 / sumW) * fIsum - uf);
           
       end
    end
    
end

