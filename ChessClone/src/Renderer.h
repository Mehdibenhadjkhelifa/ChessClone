#pragma once
#include <string>

#ifdef _WIN32
#define ASSERT(x) if(!(x)) __debugbreak()
#else
#include <signal.h>
#define ASSERT(x) if(!(x)) raise(SIGTRAP)
#endif

#define COLOR_DARKBROWN 0.28f,0.12f,0.0f,1.0f
#define COLOR_LIGHTBROWN 0.6f,0.48f,0.3f,1.0f

class Renderer
{
private:
	GLFWwindow* m_window=nullptr;
	unsigned int m_Shader=-1;
	bool m_black{true};
	int m_flipflopcount = 0;
	int m_StartingIndex = 0;
public:

	Renderer(bool InitSuccess);
	~Renderer();

	GLFWwindow* GetWindow() { return m_window; }

	void ChargeVertexBuffer(unsigned int& vbo, const void* Data, uint32_t Size);
	void ChargeIndexBuffer(unsigned int& ibo, const void* Data,uint32_t Size);

	unsigned int CreateShader(std::string VertexShader, std::string FragmentShader);
	void SetShader(const unsigned int& Shader);

	void RenderFrame();
private:
	unsigned int CompiledShader(unsigned int Type, std::string Source);
	int GetUniformLocation(const char* Uniform);
	void SetShaderUniform4f(const char* uniform, float x1, float x2, float x3, float x4);
	void SetAppropriateUniform();
};