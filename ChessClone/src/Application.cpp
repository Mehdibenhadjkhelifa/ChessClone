
//external headers
#include <iostream>
#include <glew.h>
#include <glfw3.h>

//chess logic headers
#include "ChessCore.h"
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"


//render logic headers
#include "Renderer.h"
#include "RendererData.h"
#include "Application.h"

std::ostream& operator<<(std::ostream& stream, Piece* piece)
{
    stream << piece->GetName() << " : " << piece->PiecePosX << " , " << piece->PiecePosY << "  Color : " << ( piece->Color ? "White" : "Black");
    return stream;

}
Board ChessBoard;


namespace Chess {

	void Run() 
	{
        //Using RAII to init the GLFWwindow
        bool InitSuccess=true;
        Renderer renderer(InitSuccess);

        if (!InitSuccess)
            return;

        Line* _Board=new Line[9];
        unsigned int* BoardInd = new unsigned int[384];

        RendererData::BindData(_Board, BoardInd);

       


        unsigned int vbo;
        unsigned int ibo;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);
        renderer.ChargeVertexBuffer(vbo, _Board,9*sizeof(Line));
        renderer.ChargeIndexBuffer(ibo, BoardInd, 384 * sizeof(unsigned int));


        delete[] _Board;
        delete[] BoardInd;


        const auto& [vs, wfs, bfs] = RendererData::ParseShader(RendererData::GetFilePath("res/shaders/Basic.shader"));
        unsigned int WhiteShader = renderer.CreateShader(vs, wfs);
        unsigned int BlackShader = renderer.CreateShader(vs, bfs);


        //ChessBoard.board[2][3].PieceInTile = new Rook(2, 3, Black);        

        //ChessBoard.board[2][4].PieceInTile = new Rook(2, 4, Black);

        //ChessBoard.board[2][5].PieceInTile = new Rook(3, 2, Black);



        ChessBoard.board[0][0].PieceInTile = new Bishop(0, 0, Black);

        ChessBoard.board[4][4].PieceInTile = new Bishop(4, 4, Black);

        ChessBoard.board[7][7].PieceInTile = new Bishop(7, 7, Black);

        ChessBoard.board[7][1].PieceInTile = new Bishop(7, 1, Black);

        ChessBoard.board[7][2].PieceInTile = new Rook(7, 2, White);

        ChessBoard.board[7][0].PieceInTile = new Rook(7, 0, Black);


            for(unsigned int j=0;j< ChessBoard.board[0][0].PiecesVisionList.size();j++)
            std::cout << ChessBoard.board[0][0].PiecesVisionList[j] << std::endl;

            std::cout << "==========================" << '\n';
            for (unsigned int j = 0;j < ChessBoard.board[4][4].PiecesVisionList.size();j++)
            std::cout << ChessBoard.board[4][4].PiecesVisionList[j] << std::endl;
            std::cout << "==========================" << '\n';
            for (unsigned int j = 0;j < ChessBoard.board[7][7].PiecesVisionList.size();j++)
            std::cout << ChessBoard.board[7][7].PiecesVisionList[j] << std::endl;
            std::cout << "==========================" << '\n';
            for (unsigned int j = 0;j < ChessBoard.board[7][1].PiecesVisionList.size();j++)
            std::cout << ChessBoard.board[7][1].PiecesVisionList[j] << std::endl;
            std::cout << "==========================" << '\n';
            for (unsigned int j = 0;j < ChessBoard.board[5][3].PiecesVisionList.size();j++)
            std::cout << ChessBoard.board[5][3].PiecesVisionList[j] << std::endl;
            std::cout << "==========================" << '\n';
            for (unsigned int j = 0;j < ChessBoard.board[7][3].PiecesVisionList.size();j++)
            std::cout << ChessBoard.board[7][3].PiecesVisionList[j] << std::endl;
            std::cout << "==========================" << '\n';
        
      



        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(renderer.GetWindow()))
        {
            renderer.RenderFrame(BlackShader, WhiteShader);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return;
	}
}