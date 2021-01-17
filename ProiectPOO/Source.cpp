#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "clase.h"
using namespace std;

//Un tabel are una sau mai multe atribute (campuri)
//Un atribut are una sau mai multe inregistrari (valori)

//INSERT INTO studenti VALUES (Bogdan, 20, 6), (Ovidiu, 21, 7.5), (Delia, 22, 8.1), (Iulia, 23, 9) 
//create table studenti ((nume, text, 255, necunoscut), (varsta, integer, 20, 18), (media, float, 10, 2.5))
//update studenti set nume = bogdan where varsta = 21
//select all from studenti where nume = bogdan

int main(int argc, char* argv[])
{
	string comanda;
	char auxText[256]="";
	int auxInteger=0;
	float auxFloat=0;
	string s;
	Tabela tempt;
	Atribut* tempa;
	int nrAtribute;
	int nrInregistrari;
	ifstream g("tabele.txt");
	if (g.peek() != ifstream::traits_type::eof())
	{
		while (!g.eof())
		{
			g >> tempt;
			if (strlen(tempt.getNumeTabela()) <= 1)
			{
				continue;
			}
			nrAtribute = tempt.getNrAtribute();
			tempa = new Atribut[nrAtribute];
			for (int i = 0; i < nrAtribute; i++)
			{
				g >> tempa[i];
				string tipAtribut = tempa[i].getTipAtribut();

				nrInregistrari = tempa[i].getNrInregistrari();
				vector<Inregistrare> tempi;
				tempi.clear();
				Inregistrare tempIng;
				for (int j = 0; j < nrInregistrari; j++)
				{
					if (tipAtribut == "TEXT")
					{
						string text;
						g >> text;
						tempIng.setContinutText(text.c_str());
					}
					else if (tipAtribut == "INTEGER")
					{
						int integer;
						g >> integer;
						tempIng.setContinutInteger(integer);
					}
					else if (tipAtribut == "FLOAT")
					{
						float valFloat;
						g >> valFloat;
						
						tempIng.setContinutFloat(valFloat);
					}
					tempi.push_back(tempIng);
				}
				tempa[i].setInregistrari(tempi, nrInregistrari);
				tempi.clear();
			}
			tempt.setAtribute(tempa, nrAtribute);
			tabele.push_back(tempt);
			nrTabele++;
			//cout << tempt << endl;
		}
	}
	g.close();
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			cout << "Se executa comenzile din fisierul " << argv[i] << endl;
			ifstream g(argv[i]);
			if (g.peek() != ifstream::traits_type::eof())
			{
				while (!g.eof())
				{
					getline(g, comanda);
					for (int i = 0; i < comanda.length(); i++)
					{
						if (islower(comanda[i]))
						{
							comanda[i] = toupper(comanda[i]);
						}
					}
					try
					{
						Input i(comanda);
						i.findKeyWord(comanda);
						ofstream f("tabele.txt", ios::trunc);
						for (int i = 0; i < nrTabele; i++)
						{
							f << tabele[i];
						}
						f.close();
					}
					catch (exception e)
					{
						cout << endl << e.what() << endl;
					}
					catch (...)
					{
						cout << "A avut loc o eroare!";
					}
				}
			}
			g.close();
		}
		cout << endl << "Toate comenzile din fisiere au fost parcurse!" << endl;
	}
	cout << "Introduceti comanda SQL dorita sau 0 pentru a iesi" << endl;
	cout << "> ";
	//prelucreaza comanda
	getline(cin, comanda);
	while (comanda[0] != '0')
	{
		for (int i = 0; i < comanda.length(); i++)
		{
			if (islower(comanda[i]))
			{
				comanda[i] = toupper(comanda[i]);
			}
		}
		try 
		{
			Input i(comanda);
			i.findKeyWord(comanda);
			ofstream f("tabele.txt", ios::trunc);
			for (int i = 0; i < nrTabele; i++)
			{
				f << tabele[i];
			}
			f.close();
		}
		catch (exception e)
		{
			cout <<endl<< e.what()<<endl;
		}
		catch (...)
		{
			cout << "A avut loc o eroare!";
		}
		cout << endl;
		cout << "Introduceti comanda SQL dorita sau 0 pentru a iesi" << endl;
		cout << "> ";
		getline(cin, comanda);
	}
	//serializarea tabelelor
	char* filename=nullptr;
	for (int i = 0; i < nrTabele; i++)
	{
		filename = new char[strlen(tabele[i].getNumeTabela()) + 1];
		strcpy_s(filename, strlen(tabele[i].getNumeTabela()) + 1, tabele[i].getNumeTabela());
		strcat(filename,".bin");
		tabele[i].serializare(filename);
	}
	cout <<endl<<endl<< "Apasa orice tasta pentru a inchide!" << endl;
}