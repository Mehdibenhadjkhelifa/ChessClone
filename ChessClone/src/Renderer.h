
#include <string>


class Renderer
{
private:
	bool m_black = true;
	int m_flipflopcount = 0;
	int m_StartingIndex = 0;
public:

	GLFWwindow* Window;
	Renderer(bool InitSuccess);

	
	void ChargeVertexBuffer(unsigned int& vbo, const void* Data, uint32_t Size);
	void ChargeIndexBuffer(unsigned int& ibo, const void* Data,uint32_t Size);


	unsigned int CompiledShader(unsigned int Type, std::string Source);
	unsigned int CreateShader(std::string VertexShader, std::string FragmentShader);

	void SetInitialRawShader(const unsigned int& initialShader, const unsigned int& SecondShader, int& Count);

	void RenderFrame(const unsigned int& BlackShader, const unsigned int& WhiteShader);

};