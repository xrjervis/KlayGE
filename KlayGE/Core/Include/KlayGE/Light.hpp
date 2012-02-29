// Light.hpp
// KlayGE Light header file
// Ver 3.12.0
// Copyright(C) Minmin Gong, 2011
// Homepage: http://www.klayge.org
//
// 3.12.0
// First release (2011.1.12)
//
// CHANGE LIST
/////////////////////////////////////////////////////////////////////////////////

#ifndef _LIGHT_HPP
#define _LIGHT_HPP

#pragma once

#ifndef KLAYGE_CORE_SOURCE
#define KLAYGE_LIB_NAME KlayGE_Core
#include <KlayGE/config/auto_link.hpp>
#endif

#include <KlayGE/PreDeclare.hpp>

#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 6011)
#endif
#include <boost/smart_ptr.hpp>
#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(pop)
#endif
#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 6385)
#endif
#include <boost/array.hpp>
#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(pop)
#endif
#include <boost/function.hpp>

namespace KlayGE
{
	enum LightType
	{
		LT_Ambient = 0,
		LT_Point,
		LT_Directional,
		LT_Spot,

		LT_NumLightTypes
	};

	enum LightSrcAttrib
	{
		LSA_NoShadow = 1UL << 0,
		LSA_NoDiffuse = 1UL << 1,
		LSA_NoSpecular = 1UL << 2,
		LSA_IndirectLighting = 1UL << 3
	};

	class KLAYGE_CORE_API LightSource : public boost::enable_shared_from_this<LightSource>
	{
	public:
		explicit LightSource(LightType type);
		virtual ~LightSource();

		LightType Type() const;

		int32_t Attrib() const;
		void Attrib(int32_t attrib);

		bool Enabled() const;
		void Enabled(bool enabled);

		void BindUpdateFunc(boost::function<void(LightSource&, float, float)> const & update_func);

		virtual void Update(float app_time, float elapsed_time);

		virtual void AddToSceneManager();
		virtual void DelFromSceneManager();

		float4 const & Color() const;
		void Color(float3 const & clr);

		virtual float3 const & Position() const;
		virtual void Position(float3 const & pos);
		virtual float3 Direction() const;
		virtual void Direction(float3 const & dir);
		virtual Quaternion const & Rotation() const;
		virtual void Rotation(Quaternion const & quat);
		virtual void ModelMatrix(float4x4 const & model);
		virtual float3 const & Falloff() const;
		virtual void Falloff(float3 const & fall_off);
		virtual float CosInnerAngle() const;
		virtual void InnerAngle(float angle);
		virtual float CosOuterAngle() const;
		virtual void OuterAngle(float angle);
		virtual float4 const & CosOuterInner() const;

		virtual TexturePtr const & ProjectiveTexture() const;
		virtual void ProjectiveTexture(TexturePtr const & tex);

		virtual ConditionalRenderPtr const & ConditionalRenderQuery(uint32_t index) const;
		virtual CameraPtr const & SMCamera(uint32_t index) const;

	protected:
		LightType type_;
		int32_t attrib_;
		bool enabled_;
		float4 color_;

		boost::function<void(LightSource&, float, float)> update_func_;
	};

	class KLAYGE_CORE_API AmbientLightSource : public LightSource
	{
	public:
		AmbientLightSource();
		virtual ~AmbientLightSource();
	};

	class KLAYGE_CORE_API PointLightSource : public LightSource
	{
	public:
		PointLightSource();
		virtual ~PointLightSource();

		float3 const & Position() const;
		void Position(float3 const & pos);
		float3 Direction() const;
		void Direction(float3 const & dir);
		Quaternion const & Rotation() const;
		void Rotation(Quaternion const & quat);
		void ModelMatrix(float4x4 const & model);

		float3 const & Falloff() const;
		void Falloff(float3 const & fall_off);

		TexturePtr const & ProjectiveTexture() const;
		void ProjectiveTexture(TexturePtr const & tex);

		ConditionalRenderPtr const & ConditionalRenderQuery(uint32_t index) const;
		CameraPtr const & SMCamera(uint32_t index) const;

	protected:
		void UpdateCameras();

	protected:
		Quaternion quat_;
		float3 pos_;
		float3 falloff_;

		TexturePtr projective_tex_;

		boost::array<ConditionalRenderPtr, 7> crs_;
		boost::array<CameraPtr, 6> sm_cameras_;
	};

	class KLAYGE_CORE_API SpotLightSource : public LightSource
	{
	public:
		SpotLightSource();
		virtual ~SpotLightSource();

		float3 const & Position() const;
		void Position(float3 const & pos);
		float3 Direction() const;
		void Direction(float3 const & dir);
		Quaternion const & Rotation() const;
		void Rotation(Quaternion const & quat);
		void ModelMatrix(float4x4 const & model);

		float3 const & Falloff() const;
		void Falloff(float3 const & falloff);

		float CosInnerAngle() const;
		void InnerAngle(float angle);

		float CosOuterAngle() const;
		void OuterAngle(float angle);

		float4 const & CosOuterInner() const;

		TexturePtr const & ProjectiveTexture() const;
		void ProjectiveTexture(TexturePtr const & tex);

		ConditionalRenderPtr const & ConditionalRenderQuery(uint32_t index) const;
		CameraPtr const & SMCamera(uint32_t index) const;

	protected:
		void UpdateCamera();

	protected:
		Quaternion quat_;
		float3 pos_;
		float3 falloff_;
		float4 cos_outer_inner_;

		TexturePtr projective_tex_;

		ConditionalRenderPtr cr_;
		CameraPtr sm_camera_;
	};

	class KLAYGE_CORE_API DirectionalLightSource : public LightSource
	{
	public:
		DirectionalLightSource();
		virtual ~DirectionalLightSource();

		float3 Direction() const;
		void Direction(float3 const & dir);
		Quaternion const & Rotation() const;
		void Rotation(Quaternion const & quat);
		void ModelMatrix(float4x4 const & model);

		float3 const & Falloff() const;
		void Falloff(float3 const & falloff);

	protected:
		Quaternion quat_;
		float3 falloff_;
	};
}

#endif		// _LIGHT_HPP
