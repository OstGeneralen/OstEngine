// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Rendering/TextureRenderTarget.h"

#include <glad/glad.h>
#include <glfw3.h>

// ------------------------------------------------------------

void ost::CTextureRenderTarget::Create(uint32 w, uint32 h)
{
	_width = w;
	_height = h;
	CreateResources();
}

// ------------------------------------------------------------

void ost::CTextureRenderTarget::Resize(uint32 w, uint32 h)
{
	_width = w;
	_height = h;
	DeleteResources();
	CreateResources();
}

// ------------------------------------------------------------

void ost::CTextureRenderTarget::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferObjectID);
	glViewport(0, 0, _width, _height);
}

// ------------------------------------------------------------

void ost::CTextureRenderTarget::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// ------------------------------------------------------------

ost::uint32 ost::CTextureRenderTarget::GetW() const 
{
	return _width;
}

// ------------------------------------------------------------

ost::uint32 ost::CTextureRenderTarget::GetH() const
{
	return _height;
}

// ------------------------------------------------------------

void ost::CTextureRenderTarget::CreateResources()
{
	glGenFramebuffers(1, &_frameBufferObjectID);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferObjectID);

	glGenTextures(1, &_colorAttachmentID);
	glBindTexture(GL_TEXTURE_2D, _colorAttachmentID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachmentID, 0);

	glGenRenderbuffers(1, &_depthStencilAttachmentID);
	glBindRenderbuffer(GL_RENDERBUFFER, _depthStencilAttachmentID);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthStencilAttachmentID);

	glBindBuffer(GL_FRAMEBUFFER, 0);
}

// ------------------------------------------------------------

void ost::CTextureRenderTarget::DeleteResources()
{
	if(_frameBufferObjectID != 0)		glDeleteFramebuffers(1, &_frameBufferObjectID);
	if(_colorAttachmentID != 0)			glDeleteTextures(1, &_colorAttachmentID);
	if(_depthStencilAttachmentID != 0)	glDeleteRenderbuffers(1, &_depthStencilAttachmentID);

	_frameBufferObjectID = 0;
	_colorAttachmentID = 0;
	_depthStencilAttachmentID = 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------