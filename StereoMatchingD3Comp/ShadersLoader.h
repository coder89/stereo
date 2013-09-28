#pragma once

#include "Direct3DBase.h"
#include "Config.h"

class ShadersLoader
{
public:

	static Concurrency::task<void> LoadVS(Platform::String^ fileName, 
											const D3D11_INPUT_ELEMENT_DESC * layout, 
											uint8 inputCount,
											ID3D11Device * device, 
											ID3D11VertexShader * * result, 
											ID3D11InputLayout * * inputLayout);

	static Concurrency::task<void> LoadPS(Platform::String^ fileName, 
											ID3D11Device * device, 
											ID3D11PixelShader * * result);
};