// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Rendering/IRenderTarget.h"

// ------------------------------------------------------------

namespace ost
{
	class CTextureRenderTarget : public IRenderTarget
	{
	public:
		void Create(uint32 w, uint32 h);
		void Resize(uint32 w, uint32 h);

		void Bind();
		void Unbind();
		uint32 GetW() const;
		uint32 GetH() const;

	private:
		void CreateResources();
		void DeleteResources();

		uint32 _width;
		uint32 _height;

		uint32 _frameBufferObjectID;
		uint32 _colorAttachmentID;
		uint32 _depthStencilAttachmentID;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------