#pragma once

#define MAX_DISPARITY 20

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
		this->max_disparity = MAX_DISPARITY;

		// Default and has to be initialized later on
		this->dx = 0;
		this->dy = 0;
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
	float max_disparity;	// (1.0/max_disparity) => Normalized pixel "thickness" in Z-axis
};

extern ConstantParameters * ConstantParametersBuffer;