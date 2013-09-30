Matlab demo code accompanying the CVPR11 paper
[C. Rhemann, A. Hosni, M. Bleyer, C. Rother, M. Gelautz, Fast Cost-Volume Filtering for Visual Correspondence and Beyond, CVPR11]

Contributed by Christoph Rhemann (rhemann@ims.tuwien.ac.at)

-----------------------------------------------------------------------------

Important notes:

(1) To run our code you need to additionally download the "Guided Image Filter" [K. He, J. Sun, X. Tang, Guided Image Filtering, ECCV10] from Kaiming He's website (http://personal.ie.cuhk.edu.hk/~hkm007/) and extract the files "guidedfilter_color.m" and "boxfilter.m" into the same directory as the other Matlab files.

(2) The code is provided for academic use only. Use of the code in any commercial or industrial related activities is prohibited. 

(3) If you use our code we request that you cite the paper [C. Rhemann, A. Hosni, M. Bleyer, C. Rother, M. Gelautz, Fast Cost-Volume Filtering for Visual Correspondence and Beyond, CVPR11]

(4) Please note that the running time and results reported in the paper is from a CUDA implementation. Hence, results and running times do not match this Matlab implementation.

-----------------------------------------------------------------------------

Usage:

Run “runStereoMatcher.m” to see results for the 4 Middlebury test images.