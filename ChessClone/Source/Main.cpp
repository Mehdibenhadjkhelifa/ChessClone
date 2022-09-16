

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Piece.h"
#include "Rook.cpp"
#define Width 620
#define Height 620
#define COLOR_DarkBrown "(0.28,0.12,0.0,1.0)"
#define COLOR_LightBrown "(0.6,0.48,0.3,1.0)"

Board ChessBoard;

bool black = true;
int flipflopcount=0;
int TileCountOnRaw{0};
float BuildingX{ -1 };
float BuildingY{ -1 };
int StartingIndex{0};
const float Quarter= 0.25;
struct tile {

    float LowerTriangle[6];

    float UpperTriangle[6];

};

void AssignPosToTile(float InitialX, float InitialY, tile* Tile)
{
    Tile->LowerTriangle[0] = InitialX;
    Tile->LowerTriangle[1] = InitialY;
    Tile->LowerTriangle[2] = InitialX + Quarter;
    Tile->LowerTriangle[3] = InitialY;
    Tile->LowerTriangle[4] = InitialX;
    Tile->LowerTriangle[5] = InitialY + Quarter;
    Tile->UpperTriangle[0] = InitialX + Quarter;
    Tile->UpperTriangle[1] = InitialY + Quarter;
    Tile->UpperTriangle[2] = InitialX + Quarter;
    Tile->UpperTriangle[3] = InitialY;
    Tile->UpperTriangle[4] = InitialX;
    Tile->UpperTriangle[5] = InitialY + Quarter;

    //Start Assigning by the bottom left corner of the rectangle,then bottom right,then top left,then top right, then bottom right, then top left
}

inline void ChargeBuffer(unsigned int& buffer,tile* Board)
{

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 64 * sizeof(tile),Board,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
   
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

    tile Board[64];
    
    for(tile& T:Board)
    {
        
        AssignPosToTile(BuildingX, BuildingY, &T);
        BuildingX += Quarter;
        TileCountOnRaw++;
        if (TileCountOnRaw ==8) 
        {
            TileCountOnRaw = 0;
            BuildingX = -1;
            BuildingY += Quarter;
        }
            

    }

    unsigned int buffer1;
    glGenBuffers(1, &buffer1);
        ChargeBuffer(buffer1,Board);


        std::string VertexShader =
            "#version 330 core\n"
            "\n"
            "layout(location=0) in vec4 position;\n"
            "\n"
            "void main(){\n"
            "gl_Position=position;\n"
            "}\n";

        std::string BlackFragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location=0) out vec4 color;\n"
            "\n"
            "void main(){\n"
            "\n"
            "color = vec4" COLOR_DarkBrown ";\n"
            "}\n";
        std::string WhiteFragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location=0) out vec4 color;\n"
            "\n"
            "void main(){\n"
            "\n"
            "color = vec4" COLOR_LightBrown ";\n"
            "}\n";

        unsigned int BlackShader = CreateShader(VertexShader,BlackFragmentShader);
        unsigned int WhiteShader = CreateShader(VertexShader, WhiteFragmentShader);










        ChessBoard.board[2][3].PieceInTile = new Rook(2, 3, Black);        
        ChessBoard.board[2][4].PieceInTile = new Rook(2, 4, Black);

        ChessBoard.board[2][5].PieceInTile = new Rook(3, 2, Black);

        std::cout << ChessBoard.board[2][3].tileState << std::endl;

        std::cout << ChessBoard.board[2][4].tileState << std::endl;

        std::cout << ChessBoard.board[2][5].tileState << std::endl;


        std::cout << ChessBoard.board[3][2].tileState << std::endl;







  

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0;i < 64;i++)
        {
            if(black)
                SetInitialRawShader(BlackShader, WhiteShader, flipflopcount);
            else
                SetInitialRawShader(WhiteShader, BlackShader, flipflopcount);
            if(flipflopcount==8)
            {
                flipflopcount = 0;
                black = !black;
            }

            

            glDrawArrays(GL_TRIANGLES, StartingIndex, 6);
            StartingIndex += 6;

        }
        StartingIndex = 0;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}