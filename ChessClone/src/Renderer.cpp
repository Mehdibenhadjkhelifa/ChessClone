#include <glew.h>
#include <glfw3.h>
#include <iostream>


#include "Renderer.h"

#define Width 640
#define Height 640


Renderer::Renderer(bool InitSuccess)
    :Window(nullptr)
{
    /* Initialize the library */
    if (!glfwInit()) 
    {
        Window = false;
        return;
    }

    /* Create a windowed mode window and its OpenGL context */
    Window = glfwCreateWindow(Width, Height, "Chess Clone", NULL, NULL);
    if (!Window)
    {
        glfwTerminate();
        InitSuccess = false;
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(Window);

    if (glewInit() == GLEW_OK)
    {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

}
void Renderer::ChargeVertexBuffer(unsigned int& vbo, const void* Data, uint32_t Size)
{

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

}

void Renderer::ChargeIndexBuffer(unsigned int& ibo, const void* Data, uint32_t Size) 
{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW);

}

unsigned int Renderer::CompiledShader(unsigned int Type, std::string Source)
{
    unsigned int id = glCreateShader(Type);
    const char* src = Source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Compilation Of the " << (Type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader Has Failed : " << std::endl << message << std::endl;
        glDeleteShader(id);
        free(message);
        return 0;
    }
    return id;
}



unsigned int Renderer::CreateShader(std::string VertexShader, std::string FragmentShader)
{
    unsigned int program;
    program = glCreateProgram();

    unsigned int vs = CompiledShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int fs = CompiledShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}


void Renderer::SetInitialRawShader(const unsigned int& initialShader, const unsigned int& SecondShader, int& Count)
{

    if (!(Count % 2))
    {
        glUseProgram(initialShader);
    }
    else
    {
        glUseProgram(SecondShader);
    }

    Count++;

}

void Renderer::RenderFrame(const unsigned int& BlackShader,const unsigned int& WhiteShader)
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);


    for (int i = 0;i < 64;i++)
    {
        if (m_black)
            SetInitialRawShader(BlackShader, WhiteShader, m_flipflopcount);
        else
            SetInitialRawShader(WhiteShader, BlackShader, m_flipflopcount);
        if (m_flipflopcount == 8)
        {
            m_flipflopcount = 0;
            m_black = !m_black;
        }



        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (const void*)m_StartingIndex);
        m_StartingIndex += 24;

    }
    m_StartingIndex = 0;

    /* Swap front and back buffers */
    glfwSwapBuffers(Window);


}