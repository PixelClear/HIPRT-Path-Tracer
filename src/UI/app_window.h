#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include "UI/application_settings.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer/renderer.h"
#include "Renderer/open_image_denoiser.h"
#include "Image/image_writer.h"
#include "Utils/commandline_arguments.h"

class AppWindow
{
public:
	static constexpr int DISPLAY_TEXTURE_UNIT = 1;
	static constexpr int DISPLAY_COMPUTE_IMAGE_UNIT = 2;

	struct DisplaySettings
	{
		bool display_normals = false;
		bool scale_by_frame_number = true;
		bool do_tonemapping = true;
		int sample_count_override = -1;
	};



	AppWindow(int width, int height);
	~AppWindow();

	static void APIENTRY gl_debug_output_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	void resize_frame(int pixels_width, int pixels_height);
	void change_resolution_scaling(float new_scaling);

	int get_width();
	int get_height();
	void set_interacting(bool is_interacting);

	ApplicationSettings& get_application_settings();
	const ApplicationSettings& get_application_settings() const;
	Renderer& get_renderer();

	void setup_display_program();
	void set_renderer_scene(Scene& scene);
	void update_renderer_view_translation(float translation_x, float translation_y);
	void update_renderer_view_zoom(float offset);
	void update_renderer_view_rotation(float offset_x, float offset_y);
	void increment_sample_number();
	void reset_sample_number();
	void reset_frame_number();

	std::pair<float, float> get_cursor_position();
	void set_cursor_position(std::pair<float, float> new_position);

	DisplaySettings get_necessary_display_settings();
	void setup_display_uniforms(GLuint program, const AppWindow::DisplaySettings& display_settings);
	void display(const void* data, const AppWindow::DisplaySettings& display_settings = { false, true, true, -1 });
	template <typename T>
	void display(const std::vector<T>& orochi_buffer, const AppWindow::DisplaySettings& display_settings = { false, true, true, -1 });
	template <typename T>
	void display(const OrochiBuffer<T>& orochi_buffer, const AppWindow::DisplaySettings& display_settings = { false, true, true, -1 });

	void show_render_settings_panel();
	void show_denoiser_panel();
	void show_post_process_panel();
	void display_imgui();

	void run();
	void quit();

private:
	int m_viewport_width, m_viewport_height;
	std::pair<float, float> m_cursor_position;
	bool m_interacting;

	std::chrono::high_resolution_clock::time_point m_startRenderTime;

	ApplicationSettings m_application_settings;

	Renderer m_renderer;
	RenderSettings& m_render_settings;
	OpenImageDenoiser m_denoiser;

	ImageWriter m_image_writer;

	GLuint m_display_program;
	GLuint m_display_texture;
	GLFWwindow* m_window;
};

template <typename T>
void AppWindow::display(const std::vector<T>& pixels_data, const AppWindow::DisplaySettings& display_settings)
{
	display(pixels_data.data(), display_settings);
}

template <typename T>
void AppWindow::display(const OrochiBuffer<T>& orochi_buffer, const AppWindow::DisplaySettings& display_settings)
{	
	display(orochi_buffer.download_pixels().data(), display_settings);
}

#endif