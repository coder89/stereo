#include "pch.h"
#include "Config.h"
#include "ShadersLoader.h"

Concurrency::task<void> ShadersLoader::LoadVS(Platform::String^ fileName, const D3D11_INPUT_ELEMENT_DESC * layout, uint8 inputCount, ID3D11Device * device, ID3D11VertexShader * * result, ID3D11InputLayout * * inputLayout)
{
	return DX::ReadDataAsync(fileName)
		.then([layout, inputCount, device, result, inputLayout](Platform::Array<byte>^ fileData) {

			DX::ThrowIfFailed(
				device->CreateVertexShader(
				fileData->Data,
				fileData->Length,
				nullptr,
				result
				)
				);

			DX::ThrowIfFailed(
				device->CreateInputLayout(
				layout,
				inputCount,
				fileData->Data,
				fileData->Length,
				inputLayout
				)
				);
	});
}

Concurrency::task<void> ShadersLoader::LoadPS(Platform::String^ fileName, ID3D11Device * device, ID3D11PixelShader * * result)
{
	return DX::ReadDataAsync(fileName)
		.then([device, result](Platform::Array<byte>^ fileData) {
			DX::ThrowIfFailed(
				device->CreatePixelShader(
				fileData->Data,
				fileData->Length,
				nullptr,
				result
				)
				);
	});
}