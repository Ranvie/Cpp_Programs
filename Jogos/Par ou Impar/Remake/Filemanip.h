#include <stdio.h>

class Filemanip
{

    private:

        //Status 0 = Sucesso nas opera��es;
        //Status -1 = N�o foi poss�vel criar a pasta;
        //Status -2 = N�o foi poss�vel criar o arquivo;
        int iStatus=0, iControl;
        std::string sDirName, sCommand;

    public:

        //Coloca e retorna o nome do diret�rio;
        void setDir(std::string name)
        {
            sDirName = name;
        }

        std::string getDir()
        {
            return sDirName;
        }

        //M�todo de criar arquivo;
        int newFile(std::string sFileName)
        {

            FILE *file;

            iControl = 0;

            if()
            {

                sCommand = "mkdir " + sDirName + ">NULL";

                do
                {

                    //Tenta criar a pasta;
                    if(system(sCommand))
                    {
                        //Erro;
                        iStatus = -1;
                    } //Criou;
                    else
                    {
                        iStatus == 0;
                    }

                }while(iControl < 2 || iStatus == 0);

            }

            return iStatus;

        }

        //M�todo de escrita no arquivo;
        //M�todo de leitura do arquivo;
        //M�todo de verifica��o se o arquivo existe;
        bool fileExist(std::string sFileName)
        {
            return ;
        }

};
