#include <iostream>
#include <stdio.h>
#include <cstring>

struct Produto
{
	int iId;
	float fPreco;
	char cDescricao[50];
	Produto *strProx;
	Produto *strAnte;
};

struct Cabecalho
{
	int iTamanho;
	Produto *strInicio;	
	Produto *strTopo;
};

void iniCabecalho(Cabecalho *strCabecalho)
{
	strCabecalho->iTamanho = 0;
	strCabecalho->strInicio = NULL;	
	strCabecalho->strTopo = NULL;		
}

int tam(Cabecalho *strCabecalho)
{
	return strCabecalho->iTamanho; 	
}

void pause()
{
	fflush(stdin);
    std::cout <<std::endl <<std::endl <<"Pressione Enter para continuar..." <<std::endl <<std::endl;
    getchar();
}

Produto *buscaSimples(Cabecalho *strCabecalho, int iId)
{
	
	int iEncontrou=0;
	Produto *strAux;
	
	strAux = strCabecalho->strInicio;

	while(strAux != NULL && !iEncontrou)
	{
		
		if(iId == strAux->iId)
		{
			iEncontrou = 1;
		}
		else
		{
			strAux = strAux->strProx;
		}
		
	}
	
	return strAux;
	
}

Produto *ordemCresc(Cabecalho *strCabecalho, Produto *strItem)
{	
	
	Produto *strAux;
	int iParada=0;

	strAux = strCabecalho->strInicio;

	//Percorre a lista e retorna a primeira posição com ID maior ao que enviou a função (contido no strItem);
	while(!iParada)
	{
		
		if(strItem->iId < strAux->iId || strAux == strCabecalho->strTopo)
		{
			iParada = 1;
		}
		else
		{	
			strAux = strAux->strProx;		
		}
		
	}

	return strAux;

}

Produto *criaProduto(int iId, float fPreco, char cDescricao[50])
{
	
	Produto *strAux = new Produto;
	
	strAux->iId = iId;
	strAux->fPreco = fPreco;
	strcpy(strAux->cDescricao, cDescricao);
	strAux->strProx = NULL;
	strAux->strAnte = NULL;
	
	return strAux;
	
}

int registraProduto(Cabecalho *strCabecalho, int iId, float fPreco, char cDescricao[50], int iRepete)
{
	
	int iStatus=0;
	Produto *strItem, *strAux;

	//Se não tem IDs repetidos;	
	if(buscaSimples(strCabecalho, iId) == NULL || iRepete)
	{
		
		//Aloca memória para o novo item;
		strItem = criaProduto(iId, fPreco, cDescricao);
	
		//Se alocou com sucesso;
		if(strItem != NULL)
		{
			
			//Caso não hajam outros elementos na lista;
			if(tam(strCabecalho) == 0)
			{
				//O primeiro elemento é tanto o topo quanto o início;
				strCabecalho->strInicio = strItem;
				strCabecalho->strTopo = strItem;
			}
			else
			{
	
				//Do contrário procura a posição que o elemento deve estar na lista;
				strAux = ordemCresc(strCabecalho, strItem);
				
				//Caso onde o elemento deve estar no início da lista;
				if(strAux == strCabecalho->strInicio && strItem->iId <= strAux->iId)
				{
					strCabecalho->strInicio->strAnte = strItem;
					strCabecalho->strInicio = strItem;
					strCabecalho->strInicio->strProx = strAux;
				}
				else
				{
					
					//Caso o elemento retornado for o topo e ele deva estar no final da lista;
					if(strAux == strCabecalho->strTopo && strItem->iId >= strAux->iId)
					{
						strCabecalho->strTopo->strProx = strItem;
						strCabecalho->strTopo = strItem;
						strCabecalho->strTopo->strAnte = strAux;
					}
					else
					{
						//Pode estar em qualquer posição da lista;
						
						//Atualiza o anterior do item criado;
						strItem->strAnte = strAux->strAnte;
						strAux->strAnte = strItem;
						
						//Atualiza o próximo do item criado;
						strItem->strProx = strAux;
						strItem->strAnte->strProx = strItem;
						
					}
					
				}			
						
			}
			
			strCabecalho->iTamanho++;
			
		}
		else
		{
			//Não foi possível alocar memória;
			iStatus = 1;
		}
						
	}
	else
	{
		//O ID já existe;
		iStatus = 2;
	}		

	return iStatus;
			
}

int deletaItem(Cabecalho *strCabecalho, int iId)
{
	
	int iStatus=0;
	Produto *strAux;
	
	strAux = buscaSimples(strCabecalho, iId);
	
	//Se existe na lista;
	if(strAux != NULL)
	{
		
		if(tam(strCabecalho) == 1)
		{
			strCabecalho->strInicio = NULL;
			strCabecalho->strTopo = NULL;
		}
		else
		{
			
			//Atualiza início;
			if(strAux == strCabecalho->strInicio)
			{
				strCabecalho->strInicio = strAux->strProx;
				strCabecalho->strInicio->strAnte = NULL;
			}
			else
			{
				
				//Atualiza topo;
				if(strAux == strCabecalho->strTopo)
				{
					strCabecalho->strTopo = strAux->strAnte;
					strCabecalho->strTopo->strProx = NULL;
				}
				else
				{
					//Atualiza anterior
					strAux->strAnte->strProx = strAux->strProx;
					
					//Atualiza próximo
					strAux->strProx->strAnte = strAux->strAnte;
				}
				
			}
			
		}
		
		strCabecalho->iTamanho--;
		
	}
	else
	{
		iStatus = 1;
	}
	
	delete strAux;
	
	return iStatus;
	
}

int salvaBD(Cabecalho *strCabecalho, char cArqNome[50])
{

	FILE *arq;
	Produto *strAux, strPos;
	int iStatus=0;
	
	arq = fopen(cArqNome, "wb");
	
	if(arq)
	{
		
		for(strAux = strCabecalho->strInicio; strAux != NULL; strAux = strAux->strProx)
		{
			
			strPos.iId = strAux->iId;
			strPos.fPreco = strAux->fPreco;
			strcpy(strPos.cDescricao, strAux->cDescricao);
			strPos.strAnte = NULL;
			strPos.strProx = NULL;
			
			fwrite(&strPos, sizeof(Produto), 1, arq);
			
		}
		
	}
	else
	{
		iStatus=1;
	}
	
	fclose(arq);
	
	return iStatus;
	
}

int leBD(Cabecalho *strCabecalho, char cArqNome[50])
{
	
	FILE *arq;
	Produto *strAux = new Produto;
	int iStatus=0;
	
	arq = fopen(cArqNome, "rb");
	
	if(arq)
	{
		
		while(fread(strAux, sizeof(Produto), 1, arq))
		{
			registraProduto(strCabecalho, strAux->iId, strAux->fPreco, strAux->cDescricao, 0);
		}
		
	}
	else
	{
		iStatus=1;
	}
	
	fclose(arq);
	
	return iStatus;
	
}

float calculaTotal(Cabecalho *strCabecalho)
{
	
	float fTotal=0;
	Produto *strItem;
	
	for(strItem = strCabecalho->strInicio; strItem != NULL; strItem = strItem->strProx)
	{
		fTotal += strItem->fPreco;
	}
	
	return fTotal;
	
}

void imprimeLista(Cabecalho *strCabecalho)
{
	
	Produto *strItem;
	
	for(strItem = strCabecalho->strInicio; strItem != NULL; strItem = strItem->strProx)
	{
		std::cout <<"1 x " <<strItem->cDescricao <<" | R$" <<strItem->fPreco <<std::endl;
	}
	
}

void novoCarrinho(Cabecalho *strCabecalho)
{
	
	Cabecalho *strCarrinho = new Cabecalho;
	iniCabecalho(strCarrinho);
	Produto *strAux;
	
	char cEscolha;
	int iId;
	
	do
	{
		
		std::cout <<"------------------------------" <<std::endl;
		std::cout <<"|                            |" <<std::endl;
		std::cout <<"| 1 - Adicionar ao carrinho  |" <<std::endl;
		std::cout <<"| 2 - Retirar do carrinho    |" <<std::endl;
		std::cout <<"| 3 - Finalizar compra       |" <<std::endl;
		std::cout <<"|                            |" <<std::endl;
		std::cout <<"------------------------------" <<std::endl <<std::endl;
		
		std::cout <<"-------------CARRINHO-------------" <<std::endl <<std::endl;
		imprimeLista(strCarrinho);
		std::cout <<std::endl <<"Preço Total: " <<calculaTotal(strCarrinho) <<std::endl <<std::endl;
		std::cout <<"----------------------------------" <<std::endl <<std::endl;
		
		std::cout <<"> ";
		std::cin >>cEscolha;
		
		switch(cEscolha)
		{
			
			//Adicionar produto ao carrinho;
			case '1':
			{	
				
				std::cout <<"Digite o código do produto a adicionar: ";
				std::cin >>iId;
				
				strAux = buscaSimples(strCabecalho, iId);
				
				if(strAux != NULL)
				{
					registraProduto(strCarrinho, strAux->iId, strAux->fPreco, strAux->cDescricao, 1);
				}
				else
				{
					std::cout <<std::endl <<std::endl <<"Código inválido" <<std::endl;
					pause();
				}
				
			}break;
			
			//Remover produto do carrinho;
			case '2':
			{
				
				std::cout <<"Digite o código do produto a remover: ";
				std::cin >>iId;
				
				if(deletaItem(strCarrinho, iId) == 1)
				{
					std::cout <<std::endl <<std::endl <<"Código inválido" <<std::endl;
					pause();
				}
				
			}break;
			
			//Confirma compra;
			case '3':
			{
				std::cout <<std::endl <<std::endl <<"Compra finalizada.";
				pause();
			}break;
			
			default:
			{
				std::cout <<std::endl <<std::endl <<"Opção inválida.";
				pause();
			}break;
			
		}
		
	}while(cEscolha != '3');
	
	delete strCarrinho;
	
}

void menu(Cabecalho *strCabecalho, char cArq[50])
{
	
	int iId;
	float fPreco;
	char cDescricao[50], cEscolha;
	
	do
	{
		
		std::cout <<"------------------------------" <<std::endl;
		std::cout <<"|                            |" <<std::endl;
		std::cout <<"| 1 - Nova compra            |" <<std::endl;
		std::cout <<"| 2 - Registrar novo produto |" <<std::endl;
		std::cout <<"| 3 - Encerrar programa      |" <<std::endl;
		std::cout <<"|                            |" <<std::endl;
		std::cout <<"------------------------------" <<std::endl <<std::endl;
		
		std::cout <<"> ";
		std::cin >>cEscolha;
		
		switch(cEscolha)
		{
			
			//Nova compra;
			case '1':
			{	
				novoCarrinho(strCabecalho);
			}break;
			
			//Registrar novo produto no banco de dados;
			case '2':
			{
				
				std::cout <<"Código do produto: ";
				std::cin >>iId;
				
				std::cout <<"Digite o preço do produto: ";
				std::cin >>fPreco;
				
				std::cout <<"Digite a descrição do produto: ";
				std::cin >>cDescricao;
				
				if(registraProduto(strCabecalho, iId, fPreco, cDescricao, 0) == 0)
				{
					salvaBD(strCabecalho, cArq);
				}
				else
				{
					std::cout <<std::endl <<std::endl <<"Não foi possível criar um novo item" <<std::endl <<std::endl;
				}
				
			}break;
			
			//Sair;
			case '3':
			{
				std::cout <<std::endl <<std::endl <<"Programa encerrado.";
				pause();	
			}break;
			
			default:
			{
				std::cout <<std::endl <<std::endl <<"Opção inválida.";
				pause();
			}break;
			
		}
		
	}while(cEscolha != '3');
	
}

int main()
{

	setlocale(LC_ALL, "Portuguese");

	Cabecalho *strBD = new Cabecalho;	
	char cArq[50] = "produtos.bin";
	
	iniCabecalho(strBD);
	leBD(strBD, cArq);
	
	menu(strBD, cArq);
	
	delete strBD;
					
	return 0;
	
}
