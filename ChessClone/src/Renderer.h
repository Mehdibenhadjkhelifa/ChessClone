
#include <string>


class Renderer
{
private:
	GLFWwindow* m_window=nullptr;
	bool m_black = true;
	int m_flipflopcount = 0;
	int m_StartingIndex = 0;
public:

	Renderer(bool InitSuccess);
	~Renderer();
	GLFWwindow* GetWindow() { return m_window; }

	
	void ChargeVertexBuffer(unsigned int& vbo, const void* Data, uint32_t Size);
	void ChargeIndexBuffer(unsigned int& ibo, const void* Data,uint32_t Size);


	unsigned int CompiledShader(unsigned int Type, std::string Source);
	unsigned int CreateShader(std::string VertexShader, std::string FragmentShader);

	void SetInitialRawShader(const unsigned int& initialShader, const unsigned int& SecondShader, int& Count);

	void RenderFrame(const unsigned int& BlackShader, const unsigned int& WhiteShader);

};