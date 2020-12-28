#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;


class Inregistrare
{
private:
	int continutInteger;
	float continutFloat;
	char* continutText;
public:
	Inregistrare()
	{
		continutFloat = 0;
		continutInteger = 0;
		continutText = nullptr;
	}
	Inregistrare(float continutFloat) : Inregistrare()
	{
		this->continutFloat = continutFloat;
	}
	Inregistrare(int continutInteger) : Inregistrare()
	{
		this->continutInteger = continutInteger;
	}
	Inregistrare(const char* continutText) : Inregistrare()
	{
		this->continutText = new char[strlen(continutText) + 1];
		strcpy_s(this->continutText, strlen(continutText) + 1, continutText);
	}
	~Inregistrare()
	{
		if (continutText != nullptr)
		{
			delete continutText;
		}
	}
	Inregistrare(const Inregistrare& i)
	{
		this->continutFloat = i.continutFloat;
		this->continutInteger = i.continutInteger;
		if (i.continutText != nullptr)
		{
			this->continutText = new char[strlen(i.continutText) + 1];
			strcpy_s(this->continutText, strlen(i.continutText) + 1, i.continutText);
		}
		else
		{
			this->continutText = nullptr;
		}
	}
	Inregistrare& operator=(const Inregistrare& i)
	{
		if (continutText != nullptr)
		{
			delete continutText;
		}
		this->continutFloat = i.continutFloat;
		this->continutInteger = i.continutInteger;
		if (i.continutText != nullptr)
		{
			this->continutText = new char[strlen(i.continutText) + 1];
			strcpy_s(this->continutText, strlen(i.continutText) + 1, i.continutText);
		}
		else
		{
			this->continutText = nullptr;
		}
		return *this;
	}
	//friend class Atribut;
};

class Atribut
{
private:
	char* numeAtribut;
	char* tipAtribut; //text integer float
	int dimensiuneAtribut;
	float valoareImplicitaNumeric;
	char* valoareImplicitaText;
	int nrInregistrari;
	Inregistrare* inregistrari;

public:
	Atribut()
	{
		numeAtribut = nullptr;
		tipAtribut = nullptr;
		dimensiuneAtribut = 0;
		valoareImplicitaNumeric = 0;
		valoareImplicitaText = nullptr;
		nrInregistrari = 0;
		inregistrari = nullptr;
	}
	~Atribut()
	{
		if (numeAtribut != nullptr)
		{
			delete[] numeAtribut;
		}
		if (tipAtribut != nullptr)
		{
			delete[] tipAtribut;
		}
		if (valoareImplicitaText != nullptr)
		{
			delete[] valoareImplicitaText;
		}
		if (inregistrari != nullptr)
		{
			delete[] inregistrari;
		}
	}
	Atribut(const Atribut& a)
	{
		if (a.numeAtribut != nullptr)
		{
			this->numeAtribut = new char[strlen(a.numeAtribut) + 1];
			strcpy_s(this->numeAtribut, strlen(a.numeAtribut) + 1, a.numeAtribut);
		}
		else
		{
			this->numeAtribut = nullptr;
		}
		if (a.tipAtribut != nullptr)
		{
			this->tipAtribut = new char[strlen(a.tipAtribut) + 1];
			strcpy_s(this->tipAtribut, strlen(a.tipAtribut) + 1, a.tipAtribut);
		}
		else
		{
			this->tipAtribut = nullptr;
		}
		if (a.dimensiuneAtribut > 0)
		{
			this->dimensiuneAtribut = a.dimensiuneAtribut;
		}
		else
		{
			this->dimensiuneAtribut = 0;
		}
		this->valoareImplicitaNumeric = a.valoareImplicitaNumeric;
		if (a.valoareImplicitaText != nullptr)
		{
			this->valoareImplicitaText = new char[strlen(a.valoareImplicitaText) + 1];
			strcpy_s(this->valoareImplicitaText, strlen(a.valoareImplicitaText) + 1, a.valoareImplicitaText);
		}
		else
		{
			this->valoareImplicitaText = nullptr;
		}
		if (a.nrInregistrari > 0 && a.inregistrari != nullptr)
		{
			this->nrInregistrari = a.nrInregistrari;
			this->inregistrari = new Inregistrare[a.nrInregistrari];
			for (int i = 0; i < a.nrInregistrari; i++)
			{
				this->inregistrari[i] = a.inregistrari[i];
			}
		}
		else
		{
			this->nrInregistrari = 0;
			this->inregistrari = nullptr;
		}
	}
	Atribut& operator=(const Atribut& a)
	{
		if (numeAtribut != nullptr)
		{
			delete[] numeAtribut;
		}
		if (tipAtribut != nullptr)
		{
			delete[] tipAtribut;
		}
		if (valoareImplicitaText != nullptr)
		{
			delete[] valoareImplicitaText;
		}
		if (inregistrari != nullptr)
		{
			delete[] inregistrari;
		}
		if (a.numeAtribut != nullptr)
		{
			this->numeAtribut = new char[strlen(a.numeAtribut) + 1];
			strcpy_s(this->numeAtribut, strlen(a.numeAtribut) + 1, a.numeAtribut);
		}
		else
		{
			this->numeAtribut = nullptr;
		}
		if (a.tipAtribut != nullptr)
		{
			this->tipAtribut = new char[strlen(a.tipAtribut) + 1];
			strcpy_s(this->tipAtribut, strlen(a.tipAtribut) + 1, a.tipAtribut);
		}
		else
		{
			this->tipAtribut = nullptr;
		}
		if (a.dimensiuneAtribut > 0)
		{
			this->dimensiuneAtribut = a.dimensiuneAtribut;
		}
		else
		{
			this->dimensiuneAtribut = 0;
		}
		this->valoareImplicitaNumeric = a.valoareImplicitaNumeric;
		if (a.valoareImplicitaText != nullptr)
		{
			this->valoareImplicitaText = new char[strlen(a.valoareImplicitaText) + 1];
			strcpy_s(this->valoareImplicitaText, strlen(a.valoareImplicitaText) + 1, a.valoareImplicitaText);
		}
		else
		{
			this->valoareImplicitaText = nullptr;
		}
		if (a.nrInregistrari > 0 && a.inregistrari != nullptr)
		{
			this->nrInregistrari = a.nrInregistrari;
			this->inregistrari = new Inregistrare[a.nrInregistrari];
			for (int i = 0; i < a.nrInregistrari; i++)
			{
				this->inregistrari[i] = a.inregistrari[i];
			}
		}
		else
		{
			this->nrInregistrari = 0;
			this->inregistrari = nullptr;
		}
		return *this;
	}
	void setNumeAtribut(const char* numeAtribut)
	{
		if (numeAtribut != nullptr)
		{
			if (this->numeAtribut != nullptr)
			{
				delete[] this->numeAtribut;
			}
			this->numeAtribut = new char[strlen(numeAtribut) + 1];
			strcpy_s(this->numeAtribut, strlen(numeAtribut) + 1, numeAtribut);
		}
		else
		{
			this->numeAtribut = nullptr;
		}
	}
	char* getNumeAtribut()
	{
		return numeAtribut;
	}
	void setTipAtribut(const char* tipAtribut)
	{
		if (tipAtribut != nullptr)
		{
			if (this->tipAtribut != nullptr)
			{
				delete[] this->tipAtribut;
			}
			this->tipAtribut = new char[strlen(tipAtribut) + 1];
			strcpy_s(this->tipAtribut, strlen(tipAtribut) + 1, tipAtribut);
		}
		else
		{
			this->tipAtribut = nullptr;
		}
	}
	char* getTipAtribut()
	{
		return tipAtribut;
	}
	void setDimensiuneAtribut(int dimensiuneAtribut)
	{
		if (dimensiuneAtribut > 0)
		{
			this->dimensiuneAtribut = dimensiuneAtribut;
		}
		else
		{
			this->dimensiuneAtribut = 0;
		}
	}
	int getDimensiuneAtribut()
	{
		return dimensiuneAtribut;
	}
	void setValoareImplicitaNumeric(float valoareImplicitaNumeric)
	{
		this->valoareImplicitaNumeric = valoareImplicitaNumeric;
	}
	float getValoareImplicitaNumeric()
	{
		return valoareImplicitaNumeric;
	}
	void setValoareImplicitaText(const char* valoareImplicitaText)
	{
		if (valoareImplicitaText != nullptr)
		{
			if (this->valoareImplicitaText != nullptr)
			{
				delete[] this->valoareImplicitaText;
			}
			this->valoareImplicitaText = new char[strlen(valoareImplicitaText) + 1];
			strcpy_s(this->valoareImplicitaText, strlen(valoareImplicitaText) + 1, valoareImplicitaText);
		}
		else
		{
			this->valoareImplicitaText = nullptr;
		}
	}
	char* getValoareImplicitaText()
	{
		return valoareImplicitaText;
	}
	void setInregistrari(Inregistrare* inregistrari, int nrInregistrari)
	{
		if (inregistrari != nullptr && nrInregistrari > 0)
		{
			if (this->inregistrari != nullptr)
			{
				delete[] this->inregistrari;
			}
			this->nrInregistrari = nrInregistrari;
			this->inregistrari = new Inregistrare[nrInregistrari];
			for (int i = 0; i < nrInregistrari; i++)
			{
				this->inregistrari[i] = inregistrari[i];
			}
		}
		else
		{
			this->nrInregistrari = 0;
			this->inregistrari = nullptr;
		}
	}

	//friend class Tabela;
	friend ofstream& operator<<(ofstream&, Atribut);
	friend ostream& operator<<(ostream&, Atribut);
	friend ifstream& operator>>(ifstream&, Atribut&);
	friend istream& operator>>(istream&, Atribut&);
};

ofstream& operator<<(ofstream& out, Atribut a)
{
	out << a.numeAtribut << " " << a.tipAtribut << " " << a.dimensiuneAtribut << " ";
	if (strcmp(a.tipAtribut, "TEXT") == 0)
	{
		out << a.valoareImplicitaText;
	}
	else
	{
		out << a.valoareImplicitaNumeric;
	}
	return out;
}
ostream& operator<<(ostream& out, Atribut a)
{
	out << a.numeAtribut << " " << a.tipAtribut << " " << a.dimensiuneAtribut << " ";
	if (strcmp(a.tipAtribut, "TEXT") == 0)
	{
		out << a.valoareImplicitaText;
	}
	else
	{
		out << a.valoareImplicitaNumeric;
	}
	return out;
}
ifstream& operator>>(ifstream& in, Atribut& a)
{
	char buffer[100];
	in >> buffer;
	a.numeAtribut = new char[strlen(buffer) + 1];
	strcpy_s(a.numeAtribut, strlen(buffer) + 1, buffer);
	in >> buffer;
	a.tipAtribut = new char[strlen(buffer) + 1];
	strcpy_s(a.tipAtribut, strlen(buffer) + 1, buffer);
	in >> a.dimensiuneAtribut;
	if (strcmp(a.tipAtribut, "TEXT") == 0)
	{
		in >> buffer;
		a.valoareImplicitaText = new char[strlen(buffer) + 1];
		strcpy_s(a.valoareImplicitaText, strlen(buffer) + 1, buffer);
	}
	else
	{
		in >> a.valoareImplicitaNumeric;
	}
	return in;
}
istream& operator>>(istream& in, Atribut& a)
{
	char buffer[100];
	in >> buffer;
	a.numeAtribut = new char[strlen(buffer) + 1];
	strcpy_s(a.numeAtribut, strlen(buffer) + 1, buffer);
	in >> buffer;
	a.tipAtribut = new char[strlen(buffer) + 1];
	strcpy_s(a.tipAtribut, strlen(buffer) + 1, buffer);
	in >> a.dimensiuneAtribut;
	if (strcmp(a.tipAtribut, "TEXT") == 0)
	{
		in >> buffer;
		a.valoareImplicitaText = new char[strlen(buffer) + 1];
		strcpy_s(a.valoareImplicitaText, strlen(buffer) + 1, buffer);
	}
	else
	{
		in >> a.valoareImplicitaNumeric;
	}
	return in;
}

class Tabela
{
private:
	char* numeTabela;
	int nrAtribute;
	Atribut* atribute;

public:
	Tabela() {
		numeTabela = nullptr;
		nrAtribute = 0;
		atribute = nullptr;
	}
	~Tabela() {
		if (atribute != nullptr)
		{
			delete[] atribute;
		}
		if (numeTabela != nullptr)
		{
			delete[] numeTabela;
		}
	}
	Tabela(const Tabela& t)
	{
		if (t.numeTabela != nullptr)
		{
			this->numeTabela = new char[strlen(t.numeTabela) + 1];
			strcpy_s(this->numeTabela, strlen(t.numeTabela) + 1, t.numeTabela);
		}
		else
		{
			this->numeTabela = nullptr;
		}
		if (t.nrAtribute > 0 && t.atribute != nullptr)
		{
			this->nrAtribute = t.nrAtribute;
			this->atribute = new Atribut[t.nrAtribute];
			for (int i = 0; i < nrAtribute; i++)
			{
				this->atribute[i] = t.atribute[i];
			}
		}
		else
		{
			this->nrAtribute = 0;
			this->atribute = nullptr;
		}
	}
	Tabela& operator=(const Tabela& t)
	{
		if (atribute != nullptr)
		{
			delete[] atribute;
		}
		if (numeTabela != nullptr)
		{
			delete[] numeTabela;
		}
		if (t.numeTabela != nullptr)
		{
			this->numeTabela = new char[strlen(t.numeTabela) + 1];
			strcpy_s(this->numeTabela, strlen(t.numeTabela) + 1, t.numeTabela);
		}
		else
		{
			this->numeTabela = nullptr;
		}
		if (t.nrAtribute > 0 && t.atribute != nullptr)
		{
			this->nrAtribute = t.nrAtribute;
			this->atribute = new Atribut[t.nrAtribute];
			for (int i = 0; i < nrAtribute; i++)
			{
				this->atribute[i] = t.atribute[i];
			}
		}
		else
		{
			this->nrAtribute = 0;
			this->atribute = nullptr;
		}
		return *this;
	}
	void setNumeTabela(const char* numeTabela) {
		if (numeTabela != nullptr)
		{
			if (this->numeTabela != nullptr)
			{
				delete[] this->numeTabela;
			}
			this->numeTabela = new char[strlen(numeTabela) + 1];
			strcpy_s(this->numeTabela, strlen(numeTabela) + 1, numeTabela);
		}
	}
	char* getNumeTabela()
	{
		if (numeTabela != nullptr)
		{
			return numeTabela;
		}
		else
		{
			return nullptr;
		}
	}
	void setAtribute(Atribut* atribute, int nrAtribute)
	{
		if (atribute != nullptr && nrAtribute > 0)
		{
			if (this->atribute != nullptr)
			{
				delete[] this->atribute;
			}
			this->atribute = new Atribut[nrAtribute];
			this->nrAtribute = nrAtribute;
			for (int i = 0; i < nrAtribute; i++)
			{
				this->atribute[i] = atribute[i];
			}
		}
		else
		{
			this->atribute = nullptr;
			this->nrAtribute = 0;
		}
	}
	Atribut* getAtribute()
	{
		return atribute;
	}
	int getNrAtribute()
	{
		return nrAtribute;
	}

	//friend class Atribut;
	friend ofstream& operator<<(ofstream&, Tabela);
	friend ostream& operator<<(ostream&, Tabela);
	friend ifstream& operator>>(ifstream&, Tabela&);
	friend istream& operator>>(istream&, Tabela&);
};

ofstream& operator<<(ofstream& out, Tabela t)
{
	out << t.numeTabela << " " << t.nrAtribute;
	if (t.nrAtribute > 0)
	{
		for (int i = 0; i < t.nrAtribute; i++)
		{
			out << " " << t.atribute[i];
		}
	}
	return out;
}
ostream& operator<<(ostream& out, Tabela t)
{
	out << t.numeTabela << " " << t.nrAtribute;
	if (t.nrAtribute > 0)
	{
		for (int i = 0; i < t.nrAtribute; i++)
		{
			out << " " << t.atribute[i];
		}
	}
	return out;
}
ifstream& operator>>(ifstream& in, Tabela& t)
{
	char buffer[255];
	in >> buffer;
	t.numeTabela = new char[strlen(buffer) + 1];
	strcpy_s(t.numeTabela, strlen(buffer) + 1, buffer);
	in >> t.nrAtribute;
	/*if (t.nrAtribute > 0)
	{
		for (int i = 0; i < t.nrAtribute; i++)
		{
			in >> t.atribute[i];
		}
	}*/
	return in;
}
istream& operator>>(istream& in, Tabela& t)
{
	char buffer[255];
	in >> buffer;
	t.numeTabela = new char[strlen(buffer) + 1];
	strcpy_s(t.numeTabela, strlen(buffer) + 1, buffer);
	in >> t.nrAtribute;
	/*if (t.nrAtribute > 0)
	{
		for (int i = 0; i < t.nrAtribute; i++)
		{
			in >> t.atribute[i];
		}
	}*/
	return in;
}

vector<Tabela> tabele;
int nrTabele = 0;

void adaugaTabela(Tabela& t)
{
	tabele.push_back(t);
	nrTabele++;
}

class Comanda
{
private:

public:

	//create table
	void createTable(string comanda, Tabela& t1)
	{
		int contorCuvinte;
		int parantezaDreapta = 0;
		int parantezaStanga = 0;
		string str = comanda;
		char* cuvant;
		char* copie;
		string aux;
		copie = new char[comanda.length() + 1];
		strcpy(copie, comanda.c_str());
		cuvant = strtok(copie, " ");
		cuvant = strtok(NULL, " ");
		{
			cuvant = strtok(NULL, " ");
			//verificare daca tabela exista deja
			for (int i = 0; i < nrTabele; i++)
				if (strcmp(tabele[i].getNumeTabela(), cuvant) == 0)
				{
					throw exception("Tabela exista deja.");
				}
			//setare nume tabela
			t1.setNumeTabela(cuvant);
			//verificare numar paranteze
			for (unsigned i = 0; i < str.size(); i++)
			{
				if (str[i] == '(')
				{
					parantezaStanga++;
				}
				if (str[i] == ')')
				{
					parantezaDreapta++;
				}
			}
			if (parantezaDreapta != parantezaStanga)
			{
				if (parantezaDreapta > parantezaStanga)
				{
					throw exception("Paranteza ) lipsa!");
				}
				else
				{
					throw exception("Paranteza ( lipsa!");
				}
			}
			//determinare numar de parametrii
			cuvant = strtok(NULL, ", ");
			contorCuvinte = 0;
			while (cuvant)
			{
				contorCuvinte++;
				cuvant = strtok(NULL, ", ");
			}
			if (contorCuvinte % 4 != 0)
			{
				throw exception("Numar invalid de parametri!");
			}
			if (contorCuvinte == 0)
			{
				throw exception("Numar invalid de parametri!");
			}
			//scapam de primele 3 cuvinte deja citite
			delete[] copie;
			copie = new char[comanda.length() + 1];
			strcpy(copie, comanda.c_str());
			cuvant = strtok(copie, " ");
			cuvant = strtok(NULL, " ");
			cuvant = strtok(NULL, " ");
			//determinare numar atribute
			int nrAtribute = contorCuvinte / 4;
			Atribut* atribute = new Atribut[nrAtribute];
			//extragem atributele
			for (int i = 0; i < nrAtribute; i++)
			{
				//nume atribut
				cuvant = strtok(NULL, ", ");
				//scapam de eventualele (( sau (
				if (cuvant[0] == '(')
				{
					if (cuvant[1] == '(')
					{
						memmove(cuvant, cuvant + 2, strlen(cuvant + 2) + 1);
					}
					else
					{
						memmove(cuvant, cuvant + 1, strlen(cuvant + 1) + 1);
					}
				}
				atribute[i].setNumeAtribut(cuvant);
				//cout << "Nume atribut: " << atribute[i].getNumeAtribut() << endl;
				//tip atribut
				cuvant = strtok(NULL, ", ");
				atribute[i].setTipAtribut(cuvant);
				//cout << "Tip atribut: " << atribute[i].getTipAtribut() << endl;
				//dimensiune atribut
				cuvant = strtok(NULL, ", ");
				//transformam dimensiunea din char in int
				int dimensiune = 0;
				for (unsigned i = 0; i < strlen(cuvant); i++)
				{
					dimensiune = dimensiune * 10 + int(cuvant[i]) - 48;
				}
				atribute[i].setDimensiuneAtribut(dimensiune);
				//cout << "Dimensiune atribut: " << atribute[i].getDimensiuneAtribut() << endl;
				//valoare implicita
				cuvant = strtok(NULL, ", ");
				//scapam de eventualele )) sau )
				char auxiliar[255] = "";
				if (cuvant[strlen(cuvant) - 1] == ')')
				{
					if (cuvant[strlen(cuvant) - 2] == ')')
					{
						for (unsigned i = 0; i < strlen(cuvant) - 2; i++)
						{
							auxiliar[i] = cuvant[i];
						}
					}
					else
					{
						for (unsigned i = 0; i < strlen(cuvant) - 1; i++)
						{
							auxiliar[i] = cuvant[i];
						}
					}
				}
				strcpy_s(cuvant, strlen(auxiliar) + 1, auxiliar);
				//setam valoare implicita in functie de tipul atributului
				if (strcmp(atribute[i].getTipAtribut(), "TEXT") == 0)
				{
					atribute[i].setValoareImplicitaText(cuvant);
					//cout << "Valoare implicita atribut: " << atribute[i].getValoareImplicitaText() << endl;
				}
				else if (strcmp(atribute[i].getTipAtribut(), "INTEGER") == 0) //transformam valoarea impliicta din text in int sau char
				{
					int valInt = 0;
					for (unsigned i = 0; i < strlen(cuvant); i++)
					{
						valInt = valInt * 10 + int(cuvant[i]) - 48;
					}
					atribute[i].setValoareImplicitaNumeric(float(valInt));
					//cout << "Valoare implicita atribut: " << atribute[i].getValoareImplicitaNumeric() << endl;
				}
				else if (strcmp(atribute[i].getTipAtribut(), "FLOAT") == 0)
				{
					float valFloat = 0;
					float zecimale = 1;
					for (unsigned i = 0; i < strlen(cuvant); i++)
					{
						if (cuvant[i] != '.')
						{
							valFloat = valFloat * 10 + int(cuvant[i]) - 48;
						}
						else if (cuvant[i] == '.')
						{
							zecimale = zecimale * 10;
						}
					}
					valFloat = valFloat / zecimale;
					atribute[i].setValoareImplicitaNumeric(valFloat);
					//cout << "Valoare implicita atribut: " << atribute[i].getValoareImplicitaNumeric() << endl;
				}
			}
			t1.setAtribute(atribute, nrAtribute);
			cout << endl << "Tabela " << t1.getNumeTabela() << " a fost creata cu succes!" << endl;
			//adaugam tabela la vectorul de tabele
			adaugaTabela(t1);
			//adaugam tabela in fisier
			ofstream f("tabele.txt", ios::app);
			f << t1 << endl;
			f.close();
		}
	}
	//display table studenti
	void displayTable(char* numeTabela)
	{
		bool gasit = 0;
		for (int i = 0; i < nrTabele; i++)
		{
			if (strcmp(tabele[i].getNumeTabela(), numeTabela) == 0)
			{
				cout <<endl<< tabele[i]<<endl;
				gasit = 1;
			}
		}
		if (gasit == 0)
		{
			throw exception("Tabela nu exista!");
		}
	}
	//drop table studenti
	void dropTable(char* numeTabela)
	{
		if (nrTabele > 0)
		{
			bool gasit = 0;
			for (int i = 0; i < nrTabele && gasit == 0; i++)
			{
				if (strcmp(tabele[i].getNumeTabela(), numeTabela) == 0)
				{
					tabele.erase(tabele.begin() + i);
					gasit = 1;
					nrTabele--;
					cout <<endl<< "Tabela a fost stearsa!"<<endl;
					//stergem tabela din fisier
					ofstream f("tabele.txt", ios::ate);
					for (int i = 0; i < nrTabele; i++)
					{
						f << tabele[i] << endl;
					}
					f.close();
				}
			}
			if (gasit == 0)
			{
				throw exception("Tabela nu exista!");
			}
		}
		else
		{
			throw exception("Tabela nu exista!");
		}
	}
};

class Input
{
private:
	string comanda;

public:
	Input()
	{
		comanda = "";
	}
	Input(string comanda)
	{
		if (comanda.length() > 0)
		{
			this->comanda = comanda;
		}
		else
		{
			throw exception("Comanda necunosuta!");
		}
	}
	Input(const Input& i)
	{
		this->comanda = i.comanda;
	}
	void findKeyWord(string comanda)
	{
		//create table studenti ((nume, text, 255, necunoscut), (varsta, integer, 20, 18), (media, float, 10, 2.5))
		char* cuvant;
		char* copie;
		copie = new char[comanda.length() + 1];
		strcpy(copie, comanda.c_str());
		cuvant = strtok(copie, " ");
		//CREATE TABLE
		if (strcmp(cuvant, "CREATE") == 0)
		{
			cuvant = strtok(NULL, " ");
			if (strcmp(cuvant, "TABLE") == 0)
			{
				Tabela t;
				Comanda CT;
				CT.createTable(comanda, t);
			}
			else
			{
				throw exception("Cuvant cheie incorect!");
			}
		}
		//DISPLAY TABLE
		else if (strcmp(cuvant, "DISPLAY") == 0)
		{
			cuvant = strtok(NULL, " ");
			if (strcmp(cuvant, "TABLE") == 0)
			{
				cuvant = strtok(NULL, " ");
				//cuvant=numeTabela
				Comanda DT;
				DT.displayTable(cuvant);
			}
			else
			{
				throw exception("Cuvant cheie incorect!");
			}
		}
		//DROP TABLE
		else if (strcmp(cuvant, "DROP") == 0)
		{
			cuvant = strtok(NULL, " ");
			if (strcmp(cuvant, "TABLE") == 0)
			{
				cuvant = strtok(NULL, " ");
				//cuvant=numeTabela
				Comanda DrT;
				DrT.dropTable(cuvant);
			}
			else
			{
				throw exception("Cuvant cheie incorect!");
			}
		}
		//COMANDA NECUNOSCUTA
		else
		{
			throw exception("Comanda necunoscuta!");
		}
		
	}

};