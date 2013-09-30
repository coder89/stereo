function medianFiltered = weightedMedianMatlab(left_img,disp_img,winsize,gamma_c,gamma_p)

[h,w,c] = size(left_img);

smoothed_left_img = medfilt2(left_img(:,:,1));
smoothed_left_img(:,:,2) = medfilt2(left_img(:,:,2));
smoothed_left_img(:,:,3) = medfilt2(left_img(:,:,3));

radius = floor(winsize/2);

medianFiltered = zeros(h,w);
for y = 1:h
    for x = 1:w
        maskVals = double(filtermask(smoothed_left_img, x, y, winsize,gamma_c,gamma_p));
        dispVals = disp_img(max(1,y-radius):min(h,y+radius),max(1,x-radius):min(w,x+radius));
        maxDispVal = max(dispVals(:));
        
        % Make histogram
        hist = sparse(1,dispVals(:),maskVals(:),1,maxDispVal);
        hist_sum = sum(hist(:));
        hist_cumsum = cumsum(hist);
        
        possbileDispVals = 1:maxDispVal;
        medianval = possbileDispVals(hist_cumsum>(hist_sum/2));
        medianFiltered(y,x) = medianval(1);
    end
end

end