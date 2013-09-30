
%Il = imread('31_L.jpg');
%Ir = imread('31_R.jpg');
Il = double(imread('im2.png')) / 256;
Ir = double(imread('im6.png')) / 256;

% [gx, gy] = gradient(Il);
% Gl = imgrad(Il);
% Gr = imgrad(Ir);
% 
% figure;
% subplot(1,2,1)
% imshow(gx,[]);
% subplot(1,2,2)
% imshow(Gl,[]);
% 
% return;
% Il = ones([5 5 3]);
% Ir = repmat([[1, 2, 3, 4, 5]
%              [6, 7, 8, 9, 10]
%              [11,12,13,14,15]
%              [16,17,18,19,20]
%              [21,22,23,24,25]]', [1 1 3]);
%          Il=Ir;
% Ir(:,:,2) = Ir(:,:,2) + 25;
% Ir(:,:,3) = Ir(:,:,3) + 50;
[x,y,z] = size(Il);

r = 9;
epsilon = 0.0001;
alpha = 0.9;
sig_s = 9;
sig_c = 0.1;
T_c = 0.028 * ones(x,y);
T_g = 0.008 * ones(x,y);
p = [2, 2];
d = [-1, -1];
w = ones(r,r);

C1 = ones(x, y);
Dx = ones(x, y);
Dy = ones(x, y);
for i=1:10
        
        tmp = cost_volume(Il, Ir, [i i], alpha, T_c, T_g);
        tmp = guidedfilter_color((Il), (tmp), r, epsilon);
        indices = find(tmp < C1);
        C1(indices) = tmp(indices);
        %Dx(indices) = i;
        %Dy(indices) = i;
end
imshow(C1, [])
result = 1;

% close all
% figure
% hold on
% subplot(2, 2, 1);
% imshow(Il);
% subplot(2, 2, 2);
% imshow(Ir);
% subplot(2, 2, [3 4]);
% imshow(C1, [])
% hold off
