//+---------------------------------------------------------------------------
//  Bluecadet Interactive 2016
//  Contents: 
//  Comments: 
//----------------------------------------------------------------------------
#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Text.h"
#include "StyledTextLayout.h"
#include "BaseView.h"

namespace bluecadet { namespace views {

	typedef std::shared_ptr<class TextView> TextViewRef;

	class TextView : public BaseView, public text::StyledTextLayout {

	public:
		TextView();
		~TextView();

		//! Creates a TextViewRef instance. Convenience method that groups a few calls together.
		static TextViewRef create(const std::string& text = "", const std::string& styleKey = "", const bool parseText = true, const float maxWidth = -1.0f);
		static TextViewRef create(const std::wstring& text = L"", const std::string& styleKey = "", const bool parseText = true, const float maxWidth = -1.0f);
		
		//! Configures a TextView instance. Convenience method that groups a few calls together.
		void setup(const std::wstring& text = L"", const std::string& styleKey = "", const bool parseText = true, const float maxWidth = -1.0f);
		void setup(const std::string& text = "", const std::string& styleKey = "", const bool parseText = true, const float maxWidth = -1.0f);


		virtual void	reset() override;


		//! Will update the text texture if necessary.
		virtual void	willDrawContent() override;
		virtual void	drawContent() override;


		void			animateOn(float alpha, float aniDur, float aniDelay);
		void			animateOff(float alpha, float aniDur, float aniDelay);


		//! Use these methods for more granular rendering control. Textures will otherwise automatically be rendered if necessary when draw() is called.

		bool			getAutoRender() const { return mAutoRender; }
		void			setAutoRender(const bool value) { mAutoRender = value; }

		bool			needsToBeRendered(bool surfaceOnly = false) const;

		//! Renders content. If surfaceOnly is false this will render into a texture and has to be called on the main thread. Surfaces can be rendered on a worker thread.
		void			renderContent(bool surfaceOnly = false, bool alpha = true, bool premultiplied = false, bool force = false);
		void			resetRenderedContent();

		//! Enabling smooth scaling uses mipmapping. Does not affect existing texture. Default is true.
		void			setSmoothScalingEnabled(const bool value) { mSmoothScalingEnabled = value; }
		bool			getSmoothScalingEnabled() const { return mSmoothScalingEnabled; }

	protected:
		ci::gl::Texture::Format createTextureFormat(bool smoothScaling) const;
		virtual inline void		invalidate(const bool layout = true, const bool size = true) override;

		bool				mHasInvalidRenderedContent;
		bool				mSmoothScalingEnabled;
		bool				mAutoRender;
		ci::Surface			mSurface;
		ci::gl::TextureRef	mTexture;


	};
}}