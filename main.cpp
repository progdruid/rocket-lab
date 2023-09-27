#define LAB_WIDTH 800
#define LAB_HEIGHT 600

#include <iostream>
#include <cstring>

#define _ITERATOR_DEBUG_LEVEL 0
#define BX_CONFIG_DEBUG 1;
#include "bx/bx.h"
#include "bimg/bimg.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <Windows.h>
#include "glfw/glfw3.h"
#include "glfw/glfw3native.h"

const char* vertexShaderCode = 
"struct VertexInput {"
"	float3 position : POSITION;"
"	float3 color : COLOR; };"
"struct VertexToPixel {"
"   float4 position : SV_POSITION;"
"	float3 color : COLOR; };"
"vertex_to_pixel main(in VertexInput IN) {"
"	VertexToPixel OUT;"
"	OUT.position = float4(IN.position, 1.0);"
"	OUT.color = IN.color;"
"	return OUT;};";

const char* fragmentShaderCode =
"struct VertexToPixel {"
"	float4 position : POSITION;"
"	float3 color : COLOR;};"
"float4 main(in VertexToPixel IN) : COLOR {"
"	return float4(IN.color, 1.0);}";

struct SpriteVertex
{
public:
	float x, y, z;
	float r, g, b;
};

int main()
{
	//init glfw, stop execution in case of an error
	if (!glfwInit())
		return -1;

	
	//create glfw window
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(LAB_WIDTH, LAB_HEIGHT, "Rocket Lab", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	//init bgfx platform data
	bgfx::PlatformData pd;
	pd.type = bgfx::NativeWindowHandleType::Count;
	pd.context = GetDC(glfwGetWin32Window(window));
	pd.nwh = glfwGetWin32Window(window);


	//init bgfx
	bgfx::Init init;
	init.platformData = pd;
	init.type = bgfx::RendererType::Direct3D12;
	bgfx::init(init);

	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);


	SpriteVertex spriteVertices[4] =
	{
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{1.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 1.0, 0.0, 0.0, 0.0, 0.0},
		{1.0, 1.0, 0.0, 0.0, 0.0, 0.0}
	};
	
	bgfx::VertexLayout layout;
	layout.begin(bgfx::RendererType::Direct3D12)
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 3, bgfx::AttribType::Float)
		.end();

	bgfx::VertexBufferHandle vertexBuffer = bgfx::createVertexBuffer(
		bgfx::makeRef(&spriteVertices, sizeof(spriteVertices)),
		layout);

	bgfx::ShaderHandle vertexShader = bgfx::createShader(bgfx::makeRef(vertexShaderCode, std::strlen(vertexShaderCode)+1));
	bgfx::ShaderHandle fragmentShader = bgfx::createShader(bgfx::makeRef(fragmentShaderCode, std::strlen(fragmentShaderCode) + 1));
	
	bgfx::ProgramHandle program = bgfx::createProgram(vertexShader, fragmentShader, true);

	//main loop
	int windowWidth, windowHeight;
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		glfwPollEvents();

		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1e2952ff, 1.0f, 0);
		bgfx::setState(BGFX_STATE_DEFAULT);

		bgfx::submit(0, program, 1.0, BGFX_DISCARD_ALL);
		//bgfx::touch(0);

		bgfx::frame();
	}

	
	//terminaion
	bgfx::destroy(vertexBuffer);
	bgfx::shutdown();
	glfwTerminate();

}