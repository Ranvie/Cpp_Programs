//Bugs:

//Looping nas funções que o bRepeatChar é falso;

//Bug na hora de escolher o dicionário, onde se o dicionário estiver desabilitado, ele cria um espaço em branco entre os caractéres;

//Problema na hora de transformar o que está em iRand em -1, isso porque, em algum momento algum dos dicionários não vai ter
//caractéres suficientes para gerar, então vai ficar em um looping infinito, onde nunca encontra um valor diferente de -1;
//Exemplo: dicionário do espaço que com certeza vai dar problema;

#include <iostream>
#include "../Minhas classes/Randomic.hpp"

char *genPassword(int iSize, bool bSpecialChar, bool bNumber, bool bChar, bool bCapsLock, bool iSpace, bool bRepeatChar)
{

    char *cPassword;
    int *iRandCombination, iCont, *iPickFromDict, iAux;

    char cCharLowerCase[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    char cCharUpperCase[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    char cNumber[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    char cSpace[1] = {' '};

    char cSpecial[32] = {'!', '"', '#', '$', '%' , '&' , '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=',
    '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'};

    if(iSize > 0 && iSize <= 32)
    {

        cPassword = new char[iSize];

        //Não podem ter caractéres repetidos;
        if(bRepeatChar)
        {
            iRandCombination = noRepeatGen(iSize, 0, 32);
        }

        //Define de qual dicionário vai ser o elemento;
        iPickFromDict = randGen(iSize, 0, 4);

        //Enquanto não gerar todos os caractéres da senha;
        for(iCont=0; iCont < iSize; iCont++)
        {

            //Caractéres especiais;
            if(bSpecialChar && iPickFromDict[iCont] == 0)
            {

                //Pode repetir;
                if(bRepeatChar)
                {
                    cPassword[iCont] = cSpecial[singleGen(0,31)];
                } //Não pode repetir;
                else
                {

                    //Loopar se iRandCombination na posição iAux for -1;
                    //Fazer isso pra todos, to com preguiça agora :b;

                    iAux = singleGen(0,31);
                    cPassword[iCont] = cSpecial[iRandCombination[iAux]];
                    iRandCombination[iAux] = -1;
                }

            }
            else
            {

                //Números;
                if(bNumber && iPickFromDict[iCont] == 1)
                {

                    if(bRepeatChar)
                    {
                        cPassword[iCont] = cNumber[singleGen(0,9)];
                    }
                    else
                    {
                        iAux = singleGen(0,9);
                        cPassword[iCont] = cNumber[iRandCombination[iAux]];
                        iRandCombination[iAux] = -1;
                    }

                }
                else
                {

                    //Caractéres minúsculos;
                    if(bChar && iPickFromDict[iCont] == 2)
                    {

                        if(bRepeatChar)
                        {
                            cPassword[iCont] = cCharLowerCase[singleGen(0,25)];
                        }
                        else
                        {
                            iAux = singleGen(0,25);
                            cPassword[iCont] = cCharLowerCase[iRandCombination[iAux]];
                            iRandCombination[iAux] = -1;
                        }

                    }
                    else
                    {

                        //Caractéres maiúsculos;
                        if(bCapsLock && iPickFromDict[iCont] == 3)
                        {

                            if(bRepeatChar)
                            {
                                cPassword[iCont] = cCharUpperCase[singleGen(0,25)];
                            }
                            else
                            {
                                iAux = singleGen(0,25);
                                cPassword[iCont] = cCharUpperCase[iRandCombination[iAux]];
                                iRandCombination[iAux] = -1;
                            }

                        }
                        else
                        {

                            //Barra de espaço;
                            if(iSpace && iPickFromDict[iCont] == 4)
                            {

                                if(bRepeatChar)
                                {
                                    cPassword[iCont] = cSpace[singleGen(0,25)];
                                }
                                else
                                {
                                    iAux = singleGen(0,25);
                                    cPassword[iCont] = cSpace[iRandCombination[iAux]];
                                    iRandCombination[iAux] = -1;
                                }

                            }

                        }

                    }

                }

            }

        }

    }

    delete iPickFromDict;
    delete iRandCombination;

    return cPassword;

}

int main()
{

    setlocale(LC_ALL, "Portuguese");

    char *cPassword;
    int iPos, iSize=10;

    cPassword = genPassword(iSize, 1, 1, 1, 1, 0, 1);

    std::cout <<"Senha gerada: ";

    for(int iPos=0; iPos < iSize; iPos++)
    {
        std::cout <<cPassword[iPos];
    }

    delete cPassword;

    return 0;

}
