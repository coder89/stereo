#pragma once

#include <stack>

class Texture
{
public:

	Texture(Windows::Foundation::Size size, ID3D11Device * device);

	const Windows::Foundation::Size Size;
	ID3D11Texture2D * Resource;
	ID3D11ShaderResourceView * ResourceView;
	ID3D11RenderTargetView * RenderTarget;
	
};

class TextureCache
{
public:

	static TextureCache * Instance(Windows::Foundation::Size size, ID3D11Device * device);

	Concurrency::task<void> InitializeAsync();

	const Texture * Alloc()
	{
		const Texture * tmp = m_available_stack.top();
		m_available_stack.pop();
		m_inuse_set.insert(tmp);
		return tmp;
	}

	void Free(const Texture * texture)
	{
		auto tmp = m_inuse_set.erase(texture);
		if (tmp <= 0)
			return;
		m_available_stack.push(texture);
	}

private:
	
	TextureCache(Windows::Foundation::Size size, ID3D11Device * device);

	std::stack<const Texture*> m_available_stack;
	std::set<const Texture*> m_inuse_set;

	ID3D11Device * m_device;
	Windows::Foundation::Size m_size;

};
