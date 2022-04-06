#include <iostream>
#include <thread>

void cesarCode(char *data, int key, int mode)
{

    char *aux;
    int maxBoundry=27, minBoundry=0;

    char dictionaryLowerCase[maxBoundry] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', ' '};

    char dictionaryUpperCase[maxBoundry] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', ' '};

    int iPosDict=0, iPosData=0;
    int movePos=0;

    aux = data;

    //Deixar o número da chave dentro dos limites do alfabeto 0 >= key <= 25;
    if(key < minBoundry)
    {

        //Se menor que zero, deixa entre 0 e 25;
        while(key < minBoundry)
        {
            key = key+(maxBoundry-1);
        }

    }
    else
    {

        //Se maior que vinte e cinco, deixa entre 0 e 25;
        if(key > maxBoundry)
        {

            while(key > maxBoundry)
            {
                key = key-(maxBoundry-1);
            }

        }

    }

    //Enquanto não encontrar o caracter que termina a string;
    while(*aux!='\0')
    {

        iPosDict=0;

        //Verifica posição por posição até encontrar em qual posição do alfabeto a letra de data se encontra;
        while(*aux != dictionaryLowerCase[iPosDict] && *aux != dictionaryUpperCase[iPosDict])
        {
            iPosDict++;
        }

        //No modo 1 é feita a criptografia;
        if(mode == 1)
        {

            movePos = iPosDict+key;

            //Caso a "chave" ou, o valor de letras para pular para embaralhar for maior que vinte e cinco, do z pula para o a;
            while(movePos > 25)
            {
                //Subtrai 26 enquanto for possível, assim garante que o valor não vai ser maior que a quantidade de letras no alfabeto;
                movePos = movePos-26;
            }

            //Troca a letra de data pela que está no dicionário N vezes a frente;
            //Garantindo as letras maiúsculas e minúsculas também;
            if(*aux == dictionaryLowerCase[iPosDict] && *aux != ' ')
            {
                data[iPosData] = dictionaryLowerCase[movePos];
            }
            else
            {

                if(*aux == dictionaryUpperCase[iPosDict] && *aux != ' ')
                {
                    data[iPosData] = dictionaryUpperCase[movePos];
                }

            }

        }
        else
        {

            //No modo 2 é feita a descriptografia;
            if(mode == 2)
            {

                movePos = iPosDict-key;

                //Caso a "chave" ou, o valor de letras para pular para embaralhar for menor que 0, do a pula para o z;
                while(movePos < 0)
                {
                    //Incrementa 26 enquanto for possível, assim garante que o valor não vai ser menor que a quantidade de letras no alfabeto;
                    movePos = movePos+26;
                }

                //Troca a letra de data pela que está no dicionário N vezes a frente;
                //Garantindo as letras maiúsculas e minúsculas também;
                if(*aux == dictionaryLowerCase[iPosDict] && *aux != ' ')
                {
                    data[iPosData] = dictionaryLowerCase[movePos];
                }
                else
                {

                    if(*aux == dictionaryUpperCase[iPosDict] && *aux != ' ')
                    {
                        data[iPosData] = dictionaryUpperCase[movePos];
                    }

                }

            }

        }

        //Vai para a próxima letra de data;
        aux++;
        iPosData++;

    }

}

int main()
{

    /*
    char *data;

    data = (char *)malloc(sizeof(char));

    if(data != NULL)
    {

        std::cout <<"Teste: ";
        std::cin.getline(data, 100);

        //Criptografar;
        cesarCode(data, -15, 1);

        std::cout <<data <<std::endl;

        //Descriptografar;
        cesarCode(data, -15, 2);

        std::cout <<data;

    }
    */

    //free(data);

    char cText[50] = "Eu gosto de panqueca no cafe da manha";

    cesarCode(cText, 0, 1);

    std::cout <<cText <<std::endl;

    cesarCode(cText, 0, 2);

    std::cout <<cText <<std::endl;

}
