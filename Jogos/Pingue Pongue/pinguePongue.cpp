#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//Arena do jogo;
int l=40, h=20;
int frames = 100;

//Configurações referentes a bolinha;
int bX = l/2, bY = h/2;
int antBX, antBY;
char direcaoX = 'd', direcaoY = 'c', mover=1;

//ISSUES:

/*

    1. O personagem desaparece ao atingir o limite superior e pressionar W;

*/

class Player
{

    private:
        //Configurações do player;
        int pY = h/2, pX=4, entrada;
        int antPY = -1;

    public:
        int getPX()
        {
            return pX;
        }

        int getPY()
        {
            return pY;
        }

        int getAntPY()
        {
            return antPY;
        }

        void input()
        {

            switch(getch())
            {

                case 'w':
                case 'W':
                {
                    entrada = 1;
                }break;

                case 's':
                case 'S':
                {
                    entrada = 2;
                }break;

                default:
                {
                    entrada = -1;
                }break;

            }

        }

        int inputValido()
        {

            int valido=0;

            if(entrada == 1 || entrada == 2 && pY > 1 && pY < h-1)
            {
                valido=1;
            }

            return valido;

        }

        void fisicaPlayer()
        {

            if(inputValido())
            {
                antPY = pY;
            }

            //Tecla W/w;
            if(entrada == 1)
            {

                //Se está dentro dos limites do cenário;
                if(pY > 1)
                {
                    pY--;
                }

            }
            else
            {

                //tecla S/s;
                if(entrada == 2)
                {

                    //Se está dentro dos limites do cenário;
                    if(pY < h-1)
                    {
                        pY++;
                    }

                }

            }

        }

};

void movimenta()
{

    antBX = bX;
    antBY = bY;

    //Frente e cima;
    if(direcaoX == 'd' && direcaoY == 'c')
    {
        bX++;
        bY--;
    }
    else
    {

        //Trás e cima;
        if(direcaoX == 'e' && direcaoY == 'c')
        {
            bX--;
            bY--;
        }
        else
        {

            //Trás e baixo;
            if(direcaoX == 'e' && direcaoY == 'b')
            {
                bX--;
                bY++;
            } //Frente e baixo;
            else
            {
                bX++;
                bY++;
            }

        }

    }

}

void verDirecao(Player player)
{

    //Trata dos limites inferiores e direitos;
    if(bX == l-2 && bY == 1 && direcaoX == 'd' && direcaoY == 'c')
    {
        direcaoX = 'e';
        direcaoY = 'b';
    }
    else
    {

        if(bX == l-2 && bY == h-1 && direcaoX == 'd' && direcaoY == 'b')
        {
            direcaoX = 'e';
            direcaoY = 'c';
        }
        else
        {

            //Trata dos limites inferiores e esquerdos;
            if(bX == 1 && bY == h-1 && direcaoX == 'e' && direcaoY == 'b')
            {
                direcaoX = 'd';
                direcaoY = 'c';
            }
            else
            {

                if(bX == 1 && bY == 1 && direcaoX == 'e' && direcaoY == 'c')
                {
                    direcaoX = 'd';
                    direcaoY = 'b';
                }
                else
                {

                    //Trata dos limites superiores e direitos;
                    if(bX == l-2 && direcaoX == 'd' && direcaoY == 'c')
                    {
                        direcaoX = 'e';
                    }
                    else
                    {

                        if(bY == 1 && direcaoX == 'd' && direcaoY == 'c')
                        {
                            direcaoY = 'b';
                        }
                        else
                        {

                            //Trata dos limites superiores e esquerdos;
                            if(bX == 1 && direcaoX == 'e' && direcaoY == 'c')
                            {
                                direcaoX = 'd';
                            }
                            else
                            {

                                if(bY == 1 && direcaoX == 'e' && direcaoY == 'c')
                                {
                                    direcaoY = 'b';
                                }
                                else
                                {

                                    //Limite esquerdo;
                                    if(bX == 1 && direcaoX == 'e' && direcaoY == 'c')
                                    {
                                        direcaoX = 'd';
                                    }
                                    else
                                    {

                                        //Limite superior;
                                        if(bY == 1 && direcaoX == 'e' && direcaoY == 'c')
                                        {
                                            direcaoY = 'b';
                                        }
                                        else
                                        {

                                            //Limite esquerdo;
                                            if(bX == 1 && direcaoX == 'd' && direcaoY == 'b')
                                            {
                                                direcaoX = 'd';
                                            }
                                            else
                                            {

                                                //Limite inferior;
                                                if(bY == h-1 && direcaoX == 'd' && direcaoY == 'b')
                                                {
                                                    direcaoY = 'c';
                                                }
                                                else
                                                {

                                                    //Limite esquerdo;
                                                    if(bX == l-2 && direcaoX == 'd' && direcaoY == 'b')
                                                    {
                                                        direcaoX = 'e';
                                                    }
                                                    else
                                                    {

                                                        //Limite inferior;
                                                        if(bY == h-1 && direcaoX == 'd' && direcaoY == 'b')
                                                        {
                                                            direcaoY = 'c';
                                                        }
                                                        else
                                                        {

                                                            //Limite esquerdo;
                                                            if(bX == 1 && direcaoX == 'e' && direcaoY == 'b')
                                                            {
                                                                direcaoX = 'd';
                                                            }
                                                            else
                                                            {

                                                                //Limite inferior;
                                                                if(bY == h-1 && direcaoX == 'e' && direcaoY == 'b')
                                                                {
                                                                    direcaoY = 'c';
                                                                }
                                                                else
                                                                {

                                                                    //Caso o player atinja a bolinha;
                                                                    if(bX == player.getPX() && bY == player.getPY() && direcaoX == 'e' && direcaoY == 'c')
                                                                    {
                                                                        direcaoX = 'd';
                                                                        direcaoY = 'c';
                                                                    }
                                                                    else
                                                                    {

                                                                        if(bX == player.getPX() && bY == player.getPY() && direcaoX == 'e' && direcaoY == 'b')
                                                                        {
                                                                            direcaoX = 'd';
                                                                            direcaoY = 'b';
                                                                        }

                                                                    }

                                                                }

                                                            }

                                                        }

                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

}

void fisicaObjeto(Player player)
{

    verDirecao(player);
    movimenta();

}

BOOL moveCursor(short x, short y)
{
	COORD coord = {x, y};
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void erase(int posX, int posY)
{
	moveCursor(posX, posY);
	std::cout <<" ";
	moveCursor(0, h+1);
}

void draw(int posX, int posY, int objeto, Player player)
{

    char parede = '#';

    moveCursor(posX, posY);

    //Cenário
    if(objeto == 1)
    {

        for(int i=posX; i < l; i++)
		{
			std::cout <<parede;
		}

		for(int i=posY+1; i < posY + h; i++)
		{

			moveCursor(posX, i);
			std::cout <<parede;
			moveCursor((posX+l)-1, i);
			std::cout <<parede;

		}

		moveCursor(posX, posY + h);

		for(int i=posX; i < l; i++)
		{
			std::cout <<parede;
		}

    }
    else
    {

        //Bolinha;
        if(objeto == 2)
        {
            std::cout <<'0';
            erase(antBX, antBY);
        }
        else
        {

            //Player;
            if(objeto == 3)
            {
                std::cout <<'|';
                erase(player.getPX(), player.getAntPY());
            }

        }

    }

}

int main()
{

    Player player1;

    //Desenha o cenário;
    draw(0, 0, 1, player1);

    while(1)
    {

        Sleep(frames);

        //Físicas da bolinha;
        fisicaObjeto(player1);

        //Físicas e controles do player;
        if(_kbhit())
        {
            player1.input();
            player1.fisicaPlayer();
        }

        //Desenha a bolinha;
        draw(bX, bY, 2, player1);
        //Desenha o player;
        draw(player1.getPX(), player1.getPY(), 3, player1);

        moveCursor(0, h+2);
        std::cout <<"X: " <<player1.getPX() <<" Y: " <<player1.getPY();

    }

    return 0;

}
