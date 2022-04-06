#include <iostream>
	using std::cout;
	using std::cin;
#include <fstream>
	using std::ifstream;
	using std::ofstream;
#include <string>
	using std::string;
	using std::to_string;
#include <vector>
	using std::vector;
#include <sstream>
	using std::ostringstream;
#include <iterator>
	using std::ostream_iterator;
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <locale.h>

class FileManipulation
{

	//Bibliotecas necessarias para o funcionamento;
	/*----------------\
	#include <iostream>
		using std::cout;
		using std::cin;
	#include <fstream>
		using std::ifstream;
		using std::ofstream;
	#include <string>
		using std::string;
	#include <sstream>
		using std::ostringstream;
	#include <vector>
		using std::vector;
	#include <iterator>
		using std::ostream_iterator;
	\----------------*/

	public:

	//Altere 'fileExample.txt' pelo nome desejado;
	//Mantenha o '.txt' para criar arquivos do tipo texto;
	string fileName = "score.txt";

	//Verificar se um arquivo especifico existe;
	bool doFileExist()
	{
		ifstream fileRead(fileName);
		return fileRead.good();
	}

	//Cria um arquivo;
	void createFile()
	{

		ofstream createFile(fileName);
		createFile.close();

	}

	//Le o arquivo e retorna uma variavel com todo conteudo;
	string readFile()
	{

		string sFileRead;

		ifstream readFile(fileName);

		ostringstream readBuffer;
		readBuffer <<readFile.rdbuf();

		sFileRead = readBuffer.str();

		readFile.close();

		return sFileRead;

	}

	//Salva dados em um documento no formato de vetor;
	void writeScore(string lose, string win)
	{

		vector<string> vSaveScore = {lose, win};

		ofstream createFile(fileName);
		ostream_iterator<string> output_iterator(createFile, "\n");

		copy(vSaveScore.begin(), vSaveScore.end(), output_iterator);

		createFile.close();

	}

	//Le as variaveis no documento e coloca no vetor vReadscore;
	vector<string> readScore()
	{

		vector<string> vReadScore;

		ifstream readFile(fileName);

		string tempVar;
		while(readFile >> tempVar)
		{

			vReadScore.push_back(tempVar);

		}

		readFile.close();

		return vReadScore;

	}

	//Conta a quantidade de linhas em um arquivo;
	int countLine()
	{

		int count = 0;
	    string line;

	    ifstream readFile(fileName);
	    while (getline(readFile, line))
	 	{

	        count++;

	    }

	    return count;

	}

};

class Utils
{

	//Bibliotecas necessarias para o funcionamento;
	/*-----------------\
	#include <iostream>
		using std::cout;
		using std::cin;
	#include <string>
		using std::string;
		using std::to_string;
	\-----------------*/

	public:

	//Funcao para tratar se foram digitados caracteres;
	bool isNumber(const string& s)
	{

    	return(strspn(s.c_str(), "0123456789") == s.size());

	}

	//Funcao para converter de String para Inteiros;
	int stringToInt(const string &s)
	{

		return stoi(s);

	}

	//Funcao para converter de Inteiro para String;
	string intToString(int s)
	{

		return to_string(s);

	}

	//Funcao para limpar a tela;
	void clrscr()
	{

		cout << "\x1B[2J\x1B[H";

	}

	//Funcao de pausa;
	void pause()
	{

		cin.ignore();
		cout <<"\n\n";
		cout <<"------------------------------------------\n";
		cout <<"| Pressione <ENTER> para continuar . . . |\n";
		cout <<"------------------------------------------\n\n";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		clrscr();

	}

	//Funcao para definir um limite ao input do usuario;
	bool inputLength(string userInput)
	{

		//Altere este valor para definir a quantidade maxima de caracteres;
		int charMaximum = 3;

		if(userInput.size() <= charMaximum)
		{

			return true;

		}
		else
		{

			return false;

		}

	}

};

int main()
{

	//Declarando a classe Utils;
	Utils utils;

	//Declarando a classe fileManipulation;
	FileManipulation fileManipulation;

	setlocale(LC_ALL, "Portuguese");

	//Declarar a variavel de escolha do usuario e variavel looping;
	int iLoop = 1;
	string sMenuChoice;

	//Sistema de looping para as filtragens;
	while(iLoop == 1)
	{

		//Pedir input do usuario;
		cout <<"---------------------------------------\n";
		cout <<"| Bem vindo(a) ao jogo: Par ou Impar! |\n";
		cout <<"|                                     |\n";
		cout <<"|                [MENU]               |\n";
		cout <<"|                                     |\n";
		cout <<"| [1] Iniciar jogo                    |\n";
		cout <<"| [2] Placar                          |\n";
		cout <<"| [3] Instrucoes                      |\n";
		cout <<"| [4] Sair                            |\n";
		cout <<"|                                     |\n";
		cout <<"---------------------------------------\n\n";

		cout <<"> Digite a operação desejada[um valor de 1 a 4]: ";
		cin >>sMenuChoice;

		utils.clrscr();

		//Filtragem para saber se é um número ou caracter;
		//Ou se excede o tamanho maximo definido na funcao inputLength();
		if(utils.inputLength(sMenuChoice) && utils.isNumber(sMenuChoice) == 1)
		{

			switch(utils.stringToInt(sMenuChoice))
			{

				case 1:
				{

					//Declarar a seed, escolha do usuario e input do usuario;
					//O unsigned apenas deixa serem gerados numeros positivos;
					unsigned int unsISeed;
					unsISeed = time(0);
					string sUserChoice, sUserInput;

					//Gerar numero aleatorio de 0 a 10;
					srand(unsISeed);
					unsigned int unsIRandomized;
					unsIRandomized = rand()%11;

					//looping para as filtragens
					int iLoopGame;
					iLoopGame = 1;

					while(iLoopGame == 1)
					{

						cout <<"-----------------------------\n";
						cout <<"|                           |\n";
						cout <<"| Selecione uma das opcoes: |\n";
						cout <<"|                           |\n";
						cout <<"| [0] Selecionar Par        |\n";
						cout <<"| [1] Selecionar Impar      |\n";
						cout <<"| [2] Voltar                |\n";
						cout <<"|                           |\n";
						cout <<"-----------------------------\n\n";

						cout <<"Digite sua escolha: ";
						cin >>sUserChoice;
						utils.clrscr();

						//Filtragem para saber se foram digitados apenas numeros;
						if(utils.inputLength(sUserChoice) && utils.isNumber(sUserChoice) == 1)
						{

							//Conversao de string para inteiro;
							switch(utils.stringToInt(sUserChoice))
							{

								case 0:
								{

									while(iLoopGame == 1)
									{

										//Usuario selecionou par;
										//Entrada do usuario;
										cout <<"----------------------\n";
										cout <<"| Voce escolheu: Par |\n";
										cout <<"----------------------\n\n";

										cout <<"> Digite um numero de 0 ate 10: ";
										cin >>sUserInput;
										utils.clrscr();

										//Filtragem para saber se foram digitados apenas numeros;
										if(utils.inputLength(sUserInput) && utils.isNumber(sUserInput) == 1)
										{

											//Filtragem para limitar o input do usuario de 0 a 10;
											if(utils.stringToInt(sUserInput) >= 0 && utils.stringToInt(sUserInput) <= 10)
											{

												//Casting de Char para Int para fazer a soma entre o numero gerado
												//pelo computador e entre o valor de input do usuario;
												int iUserInput = utils.stringToInt(sUserInput);

												int iResultEven = unsIRandomized + iUserInput;

												//Mostrar resultado
												cout <<"------------------------\n";
												cout <<"| Voce selecionou: Par |\n";
												cout <<"------------------------\n\n";

												cout <<"| Seu numero: " <<iUserInput <<" |\n\n";
												cout <<"| O numero do computador: " <<unsIRandomized <<" |\n\n";
												cout <<"| " <<iUserInput <<" + " <<unsIRandomized <<" = " <<iUserInput+unsIRandomized <<" |\n\n";

												if(iResultEven % 2 == 0)
												{

													int iFileLoop = 1;

													cout <<"------------\n";
													cout <<"| Deu Par! |\n";
													cout <<"------------\n\n";

													cout <<"-----------------------------\n";
													cout <<"| Parabens! Voce venceu! :) |\n";
													cout <<"-----------------------------\n";

													//Roda este trecho ate o arquivo ser criado e a pontuacao ser devidamente salva;
													while(iFileLoop == 1)
													{
														//Salvar pontuacao em um arquivo;
														//Verificar se arquivo existe;
														if(fileManipulation.doFileExist())
														{

															//Verificar se o documento possui mais, ou, menos de 2 linhas;
															if(fileManipulation.countLine() == 2)
															{

																vector<string> vsScore;

																//Abrir arquivo e salvar as variaveis do vetor;
																vsScore = fileManipulation.readScore();
																string sLose = vsScore[0], sWin = vsScore[1];

																//Verifica se e inteiro;
																if(utils.isNumber(sLose) && utils.isNumber(sWin))
																{

																	//converter de string para inteiro;
																	int iLose = utils.stringToInt(sLose), iWin = utils.stringToInt(sWin);

																	//Adicionar um ponto no win;
																	iWin = iWin+1;

																	//Converter de inteiro para String;
																	sLose = utils.intToString(iLose), sWin = utils.intToString(iWin);

																	//mandar a pontuacao de volta ao documento;
																	fileManipulation.writeScore(sLose, sWin);

																	iFileLoop = 0;

																}
																else
																{

																	//Cria o arquivo;
																	fileManipulation.createFile();

																	string sLose = "0", sWin = "0";
																	fileManipulation.writeScore(sLose, sWin);

																}

															}
															else
															{

																//Cria o arquivo;
																fileManipulation.createFile();

																string sLose = "0", sWin = "0";
																fileManipulation.writeScore(sLose, sWin);

															}

														}
														else
														{

															//Cria o arquivo;
															fileManipulation.createFile();

															string sLose = "0", sWin = "0";
															fileManipulation.writeScore(sLose, sWin);

														}

													}

													iLoopGame = 0;
													iLoop = 0;

													utils.pause();

												}
												else
												{

													int iFileLoop = 1;

													cout <<"--------------\n";
													cout <<"| Deu Impar! |\n";
													cout <<"--------------\n\n";

													cout <<"| Que pena, voce perdeu :( |";

													//Roda este trecho ate o arquivo ser criado e a pontuacao ser devidamente salva;
													while(iFileLoop == 1)
													{
														//Salvar pontuacao em um arquivo;
														//Verificar se arquivo existe;
														if(fileManipulation.doFileExist())
														{

															//Verificar se o documento possui mais, ou, menos de 2 linhas;
															if(fileManipulation.countLine() == 2)
															{

																vector<string> vsScore;

																//Abrir arquivo e salvar as variaveis do vetor;
																vsScore = fileManipulation.readScore();
																string sLose = vsScore[0], sWin = vsScore[1];

																//Verifica se e inteiro;
																if(utils.isNumber(sLose) && utils.isNumber(sWin))
																{

																	//converter de string para inteiro;
																	int iLose = utils.stringToInt(sLose), iWin = utils.stringToInt(sWin);

																	//Adicionar um ponto no lose;
																	iLose = iLose+1;

																	//Converter de inteiro para String;
																	sLose = utils.intToString(iLose), sWin = utils.intToString(iWin);

																	//mandar a pontuacao de volta ao documento;
																	fileManipulation.writeScore(sLose, sWin);

																	iFileLoop = 0;

																}
																else
																{

																	//Cria o arquivo;
																	fileManipulation.createFile();

																	string sLose = "0", sWin = "0";
																	fileManipulation.writeScore(sLose, sWin);

																}

															}
															else
															{

																//Cria o arquivo;
																fileManipulation.createFile();

																string sLose = "0", sWin = "0";
																fileManipulation.writeScore(sLose, sWin);

															}

														}
														else
														{

															//Cria o arquivo;
															fileManipulation.createFile();

															string sLose = "0", sWin = "0";
															fileManipulation.writeScore(sLose, sWin);

														}

													}

													iLoopGame = 0;
													iLoop = 0;

													utils.pause();

												}

						 					}
											else
											{

												cout <<"| Digite um numero entre 0 e 10! |";

												utils.pause();

											}

										}
										else
										{

											cout <<"| Nao sao permitidos caracteres, ou, mais de 3 digitos! |";

											utils.pause();

										}

									}

								}break;

								case 1:
								{

									while(iLoopGame == 1)
									{

										//Usuario selecionou impar;
										//Entrada do usuario;
										cout <<"------------------------\n";
										cout <<"| Voce escolheu: Impar |\n";
										cout <<"------------------------\n\n";

										cout <<"> Digite um numero de 0 ate 10: ";
										cin >>sUserInput;
										utils.clrscr();

										//Filtragem para saber se foram digitados apenas numeros;
										if(utils.inputLength(sUserInput) && utils.isNumber(sUserInput) == 1)
										{

											if(utils.stringToInt(sUserInput) >= 0 && utils.stringToInt(sUserInput) <= 10)
											{

												//Casting de Char para Int para fazer a soma entre o numero gerado
												//pelo computador e entre o valor de input do usuario;
												int iUserInput = utils.stringToInt(sUserInput);

												int iResultOdd = unsIRandomized + iUserInput;

												//Mostrar resultado
												cout <<"--------------------------\n";
												cout <<"| Voce selecionou: Impar |\n";
												cout <<"--------------------------\n\n";

												cout <<"| Seu numero: " <<iUserInput <<" |\n\n";
												cout <<"| O numero do computador: " <<unsIRandomized <<" |\n\n";
												cout <<"| " <<iUserInput <<" + " <<unsIRandomized <<" = " <<iUserInput+unsIRandomized <<" |\n\n";

												if(iResultOdd % 2 != 0)
												{

													int iFileLoop = 1;

													cout <<"--------------\n";
													cout <<"| Deu Impar! |\n";
													cout <<"--------------\n\n";

													cout <<"| Parabens! Voce venceu! :) |\n\n";

													//Roda este trecho ate o arquivo ser criado e a pontuacao ser devidamente salva;
													while(iFileLoop == 1)
													{
														//Salvar pontuacao em um arquivo;
														//Verificar se arquivo existe;
														if(fileManipulation.doFileExist())
														{

															//Verificar se o documento possui mais, ou, menos de 2 linhas;
															if(fileManipulation.countLine() == 2)
															{

																vector<string> vsScore;

																//Abrir arquivo e salvar as variaveis do vetor;
																vsScore = fileManipulation.readScore();
																string sLose = vsScore[0], sWin = vsScore[1];

																//Verifica se e inteiro;
																if(utils.isNumber(sLose) && utils.isNumber(sWin))
																{

																	//converter de string para inteiro;
																	int iLose = utils.stringToInt(sLose), iWin = utils.stringToInt(sWin);

																	//Adicionar um ponto no win;
																	iWin = iWin+1;

																	//Converter de inteiro para String;
																	sLose = utils.intToString(iLose), sWin = utils.intToString(iWin);

																	//mandar a pontuacao de volta ao documento;
																	fileManipulation.writeScore(sLose, sWin);

																	iFileLoop = 0;

																}
																else
																{

																	//Cria o arquivo;
																	fileManipulation.createFile();

																	string sLose = "0", sWin = "0";
																	fileManipulation.writeScore(sLose, sWin);

																}

															}
															else
															{

																//Cria o arquivo;
																fileManipulation.createFile();

																string sLose = "0", sWin = "0";
																fileManipulation.writeScore(sLose, sWin);

															}

														}
														else
														{

															//Cria o arquivo;
															fileManipulation.createFile();

															string sLose = "0", sWin = "0";
															fileManipulation.writeScore(sLose, sWin);

														}

													}

													iLoopGame = 0;
													iLoop = 0;

													utils.pause();

												}
												else
												{

													int iFileLoop = 1;

													cout <<"------------\n";
													cout <<"| Deu Par! |\n";
													cout <<"------------\n\n";

													cout <<"| Que pena, voce perdeu :( |\n\n";

													//Roda este trecho ate o arquivo ser criado e a pontuacao ser devidamente salva;
													while(iFileLoop == 1)
													{
														//Salvar pontuacao em um arquivo;
														//Verificar se arquivo existe;
														if(fileManipulation.doFileExist())
														{

															//Verificar se o documento possui mais, ou, menos de 2 linhas;
															if(fileManipulation.countLine() == 2)
															{

																vector<string> vsScore;

																//Abrir arquivo e salvar as variaveis do vetor;
																vsScore = fileManipulation.readScore();
																string sLose = vsScore[0], sWin = vsScore[1];

																//Verifica se e inteiro;
																if(utils.isNumber(sLose) && utils.isNumber(sWin))
																{

																	//converter de string para inteiro;
																	int iLose = utils.stringToInt(sLose), iWin = utils.stringToInt(sWin);

																	//Adicionar um ponto no lose;
																	iLose = iLose+1;

																	//Converter de inteiro para String;
																	sLose = utils.intToString(iLose), sWin = utils.intToString(iWin);

																	//mandar a pontuacao de volta ao documento;
																	fileManipulation.writeScore(sLose, sWin);

																	iFileLoop = 0;

																}
																else
																{

																	//Cria o arquivo;
																	fileManipulation.createFile();

																	string sLose = "0", sWin = "0";
																	fileManipulation.writeScore(sLose, sWin);

																}

															}
															else
															{

																//Cria o arquivo;
																fileManipulation.createFile();

																string sLose = "0", sWin = "0";
																fileManipulation.writeScore(sLose, sWin);

															}

														}
														else
														{

															//Cria o arquivo;
															fileManipulation.createFile();

															string sLose = "0", sWin = "0";
															fileManipulation.writeScore(sLose, sWin);

														}

													}

													iLoopGame = 0;
													iLoop = 0;

													utils.pause();

												}

											}
											else
											{

												cout <<"| Digite um numero entre 0 e 10! |";

												utils.pause();

											}

										}
										else
										{

											cout <<"| Nao sao permitidos caracteres, ou, mais de 3 digitos! |";

											utils.pause();

										}

									}

								}break;

								case 2:
								{

									//Volta ao comeco do codigo;
									return main();

								}break;

								default:
								{

									cout <<"| Opcao invalida! Selecione entre 0 e 2 |";

									utils.pause();

								}break;

							}

						}
						else
						{

							cout <<"| Nao sao permitidos caracteres, ou, mais de 3 digitos! |";

							utils.pause();

						}

					}

				}break;

				case 2:
				{

					string sUserInput;
					int iLoop = 1;

					//Consultar pontuacao;
					while(iLoop == 1)
					{

						//Verificando se o arquivo existe;
						if(fileManipulation.doFileExist())
						{

							//Verifica se documento possui 2 linhas;
							if(fileManipulation.countLine() == 2)
							{

								//Chamar a funcao de leitura de arquivo para mostrar a pontuacao;
								vector<string> vReadScore = fileManipulation.readScore();
								string sLose = vReadScore[0], sWin = vReadScore[1];

								//Verifica se e inteiro;
								if(utils.isNumber(sLose) && utils.isNumber(sWin))
								{

									cout <<"------------------------\n";
									cout <<"|      [PONTUACAO]     |\n";
									cout <<"|                      |\n";
									cout <<"| [1] Apagar Pontuacao |\n";
									cout <<"| [2] Voltar           |\n";
									cout <<"|                      |\n";
									cout <<"------------------------\n\n";

									cout <<"| Voce venceu: " <<sLose <<" vez(es). |\n\n";
									cout <<"| Voce perdeu: " <<sWin <<" vez(es). |\n\n";

									cout <<"> Selecione uma opcao: ";
									cin >>sUserInput;

									utils.clrscr();

									//Verificando se foram digitados caracteres ou se o input passa de 3 caracteres;
									if(utils.isNumber(sUserInput) == 1 && utils.inputLength(sUserInput))
									{

										switch(utils.stringToInt(sUserInput))
										{

											case 1:
											{

												//Definir as variaveis como 0;
												string lose = "0", win = "0";
												fileManipulation.writeScore(lose, win);

											}break;

											case 2:
											{

												//Retornar ao menu inicial;
												return main();

											}break;

											default:
											{

												cout <<"| Opcao invalida! Selecione entre 1 e 2! |";

												utils.pause();

											}break;

										}

									}
									else
									{

										cout <<"| Nao sao permitidos caracteres, ou, mais de 3 digitos! |";

										utils.pause();

									}

								}
								else
								{

									//Criar arquivo;
									fileManipulation.createFile();

									//Definir as variaveis como 0 dentro do documento;
									string lose = "0", win = "0";
									fileManipulation.writeScore(lose, win);

								}

							}
							else
							{

								//Criar arquivo;
								fileManipulation.createFile();

								//Definir as variaveis como 0 dentro do documento;
								string lose = "0", win = "0";
								fileManipulation.writeScore(lose, win);

							}

						}
						else
						{

							//Criar arquivo;
							fileManipulation.createFile();

							//Definir as variaveis como 0 dentro do documento;
							string lose = "0", win = "0";
							fileManipulation.writeScore(lose, win);

						}

					}

				}break;

				case 3:
				{

					//Explicar como o jogo funciona;
					cout <<"---------------------------------------------------------\n";
					cout <<"|                    [REGRAS DO JOGO]                   |\n";
					cout <<"|                                                       |\n";
					cout <<"| *Antes de o jogo iniciar, escolha entre par ou impar  |\n";
					cout <<"|                                                       |\n";
					cout <<"| *Ao iniciar o jogo, selecione um numero entre 0 e 10  |\n";
					cout <<"|                                                       |\n";
					cout <<"| *O computador tambem selecionara um numero de 0 a 10  |\n";
					cout <<"|                                                       |\n";
					cout <<"| *Sera feita a soma entre seu numero e o do computador |\n";
					cout <<"|                                                       |\n";
					cout <<"| *Assim sabera se venceu ou perdeu                     |\n";
					cout <<"---------------------------------------------------------\n";

					utils.pause();
					return main();

				}break;

				case 4:
				{

					//Encerrar programa;
					cout <<"----------------------\n";
					cout <<"| !!!Volte Sempre!!! |\n";
					cout <<"----------------------\n";

					utils.pause();

					return 0;

				}break;

				default:
				{

					cout <<"| Escolha um valor de 1 a 4! |";

					utils.pause();

				}break;

			}

		}
		else
		{

			cout <<"| Nao sao permitidos caracteres, ou, mais de 3 digitos! |";

			utils.pause();

		}

	}

	int exitLoop = 1;

	while(exitLoop == 1)
	{

		string userChoice;

		cout <<"---------------------\n";
		cout <<"| Deseja Continuar? |\n";
		cout <<"|                   |\n";
		cout <<"| [0] Nao           |\n";
		cout <<"| [1] Sim           |\n";
		cout <<"|                   |\n";
		cout <<"---------------------\n\n";

		cout <<"> Digite sua escolha: ";
		cin >>userChoice;

		utils.clrscr();

		if(utils.isNumber(userChoice) == 1 && utils.inputLength(userChoice))
		{

			switch(utils.stringToInt(userChoice))
			{

				case 0:
				{

					//Encerrar programa;
					cout <<"----------------------\n";
					cout <<"| !!!Volte Sempre!!! |\n";
					cout <<"----------------------\n";

					utils.pause();

					return 0;

				}break;

				case 1:
				{

					//Retornar ao comeco do programa;
					return main();

				}break;

			}

		}
		else
		{

			cout <<"| Nao sao permitidos caracteres, ou, mais de 3 digitos! |";

			utils.pause();

		}

	}

}
