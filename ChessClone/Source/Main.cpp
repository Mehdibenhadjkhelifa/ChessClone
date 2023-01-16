

#include <iostream>
#include <tuple>
#include <sstream>
#include <fstream>
#include <glew.h>
#include <glfw3.h>
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"

//#include "Rook.cpp"
#define Width 640
#define Height 640
#define COLOR_DarkBrown "(0.28,0.12,0.0,1.0)"
#define COLOR_LightBrown "(0.6,0.48,0.3,1.0)"

class Rook;
Board ChessBoard;

bool black = true;
int flipflopcount=0;
int TileCountOnRaw{0};
float BuildingX{ -1 };
float BuildingY{ -1 };
int StartingIndex=0;
const float Quarter= 0.25;
unsigned int* BoardInd=new unsigned int[384];

struct Line {

	float posInLine[18];

	

};

void AssignPosInLine(float InitialX, float InitialY, Line* line)
{
    for (int i = 0;i < 18;i++)
    {
        if (i % 2)
            line->posInLine[i] = InitialY;
        else
			line->posInLine[i] = InitialX + (Quarter * (i / 2));

    }

    
}

void AssignIndexToTile(unsigned int InitialIndex,unsigned int* Data,unsigned int& DataIndex)
{

    for (int i = 1;i < 9;i++)
    {
       Data[DataIndex]   = InitialIndex + i - 1;
       Data[DataIndex+1] = InitialIndex + i;
       Data[DataIndex+2] = InitialIndex +i+9;
       Data[DataIndex+3] = InitialIndex +i+9;
       Data[DataIndex+4] = InitialIndex+ i+9 - 1;
       Data[DataIndex+5] = InitialIndex+i-1;

        DataIndex += 6;
    }


}



static const std::tuple<std::string, std::string, std::string> ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    std::stringstream ss[3];
    std::string line;

    enum class ShaderTYPE
    {
        NONE = -1,
        VERTEX = 0,
        WHITEFRAGMENT = 1,
        BLACKFRAGMENT = 2
    };

    ShaderTYPE type=ShaderTYPE::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos) 
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderTYPE::VERTEX;
            else if (line.find("whiteFragment") != std::string::npos)
                type = ShaderTYPE::WHITEFRAGMENT;
            else if (line.find("blackFragment") != std::string::npos)
                type = ShaderTYPE::BLACKFRAGMENT;

        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return std::make_tuple(ss[0].str(), ss[1].str(), ss[2].str());
}




inline void ChargeVertexBuffer(unsigned int& buffer,Line* Board)
{

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(Line),Board,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
   
}

inline void ChargeIndexBuffer(unsigned int& ibo, unsigned int* Data)
{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 384 * (sizeof(unsigned int)), Data, GL_STATIC_DRAW);

}




unsigned int CompiledShader(unsigned int Type,std::string Source)
{
    unsigned int id = glCreateShader(Type);
    const char* src = Source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS,&success);
    if(success==GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Compilation Of the " << (Type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader Has Failed : " << std::endl << message << std::endl;
        glDeleteShader(id);
        free(message);
        return 0;
    }

    return id;
}

unsigned int CreateShader(std::string VertexShader,std::string FragmentShader)
{
    unsigned int program;
    program=glCreateProgram();

    unsigned int vs = CompiledShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int fs = CompiledShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    glDetachShader(program,vs);
    glDetachShader(program,fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}



void SetInitialRawShader(const unsigned int& initialShader,const unsigned int& SecondShader,int& Count) 
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




int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
   


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Width, Height, "Chess Clone", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() == GLEW_OK) 
    {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    Line Board[9];
    
    for (Line& L : Board)
    {

        AssignPosInLine(BuildingX, BuildingY, &L);
        BuildingY += Quarter;

    }

    unsigned int DataIndex=0;

    for (int i = 0;i < 8; i++)
    {
        AssignIndexToTile(i * 9, BoardInd, DataIndex);
  

    }

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    ChargeVertexBuffer(vbo,Board);
    unsigned int ibo;
    ChargeIndexBuffer(ibo, BoardInd);
    delete[] BoardInd;


     

        const auto& [vs, wfs, bfs] = ParseShader("res/shaders/Basic.shader");

        unsigned int WhiteShader = CreateShader(vs, wfs);
        unsigned int BlackShader = CreateShader(vs, bfs);







        /*std::cout << (int)&((Piece*)0)->PiecePosY << std::endl;*/
        /*std::cout << sizeof(bool) << std::endl;*/
        


        //ChessBoard.board[2][3].PieceInTile = new Rook(2, 3, Black);        

        //ChessBoard.board[2][4].PieceInTile = new Rook(2, 4, Black);

        //ChessBoard.board[2][5].PieceInTile = new Rook(3, 2, Black);



        ChessBoard.board[0][0].PieceInTile = new Bishop(0, 0, Black);
        
        ChessBoard.board[4][4].PieceInTile = new Bishop(4, 4, Black);

        ChessBoard.board[7][7].PieceInTile = new Bishop(7, 7, Black);

        ChessBoard.board[7][1].PieceInTile = new Bishop(7, 1, Black);
        

        std::cout << ChessBoard.board[0][0].tileState << std::endl;

        std::cout << ChessBoard.board[4][4].tileState << std::endl;

        std::cout << ChessBoard.board[7][7].tileState << std::endl;

        std::cout << ChessBoard.board[7][1].tileState << std::endl;

        std::cout << ChessBoard.board[5][3].tileState << std::endl;
  
        std::cout << ChessBoard.board[7][2].tileState << std::endl;



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        
		for (int i = 0;i < 64;i++)
		{
			if (black)
				SetInitialRawShader(BlackShader, WhiteShader, flipflopcount);
			else
				SetInitialRawShader(WhiteShader, BlackShader, flipflopcount);
			if (flipflopcount == 8)
			{
				flipflopcount = 0;
				black = !black;
			}



			glDrawElements(GL_TRIANGLES, 9 , GL_UNSIGNED_INT,(const void*) StartingIndex);
            StartingIndex += 24;

		}
		StartingIndex = 0;
        //glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}