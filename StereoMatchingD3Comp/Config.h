#pragma once

#define MAX_DISPARITY 16

__declspec(align(16)) struct ConstantParameters
{
	ConstantParameters(	float r,
						float epsilon,
						float alpha,
						float sigma_s,
						float sigma_c,
						float Tc,
						float Tg )
	{
		this->r = r;
		this->epsilon = epsilon;
		this->alpha = alpha;
		this->sigma_s = sigma_s;
		this->sigma_c = sigma_c;
		this->Tc = Tc;
		this->Tg = Tg;

		// Default and has to be initialized later on
		this->dx = 0;
		this->dy = 0;
		this->dz = 1.0f / (float) MAX_DISPARITY;
	}

	// Algorithm parameters
	float r;
	float epsilon;
	float alpha;
	float sigma_s;
	float sigma_c;
	float Tc;
	float Tg;

	// Image metrics
	float dx;				// Normalized pizel width
	float dy;				// Normalized pixel height
	float dz;				// Normalized pixel "thickness" in Z-axis => (1.0/dz) = max_disparity
};

#if MAX_DISPARITY % 16
	#error MAX_DISTARITY has to be dividable by 4!
#endif

extern ConstantParameters * ConstantParametersBuffer;