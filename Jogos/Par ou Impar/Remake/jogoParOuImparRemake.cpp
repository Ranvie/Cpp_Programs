#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Filemanip.h"

using namespace std;
const char* FILE_SRC = "Score.bin";

enum class OddOrEven { Odd=2, Even=1 };
enum class Result { Win, Lose };

struct Score
{
    int win;
    int lose;
};

string errMsgOnlyIntAllowed()
{
    string msg = "| Apenas números inteiros são permitidos |";

    return msg;
}

string errMsgMaxStringSize(int maxSize)
{
    return string("| O tamanho máximo de entrada é de até ") + to_string(maxSize) + string(" caractere(s) ou dígito(s) |");
}

string errMsgOutsideBounds(int minBound, int maxBound)
{
    return string("| Digite um número entre ") + to_string(minBound) + " e " + to_string(maxBound) + string(" |");
}

string handleInput(string input, int inputMaxLength, int boundMin, int boundMax)
{
    string status = "OK";
    int converted;

    try
    {
        if(inputMaxLength > 0 && input.length() > inputMaxLength)
        {
            throw -1;
        }
        else
        {
            converted = stoi(input);

            if(converted < boundMin || converted > boundMax)
            {
                throw -2;
            }
        }
    }
    catch(invalid_argument)
    {
        status = errMsgOnlyIntAllowed();
    }
    catch(int errCode)
    {
        switch(errCode)
        {
            case -1:
                status = errMsgMaxStringSize(inputMaxLength);
                break;

            case -2:
                status = errMsgOutsideBounds(boundMin, boundMax);
                break;
        }
    }
    catch(...)
    {
        status = "| Erro desconhecido, por favor, tente novamente |";
    }

    return status;
}

template<typename ...Args>
int inputMenu(void (*messageFunction)(Args...), int maxInputLength, int boundMin, int boundMax, Args ...args)
{
    string input;
    string status;
    bool isErrorOcurred;

    do
    {
        try
        {
            messageFunction(args...);
            cin.clear();
            cin >>input;

            status = handleInput(input, maxInputLength, boundMin, boundMax);

            if(status != "OK")
            {
                throw status;
            }

            isErrorOcurred = false;
        }
        catch(string err)
        {
            cout <<"\n" <<err <<"\n";
            system("pause");
            system("cls");

            isErrorOcurred = true;
        }
    }while(isErrorOcurred);

    return stoi(input);
}

void showPlayerChoiceMenu()
{
    cout <<"-----------------------------\n";
    cout <<"|                           |\n";
    cout <<"| Selecione uma das opções: |\n";
    cout <<"|                           |\n";
    cout <<"| [1] Selecionar Par        |\n";
    cout <<"| [2] Selecionar Ímpar      |\n";
    cout <<"| [3] Voltar                |\n";
    cout <<"|                           |\n";
    cout <<"-----------------------------\n\n";

    cout <<"Digite sua escolha: ";
}

void evenChoiceMessage()
{
    cout <<"----------------------\n";
    cout <<"| Você escolheu: Par |\n";
    cout <<"----------------------\n\n";
}

void showEvenChoiceMenu()
{
    evenChoiceMessage();
    cout <<"> Digite um número de 0 até 10: ";
}

void oddChoiceMessage()
{
    cout <<"------------------------\n";
    cout <<"| Você escolheu: Ímpar |\n";
    cout <<"------------------------\n\n";
}

void showOddChoiceMenu()
{
    oddChoiceMessage();
    cout <<"> Digite um número de 0 até 10: ";
}

int randNumber(int minInclusive, int maxExclusive)
{
    return rand() % maxExclusive + minInclusive;
}

void showEvenResult()
{
    cout <<"------------\n";
    cout <<"| Deu Par! |\n";
    cout <<"------------\n\n";
}

void showOddResult()
{
    cout <<"--------------\n";
    cout <<"| Deu Ímpar! |\n";
    cout <<"--------------\n\n";
}

void showLoseMsg()
{
    cout <<"| Que pena, você perdeu :( |\n\n";
}

void showLoseMessage(OddOrEven userChoice)
{
    if(userChoice == OddOrEven::Even)
    {
        showEvenResult();
        showLoseMsg();
    }
    else
    {
        showOddResult();
        showLoseMsg();
    }
}

void showWinMessage()
{
    cout <<"| Parabéns! Você venceu! :) |\n\n";
}

void showWinMessage(OddOrEven userChoice)
{
    if(userChoice == OddOrEven::Even)
    {
        showEvenResult();
        showWinMessage();
    }
    else
    {
        showOddResult();
        showWinMessage();
    }
}

Result checkResult(int userChoice, int result)
{
    Result status;

    if(userChoice == (int)OddOrEven::Even)
    {
        if(result % 2 == 0)
        {
            showWinMessage(OddOrEven::Even);
            status = Result::Win;
        }
        else
        {
            showLoseMessage(OddOrEven::Odd);
            status = Result::Lose;
        }
    }
    else
    {
        if(result % 2 != 0)
        {
            showWinMessage(OddOrEven::Odd);
            status = Result::Win;
        }
        else
        {
            showLoseMessage(OddOrEven::Even);
            status = Result::Lose;
        }
    }

    return status;
}

Score readScore(const char *fileSrc)
{
    Filemanip filemanip;
    Score score;
    score.win = 0;
    score.lose = 0;

    try
    {
        if(!filemanip.isFileExists(fileSrc))
        {
            filemanip.createFile(fileSrc);
            filemanip.writeFile(fileSrc, score);
        }

        score = filemanip.readFile(fileSrc, score);
    }
    catch(...)
    {
        cout <<"| Um erro ocorreu ao ler as pontuações. |";
    }

    return score;
}

void saveScore(const char *fileSrc, Score score)
{
    Filemanip filemanip;

    try
    {
        if(&score == nullptr) { throw exception(); }

        if(!filemanip.isFileExists(fileSrc))
        {
            filemanip.createFile(fileSrc);
        }

        filemanip.writeFile(fileSrc, score);
    }
    catch(...)
    {
        cout <<"| Um erro ocorreu ao salvar as pontuações. |";
    }
}

void saveWinAndLose(const char *fileSrc, Result result)
{
    Score templScore;
    Score score = readScore(fileSrc);

    if(result == Result::Win)
    {
        score.win++;
    }
    else
    {
        score.lose++;
    }

    saveScore(fileSrc, score);
}

void showContinueMenu()
{
    cout <<"---------------------\n";
    cout <<"| Deseja Continuar? |\n";
    cout <<"|                   |\n";
    cout <<"| [1] Sim           |\n";
    cout <<"| [2] Não           |\n";
    cout <<"|                   |\n";
    cout <<"---------------------\n\n";

    cout <<"> Digite sua escolha: ";
}

void startGame()
{
    int userChoice;
    int userNumber;
    int computerNumber;
    int sum;

    do
    {
        userChoice = inputMenu(&showPlayerChoiceMenu, 1, 1, 3);
        system("cls");

        switch(userChoice)
        {
            case 1:
                userNumber = inputMenu(&showEvenChoiceMenu, 2, 0, 10);

                system("cls");
                evenChoiceMessage();
                break;
            case 2:
                userNumber = inputMenu(&showOddChoiceMenu, 2, 0, 10);

                system("cls");
                oddChoiceMessage();
                break;
        }

        if(userChoice != 3)
        {
            computerNumber = randNumber(0, 11);
            sum = userNumber + computerNumber;

            cout <<"| Seu número: " <<userNumber <<" |\n\n";
            cout <<"| O número do computador: " <<computerNumber <<" |\n\n";
            cout <<"| " <<userNumber <<" + " <<computerNumber <<" = " <<sum <<" |\n\n";

            saveWinAndLose(FILE_SRC, checkResult(userChoice, sum));
            system("pause");
            system("cls");

            userChoice = (inputMenu(&showContinueMenu, 1, 1, 2) == 2) ? 3 : userChoice; //Think a better way of doing this :P
            system("cls");
        }

    }while(userChoice != 3);
}

void showConfirmationMenu()
{
    cout <<"-----------------------\n";
    cout <<"| Apagar a pontuação? |\n";
    cout <<"|    (Irreversível)   |\n";
    cout <<"|                     |\n";
    cout <<"| [1] Sim             |\n";
    cout <<"| [2] Não             |\n";
    cout <<"|                     |\n";
    cout <<"-----------------------\n\n";

    cout <<"> Digite sua escolha: ";
}

void showWinLoseMenu(int win, int lose)
{
    cout <<"------------------------\n";
    cout <<"|      [PONTUAÇÃO]     |\n";
    cout <<"|                      |\n";
    cout <<"| [1] Apagar Pontuação |\n";
    cout <<"| [2] Voltar           |\n";
    cout <<"|                      |\n";
    cout <<"------------------------\n\n";

    cout <<"| Você venceu: " <<win <<" vez(es). |\n\n";
    cout <<"| Você perdeu: " <<lose <<" vez(es). |\n\n";

    cout <<"> Selecione uma opção: ";
}

void showScore()
{
    Filemanip filemanip;
    Score score = readScore(FILE_SRC);

    int userChoice;

    do
    {
        userChoice = inputMenu(&showWinLoseMenu, 1, 1, 2, score.win, score.lose);
        system("cls");

        if(userChoice == 1)
        {
            if(inputMenu(&showConfirmationMenu, 1, 1, 2) == 1)
            {
                score.win = 0;
                score.lose = 0;
                filemanip.writeFile(FILE_SRC, score);
            }
            system("cls");
        }
    }while(userChoice != 2);
}

void showTutorial()
{
    cout <<"---------------------------------------------------------\n";
    cout <<"|                    [REGRAS DO JOGO]                   |\n";
    cout <<"|                                                       |\n";
    cout <<"| *Antes de o jogo iniciar, escolha entre par ou ímpar  |\n";
    cout <<"|                                                       |\n";
    cout <<"| *Ao iniciar o jogo, selecione um número entre 0 e 10  |\n";
    cout <<"|                                                       |\n";
    cout <<"| *O computador tambem selecionará um número de 0 a 10  |\n";
    cout <<"|                                                       |\n";
    cout <<"| *Será feita a soma entre seu número e o do computador |\n";
    cout <<"|                                                       |\n";
    cout <<"| *Assim saberá se venceu ou perdeu                     |\n";
    cout <<"---------------------------------------------------------\n\n";
    system("pause");
    system("cls");
}

void showGoodbye()
{
    cout <<"----------------------\n";
    cout <<"| !!!Volte Sempre!!! |\n";
    cout <<"----------------------\n\n";
    system("pause");
}

void showMainMenu()
{
    cout <<"---------------------------------------\n";
    cout <<"| Bem vindo(a) ao jogo: Par ou Ímpar! |\n";
    cout <<"|                                     |\n";
    cout <<"|                [MENU]               |\n";
    cout <<"|                                     |\n";
    cout <<"| [1] Iniciar jogo                    |\n";
    cout <<"| [2] Placar                          |\n";
    cout <<"| [3] Instruções                      |\n";
    cout <<"| [4] Sair                            |\n";
    cout <<"|                                     |\n";
    cout <<"---------------------------------------\n\n";

    cout <<"> Digite a operação desejada[um valor de 1 a 4]: ";
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int menuChoice;
    srand(time(0));

    do
    {
        menuChoice = inputMenu(&showMainMenu, 1, 1, 4);
		system("cls");

        switch(menuChoice)
        {
            case 1:
                startGame();
                break;

            case 2:
                showScore();
                break;

            case 3:
                showTutorial();
                break;

            case 4:
                showGoodbye();
                break;
        }
    }while(menuChoice != 4);

    return 0;
}
