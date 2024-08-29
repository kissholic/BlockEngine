/*
 * File: GraphicsContext.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */


#include <vector>

#define GLFW_INCLUDE_OPENGL
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Graphics/GraphicsContext.h"


namespace be {


GraphicsContext::GraphicsContext(int Width, int Height, const std::string& Title)
        : mTitle(Title)
        , mWindow(nullptr)
        , mWidth(Width)
        , mHeight(Height)
{ 
}


GraphicsContext::~GraphicsContext() {
    ImGuiTerminate();
    GLTerminate();
    GLFWTerminate();
}


bool GraphicsContext::Init() noexcept {
    if (!GLFWInit()) {
        return false;
    }

    if (!GLInit()) {
        return false;
    }
    
    if (!ImGuiInit()) {
        return false;
    }

    return true;
}


void GraphicsContext::Step(double DeltaTime) noexcept {
    ImGuiStepPrev();
    ImGuiStep(DeltaTime);
    ImGuiStepPost();

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}


bool GraphicsContext::ShouldExit() noexcept {
    return glfwWindowShouldClose(mWindow);
}


bool GraphicsContext::GLFWInit() noexcept {
    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW");
        return false;
    }

    // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
    if (!mWindow) {
        spdlog::error("Failed to create GLFW window");
        return false;
    }

    glfwMakeContextCurrent(mWindow);
    glfwSetWindowUserPointer(mWindow, this);

    // Set error callback
    glfwSetErrorCallback([](int Error, const char* Description) {
        spdlog::error("GLFW Error {}: {}", Error, Description);
    });

    // Set keyboard input callback
    glfwSetKeyCallback(mWindow, [](GLFWwindow* Window, int Key, [[maybe_unused]] int Scancode, int Action, [[maybe_unused]] int Mods) {
        if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS) {
            glfwSetWindowShouldClose(Window, GLFW_TRUE);
        }
    });

    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* Window, int Width, int Height) {
        auto* Context = reinterpret_cast<GraphicsContext*>(glfwGetWindowUserPointer(Window));
        Context->mWidth = Width;
        Context->mHeight = Height;
        glViewport(0, 0, Context->mWidth, Context->mHeight);
    });

    return true;
}


void GraphicsContext::GLFWTerminate() noexcept {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}


bool GraphicsContext::GLInit() noexcept {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD");
        return false;
    }

    glViewport(0, 0, mWidth, mHeight);

    return true;
}

void GraphicsContext::GLTerminate() noexcept {
}


bool GraphicsContext::ImGuiInit() noexcept {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
	ImGui_ImplOpenGL3_Init();

	return true;
}


void GraphicsContext::ImGuiTerminate() noexcept {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


void GraphicsContext::ImGuiStepPrev() noexcept {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}


void GraphicsContext::ImGuiStep(double DeltaTime) noexcept {
	ImGui::Begin("Config Menu");

    ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
    static float f;
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::Spacing();

    ImGui::End();
}


void GraphicsContext::ImGuiStepPost() noexcept {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


} // namespace be
