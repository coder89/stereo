function [ result ] = imshift( I, disparity )

    [x,y,~] = size(I);
    xStart1 = max(1, (1 - disparity(1)));
    yStart1 = max(1, (1 - disparity(2)));
    xStart2 = max(1, (1 + disparity(1)));
    yStart2 = max(1, (1 + disparity(2)));
    xEnd1 = min(x, x - disparity(1));
    yEnd1 = min(y, y - disparity(2));
    xEnd2 = min(x, x + disparity(1));
    yEnd2 = min(y, y + disparity(2));

    I(xStart2:xEnd2,yStart2:yEnd2,:) = I(xStart1:xEnd1,yStart1:yEnd1,:);
    if (xStart2 == 1)
        I((xEnd2+1):x,:,:) = 0;
    else
        I(1:(xStart2-1),:,:) = 0;
    end
    if (yStart2 == 1)
        I(:,(yEnd2+1):y,:) = 0;
    else
        I(:,1:(yStart2-1),:) = 0;
    end
    
    result = I;
    
end

