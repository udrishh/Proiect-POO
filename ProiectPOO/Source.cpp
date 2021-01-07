#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "clase.h"
using namespace std;

//Un tabel are una sau mai multe atribute (campuri)
//Un atribut are una sau mai multe inregistrari (valori)

//INSERT INTO studenti VALUES (Bogdan, 20, 6), (Ovidiu, 21, 7.5) 
//create table studenti ((nume, text, 255, necunoscut), (varsta, integer, 20, 18), (media, float, 10, 2.5))
//update studenti set nume = bogdan where varsta = 21

int main()
{
	//citeste tabelele din fisier
	char auxText[256]="";
	int auxInteger=0;
	float auxFloat=0;
	Tabela tempt;
	Atribut* tempa;
	Inregistrare* tempi;
	ifstream g("tabele.txt",ios::ate);
	//momentan nu merge
	if (g.peek() != ifstream::traits_type::eof())
	{
		while (!g.eof())
		{
			g >> tempt;
			tempa = new Atribut[tempt.getNrAtribute()];
			
			for (int i = 0; i < tempt.getNrAtribute(); i++)
			{
				g >> tempa[i];
				int nrInregistrari = 0;
				g >> nrInregistrari;
				tempi = new Inregistrare[nrInregistrari];
				for (int j = 0; j < nrInregistrari; j++)
				{
					if(strcmp(tempa[i].getTipAtribut(),"TEXT")==0)
					{
						g >> auxText;
						tempi[i].setContinutText(auxText);
					}
					else if (strcmp(tempa[i].getTipAtribut(), "INTEGER") == 0)
					{
						g >> auxInteger;
						tempi[i].setContinutInteger(auxInteger);
					}
					else if (strcmp(tempa[i].getTipAtribut(), "FLOAT") == 0)
					{
						g >> auxFloat;
						tempi[i].setContinutFloat(auxFloat);
					}
				}
				//tempa[i].setInregistrari(tempi, nrInregistrari);
				delete[] tempi;
			}
			tempt.setAtribute(tempa, tempt.getNrAtribute());
			delete[] tempa;
			cout << tempt;
		}
	}
	g.close();
	cout << "Introduceti comanda SQL dorita sau 0 pentru a iesi" << endl;
	cout << "> ";
	string comanda;
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
}