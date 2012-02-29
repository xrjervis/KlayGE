#ifndef _PARTICLESYSTEMAPP_HPP
#define _PARTICLESYSTEMAPP_HPP

#include <KlayGE/PreDeclare.hpp>
#include <KlayGE/App3D.hpp>
#include <KlayGE/Font.hpp>
#include <KlayGE/CameraController.hpp>
#include <KlayGE/ParticleSystem.hpp>
#include <KlayGE/Timer.hpp>
#include <KlayGE/PostProcess.hpp>
#include <KlayGE/UI.hpp>

#include <boost/function.hpp>

struct Particle
{
	KlayGE::float3 pos;
	KlayGE::float3 vel;
	float life;
	float spin;
	float birth_time;
};

class ParticleEditorApp : public KlayGE::App3DFramework
{
public:
	ParticleEditorApp();

	bool ConfirmDevice() const;

private:
	void InitObjects();
	void OnResize(KlayGE::uint32_t width, KlayGE::uint32_t height);
	void DoUpdateOverlay();
	KlayGE::uint32_t DoUpdate(KlayGE::uint32_t pass);

	void InputHandler(KlayGE::InputEngine const & sender, KlayGE::InputAction const & action);
	void OpenHandler(KlayGE::UIButton const & sender);
	void SaveAsHandler(KlayGE::UIButton const & sender);
	void AngleChangedHandler(KlayGE::UISlider const & sender);
	void LifeChangedHandler(KlayGE::UISlider const & sender);
	void DensityChangedHandler(KlayGE::UISlider const & sender);
	void MinVelocityChangedHandler(KlayGE::UISlider const & sender);
	void MaxVelocityChangedHandler(KlayGE::UISlider const & sender);
	void FPSCameraHandler(KlayGE::UICheckBox const & sender);
	void ChangeParticleAlphaFromHandler(KlayGE::UITexButton const & sender);
	void ChangeParticleAlphaToHandler(KlayGE::UITexButton const & sender);
	void ChangeParticleColorFromHandler(KlayGE::UITexButton const & sender);
	void ChangeParticleColorToHandler(KlayGE::UITexButton const & sender);
	void CurveTypeChangedHandler(KlayGE::UIComboBox const & sender);

	void LoadParticleAlpha(int id, std::string const & name);
	void LoadParticleColor(int id, KlayGE::Color const & clr);

	void LoadParticleSystem(std::string const & name);
	void SaveParticleSystem(std::string const & name);

	KlayGE::FontPtr font_;

	KlayGE::SceneObjectPtr particles_;
	KlayGE::SceneObjectPtr terrain_;

	KlayGE::FirstPersonCameraController fpsController_;

	boost::shared_ptr<KlayGE::ParticleSystem<Particle> > ps_;
	float init_life_;

	std::string particle_alpha_from_tex_;
	std::string particle_alpha_to_tex_;
	KlayGE::Color particle_color_from_;
	KlayGE::Color particle_color_to_;

	KlayGE::TexturePtr scene_tex_;
	KlayGE::FrameBufferPtr scene_buffer_;

	KlayGE::PostProcessPtr copy_pp_;

	KlayGE::UIDialogPtr dialog_;
	int id_open_;
	int id_save_as_;
	int id_angle_static_;
	int id_angle_slider_;
	int id_life_static_;
	int id_life_slider_;
	int id_density_static_;
	int id_density_slider_;
	int id_min_velocity_static_;
	int id_min_velocity_slider_;
	int id_max_velocity_static_;
	int id_max_velocity_slider_;
	int id_fps_camera_;
	int id_particle_alpha_from_button_;
	int id_particle_alpha_to_button_;
	int id_particle_color_from_button_;
	int id_particle_color_to_button_;
	int id_curve_type_;
	int id_size_over_life_;
	int id_weight_over_life_;
	int id_transparency_over_life_;
};

#endif		// _PARTICLESYSTEMAPP_HPP
