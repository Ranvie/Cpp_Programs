#include <iostream>

struct No{
	int iNum;
	No *strEsq;
	No *strDir;
};

struct Arvore{
	No *strRaiz;
};

void iniArv(Arvore *strArv)
{
	strArv->strRaiz = NULL;
}

No *criaNo(Arvore *strArv, int iNum)
{

	No *strItem = new No;

	strItem->iNum = iNum;
	strItem->strDir = NULL;
	strItem->strEsq = NULL;

	return strItem;

}

No *buscaNo(No *strNo, int iNum)
{

	No *strAux;

	while(strNo != NULL)
	{

		strAux = strNo;

		if(iNum < strNo->iNum)
		{
			strNo = strNo->strEsq; //5 //3
		}
		else
		{
			strNo = strNo->strDir; //2
		}

	}

	return strAux;

}

void insereNo(Arvore *strArv, int iNum)
{

	No *strItem, *strPos;

	strItem = criaNo(strArv, iNum);

	//Alocou memória;
	if(strItem != NULL)
	{

		//Insere na raiz;
		if(strArv->strRaiz == NULL)
		{
			strArv->strRaiz = strItem;
		}
		else
		{

			//Busca o nó para inserir;
			strPos = buscaNo(strArv->strRaiz, iNum);

			if(iNum < strPos->iNum)
			{
				strPos->strEsq = strItem;
			}
			else
			{
				strPos->strDir = strItem;
			}

		}

	}

}

int calcAltura(No *strNo)
{

    int altE, altD;

	if(strNo == NULL)
    {
        return -1;
    }
    else
    {

        altE = calcAltura(strNo->strEsq);
        altD = calcAltura(strNo->strDir);

        if(altE < altD)
        {
            return altD + 1;
        }
        else
        {
            return altE + 1;
        }

    }

}

int calcFolha(No *strNo)
{

	int iTamanho=0;

	if(strNo != NULL)
	{
		iTamanho++;
		iTamanho += calcFolha(strNo->strEsq);
		iTamanho += calcFolha(strNo->strDir);
	}

	return iTamanho;

}

void imprimeArv(No *strNo)
{

	if(strNo != NULL)
	{

		std::cout <<strNo->iNum;

		imprimeArv(strNo->strEsq);
		imprimeArv(strNo->strDir);

	}

}

int main()
{

	Arvore *strArv = new Arvore;
	No *strNo;

	iniArv(strArv);

	insereNo(strArv, 5);
	insereNo(strArv, 3);
	insereNo(strArv, 2);
	insereNo(strArv, 4);
	insereNo(strArv, 2);
	insereNo(strArv, 6);
	insereNo(strArv, 5);
	insereNo(strArv, 7);
	insereNo(strArv, 1);
	insereNo(strArv, 2);

	std::cout <<calcAltura(strArv->strRaiz);

	//imprimeArv(strArv->strRaiz);

	delete strArv;

	return 0;

}
