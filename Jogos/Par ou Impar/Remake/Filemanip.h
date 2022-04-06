#include <stdio.h>

class Filemanip
{

    private:

        //Status 0 = Sucesso nas operações;
        //Status -1 = Não foi possível criar a pasta;
        //Status -2 = Não foi possível criar o arquivo;
        int iStatus=0, iControl;
        std::string sDirName, sCommand;

    public:

        //Coloca e retorna o nome do diretório;
        void setDir(std::string name)
        {
            sDirName = name;
        }

        std::string getDir()
        {
            return sDirName;
        }

        //Método de criar arquivo;
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

        //Método de escrita no arquivo;
        //Método de leitura do arquivo;
        //Método de verificação se o arquivo existe;
        bool fileExist(std::string sFileName)
        {
            return ;
        }

};
