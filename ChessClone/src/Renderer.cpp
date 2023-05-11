#include <glew.h>
#include <glfw3.h>
#include <iostream>

#include "Renderer.h"
#include "RendererData.h"
#define Width 640
#define Height 640


Renderer::Renderer(bool InitSuccess)
{
    /* Initialize the library */
    if (!glfwInit()) 
    {
        InitSuccess = false;
        return;
    }

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(Width, Height, "Chess Clone", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        InitSuccess = false;
        return;
    }
    if (!RendererData::SetWorkingDirectory())
    {
        InitSuccess = false;
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    if (glewInit() == GLEW_OK)
    {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

}
Renderer::~Renderer()
{

    
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

int Renderer::GetUniformLocation(const char* Uniform)
{
    int Location =glGetUniformLocation(m_Shader, "u_Color");
    ASSERT(Location != -1);
    return Location;
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

void Renderer::SetShader(const unsigned int& shader)
{
    m_Shader = shader;
    glUseProgram(shader);

}

void Renderer::SetShaderUniform4f(const char* uniform,float x1,float x2,float x3,float x4)
{
    glUniform4f(GetUniformLocation(uniform),x1,x2,x3,x4);
}


void Renderer::SetAppropriateUniform()
{
    if (!(m_flipflopcount % 2))
    {
        if (m_black)
            SetShaderUniform4f("u_Color", COLOR_DARKBROWN);
        else
            SetShaderUniform4f("u_Color", COLOR_LIGHTBROWN);
    }
    else
    {
        if (m_black)
            SetShaderUniform4f("u_Color", COLOR_LIGHTBROWN);
        else
            SetShaderUniform4f("u_Color", COLOR_DARKBROWN);
    }
    m_flipflopcount++;
    if (m_flipflopcount == 8)
    {
        m_flipflopcount = 0;
        m_black = !m_black;
    }
}




void Renderer::RenderFrame()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);


    for (int i = 0;i < 64;i++)
    {
        SetAppropriateUniform();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)m_StartingIndex);
        m_StartingIndex += 24;
    }
    m_StartingIndex = 0;

    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);


}