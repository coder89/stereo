function weights = filtermask(colimg, x, y, winsize,gamma_c,gamma_p)

radius = floor(winsize / 2);
[h,w,c] = size(colimg);

patch_h = length(max(1,y-radius):min(h,y+radius));
patch_w = length(max(1,x-radius):min(w,x+radius));
centercol = colimg(y,x,:);
centercol = repmat(centercol,[patch_h patch_w 1]);

patchYinds = max(1,y-radius):min(h,y+radius);
patchYinds = repmat(patchYinds', [1 patch_w]);
patchXinds = max(1,x-radius):min(w,x+radius);
patchXinds = repmat(patchXinds, [patch_h 1]);

curPatch = colimg(max(1,y-radius):min(h,y+radius),max(1,x-radius):min(w,x+radius),:);
coldiff = sqrt(sum((centercol - curPatch).^2,3));

sdiff = sqrt( (x-patchXinds).^2 + (y-patchYinds).^2 );

weights = exp(-1 * coldiff ./ (gamma_c*gamma_c)).*exp(-1 * sdiff ./ (gamma_p*gamma_p));

end