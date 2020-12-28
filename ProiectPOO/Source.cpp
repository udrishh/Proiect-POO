#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "clase.h"
using namespace std;

//Un tabel are una sau mai multe atribute (campuri)
//Un atribut are una sau mai multe inregistrari (valori)


int main()
{
	//citeste tabelele din fisier
	Tabela tempt;
	Atribut* tempa;
	ifstream g("tabele.txt");
	if (g.peek() != ifstream::traits_type::eof())
	{
		while (!g.eof())
		{
			g >> tempt;
			tempa = new Atribut[tempt.getNrAtribute()];
			for (int i = 0; i < tempt.getNrAtribute(); i++)
			{
				g >> tempa[i];
			}
			tempt.setAtribute(tempa, tempt.getNrAtribute());
			delete[] tempa;
			//cout << tempt;
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