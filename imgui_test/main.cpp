#include "Application.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
//#include "ImGuiFileDialog.h"
#include <GL/gl3w.h>            // GL3w, initialized with gl3wInit() below
#include <GLFW/glfw3.h> // 引入GLFW库
#include <stdio.h>
int main()
{

	// Setup window
	//glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		return 1;
	}

	// Use GL 3.2 (All Platforms)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// 设置窗口和OpenGL上下文
	// 创建隐藏的GLFW窗口
	//glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // 隐藏窗口
	GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Table Example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // 开启垂直同步

	// Initialize OpenGL loader
	if (gl3wInit() != 0) {
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// 设置ImGui上下文
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsLight();
	ImFont* myFont = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 18.0f,
		NULL, io.Fonts->GetGlyphRangesChineseFull());


	// 获取ImGui的样式引用
	//ImGuiStyle& style = ImGui::GetStyle();

	// 设置窗口背景颜色为白色，颜色值的格式是0到1之间的浮点数
	//style.Colors[ImGuiCol_WindowBg] = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); // 

	// 初始化ImGui平台和渲染器绑定
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");


	// 主循环
	while (!glfwWindowShouldClose(window))
	{
		// 处理输入
		glfwPollEvents();



		// 开始ImGui帧
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		App::RenderUI();

		// 渲染ImGui帧
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	// 清理资源
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}