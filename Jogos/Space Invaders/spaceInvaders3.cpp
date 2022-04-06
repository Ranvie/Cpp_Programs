#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <thread>
#include <Windows.h>
#include <time.h>

//Configurações do jogo;
int l = 40, h = 20, FPS = 11;

class Player
{

	public:
        int playerX = l/2, playerY = h-1;
        int antPlayerX=-1, antPlayerY=playerY;

        int disparo=0, dX=-1, dY=-1;
		int antDX=-1, antDY=-1;
		int limpaDisparo=0;

        char player = 207;
        char playerProjetil = '^';

        int input()
        {

            int tecla = -1;

			fflush(stdin);
            switch(getch())
            {

                case 'a':
                {
                    tecla = 1;
                }break;

                case 'd':
                {
                    tecla = 2;
                }break;

                case 'j':
                {
                    tecla = 3;
                }break;

            }

            return tecla;

        }

        void acao(int input)
        {

            switch(input)
            {

                case 1:
                {

                    if(playerX > 1)
                    {
                    	antPlayerX = playerX;
                        playerX--;
                    }

                }break;

                case 2:
                {

                    if(playerX < l-2)
                    {
                    	antPlayerX = playerX;
                        playerX++;
                    }

                }break;

                case 3:
                {

                    if(!disparo)
                    {
                        dX = playerX;
                        dY = playerY;
                        disparo = 1;
                    }

                }

            }

        }

        int projetil()
        {

            if(disparo)
            {

				if(dY != h-1)
				{
					antDX = dX;
                	antDY = dY;
				}

                if(dY > 1)
                {
                    dY--;
                }
                else
                {

                	if(dY == 1)
                	{
                		dX = -1;
	                	dY = -1;
	                	disparo=0;
	                	limpaDisparo=1;
					}

                }

            }

            return disparo;

        }

};

class Entidade
{

	public:

		//Matriz do inimigo;
		int inimigo[2][2];
		int linha=0, coluna=0;

		//Padronizando com matrizes;
		//h = linha, l = coluna;
		//Hitbox do inimigo;
		int h=2, l=2;
		int inimigoX, inimigoY;
		int antInimigoX=inimigoX, antInimigoY=inimigoY;
		int hit;

		int linAux, colAux;
		char icone = '#';
		int vivo;

		void respawn()
		{

			for(int lin=0; lin < h; lin++)
			{

				for(int col=0; col < l; col++)
				{
					inimigo[lin][col] = 1;
				}

			}

			//ponto 0 0 do inimigo;
			inimigoX=5;
			inimigoY=5;
			vivo=true;

		}

		int hitBox(int x, int y, int atualizaMatriz)
		{

			//Se a posição passada para a função pertence a área do inimigo;
			if(x >= inimigoX && x < inimigoX+l && y >= inimigoY && y < inimigoY+h && inimigo[linha][coluna] == 1)
			{

				hit = 1;

				//Só atualiza quando for mostrar na tela, pra verificar se aquele inimigo está vivo ou não;
				if(atualizaMatriz)
				{
					controlaMatriz();
				}

			}
			else
			{

				if(x >= inimigoX && x < inimigoX+l && y >= inimigoY && y < inimigoY+h && inimigo[linha][coluna] == 0)
				{

					hit = 0;

					//Só atualiza quando for mostrar na tela, pra verificar se aquele inimigo está vivo ou não;
					if(atualizaMatriz)
					{
						controlaMatriz();
					}

				}
				else
				{
					hit = 0;
				}

			}

			return hit;

		}

		int atingido(int x, int y)
		{

			hit = 0;

			if(hitBox(x, y, 0))
			{

				linAux = 0;

				for(int lin=inimigoY; lin < inimigoY+h; lin++)
				{

					colAux = 0;

					for(int col=inimigoX; col < inimigoX+l; col++)
					{

						if(x == col && y == lin)
						{
							inimigo[linAux][colAux] = 0;
							hit = 1;
						}

						colAux++;
					}
					linAux++;
				}

			}

			return hit;

		}

		int status()
		{

			vivo = 0;

			for(int j=0; j < h; j++)
			{

				for(int i=0; i < l && !vivo; i++)
				{
					if(inimigo[j][i] == 1)
					{
						vivo = 1;
					}
				}

			}

			return vivo;
		}

	private:
		void controlaMatriz()
		{

			//Controla a posição dos inimigos na matriz;
			if(coluna == l-1 && linha == h-1)
			{
				linha=0;
				coluna=0;
			}
			else
			{

				if(coluna == l-1)
				{
					coluna=0;
					linha++;
				}
				else
				{
					coluna++;
				}

			}

		}

};

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

void draw(int posX, int posY, int objeto, Player *player, Entidade *inimigo)
{

	char parede = 219;

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

	//Jogador;
	if(objeto == 2)
	{
		std::cout <<player->player;
		erase(player->antPlayerX, player->antPlayerY);
	}

	//Disparo;
	if(objeto == 3)
	{
		std::cout <<player->playerProjetil;
		erase(player->antDX, player->antDY);
	}

	//Inimigo
	if(objeto == 4)
	{

		//Apaga inimigo;
		for(int j=inimigo->antInimigoY; j < posY + inimigo->h; j++)
		{

			for(int i=inimigo->antInimigoX; i < posX + inimigo->l; i++)
			{

				if(inimigo->hitBox(i, j, 1))
				{
					erase(i, j);
				}

			}

		}

		//Mostro inimigo;
		for(int j=posY; j < posY + inimigo->h; j++)
		{

			for(int i=posX; i < posX + inimigo->l; i++)
			{

				if(inimigo->hitBox(i, j, 1))
				{
					moveCursor(i, j);
					std::cout <<inimigo->icone;
				}

			}

		}

	}

	moveCursor(0, h+1);

}

void sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main()
{

	int tecla;
	Player player;
	Entidade inimigo;
	clock_t tempo;

	//Desenha o cenário em x:0 e y:0;
	draw(0, 0, 1, &player, &inimigo);

	inimigo.respawn();
	draw(player.playerX, player.playerY, 2, &player, &inimigo);
	draw(inimigo.inimigoX, inimigo.inimigoY, 4, &player, &inimigo);

	while(inimigo.status())
	{

		tempo = clock();

		sleep(1000/FPS);

		//Input;
		if(_kbhit())
		{
			tecla = player.input();
			player.acao(tecla);
			draw(player.playerX, player.playerY, 2, &player, &inimigo);
		}

		if(player.projetil())
		{
			draw(player.dX, player.dY, 3, &player, &inimigo);
		}
		else
        {

            if(player.limpaDisparo)
            {
                draw(player.dX, player.dY, 3, &player, &inimigo);
            }

        }

		if(inimigo.atingido(player.dX, player.dY) /* Programar pra caso o inimigo se mover tbm atualiza */)
		{
			draw(inimigo.inimigoX, inimigo.inimigoY, 4, &player, &inimigo);
		}

		tempo = clock() - tempo;

		//Debug;
		moveCursor(0, h+2);
		//std::cout <<inimigo.inimigo[0][0] <<inimigo.inimigo[0][1] <<std::endl <<inimigo.inimigo[1][0] <<inimigo.inimigo[1][1];
		//std::cout <<"FPS: " <<1000/tempo <<std::endl <<"Variavel: " <<FPS;

	}

	return 0;

}
