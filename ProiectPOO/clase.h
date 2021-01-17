#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
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
	void serializare(const char* filename)
	{
		ofstream f("filename", ios::out | ios::binary | ios::ate | ios::app);
		if (continutText != nullptr)
		{
			int length = strlen(continutText);
			f.write((char*)&length, sizeof(length));
			f.write(continutText, length + 1);
		}
		if (continutInteger != 0)
		{
			f.write((char*)&continutInteger, sizeof(continutInteger));
		}
		if (continutFloat != 0)
		{
			f.write((char*)&continutFloat, sizeof(continutFloat));
		}
		
		f.close();
	}
	void deserializare()
	{
		ifstream f("fisier_binar.bin", ios::binary);
		if (continutInteger != 0)
		{
			f.read((char*)&continutInteger, sizeof(continutInteger));
		}
		if (continutFloat != 0)
		{
			f.read((char*)&continutFloat, sizeof(continutFloat));
		}
		if (continutText != nullptr)
		{
			int length = 0;
			f.read((char*)&length, sizeof(length));
			delete[] continutText;
			continutText = new char[length + 1];
			f.read(continutText, length + 1);
		}
		f.close();
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
	int getContinutInteger()
	{
		return continutInteger;
	}
	float getContinutFloat()
	{
		return continutFloat;
	}
	char* getContinutText()
	{
		return continutText;
	}
	void setContinutText(const char* continutText)
	{
		if (continutText != nullptr)
		{
			if (this->continutText != nullptr)
			{
				delete[] this->continutText;
			}
			this->continutText = new char[strlen(continutText) + 1];
			strcpy_s(this->continutText, strlen(continutText) + 1, continutText);
		}
		else
		{
			this->continutText = nullptr;
		}
	}
	void setContinutInteger(int continutInteger)
	{
		if (continutInteger > 0)
		{
			this->continutInteger = continutInteger;
		}
		else
		{
			this->continutInteger = 0;
		}
	}
	void setContinutFloat(float continutFloat)
	{
		if (continutFloat > 0)
		{
			this->continutFloat = continutFloat;
		}
		else
		{
			this->continutFloat = 0;
		}
	}

	void updateInregistrare(const char* updateWith, const char* tipAtribut)
	{
		if (strcmp(tipAtribut, "TEXT") == 0)
		{
			if (continutText != nullptr)
			{
				delete[] continutText;
			}
			continutText = new char[strlen(updateWith) + 1];
			strcpy_s(continutText, strlen(updateWith) + 1, updateWith);
		}
		else if (strcmp(tipAtribut, "INTEGER") == 0)
		{
			int integer = 0;
			for (unsigned i = 0; i < strlen(updateWith); i++)
			{
				integer = integer * 10 + int(updateWith[i]) - 48;
			}
			continutInteger = integer;
		}
		else if (strcmp(tipAtribut, "FLOAT") == 0)
		{
			float valFloat = 0;
			float zecimale = 1;
			for (unsigned i = 0; i < strlen(updateWith); i++)
			{
				if (updateWith[i] != '.')
				{
					valFloat = valFloat * 10 + int(updateWith[i]) - 48;
				}
				else if (updateWith[i] == '.')
				{
					zecimale = zecimale * 10;
				}
			}
			valFloat = valFloat / zecimale;
			continutFloat = valFloat;
		}
	}

	friend class Atribut;
	friend ostream& operator<<(ostream&, Inregistrare);
	friend istream& operator>>(istream&, Inregistrare&);
	friend ifstream& operator>>(ifstream&, Inregistrare&);
	
};
ostream& operator<<(ostream& out, Inregistrare i)
{
	if (i.continutInteger != 0)
	{
		out << i.continutInteger << " ";
	}
	if (i.continutFloat != 0)
	{
		out << i.continutFloat << " ";
	}
	if (i.continutText != nullptr)
	{
		out<< i.continutText<<" ";
	}
	return out;
}
istream& operator>>(istream& in, Inregistrare& i)
{
	in >> i.continutInteger;
	in >> i.continutFloat;
	char buffer[100];
	in >> buffer;
	i.continutText = new char[strlen(buffer) + 1];
	strcpy_s(i.continutText, strlen(buffer) + 1, buffer);

	return in;
}

ifstream& operator>>(ifstream& in, Inregistrare& i)
{
	in >> i.continutInteger;
	in >> i.continutFloat;
	char buffer[100];
	in >> buffer;
	i.continutText = new char[strlen(buffer) + 1];
	strcpy_s(i.continutText, strlen(buffer) + 1, buffer);

	return in;
}

class Atribut
{
private:
	char* numeAtribut;
	char* tipAtribut; //text integer float
	int dimensiuneAtribut;
	float valoareImplicitaNumeric;
	char* valoareImplicitaText;
	int nrInregistrari;
	vector<Inregistrare> inregistrari;
	//vector<Inregistrare> inregistrari;


public:
	Atribut()
	{
		numeAtribut = nullptr;
		tipAtribut = nullptr;
		dimensiuneAtribut = 0;
		valoareImplicitaNumeric = 0;
		valoareImplicitaText = nullptr;
		nrInregistrari = 0;
		
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
		
	}
	
	void serializare(const char* filename)
	{
		ofstream f(filename, ios::out | ios::binary | ios::ate | ios::app);
		int length = strlen(numeAtribut);
		f.write((char*)&length, sizeof(length));
		f.write(numeAtribut, length + 1);
		length = strlen(tipAtribut);
		f.write((char*)&length, sizeof(length));
		f.write(tipAtribut, length + 1);
		f.write((char*)&dimensiuneAtribut, sizeof(dimensiuneAtribut));
		if (valoareImplicitaNumeric != 0)
		{
			f.write((char*)&valoareImplicitaNumeric, sizeof(valoareImplicitaNumeric));
		}
		if (valoareImplicitaText != nullptr)
		{
			length = strlen(valoareImplicitaText);
			f.write((char*)&length, sizeof(length));
			f.write(valoareImplicitaText, length + 1);
		}
		
		f.write((char*)&nrInregistrari, sizeof(nrInregistrari));
		for (int i = 0; i < nrInregistrari; i++)
		{
			//f.write((char*)&inregistrari[i], sizeof(inregistrari[i]));
			inregistrari[i].serializare(filename); 
		}
		
	}
	
	void deserializare()
	{
		ifstream f("fisier_binar.bin", ios::binary);
		int length = 0;
		f.read((char*)&length, sizeof(length));
		delete[] numeAtribut;
		numeAtribut = new char[length + 1];
		f.read(numeAtribut, length + 1);

		length = 0;
		f.read((char*)&length, sizeof(length));
		delete[] tipAtribut;
		tipAtribut = new char[length + 1];
		f.read(tipAtribut, length + 1);

		f.read((char*)&dimensiuneAtribut, sizeof(dimensiuneAtribut));
		f.read((char*)&valoareImplicitaNumeric, sizeof(valoareImplicitaNumeric));

		length = 0;
		f.read((char*)&length, sizeof(length));
		delete[] valoareImplicitaText;
		valoareImplicitaText = new char[length + 1];
		f.read(valoareImplicitaText, length + 1);

		f.read((char*)&nrInregistrari, sizeof(nrInregistrari));

		for (int i = 0; i < nrInregistrari; i++)
		{
			f.read((char*)&inregistrari[i], sizeof(inregistrari[i]));
		}
		f.close();


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
		if (a.nrInregistrari > 0 )
		{
			this->nrInregistrari = a.nrInregistrari;
			for (int i = 0; i < a.nrInregistrari; i++)
				this->inregistrari.push_back(a.inregistrari[i]);
		}
		else
		{
			this->nrInregistrari = 0;
			this->inregistrari.empty();
			
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
		if (a.nrInregistrari > 0 )
		{
			this->nrInregistrari = a.nrInregistrari;
			for (int i = 0; i < a.nrInregistrari; i++)
				this->inregistrari.push_back(a.inregistrari[i]);
		}
		else
		{
			this->nrInregistrari = 0;
			this->inregistrari.empty();
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
	void setInregistrari(vector<Inregistrare> inregistrari, int nrInregistrari)
	{
		if ( nrInregistrari > 0)
		{
			
			this->nrInregistrari = nrInregistrari;
			for (int i = 0; i < nrInregistrari; i++)
				this->inregistrari.push_back(inregistrari[i]);
		}
		else
		{
			this->nrInregistrari = 0;
			this->inregistrari.empty();
		}
	}
	void setNrInregistrari(int nrInregistrari)
	{
		if (nrInregistrari > 0)
		{
			this->nrInregistrari = nrInregistrari;
		}
		else
		{
			this->nrInregistrari = 0;
		}
	}
	vector<Inregistrare> getInregistrari()
	{
		return inregistrari;
	}
	int getNrInregistrari()
	{
		return nrInregistrari;
	}
	void adaugaInregistrare(const char* cuvant)
	{
		if (strcmp(cuvant, "NULL") == 0)
		{
			
			if (strcmp(tipAtribut, "TEXT") == 0)
			{
				Inregistrare inr;
				inr.continutText = new char[strlen(valoareImplicitaText) + 1];
				strcpy_s(inr.continutText, strlen(valoareImplicitaText) + 1, valoareImplicitaText);
				inregistrari.push_back(inr.continutText);
				nrInregistrari++;
			}
			else if (strcmp(tipAtribut, "INTEGER") == 0)
			{
				Inregistrare inr;
				inr.continutInteger = valoareImplicitaNumeric;
				inregistrari.push_back(inr.continutInteger);
				nrInregistrari++;
			}
			else if (strcmp(tipAtribut, "FLOAT") == 0)
			{
				Inregistrare inr;
				inr.continutFloat = valoareImplicitaNumeric;
				inregistrari.push_back(inr.continutFloat);
				nrInregistrari++;
			}
		}
		else
		{
			if (strcmp(tipAtribut, "TEXT") == 0)
			{
				Inregistrare inr;
				inr.continutText = new char[strlen(cuvant) + 1];
				strcpy_s(inr.continutText, strlen(cuvant) + 1, cuvant);
				inregistrari.push_back(inr.continutText);
				nrInregistrari++;
			}
			else if (strcmp(tipAtribut, "INTEGER") == 0)
			{
				Inregistrare inr;
				int integer = 0;
				for (unsigned i = 0; i < strlen(cuvant); i++)
				{
					integer = integer * 10 + int(cuvant[i]) - 48;
				}
				inr.continutInteger = integer;
				inregistrari.push_back(inr.continutInteger);
				nrInregistrari++;
			}
			else if (strcmp(tipAtribut, "FLOAT") == 0)
			{
				Inregistrare inr;
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
				inr.continutFloat = valFloat;
				
				inregistrari.push_back(inr.continutFloat);
				nrInregistrari++;
			}
		}
	}

	void stergeInregistrarePozitie(int pozitie)
	{
		inregistrari.erase(inregistrari.begin() + pozitie);
		nrInregistrari--;
	}

	void updateAtribut(int pozitieI, const char* updateWith)
	{
		inregistrari[pozitieI].updateInregistrare(updateWith, tipAtribut);
	}
	//friend class Tabela;
	friend class Inregistrare;
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
	out << endl;
	out << a.nrInregistrari<<" ";
	for (int i = 0; i < a.nrInregistrari; i++)
	{
		if (strcmp(a.tipAtribut, "TEXT") == 0)
		{
			out << a.inregistrari[i].getContinutText() << " ";
		}
		else if (strcmp(a.tipAtribut, "INTEGER") == 0)
		{
			out << a.inregistrari[i].getContinutInteger() << " ";
		}
		else
		{
			out << a.inregistrari[i].getContinutFloat() << " ";
		}

	}
	out << endl;
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
	out << endl;
	out << a.nrInregistrari<<" ";
	for (int i = 0; i < a.nrInregistrari; i++)
	{
		if (strcmp(a.tipAtribut, "TEXT") == 0)
		{
			out << a.inregistrari[i].getContinutText() << " ";
		}
		else if (strcmp(a.tipAtribut, "INTEGER") == 0)
		{
			out << a.inregistrari[i].getContinutInteger() << " ";
		}
		else
		{
			out << a.inregistrari[i].getContinutFloat() << " ";
		}

	}
	out << endl;
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
	in>>a.nrInregistrari;
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
	void serializare(const char* filename)
	{
		ofstream f("filename", ios::out | ios::binary | ios::ate | ios::app);
		int length = strlen(numeTabela);
		f.write((char*)&length, sizeof(length));
		f.write(numeTabela, length + 1);
		f.write((char*)&nrAtribute, sizeof(nrAtribute));
		f.close();
		for (int i = 0; i < nrAtribute; i++)
		{
			//f.write((char*)&atribute[i], sizeof(atribute[i]));
			atribute[i].serializare(filename);
			
		}
		
	}
	void deserializare()
	{
		ifstream f("fisier_binar.bin", ios::binary);

		int length = 0;
		f.read((char*)&length, sizeof(length));
		delete[] numeTabela;
		numeTabela = new char[length + 1];
		f.read(numeTabela, length + 1);

		f.read((char*)&nrAtribute, sizeof(nrAtribute));

		delete[] atribute;
		atribute = new Atribut[nrAtribute];
		for (int i = 0; i < nrAtribute; i++)
		{
			f.read((char*)&atribute[i], sizeof(atribute[i]));
		}
		f.close();
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

	friend ofstream& operator<<(ofstream&, Tabela);
	friend ostream& operator<<(ostream&, Tabela);
	friend ifstream& operator>>(ifstream&, Tabela&);
	friend istream& operator>>(istream&, Tabela&);
};

ofstream& operator<<(ofstream& out, Tabela t)
{
	out << t.numeTabela << " " << t.nrAtribute<<endl;
	if (t.nrAtribute > 0)
	{
		for (int i = 0; i < t.nrAtribute; i++)
		{
			out << t.atribute[i];
		}
	}
	return out;
}
ostream& operator<<(ostream& out, Tabela t)
{
	out << t.numeTabela << " " << t.nrAtribute << endl;
	if (t.nrAtribute > 0)
	{
		for (int i = 0; i < t.nrAtribute; i++)
		{
			out << t.atribute[i];
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
	return in;
}
istream& operator>>(istream& in, Tabela& t)
{
	char buffer[255];
	in >> buffer;
	t.numeTabela = new char[strlen(buffer) + 1];
	strcpy_s(t.numeTabela, strlen(buffer) + 1, buffer);
	in >> t.nrAtribute;
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
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
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
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			contorCuvinte = 0;
			while (cuvant)
			{
				contorCuvinte++;
				cuvant = strtok(NULL, ", ");
				/*if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}*/
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
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			//determinare numar atribute
			int nrAtribute = contorCuvinte / 4;
			Atribut* atribute = new Atribut[nrAtribute];
			//extragem atributele
			for (int i = 0; i < nrAtribute; i++)
			{
				//nume atribut
				cuvant = strtok(NULL, ", ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
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
				atribute[i].setNumeAtribut(cuvant);;
				//tip atribut
				cuvant = strtok(NULL, ", ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
				atribute[i].setTipAtribut(cuvant);
				//dimensiune atribut
				cuvant = strtok(NULL, ", ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
				//transformam dimensiunea din char in int
				int dimensiune = 0;
				for (unsigned i = 0; i < strlen(cuvant); i++)
				{
					dimensiune = dimensiune * 10 + int(cuvant[i]) - 48;
				}
				atribute[i].setDimensiuneAtribut(dimensiune);
				//valoare implicita
				cuvant = strtok(NULL, ", ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
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
				}
				else if (strcmp(atribute[i].getTipAtribut(), "INTEGER") == 0) //transformam valoarea impliicta din text in int sau char
				{
					int valInt = 0;
					for (unsigned i = 0; i < strlen(cuvant); i++)
					{
						valInt = valInt * 10 + int(cuvant[i]) - 48;
					}
					atribute[i].setValoareImplicitaNumeric(float(valInt));
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
				}
			}
			t1.setAtribute(atribute, nrAtribute);
			cout << endl << "Tabela " << t1.getNumeTabela() << " a fost creata cu succes!" << endl;
			//adaugam tabela la vectorul de tabele
			adaugaTabela(t1);
			//adaugam tabela in fisier
			ofstream f("tabele.txt", ios::ate);
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
				//tabele[i].serializare();
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

	//INSERT INTO studenti VALUES (Bogdan, 20, 6), (Ovidiu, 21, 7.5) 
	void insertInto(string comanda, Tabela& t)
	{
		int contorCuvinte;
		int parantezaDreapta = 0;
		int parantezaStanga = 0;
		char* cuvant;
		char* copie;
		string aux;
		copie = new char[comanda.length() + 1];
		strcpy(copie, comanda.c_str());
		cuvant = strtok(copie, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		if (strcmp(cuvant, "VALUES") != 0)
		{
			cout << cuvant;
			throw exception("Comanda invalida !");
		}
		//verificare numar paranteze
		for (unsigned i = 0; i < strlen(copie); i++)
			{
			if (copie[i] == '(')
			{
parantezaStanga++;
			}
			if (copie[i] == ')')
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
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		contorCuvinte = 0;
		while (cuvant)
		{
			contorCuvinte++;
			cuvant = strtok(NULL, ", ");
			/*if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}*/
		}
		if (contorCuvinte % t.getNrAtribute() != 0)
		{
			throw exception("Numar invalid de parametri!");
		}
		if (contorCuvinte == 0)
		{
			throw exception("Numar invalid de parametri!");
		}
		Atribut* tempAtribute = new Atribut[t.getNrAtribute()];
		tempAtribute = t.getAtribute();
		delete[] copie;
		copie = new char[comanda.length() + 1];
		strcpy(copie, comanda.c_str());
		cuvant = strtok(copie, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		//Inregistrare tempInregistrari = new inregistrari
		for (int i = 0; i < contorCuvinte / t.getNrAtribute(); i++)
		{
			//inregistrarea i
			for (int j = 0; j < t.getNrAtribute(); j++)
			{
				//atribut j
				cuvant = strtok(NULL, ", ");
				//scoatem paranteza ( sau ) daca este cazul
				if (cuvant[0] == '(')
				{
					memmove(cuvant, cuvant + 1, strlen(cuvant + 1) + 1);
				}
				else if (cuvant[strlen(cuvant) - 1] == ')')
				{
					char auxiliar[255] = "";
					for (unsigned i = 0; i < strlen(cuvant) - 1; i++)
					{
						auxiliar[i] = cuvant[i];
					}
					strcpy_s(cuvant, strlen(auxiliar) + 1, auxiliar);
				}
				//verificam daca e null
				tempAtribute[j].adaugaInregistrare(cuvant);//val implicita
			}
		}
	}

	//DELETE FROM STUDENTI WHERE NUME = BOGDAN
	//DELETE FROM STUDENTI WHERE MEDIA = 4
	void deleteFrom(string comanda, Tabela& t)
	{	
		char* cuvant;
		char* copie;
		copie = new char[comanda.length() + 1];
		strcpy(copie, comanda.c_str());
		cuvant = strtok(copie, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		if (strcmp(cuvant, "WHERE") != 0)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " "); //nume atribut de cautat
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		//verificam daca numele de atribut este valid	
		Atribut* tempAtribute = new Atribut[t.getNrAtribute()];
		tempAtribute = t.getAtribute();
		bool gasit = 0;
		char numeAtribut[255] = "";
		char tipAtribut[255] = "";
		Atribut atributDeCautat;
		int pozitie=0;
		strcpy_s(numeAtribut, strlen(cuvant) + 1, cuvant);
		for (int i = 0; i < t.getNrAtribute() && gasit==0; i++)
		{
			if (strcmp(tempAtribute[i].getNumeAtribut(), numeAtribut) == 0)
			{
				gasit = 1;
				strcpy_s(tipAtribut, strlen(tempAtribute[i].getTipAtribut()) + 1, tempAtribute[i].getTipAtribut());
				atributDeCautat = tempAtribute[i];
				pozitie = i;
			}
		}
		if (gasit)
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "=") != 0)
			{
				throw exception("Comanda invalida!");
			}
			cuvant = strtok(NULL, " ");//valoarea care trebuie starsa
			int pozitie2 = 0;

			if (strcmp(tipAtribut, "TEXT") == 0)
			{
				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (strcmp(cuvant, tempAtribute[pozitie].getInregistrari()[i].getContinutText()) == 0)
					{
						pozitie2 = i;
					}
				}
			}
			else if (strcmp(tipAtribut, "INTEGER") == 0)
			{
				int integer = 0;
				for (unsigned i = 0; i < strlen(cuvant); i++)
				{
					integer = integer * 10 + int(cuvant[i]) - 48;
				}
				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (integer == tempAtribute[pozitie].getInregistrari()[i].getContinutInteger())
					{
						pozitie2 = i;
					}
				}
			}
			else if (strcmp(tipAtribut, "FLOAT") == 0)
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
				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (valFloat == tempAtribute[pozitie].getInregistrari()[i].getContinutFloat())
					{
						pozitie2 = i;
					}
				}
			}
			for (int i = 0; i < t.getNrAtribute(); i++)
			{

				tempAtribute[i].stergeInregistrarePozitie(pozitie2);
			}
			cout << "Inregistrarea a fost stearsa!" << endl;
		}
		else
		{
			throw exception("Nume atribut invalid!");
		}
	}

	void selectAllFrom(string comanda, Tabela& t)
	{
		//delete from studenti where nume = bogdan
		//select all from studenti where nume = bogdan
		char* cuvant;
		char* copie;
		copie = new char[comanda.length() + 1];
		strcpy(copie, comanda.c_str());
		cuvant = strtok(copie, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		if (strcmp(cuvant, "WHERE") != 0)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " "); //nume atribut de cautat
		//verificam daca numele de atribut este valid
		Atribut* tempAtribute = new Atribut[t.getNrAtribute()];
		tempAtribute = t.getAtribute();
		bool gasit = 0;
		char numeAtribut[255] = "";
		char tipAtribut[255] = "";
		Atribut atributDeCautat;
		int pozitie = 0;
		strcpy_s(numeAtribut, strlen(cuvant) + 1, cuvant);
		for (int i = 0; i < t.getNrAtribute() && gasit == 0; i++)
		{
			if (strcmp(tempAtribute[i].getNumeAtribut(), numeAtribut) == 0)
			{
				gasit = 1;
				strcpy_s(tipAtribut, strlen(tempAtribute[i].getTipAtribut()) + 1, tempAtribute[i].getTipAtribut());
				atributDeCautat = tempAtribute[i];
				pozitie = i;
				strcpy_s(tipAtribut, strlen(tempAtribute[i].getTipAtribut()) + 1, tempAtribute[i].getTipAtribut());
			}
		}
		//pozitie=pozitie atribut (nume)
		if (gasit)
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "=") != 0)
			{
				throw exception("Comanda invalida!");
			}
			cuvant = strtok(NULL, " ");//valoarea care trebuie starsa
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			int pozitie2 = 0;
			if (strcmp(tipAtribut, "TEXT") == 0)
			{

				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (strcmp(cuvant, tempAtribute[pozitie].getInregistrari()[i].getContinutText()) == 0)
					{
						pozitie2 = i;
					}
				}
			}
			else if (strcmp(tipAtribut, "INTEGER") == 0)
			{
				int integer = 0;
				for (unsigned i = 0; i < strlen(cuvant); i++)
				{
					integer = integer * 10 + int(cuvant[i]) - 48;
				}
				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (integer==tempAtribute[pozitie].getInregistrari()[i].getContinutInteger())
					{
						pozitie2 = i;
					}
				}
			}
			else if (strcmp(tipAtribut, "FLOAT") == 0)
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
				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (valFloat == tempAtribute[pozitie].getInregistrari()[i].getContinutFloat())
					{
						pozitie2 = i;
					}
				}
			}
			for (int i = 0; i < t.getNrAtribute() ; i++)
			{
				cout << tempAtribute[i].getNumeAtribut() << " : ";
				cout << tempAtribute[i].getInregistrari()[pozitie2]<<" | ";
			}
		}
		else
		{
			throw exception("Nume atribut invalid!");
		}
	}
	
	void selectWhat(string comanda, Tabela& t,set<char*>listaAtribute)
	{
		//delete from studenti where nume = bogdan
		//select all from studenti where nume = bogdan
		char* cuvant;
		char* copie;
		copie = new char[comanda.length() + 1];
		strcpy(copie, comanda.c_str());
		cuvant = strtok(copie, " ");//select
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		for (int i = 0; i < listaAtribute.size(); i++)
		{
			cuvant = strtok(NULL, " ");//numeAtribut de afisat
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
		}
		cuvant = strtok(NULL, " ");//from
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");//numetabel
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");//where
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		if (strcmp(cuvant, "WHERE") != 0)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " "); //nume atribut de cautat
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		//verificam daca numele de atribut este valid
		Atribut* tempAtribute = new Atribut[t.getNrAtribute()];
		tempAtribute = t.getAtribute();
		bool gasit = 0;
		char numeAtribut[255] = "";
		char tipAtribut[255] = "";
		Atribut atributDeCautat;
		int pozitie = 0;
		strcpy_s(numeAtribut, strlen(cuvant) + 1, cuvant);
		for (int i = 0; i < t.getNrAtribute() && gasit == 0; i++)
		{
			if (strcmp(tempAtribute[i].getNumeAtribut(), numeAtribut) == 0)
			{
				gasit = 1;
				strcpy_s(tipAtribut, strlen(tempAtribute[i].getTipAtribut()) + 1, tempAtribute[i].getTipAtribut());
				atributDeCautat = tempAtribute[i];
				pozitie = i;
				strcpy_s(tipAtribut, strlen(tempAtribute[i].getTipAtribut()) + 1, tempAtribute[i].getTipAtribut());
			}
		}
		if (gasit)
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "=") != 0)
			{
				throw exception("Comanda invalida!");
			}
			cuvant = strtok(NULL, " ");//valoarea care trebuie starsa
			int pozitie2 = 0;

			if (strcmp(tipAtribut, "TEXT") == 0)
			{
				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (strcmp(cuvant, tempAtribute[pozitie].getInregistrari()[i].getContinutText()) == 0)
					{
						pozitie2 = i;
					}
				}
			}
			else if (strcmp(tipAtribut, "INTEGER") == 0)
			{
				int integer = 0;
				for (unsigned i = 0; i < strlen(cuvant); i++)
				{
					integer = integer * 10 + int(cuvant[i]) - 48;
				}
				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (integer == tempAtribute[pozitie].getInregistrari()[i].getContinutInteger())
					{
						pozitie2 = i;
					}
				}
			}
			else if (strcmp(tipAtribut, "FLOAT") == 0)
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
				for (int i = 0; i < tempAtribute[pozitie].getNrInregistrari(); i++)
				{
					if (valFloat == tempAtribute[pozitie].getInregistrari()[i].getContinutFloat())
					{
						pozitie2 = i;
					}
				}
			}
			for (set<char*>::iterator it = listaAtribute.begin(); it!= listaAtribute.end(); it++)
			{
				for (int i = 0; i < t.getNrAtribute(); i++)
				{
					if (strcmp(tempAtribute[i].getNumeAtribut(), *it) == 0)
					{
						cout << tempAtribute[i].getNumeAtribut() << " : ";
						cout << tempAtribute[i].getInregistrari()[pozitie2] << " | ";
					}	
				}
			}
		}
		else
		{
			throw exception("Nume atribut invalid!");
		}
	}

	void update(string comanda, Tabela& t)//update studenti set varsta = 22 where nume = bogdan
	{
		char* cuvant;
		char* copie;
		string aux;
		copie = new char[comanda.length() + 1];
		strcpy(copie, comanda.c_str());
		cuvant = strtok(copie, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		cuvant = strtok(NULL, " ");
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		if (strcmp(cuvant, "SET") != 0)
		{
			cout << cuvant;
			throw exception("Comanda invalida !");
		}
		cuvant = strtok(NULL, " "); //nume atribut de cautat
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		//verificam daca numele de atribut este valid
		Atribut* tempAtribute = new Atribut[t.getNrAtribute()];
		tempAtribute = t.getAtribute();
		bool gasit = 0;
		char numeAtribut1[255] = "";
		char tipAtribut[255] = "";
		Atribut atributDeCautat;
		int pozitie1 = 99;
		strcpy_s(numeAtribut1, strlen(cuvant) + 1, cuvant);
		for (int i = 0; i < t.getNrAtribute() && gasit == 0; i++)
		{
			if (strcmp(tempAtribute[i].getNumeAtribut(), numeAtribut1) == 0)
			{
				gasit = 1;
				strcpy_s(tipAtribut, strlen(tempAtribute[i].getTipAtribut()) + 1, tempAtribute[i].getTipAtribut());
				atributDeCautat = tempAtribute[i];
				pozitie1 = i;
			}
		}
		if (gasit)
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "=") != 0)
			{
				throw exception("Comanda invalida!");
			}
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			char inlocuimCu[255] = "";//update studenti set varsta = 22 where nume = bogdan
			strcpy_s(inlocuimCu, strlen(cuvant) + 1, cuvant); //22
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "WHERE") != 0)
			{
				throw exception("Comanda invalida!");
			}
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			Atribut* tempAtribute = new Atribut[t.getNrAtribute()];
			tempAtribute = t.getAtribute();
			bool gasit = 0;
			char numeAtribut1[255] = "";
			char tipAtribut[255] = "";
			Atribut atributDeCautat;
			int pozitie2 = 99;
			strcpy_s(numeAtribut1, strlen(cuvant) + 1, cuvant);
			for (int i = 0; i < t.getNrAtribute() && gasit == 0; i++)
			{
				if (strcmp(tempAtribute[i].getNumeAtribut(), numeAtribut1) == 0)
				{
					gasit = 1;
					strcpy_s(tipAtribut, strlen(tempAtribute[i].getTipAtribut()) + 1, tempAtribute[i].getTipAtribut());
					atributDeCautat = tempAtribute[i];
					pozitie2 = i;
				}
			}
			if (gasit)
			{
				cuvant = strtok(NULL, " ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
				if (strcmp(cuvant, "=") != 0)
				{
					throw exception("Comanda invalida!");
				}
				cuvant = strtok(NULL, " ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
				//pozite 2 = pozitie nume_col2 in vector atribute
				int pozitie3 = 99;
				char tipAtribut[100];
				strcpy_s(tipAtribut,strlen(tempAtribute[pozitie2].getTipAtribut())+1,tempAtribute[pozitie2].getTipAtribut());
				//verificatm tipul atributului
				if (strcmp(tipAtribut, "TEXT") == 0)
				{
					for (int i = 0; i < tempAtribute[pozitie2].getNrInregistrari(); i++)
					{
						if (strcmp(tempAtribute[pozitie2].getInregistrari()[i].getContinutText(),cuvant)==0)
						{
							pozitie3 = i;
						}
					}
				}
				else if (strcmp(tipAtribut, "INTEGER") == 0)
				{
					int integer = 0;
					for (unsigned i = 0; i < strlen(cuvant); i++)
					{
						integer = integer * 10 + int(cuvant[i]) - 48;
					}
					for (int i = 0; i < tempAtribute[pozitie2].getNrInregistrari(); i++)
					{
						if (tempAtribute[pozitie2].getInregistrari()[i].getContinutInteger() == integer)
						{
							pozitie3 = i;
						}
					}
				}
				else if (strcmp(tipAtribut, "FLOAT") == 0)
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
					for (int i = 0; i < tempAtribute[pozitie2].getNrInregistrari(); i++)
					{
						if (tempAtribute[pozitie2].getInregistrari()[i].getContinutFloat() == valFloat)
						{
							pozitie3 = i;
						}
					}
				}
				tempAtribute[pozitie1].updateAtribut(pozitie3, inlocuimCu);
			}
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
		if (cuvant == nullptr)
		{
			throw exception("Comanda invalida!");
		}
		//CREATE TABLE
		if (strcmp(cuvant, "CREATE") == 0)
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
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
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "TABLE") == 0)
			{
				cuvant = strtok(NULL, " ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
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
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
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
		//INSERT INTO studenti VALUES (Bogdan, 20, 6), (Ovidiu, 21, 7.5) 
		else if (strcmp(cuvant, "INSERT") == 0)
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "INTO") == 0)
			{
				cuvant = strtok(NULL, " ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
				//cuvant=numeTabela
				//verificam daca exista tabela
				bool gasit = 0;
				int j;
				for (int i = 0; i < nrTabele && gasit==0; i++)
				{
					if (strcmp(cuvant, tabele[i].getNumeTabela()) == 0)
					{
						gasit = 1;
						j = i;
					}
				}
				if (gasit)
				{
						
					Tabela t=tabele[j];
					Comanda iI;
					iI.insertInto(comanda, t);
					tabele[j] = t;
					//cout << t;
					ofstream f("tabele.txt", ios::ate);
					for (int i = 0; i < nrTabele; i++)
					{
						f << tabele[i]<<endl;
					}
					cout << endl;
					cout << "Valorile au fost inserate cu succes !";
				}
				else
				{
					throw exception("Tabela nu exista!");
				}
			}
			else
			{
				throw exception("Cuvant cheie incorect!");
			}
		}
		else  if (strcmp(cuvant, "DELETE") == 0)
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "FROM") == 0)
			{
				cuvant = strtok(NULL, " ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
				bool gasit = 0;
				int j;
				//cout << "*" << cuvant << "*";
				for (int i = 0; i < nrTabele && gasit == 0; i++)
				{
					if (strcmp(cuvant, tabele[i].getNumeTabela()) == 0)
					{
						gasit = 1;
						j = i;
					}
				}
				if (gasit)
				{
					Tabela t = tabele[j];
					Comanda DF;
					DF.deleteFrom(comanda, t);
					//facem update la tabele
					tabele[j] = t;
				}
				else
				{
					throw exception("Tabela nu exista!");
				}		
			}
			else
				throw exception("Comanda invalida !");
		}
		else  if (strcmp(cuvant, "SELECT") == 0)
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			if (strcmp(cuvant, "ALL") == 0)
			{
				cuvant = strtok(NULL, " ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
				if (strcmp(cuvant, "FROM") == 0)
				{
					cuvant = strtok(NULL, " ");
					if (cuvant == nullptr)
					{
						throw exception("Comanda invalida!");
					}
					bool gasit = 0;
					int j;
					for (int i = 0; i < nrTabele && gasit == 0; i++)
					{
						if (strcmp(cuvant, tabele[i].getNumeTabela()) == 0)
						{
							gasit = 1;
							j = i;
						}
					}
					if (gasit)
					{

						Tabela t = tabele[j];
						Comanda SF;
						SF.selectAllFrom(comanda, t);
						//facem update la tabele
						tabele[j] = t;
					}
					else
					{
						throw exception("Tabela nu exista!");
					}
				}
				else
				{
					throw exception("Comanda invalida !");
				}
			}
			else //select nume, varsta from studenti where nume = bogdan
			{
				if (strcmp(cuvant, "FROM") == 0)
				{
					throw exception("Comanda invalida !");
				}
				//nume,
				//stergem virgula de dupa
				if (cuvant[strlen(cuvant) - 1] == ',')
				{
					char auxiliar[255] = "";
					for (unsigned i = 0; i < strlen(cuvant) - 1; i++)
					{
						auxiliar[i] = cuvant[i];
					}
					strcpy_s(cuvant, strlen(auxiliar) + 1, auxiliar);
				}
				set<char*>listaAtribute;
				//adaugam in lista
				listaAtribute.insert(cuvant);
				cuvant = strtok(NULL, " ");
				if (cuvant == nullptr)
				{
					throw exception("Comanda invalida!");
				}
				while (strcmp(cuvant, "FROM") != 0)
				{
					//stergem virgula de dupa
					if (cuvant[strlen(cuvant) - 1] == ',')
					{
						char auxiliar[255] = "";
						for (unsigned i = 0; i < strlen(cuvant) - 1; i++)
						{
							auxiliar[i] = cuvant[i];
						}
						strcpy_s(cuvant, strlen(auxiliar) + 1, auxiliar);
					}
					//adaugam in lista
					listaAtribute.insert(cuvant);
					cuvant = strtok(NULL, " ");
					if (cuvant == nullptr)
					{
						throw exception("Comanda invalida!");
					}
				}
				if (strcmp(cuvant, "FROM") == 0)
				{
					cuvant = strtok(NULL, " ");
					if (cuvant == nullptr)
					{
						throw exception("Comanda invalida!");
					}
					bool gasit = 0;
					int j;
					for (int i = 0; i < nrTabele && gasit == 0; i++)
					{
						if (strcmp(cuvant, tabele[i].getNumeTabela()) == 0)
						{
							gasit = 1;
							j = i;
						}
					}
					if (gasit)
					{
						//facem ce e de facut xD
						Tabela t = tabele[j];
						Comanda sW;
						sW.selectWhat(comanda, t,listaAtribute);
						tabele[j] = t;

					}
					else
					{
						throw exception("Tabela nu exista!");
					}

				}
				else
				{
					throw exception("Comanda invalida !");
				}
			}
		}
		else  if (strcmp(cuvant, "UPDATE") == 0) //update studenti set varsta = 22 where nume = bogdan
		{
			cuvant = strtok(NULL, " ");
			if (cuvant == nullptr)
			{
				throw exception("Comanda invalida!");
			}
			bool gasit = 0;
			int j;
			for (int i = 0; i < nrTabele && gasit == 0; i++)
			{
				if (strcmp(cuvant, tabele[i].getNumeTabela()) == 0)
				{
					gasit = 1;
					j = i;
				}
			}
			if (gasit)
			{
				Tabela t = tabele[j];
				Comanda uP;
				uP.update(comanda, t);
				tabele[j] = t;
			}
			else
			{
				throw exception("Tabela nu exista!");
			}
		}
		else
		{
			throw exception("Comanda necunoscuta!");
		}		
	}
};