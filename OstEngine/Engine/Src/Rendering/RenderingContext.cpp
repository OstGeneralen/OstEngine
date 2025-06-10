// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Rendering/RenderingContext.h"


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <glfw3.h>

// ------------------------------------------------------------

ost::CWindow* ost::CRenderingContext::Initialize(int w, int h)
{
	// Init GLFW and Glad + Create window
	glfwInit();
	const char* glslVer = "#version 130";

	GLFWwindow* windowPtr = glfwCreateWindow(w, h, "OstEng Window", NULL, NULL);
	glfwMakeContextCurrent(windowPtr);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Init open GL (this should be based on flag later)
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(windowPtr, true);
	ImGui_ImplOpenGL3_Init(glslVer);

	// Return the created window
	_windowPtr = windowPtr;
	return new CWindow(windowPtr);
}

// ------------------------------------------------------------

void ost::CRenderingContext::Release(CWindow** pWindow)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	(*pWindow)->Close();
	delete (*pWindow);
	(*pWindow) = nullptr;
	
	glfwTerminate();
}

// ------------------------------------------------------------

void ost::CRenderingContext::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

// ------------------------------------------------------------

void ost::CRenderingContext::EndFrame()
{
	GLFWwindow* ptrWin = (GLFWwindow*)_windowPtr;

	ImGui::Render();
	int buffW, buffH;
	glfwGetFramebufferSize(ptrWin, &buffW, &buffH);
	
	glViewport(0, 0, buffW, buffH);

	const float cc = static_cast<float>(0x10) / 255.0f;
	glClearColor(cc, cc, cc, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(ptrWin);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------