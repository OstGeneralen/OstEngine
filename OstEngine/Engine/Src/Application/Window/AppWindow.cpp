// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Application/Window/AppWindow.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <glfw3.h>

// ------------------------------------------------------------

void ost::CAppWindow::Create(int w, int h, const char* t)
{
	glfwInit();

	_winPtr = glfwCreateWindow(w, h, "OstEng Window", NULL, NULL);
	glfwMakeContextCurrent(_winPtr);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	// Bind callbacks
	glfwSetWindowUserPointer(_winPtr, this);
	glfwSetKeyCallback(_winPtr, WindowKeyEvent);
}

// ------------------------------------------------------------

void ost::CAppWindow::InitGUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(_winPtr, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	_hasGUIInit = true;
}

// ------------------------------------------------------------

void ost::CAppWindow::Destroy()
{
	if (_hasGUIInit)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	glfwDestroyWindow(_winPtr);
	glfwTerminate();
}

// ------------------------------------------------------------

ost::CTextureRenderTarget& ost::CAppWindow::GetWindowRenderBuffer()
{
	return _windowRenderTarget;
}

// ------------------------------------------------------------

ost::input::CInputEventProvider& ost::CAppWindow::GetInputEventProvider()
{
	return _inputEventProvider;
}

// ------------------------------------------------------------

bool ost::CAppWindow::ShouldRemainOpen() const
{
	return !glfwWindowShouldClose(_winPtr);
}

// ------------------------------------------------------------

void ost::CAppWindow::PollEvents()
{
	glfwPollEvents();
}

// ------------------------------------------------------------

void ost::CAppWindow::BeginWindowRenderFrame()
{
	if (_hasGUIInit)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
}

// ------------------------------------------------------------

void ost::CAppWindow::EndWindowRenderFrame()
{
	ImGui::Render();
	int buffW, buffH;
	glfwGetFramebufferSize(_winPtr, &buffW, &buffH);

	glViewport(0, 0, buffW, buffH);

	const float cc = static_cast<float>(0x10) / 255.0f;
	glClearColor(cc, cc, cc, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	// TODO: Draw the engine scene render texture here
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(_winPtr);
}

// ------------------------------------------------------------

void ost::CAppWindow::WindowKeyEvent(GLFWwindow* win, int kc, int sc, int a, int m)
{
	static_cast<CAppWindow*>(glfwGetWindowUserPointer(win))->_inputEventProvider.ReportKeyboardInput(kc, sc, a, m);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------