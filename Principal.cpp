#include<iostream>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include<fstream>
#include<algorithm>
#include<vector>
#include"persoanaFizica.h"
#include"persoanaJuridica.h"
#include"dateF.h"
#include"dateJ.h"
using namespace std;
#define WINWIDTH 70
#define WINHEIGHT 15
template <typename T>
void adauga_fisier(T a, string nume_fis) {
	ofstream outfile(nume_fis, ios::out | ios::binary | ios::app);
	//outfile.open(nume_fis, ios::out | ios::binary);
	if (outfile.is_open()) {
		if (outfile.write((char*)&a, sizeof(T)))
			cout << endl << "Adaugat cu Succes..." << endl;
		else
			cout << "Nu pot scrie in fisier!";
		outfile.close();
	}
	else
		cerr << "Fisierul outPersoana.dat nu a putut fi deschis pentru scriere!" << endl;
}
template <typename Y>
void citeste_fis(Y a, string nume_fis)
{
	ifstream infile(nume_fis, ios::in | ios::binary);
	//infile.open(nume_fis, ios::in | ios::binary);
	if (infile.is_open()) {
		infile.seekg(0, ios::end);
		cout << endl << "Nr elemente in fisierul  " << nume_fis << " : " << infile.tellg() / sizeof(a) << endl;
		infile.seekg(ios::beg);
		Y aux;
		if (infile.read((char*)&aux, sizeof(Y)))
		{
			cout << endl << "Elementele din fisierul " << nume_fis << " : " << endl;
			while (!infile.eof()) {
				Y bun;
				bun = aux;
				cout << bun;
				infile.read((char*)&aux, sizeof(Y));
				cout << endl << "******************" << endl;
			}
			cout << endl;
		}
		else
			cout << "Nu pot citi!!";

		infile.close();
	}
	else
		cerr << "Fisierul outPersoana.dat nu a putut fi deschis pentru citire!" << endl;
}
template<class K>
class Repository
{
public:
	string fileName;
	Repository(string fileName)
	{
		this->fileName = fileName;
	}
	K read(int id)
	{
		ifstream f(fileName, ios::binary);
		K obj;
		while (!f.eof())
		{
			if (f.read((char*)&obj, sizeof(obj)))
			{
				if (obj.getProdusID() == id)
				{
					f.close();
					return obj;
				}
			}
			else
			{
				break;
			}
		}
		f.close();
		K default_obj;
		return default_obj;
	}

	void stergere_produs(int id)
	{
		ifstream f(fileName, ios::binary);
		ofstream g("temp.bin", ios::binary | ios::trunc);

		K obj;
		while (f.read((char*)&obj, sizeof(obj)))
		{
			if (obj.getProdusID() != id)
			{
				g.write((char*)&obj, sizeof(obj));
			}
		}
		f.close();
		g.close();
		remove(fileName.c_str());
		int r = rename("temp.bin", fileName.c_str());
	}

	void editare_produs(K obj)
	{
		ifstream f(fileName, ios::binary);
		ofstream g("temp.dat", ios::binary | ios::trunc);

		while (!f.eof())
		{
			K obj2;
			bool ok = f.read((char*)&obj2, sizeof(obj2)) ? true : false;
			if (ok)
			{
				if (obj.getProdusID() == obj2.getProdusID())
				{
					g.write((char*)&obj, sizeof(obj));
				}
				else
				{
					g.write((char*)&obj2, sizeof(obj2));
				}
			}
			else {
				break;
			}

		}
		f.close();
		g.close();
		remove(fileName.c_str());
		int r = rename("temp.dat", fileName.c_str());
	}
};

void umplere_deco()
{
	for (int i = 0; i < 20; i++)
		cout << " ";
	for (int i = 0; i < WINWIDTH; i++)
		cout << "#";
	cout << endl;
}
void liniar()
{
	for (int i = 0; i < WINHEIGHT; i++)
		cout << endl;
}
void bun_venit()
{
	liniar();
	cout << "Loading..." << endl;
	Sleep(500);
	char mesaj[] = "BUN VENIT LA MAGAZINUL NOSTRU ELECTRONIC!";
	int len = strlen(mesaj);
	for (int i = 0; i < WINWIDTH; i++)
	{
		printf("%c", 177);
		Sleep(55);
	}
	cout << endl;
	system("CLS");
	umplere_deco();
	int x;
	x = (WINWIDTH / 2) - (len / 2);
	cout << setw(len + 2 * x) << mesaj << endl << setw(len + x) << "decorIT" << endl;
	umplere_deco();

}
int alegere_utilizator()
{
	int ok;
	system("CLS");
	cout << endl << "Sunteti administrator sau client?" << endl;
	cout << "CLIENT (1)" << endl;
	cout << "ADMINISTRATOR(2)" << endl;
	cout << "OPTIUNE: ";
	int y;
	cin >> y;
	if (y == 1 || y == 2)
		ok = 1;
	else
	{
		ok = 0;
		while (ok == 0)
		{
			cout << "ATI INTRODUS O VALOARE GRESITA!              INCERCATI DIN NOU!" << endl;
			cout << "OPTIUNE: ";
			cin >> y;
			if (y == 1 || y == 2)
				ok = 1;
			else
				ok = 0;

		}
	}

	return y;
}
int alegere_operatie()
{
	cout << "\t\t\t Alegeti una din optiunile:" << endl << endl;
	cout << "\t\t\t Adaugare produse (1)" << endl;
	cout << "\t\t\t Stergere produse (2)" << endl;
	cout << "\t\t\t Modificare produse (3)" << endl;
	cout << "\t\t\t Prelucrare comenzi si Realizare Raport (4)" << endl;
	cout << "\t\t\t Exit (5)" << endl;

	cout << endl << "Optiune: ";
	int optiune, bun;
	cin >> optiune;
	if (optiune == 1 || optiune == 2 || optiune == 3 || optiune == 4 || optiune == 4 || optiune == 5)
		bun = 1;
	else
	{
		bun = 0;
		while (bun == 0)
		{
			cout << "Ati introdus o valoare gresita!     Incercati din nou!" << endl;
			cout << endl << "Optiune: ";
			cin >> optiune;
			if (optiune == 1 || optiune == 2 || optiune == 3 || optiune == 4 || optiune == 5)
				bun = 1;
			else
				bun = 0;

		}
	}
	return optiune;
}
int alegere_categorie()
{
	system("CLS");
	cout << "\t\t\t Alegeti categoria produsului:" << endl;
	cout << "\t\t\t Laptop (1)" << endl;
	cout << "\t\t\t Desktop(2)" << endl;
	cout << "\t\t\t Telefon(3)" << endl;
	cout << "\t\t\t Tableta(4)" << endl;
	cout << "\t\t\t Audio_Video(5)" << endl;
	int optiune, bun;
	cout << "Optiune:";
	cin >> optiune;
	if (optiune == 1 || optiune == 2 || optiune == 3 || optiune == 4 || optiune == 5)
		bun = 1;
	else
	{
		bun = 0;
		while (bun == 0)
		{
			cout << "Ati introdus o valoare gresita!     Incercati din nou!" << endl;
			cout << endl << "Optiune: ";
			cin >> optiune;
			if (optiune == 1 || optiune == 2 || optiune == 3 || optiune == 4 || optiune == 5)
				bun = 1;
			else
				bun = 0;

		}
	}
	return optiune;
}
int nou_sau_vechi()
{
	system("CLS");
	cout << endl << "Introduceti un produs nou?(1)";
	cout << endl << "SAU";
	cout << endl << "Modificati stocul unuia deja existent?(2)";
	int y;
	cin >> y;
	int ok;
	if (y == 1 || y == 2)
		ok = 1;
	else
	{
		ok = 0;
		while (ok == 0)
		{
			cout << "ATI INTRODUS O VALOARE GRESITA!              INCERCATI DIN NOU!" << endl;
			cout << "OPTIUNE: ";
			cin >> y;
			if (y == 1 || y == 2)
				ok = 1;
			else
				ok = 0;

		}
	}
	return y;
}
int adaug_scad()
{
	system("CLS");
	cout << endl << "Doriti sa adaugati produse in stoc?(1)";
	cout << endl << "SAU";
	cout << endl << "Doriti sa eliminati produse din stoc?(2)";
	int y;
	cin >> y;
	int ok;
	if (y == 1 || y == 2)
		ok = 1;
	else
	{
		ok = 0;
		while (ok == 0)
		{
			cout << "ATI INTRODUS O VALOARE GRESITA!              INCERCATI DIN NOU!" << endl;
			cout << "OPTIUNE: ";
			cin >> y;
			if (y == 1 || y == 2)
				ok = 1;
			else
				ok = 0;

		}
	}
	return y;
}
class afisare
{
public:
	//Aceasta metoda virtuala pura va fi apelata pentru a afisa obiectele din clasele derivate!
	virtual std::ostream& print(std::ostream& output) const = 0;
};
std::ostream& operator<<(std::ostream& out, const afisare& rhs) {
	return rhs.print(out);
};

enum categorie_produs
{
	LAPTOP, TELEFON, TABLETA, DESKTOP, AUDIO_VIDEO, NIMIC
};
class produse :public afisare
{
protected:
	int produsID;
	char denumireProdus[100] = { "" };
	double pret;
	int cantitate;
	char descriereProdus[200] = { "" };
	categorie_produs categorie;
	char firma[50] = { "" };
public:
	//vector<produse>p;
	produse();
	produse(int produsID, char denumireProdus[100], double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categ);
	produse(const produse& p);
	produse& operator=(produse p);
	int getProdusID();
	char* getDenumireProdus();
	double getPret();
	int getCantitate();
	char* getDescriereProdus();
	categorie_produs getCategorieProdus();
	char* getFirma();
	~produse();

	void setProdusID(int produsID);
	void setDenumireProdus(const char* denumireProdus);
	void setPret(double pret);
	void setCantitate(int cantitate);
	void setDescriereProdus(const char* descriereProdus);
	void setCategorieProdus(categorie_produs categorie);
	void setFirma(const char* firma);
	void adauga_produse();

	std::ostream& print(std::ostream& output) const {
		return output << "ProdusID: " << this->produsID << endl << "Denumire:" << this->denumireProdus << endl << "Pret:" << this->pret << endl << endl << "Firma:" << this->firma << endl << "Descriere:" << this->descriereProdus << endl << "Cantitate:" << this->cantitate << endl;

	};

	bool operator==(produse p)
	{
		if (this->pret == p.getPret())
			return true;
	}

	bool operator<(produse p)
	{
		if (this->pret < p.getPret())
			return true;
	}

	bool operator>(produse p)
	{
		if (this->pret > p.getPret())
			return true;
	}

};


produse::produse()
{
	this->produsID = 0;

	this->pret = 0;
	this->cantitate = 0;

	this->categorie = NIMIC;

}

produse::produse(int produsID, char denumireProdus[100], double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categ)
{
	if (produsID > 0)
		this->produsID = produsID;
	else
		this->produsID = 0;

	strcpy_s(this->denumireProdus, denumireProdus);

	if (pret > 0)
		this->pret = pret;
	else
		this->pret = 0;

	if (cantitate > 0)
		this->cantitate = cantitate;
	else
		this->cantitate = 0;

	strcpy_s(this->descriereProdus, descriereProdus);

	strcpy_s(this->firma, firma);

	if (categ == LAPTOP || categ == TELEFON || categ == TABLETA || categ == DESKTOP || categ == AUDIO_VIDEO || categ == NIMIC)
		this->categorie = categ;
	else
		this->categorie = NIMIC;

}

produse::produse(const produse& p)
{
	produsID = p.produsID;
	strcpy_s(this->denumireProdus, p.denumireProdus);
	pret = p.pret;
	cantitate = p.cantitate;
	strcpy_s(this->descriereProdus, p.descriereProdus);
	categorie = p.categorie;
	strcpy_s(this->firma, p.firma);

}

produse& produse::operator=(produse p)
{
	this->produsID = p.produsID;
	strcpy_s(this->denumireProdus, p.denumireProdus);
	this->pret = p.pret;
	this->cantitate = p.cantitate;
	strcpy_s(this->descriereProdus, p.descriereProdus);
	this->categorie = p.categorie;
	strcpy_s(this->firma, p.firma);

	return *this;
}

int produse::getProdusID()
{
	return this->produsID;
}

char* produse::getDenumireProdus()
{
	return denumireProdus;
}

double produse::getPret()
{
	return pret;
}

int produse::getCantitate()
{
	return cantitate;
}

char* produse::getDescriereProdus()
{
	return descriereProdus;
}

categorie_produs produse::getCategorieProdus()
{
	return categorie_produs();
}

char* produse::getFirma()
{
	return this->firma;
}

produse::~produse()
{
}

void produse::setProdusID(int produsID)
{
	if (produsID > 0)
		this->produsID = produsID;
}

void produse::setDenumireProdus(const char* denumireProdus)
{
	if (denumireProdus != "")
		strcpy_s(this->denumireProdus, denumireProdus);
}

void produse::setPret(double pret)
{
	if (pret > 0)
		this->pret = pret;
}

void produse::setCantitate(int cantitate)
{
	if (cantitate > 0)
		this->cantitate = cantitate;
}

void produse::setDescriereProdus(const char* descriereProdus)
{
	if (descriereProdus != "")
		strcpy_s(this->descriereProdus, descriereProdus);
}

void produse::setCategorieProdus(categorie_produs categorie)
{
	if (categorie == LAPTOP || categorie == TELEFON || categorie == TABLETA || categorie == DESKTOP || categorie == AUDIO_VIDEO || categorie == NIMIC)
		this->categorie = categorie;
}

void produse::setFirma(const char* firma)
{
	strcpy_s(this->firma, firma);
}

void compara_pret(produse p1, produse p2)
{
	if (p1.operator==(p2) == true)
	{
		cout << "Produsul " << p1.getDenumireProdus() << " are acelasi pret ca produsul " << p2.getDenumireProdus() << endl;
	}
	else
		if (p1.operator<(p2) == true)
		{
			cout << "Produsul " << p1.getDenumireProdus() << " este mai ieftin decat produsul " << p2.getDenumireProdus() << endl;
		}
		else
			if (p1.operator>(p2) == true)
			{
				cout << "Produsul " << p1.getDenumireProdus() << " este mai scump decat produsul " << p2.getDenumireProdus() << endl;
			}
}

void produse::adauga_produse()
{
	cout << "ID: ";
	cin >> this->produsID;
	getchar();
	cout << "Denumire: ";
	cin.getline(this->denumireProdus, 100);

	cout << "Pret: ";
	cin >> this->pret;
	cout << "Cantitate: ";
	cin >> this->cantitate;
	getchar();
	cout << "Descriere: ";
	cin.getline(this->descriereProdus, 200);

	cout << "Firma: ";
	cin.getline(this->firma, 50);

}

class CosCumparaturi :public produse
{

public:
	vector <produse> produseCos;
	void adaugaInCos(produse prod);
	void stergeDinCos(int idSters);
	~CosCumparaturi();
	double getPretulCosului();
	int getNumarObiecteCos();
	void VizualizareCos();


};


void CosCumparaturi::adaugaInCos(produse prod)
{
	produseCos.push_back(prod);
	return;
}
void CosCumparaturi::stergeDinCos(int idSters)
{


	for (unsigned int i = 0; i < produseCos.size(); i++)
	{
		if (produseCos.at(i).getProdusID() == idSters)
		{
			produseCos.erase(produseCos.begin() + i);
			return;

		}
		else
		{
			cout << "Obiectul nu a fost gasit. Nimic nu a fost sters" << endl;
		}
	}

	return;
}

CosCumparaturi::~CosCumparaturi()
{

} 



double CosCumparaturi::getPretulCosului()
{
	produse p;
	double pretTotal;
	pretTotal = 0;
	for (unsigned i = 0; i < produseCos.size(); i++)
	{
		pretTotal = pretTotal + (produseCos.at(i).getPret() * produseCos.at(i).getCantitate());
	}
	return pretTotal;
}

int CosCumparaturi::getNumarObiecteCos()
{
	int numarObiecte;
	numarObiecte = 0;
	for (unsigned i = 0; i < produseCos.size(); i++)
	{
		numarObiecte = numarObiecte + produseCos.at(i).getCantitate();
	}
	return numarObiecte;
}

void CosCumparaturi::VizualizareCos()
{
	cout << "Numar de produse in cos este: " << " " << getNumarObiecteCos() << endl;
	for (unsigned i = 0; i < produseCos.size(); i++)
	{
		cout << endl << "ID-ul produs" << " " << produseCos[i].getProdusID() << " " << "Cantitatea dorita: " << produseCos[i].getCantitate() << " " << "Pretul produsului/produselor: " << produseCos[i].getPret() << " "
			<< "Valoarea totala: " << produseCos[i].getPret() * produseCos[i].getCantitate();
	}
	if (produseCos.size() == 0)
	{
		cout << " Cosul de cumparaturi este gol: " << endl;
	}
	cout << endl;
	cout << "Pretul total: " << getPretulCosului() << " " << endl << endl;
	return;
}

class tableta :
	public produse
{
protected:
	char model[30] = { "" };
	char sistem_operare[30] = { "" };
	char conectivitate[30] = { "" };
	float dimensiune_ecran;
	int capacitate_stocare;
	float frecventa;
	int capacitate_RAM;
	char culoare[30] = { "" };
public:
	tableta() :produse()
	{
		this->dimensiune_ecran = 0;
		this->capacitate_stocare = 0;
		this->frecventa = 0;
		this->capacitate_RAM = 0;
	}
	tableta(int id, char denumire[100], double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categorie,
		char model[30], char sistem_operare[30], char conectivitate[30], float dimensiune_ecr, int capacitate_stocare, float frecveanta, int capacit_RAM,
		char culoare[30]) :produse(id, denumire, pret, cantitate, descriereProdus, firma, categorie)
	{
		strcpy_s(this->model, model);
		strcpy_s(this->sistem_operare, sistem_operare);
		strcpy_s(this->conectivitate, conectivitate);
		if (dimensiune_ecr > 0)
			this->dimensiune_ecran = dimensiune_ecr;
		else
			this->dimensiune_ecran = 0;
		if (capacitate_stocare > 0)
			this->capacitate_stocare = capacitate_stocare;
		else
			this->capacitate_stocare = 0;
		if (frecveanta > 0)
			this->frecventa = frecveanta;
		else
			this->frecventa = 0;
		if (capacitate_RAM > 0)
			this->capacitate_RAM = capacitate_RAM;
		else
			this->capacitate_RAM = 0;
		strcpy_s(this->culoare, culoare);
	}
	tableta(tableta& t) : produse(t)
	{
		strcpy_s(this->model, t.model);
		strcpy_s(this->sistem_operare, t.sistem_operare);
		strcpy_s(this->conectivitate, t.conectivitate);
		this->dimensiune_ecran = t.dimensiune_ecran;
		this->capacitate_stocare = t.capacitate_stocare;
		this->frecventa = t.frecventa;
		this->capacitate_RAM = t.capacitate_RAM;
		strcpy_s(this->culoare, t.culoare);
	}
	tableta& operator=(tableta t)
	{
		this->produse::operator=(t);
		strcpy_s(this->model, t.model);
		strcpy_s(this->sistem_operare, t.sistem_operare);
		strcpy_s(this->conectivitate, t.conectivitate);
		this->dimensiune_ecran = t.dimensiune_ecran;
		this->capacitate_stocare = t.capacitate_stocare;
		this->frecventa = t.frecventa;
		this->capacitate_RAM = t.capacitate_RAM;
		strcpy_s(this->culoare, t.culoare);
		return *this;
	}
	void adauga_tableta()
	{
		this->adauga_produse();
		cout << "Modelul Tabletei:";
		cin.getline(this->model, 30);

		cout << endl << "Dimensiune Ecran:";
		cin >> this->dimensiune_ecran;
		getchar();
		cout << endl << "Sistm de Operare:";
		cin.getline(this->sistem_operare, 30);

		cout << endl << "Conectivitate:";
		cin.getline(this->conectivitate, 30);

		cout << endl << "Frecventa:";
		cin >> this->frecventa;
		cout << endl << "Capacitate Stocare:";
		cin >> this->capacitate_stocare;
		getchar();
		cout << endl << "Culoarea:";
		cin.getline(this->culoare, 30);

		cout << endl << "Capacitate RAM:";
		cin >> this->capacitate_RAM;
		getchar();
	}
	std::ostream& print(std::ostream& output) const {
		return produse::print(output) << "Model: " << this->model << endl << "Dimensiune Ecran  " << this->dimensiune_ecran << endl << " Sistem de operare: " << this->sistem_operare << endl << "Conectivitate: " << this->conectivitate << endl << "Frecventa: " << this->frecventa << endl << "Capacitate Stocare " << this->capacitate_stocare << endl << "Culoare: " << this->culoare << endl << "Capacitate RAM: " << this->capacitate_RAM;
	};
	void operator+=(int cantitate)
	{
		if (cantitate > 0)
			this->cantitate += cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
	void operator-=(int cantitate)
	{
		if (cantitate > 0 && this->cantitate - cantitate > 0)
			this->cantitate -= cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
};


class telefon :
	public produse
{
protected:
	char tip_retea[30] = { " " };
	char model[30] = { "" };
	float dimensiune_ecran;
	char sistem_operare[30] = { " " };
	char tip_procesor[30] = { "" };
	int capacitate_baterie;
	int capacitate_stocare;
	char culoare[30] = { "" };
	int rezolutie_camera;
	char cartela[30] = { "" };
public:
	telefon() :produse()
	{


		this->dimensiune_ecran = 0;

		this->capacitate_baterie = 0;
		this->capacitate_stocare = 0;

		this->rezolutie_camera = 0;

	}
	telefon(int id, char denumire[100], double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categorie,
		char tip_retea[30], char model[30], float dimensiune, char sistem_operare[30], char tip_procesor[30], int capacitate_baterie, int capacitate_stocare,
		char culoare[30], int rezolutie_camera, char cartela[30]) :produse(id, denumire, pret, cantitate, descriereProdus, firma, categorie)
	{
		strcpy_s(this->tip_retea, tip_retea);
		strcpy_s(this->model, model);
		if (dimensiune_ecran > 0)
			this->dimensiune_ecran = dimensiune;
		else
			this->dimensiune_ecran = 0;
		strcpy_s(this->sistem_operare, sistem_operare);
		strcpy_s(this->tip_procesor, tip_procesor);
		if (capacitate_baterie > 0)
			this->capacitate_baterie = capacitate_baterie;
		else
			this->capacitate_baterie = 0;
		if (capacitate_stocare > 0)
			this->capacitate_stocare = capacitate_stocare;
		else
			this->capacitate_stocare = 0;
		strcpy_s(this->culoare, culoare);
		if (rezolutie_camera > 0)
			this->rezolutie_camera = rezolutie_camera;
		else
			this->rezolutie_camera = 0;
		if (strcmp(cartela, "DUAL") == 0 || strcmp(cartela, "SINGLE") == 0)
			strcpy_s(this->cartela, cartela);
		else
			strcpy_s(this->cartela, "DUAL");
	}
	telefon(telefon& t) :produse(t)
	{
		strcpy_s(this->tip_retea, t.tip_retea);
		strcpy_s(this->model, t.model);
		this->dimensiune_ecran = t.dimensiune_ecran;
		strcpy_s(this->sistem_operare, t.sistem_operare);
		strcpy_s(this->tip_procesor, t.tip_procesor);
		this->capacitate_baterie = t.capacitate_baterie;
		this->capacitate_stocare = t.capacitate_stocare;
		strcpy_s(this->culoare, t.culoare);
		this->rezolutie_camera = t.rezolutie_camera;
		strcpy_s(this->cartela, t.cartela);
	}
	telefon& operator=(telefon t)
	{
		this->produse::operator=(t);
		strcpy_s(this->tip_retea, t.tip_retea);
		strcpy_s(this->model, t.model);
		this->dimensiune_ecran = t.dimensiune_ecran;
		strcpy_s(this->sistem_operare, t.sistem_operare);
		strcpy_s(this->tip_procesor, t.tip_procesor);
		this->capacitate_baterie = t.capacitate_baterie;
		this->capacitate_stocare = t.capacitate_stocare;
		strcpy_s(this->culoare, t.culoare);
		this->rezolutie_camera = t.rezolutie_camera;
		strcpy_s(this->cartela, t.cartela);
		return *this;
	}
	void adauga_telefon()
	{
		this->adauga_produse();
		cout << "Tipul Retelei:";
		cin.getline(this->tip_retea, 30);
		cout << endl << "Model:";
		cin.getline(this->model, 30);
		cout << endl << "Dimensiune Ecran:";
		cin >> this->dimensiune_ecran;
		getchar();
		cout << endl << "Sistem de Operare:";
		cin.getline(this->sistem_operare, 30);
		cout << endl << "Tipul Procesorului:";
		cin.getline(this->tip_procesor, 30);
		cout << endl << "Capacitate Baterie:";
		cin >> this->capacitate_baterie;
		getchar();
		cout << endl << "Capacitate Stocare:";
		cin >> this->capacitate_stocare;
		getchar();
		cout << endl << "Culoarea:";
		cin.getline(this->culoare, 30);
		cout << endl << "Rezolutie Camera:";
		cin >> this->rezolutie_camera;
		getchar();
		cout << endl << "Telefonul este Dual Sim? 1=DA/0=NU";
		char unit;
		cin >> unit;
		int ok;
		if (unit == '0' || unit == '1')
			ok = 1;
		else
		{
			ok = 0;
			while (ok == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "Telefonul este Dual Sim? 1=DA/0=NU";
				cin >> unit;
				if (unit == '0' || unit == '1')
					ok = 1;
				else
					ok = 0;
			}
		}
		if (unit == '1')
			strcpy_s(this->cartela, "DUAL");
		else
			strcpy_s(this->cartela, "SINGLE");

	}
	std::ostream& print(std::ostream& output) const {
		return produse::print(output) << "Tip Retea: " << this->tip_retea << endl << "Model: " << this->model << endl << "Dimensiune Ecran  " << this->dimensiune_ecran << endl << " Sistem de operare: " << this->sistem_operare << endl << "Tip Procesor: " << this->tip_procesor << endl << "Capacitate Baterie: " << this->capacitate_baterie << endl << "Capacitate Stocare " << this->capacitate_stocare << endl << "Culoare: " << this->culoare << endl << "Rezolutie Camera: " << this->rezolutie_camera << endl << "Cartela: " << this->cartela << endl;
	};
	void operator+=(int cantitate)
	{
		if (cantitate > 0)
			this->cantitate += cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
	void operator-=(int cantitate)
	{
		if (cantitate > 0 && this->cantitate - cantitate > 0)
			this->cantitate -= cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}

};



class Unitate :
	public produse
{
protected:
	char tip[30] = { "" };
	char sistem_operare[30] = { "" };
	char producator_procesor[30] = { "" };
	char tip_procesor[30] = { "" };
	int capacitate_RAM;
	char tip_stocare[30] = { "" };
	int capacitate_SSD;
	int capacitate_HDD;
	char placa_video[30] = { "" };
	char culoare[30] = { "" };
	char unitate_optica[30];
public:
	Unitate() :produse()
	{

		this->capacitate_RAM = 0;
		this->capacitate_SSD = 0;
		this->capacitate_HDD = 0;

	}
	Unitate(int id, char denumire[100], double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categorie, char tip[30],
		char sistem_operare[30], char producator_procesor[30], char tip_procesor[30], int capacitate_RAM, char tip_stocare[30], int capacitate_SSD, int capacitate_HDD,
		char placa_video[30], char culoare[30], char unit_optica[30]) :produse(id, denumire, pret, cantitate, descriereProdus, firma, categorie)
	{

		strcpy_s(this->tip, tip);

		strcpy_s(this->sistem_operare, sistem_operare);


		strcpy_s(this->producator_procesor, producator_procesor);


		strcpy_s(this->tip_procesor, tip_procesor);


		strcpy_s(this->culoare, culoare);

		if (capacitate_RAM > 0)
			this->capacitate_RAM = capacitate_RAM;
		else
			this->capacitate_RAM = 0;

		strcpy_s(this->tip_stocare, tip_stocare);

		if (strcmp(tip_stocare, "HDD") == 0)
		{

			if (capacitate_HDD > 0)
			{
				this->capacitate_HDD = capacitate_HDD;
				this->capacitate_SSD = 0;
			}
			else
				this->capacitate_HDD = 0;
		}
		else

			if (strcmp(tip_stocare, "SSD") == 0)
			{
				if (capacitate_SSD > 0)
				{
					this->capacitate_HDD = 0;
					this->capacitate_SSD = capacitate_SSD;
				}
				else
					this->capacitate_SSD = capacitate_SSD;
			}
			else
				if (strcmp(tip_stocare, "AMBELE") == 0)
				{
					if (capacitate_HDD < 0 || capacitate_SSD < 0)
					{
						this->capacitate_HDD = 0;
						this->capacitate_SSD = 0;
					}
					else
					{
						this->capacitate_HDD = capacitate_HDD;
						this->capacitate_SSD = capacitate_SSD;
					}
				}

				else
				{
					this->capacitate_HDD = 0;
					this->capacitate_SSD = 0;
				}



		strcpy_s(this->placa_video, placa_video);

		strcpy_s(this->unitate_optica, unit_optica);
	}

	Unitate(Unitate& u) :produse(u)
	{
		strcpy_s(this->tip, u.tip);
		strcpy_s(this->sistem_operare, u.sistem_operare);
		strcpy_s(this->producator_procesor, u.producator_procesor);
		strcpy_s(this->tip_procesor, u.tip_procesor);
		strcpy_s(this->culoare, u.culoare);
		this->capacitate_RAM = u.capacitate_RAM;
		strcpy_s(this->tip_stocare, u.tip_stocare);
		strcpy_s(this->placa_video, u.placa_video);
		this->capacitate_SSD = u.capacitate_SSD;
		this->capacitate_HDD = u.capacitate_HDD;
		strcpy_s(this->unitate_optica, u.unitate_optica);
	}
	Unitate& operator=(Unitate u)
	{
		this->produse::operator=(u);
		strcpy_s(this->tip, u.tip);
		strcpy_s(this->sistem_operare, u.sistem_operare);
		strcpy_s(this->producator_procesor, u.producator_procesor);
		strcpy_s(this->tip_procesor, u.tip_procesor);
		strcpy_s(this->culoare, u.culoare);
		this->capacitate_RAM = u.capacitate_RAM;
		strcpy_s(this->tip_stocare, u.tip_stocare);
		strcpy_s(this->placa_video, u.placa_video);
		this->capacitate_SSD = u.capacitate_SSD;
		this->capacitate_HDD = u.capacitate_HDD;
		strcpy_s(this->unitate_optica, u.unitate_optica);
		return *this;
	}
	void adauga_unitate()
	{
		this->adauga_produse();
		cout << endl << "Tipul Unitatii:   (Home,Practic,Gaming etc.) ";
		cin >> this->tip;
		cout << endl << "Sistem de operare:";
		cin >> this->sistem_operare;
		cout << endl << "Producatorul Procesorului:";
		cin >> this->producator_procesor;
		cout << endl << "Tipul Procesorului:";
		cin >> this->tip_procesor;
		cout << endl;
		cout << "Tip stocare :";
		cout << endl;
		cout << "HDD(1)" << endl << "SSD(2)" << endl << "AMBELE(3)" << endl;
		char a;
		cin >> a;
		int ok2;
		if (a == '1' || a == '2' || a == '3')
			ok2 = 1;
		else
		{
			ok2 = 0;
			while (ok2 == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "HDD(1)" << endl << "SSD(2)" << endl << "AMBELE(3)" << endl;
				cin >> a;
				if (a == '1' || a == '2' || a == '3')
					ok2 = 1;
				else
					ok2 = 0;
			}
		}
		switch (a)
		{
		case '1':
		{
			strcpy_s(this->tip_stocare, "HDD");
			cout << endl << "Capacitate HDD: ";
			cin >> this->capacitate_HDD;
			getchar();
			this->capacitate_SSD = 0;

		}
		break;
		case '2':
		{
			strcpy_s(this->tip_stocare, "SSD");
			cout << endl << "Capacitate SSD :";
			cin >> this->capacitate_SSD;
			getchar();
			this->capacitate_HDD = 0;
		}
		break;
		case '3':
		{
			strcpy_s(this->tip_stocare, "AMBELE");
			cout << endl << "Capacitate HDD: ";
			cin >> this->capacitate_HDD;
			cout << endl << "Capacitate SSD: ";
			cin >> this->capacitate_SSD;
			getchar();
		}

		}

		cout << "Placa Video: ";
		cout << endl << "Dedicata(d)";
		cout << endl << "Integrata(i)";
		char b;
		cin >> b;
		if (b != 'd' && b != 'i')
			while (b != 'd' && b != 'i')
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
				cout << endl << "Dedicata(d)";
				cout << endl;
				cout << "Integrata(i)";
				cout << endl;
				cin >> b;
			}
		switch (b)
		{
		case 'd':
			strcpy_s(this->placa_video, "DEDICATA");
			break;
		case 'i':
			strcpy_s(this->placa_video, "INTEGRATA");
		}
		cout << endl << "Dispune de Unitate Optica?   1=DA/0=NU";
		char unit;
		cin >> unit;
		int ok;
		if (unit == '0' || unit == '1')
			ok = 1;
		else
		{
			ok = 0;
			while (ok == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "Dispune de unitate optica? 1=DA/0=NU";
				cin >> unit;
				if (unit == '0' || unit == '1')
					ok = 1;
				else
					ok = 0;
			}
		}
		if (unit == '1')
			strcpy_s(this->unitate_optica, "DA");
		else
			strcpy_s(this->unitate_optica, "NU");
		cout << endl << "Culoarea Unitatii: ";
		cin >> this->culoare;
		cout << endl << "Capacitatea RAM: ";
		cin >> this->capacitate_RAM;
		getchar();
	}

	std::ostream& print(std::ostream& output) const {
		return produse::print(output) << "Tip: " << this->tip << endl << "Sistem operare: " << this->sistem_operare << endl << "Producator Procesor: " << this->producator_procesor << endl << "Tip Procesor: " << this->tip_procesor << endl << "Tip stocare: " << this->tip_stocare << endl << "Capacitate HDD:  " << this->capacitate_HDD << endl << "Capacitate SSD: " << this->capacitate_SSD << endl << "Placa Video:  " << this->placa_video << endl << "Unitate Optica: " << this->unitate_optica << endl << "Culoare: " << this->culoare << endl << "Capacitate RAM: " << this->capacitate_RAM << endl;
	};
	void operator+=(int cantitate)
	{
		if (cantitate > 0)
			this->cantitate += cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
	void operator-=(int cantitate)
	{
		if (cantitate > 0 && this->cantitate - cantitate > 0)
			this->cantitate -= cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}

};




class audio_video :
	public produse
{
protected:
	char waterproof[30] = { "" };
	char bluetooth[30] = { "" };
	float rezolutie_senzor;
	char culoare[30] = { "" };
public:
	audio_video() :produse()
	{

		this->rezolutie_senzor = 0;
	}
	audio_video(int id, char denumire[100], double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categorie,
		char waterproof[30], char bluetooth[30], float rezolutie_senzor, char culoare[30]) :produse(id, denumire, pret, cantitate, descriereProdus, firma, categorie)
	{
		if (strcmp(waterproof, "DA") == 0 || strcmp(waterproof, "NU") == 0)
			strcpy_s(this->waterproof, waterproof);
		else
			strcpy_s(this->waterproof, "DA");
		if (strcmp(bluetooth, "DA") == 0 || strcmp(bluetooth, "NU") == 0)
			strcpy_s(this->bluetooth, bluetooth);
		else
			strcpy_s(this->bluetooth, "DA");
		if (rezolutie_senzor > 0)
			this->rezolutie_senzor = rezolutie_senzor;
		else
			this->rezolutie_senzor = 0;
		strcpy_s(this->culoare, culoare);
	}
	audio_video(audio_video& av) :produse(av)
	{
		strcpy_s(this->waterproof, av.waterproof);
		strcpy_s(this->bluetooth, av.bluetooth);
		this->rezolutie_senzor = av.rezolutie_senzor;
		strcpy_s(this->culoare, av.culoare);
	}

	audio_video& operator=(audio_video av)
	{
		this->produse::operator=(av);
		strcpy_s(this->waterproof, av.waterproof);
		strcpy_s(this->bluetooth, av.bluetooth);
		this->rezolutie_senzor = av.rezolutie_senzor;
		strcpy_s(this->culoare, av.culoare);
		return *this;
	}
	void adauga_audio_video()
	{
		this->adauga_produse();
		cout << "Este Waterproof? 1=DA/0=NU";
		char unit;
		cin >> unit;
		int ok1;
		if (unit == '0' || unit == '1')
			ok1 = 1;
		else
		{
			ok1 = 0;
			while (ok1 == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "Este Waterproof? 1=DA/0=NU";
				cin >> unit;
				if (unit == '0' || unit == '1')
					ok1 = 1;
				else
					ok1 = 0;
			}
		}
		if (unit == '1')
			strcpy_s(this->waterproof, "DA");
		else
			strcpy_s(this->waterproof, "NU");
		cout << endl << "Are bluetooth? 1=DA/0=NU";
		char unite;
		cin >> unite;
		int ok;
		if (unite == '0' || unite == '1')
			ok = 1;
		else
		{
			ok = 0;
			while (ok == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "Are bluetooth? 1=DA/0=NU";
				cin >> unite;
				if (unite == '0' || unite == '1')
					ok = 1;
				else
					ok = 0;
			}
		}
		if (unite == '1')
			strcpy_s(this->bluetooth, "DA");
		else
			strcpy_s(this->bluetooth, "NU");

		cout << endl << "Rezolutie Senzor:";
		cin >> this->rezolutie_senzor;
		getchar();

		cout << endl << "Culoare:";
		cin.getline(this->culoare, 30);

	}
	std::ostream& print(std::ostream& output) const {
		return produse::print(output) << "Waterprof: " << this->waterproof << endl << "Bluetooth: " << this->bluetooth << endl << "Rezolutie Senzor:  " << this->rezolutie_senzor << endl << "Culoare:  " << this->culoare << endl;
	};
	void operator+=(int cantitate)
	{
		if (cantitate > 0)
			this->cantitate += cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
	void operator-=(int cantitate)
	{
		if (cantitate > 0 && this->cantitate - cantitate > 0)
			this->cantitate -= cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}

};


class Camera :
	public audio_video
{
protected:
	int fps_rez_max;
	char suport[30] = { "" };
	char conect[30] = { "" };
	char rezolutie_filmare[20] = { " " };
public:
	Camera() :audio_video()
	{
		this->fps_rez_max = 0;
	}
	Camera(int id, char denumire[100], char waterproof[30], char bluetooth[30], float rezolutie_senzor, char culoare[50],
		double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categorie, int fps_rez_max, char suport[30],
		char conect[30], char rezolutie_filmare[20]) :audio_video(id, denumire, pret, cantitate, descriereProdus, firma, categorie, waterproof, bluetooth, rezolutie_senzor, culoare)
	{
		if (fps_rez_max > 0)
			this->fps_rez_max = fps_rez_max;
		else
			this->fps_rez_max = 0;
		if (strcmp(suport, "MICROSD") == 0 || strcmp(suport, "SD") == 0)
			strcpy_s(this->suport, suport);
		else
			strcpy_s(this->suport, "SD");
		if (strcmp(conect, "WIFI") == 0 || strcmp(conect, "NFC") == 0)
			strcpy_s(this->conect, conect);
		else
			strcpy_s(this->conect, "NFC");
		strcpy_s(this->rezolutie_filmare, rezolutie_filmare);
	}
	Camera(Camera& c) :audio_video(c)
	{
		this->fps_rez_max = c.fps_rez_max;
		strcpy_s(this->suport, c.suport);
		strcpy_s(this->conect, c.conect);
		strcpy_s(this->rezolutie_filmare, c.rezolutie_filmare);
	}
	Camera& operator=(Camera c)
	{
		this->audio_video::operator=(c);
		this->fps_rez_max = c.fps_rez_max;
		strcpy_s(this->suport, c.suport);
		strcpy_s(this->conect, c.conect);
		strcpy_s(this->rezolutie_filmare, c.rezolutie_filmare);
		return *this;
	}

	void adauga_camera()
	{
		this->adauga_audio_video();
		cout << endl << "FPS la Rezolutie Maxima:";
		cin >> this->fps_rez_max;
		getchar();

		cout << endl << "Alegeti tipul de conectivitate:";
		cout << endl << "WIFI(w)";
		cout << endl << "NFC(n)";
		char w;
		cin >> w;
		if (w != 'w' && w != 'n')
			while (w != 'w' && w != 'n')
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
				cout << endl << "WIFI(w)";
				cout << endl;
				cout << "NFC(n)";
				cout << endl;
				cin >> w;
			}
		if (w == 'w')
			strcpy_s(this->conect, "WIFI");
		else
			if (w == 'n')
				strcpy_s(this->conect, "NFC");
		cout << endl << "Alegeti tipul suportului de inregistrare:";
		cout << endl << "MICROSD(m)";
		cout << endl << "SD(s)";
		char m;
		cin >> m;
		if (m != 'm' && m != 's')
			while (m != 'm' && m != 's')
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
				cout << endl << "MICROSD(m)";
				cout << endl;
				cout << "SD(s)";
				cout << endl;
				cin >> m;
			}
		if (m == 'm')
			strcpy_s(this->suport, "MICROSD");
		else
			if (m == 's')
				strcpy_s(this->suport, "SD");
		getchar();
		cout << endl << "Rezolutie Filmare: ";
		cin.getline(this->rezolutie_filmare, 20);
	}
	std::ostream& print(std::ostream& output) const {
		return audio_video::print(output) << "FPS Rezolutie Maxima: " << this->fps_rez_max << endl << "Conectivitate: " << this->conect << endl << "Suport inregistrare:  " << this->suport << endl << "Rezolutie Filmare:  " << this->rezolutie_filmare << endl;
	};
	void operator+=(int cantitate)
	{
		if (cantitate > 0)
			this->cantitate += cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
	void operator-=(int cantitate)
	{
		if (cantitate > 0 && this->cantitate - cantitate > 0)
			this->cantitate -= cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
};

class Laptop :
	public produse
{
protected:
	char tip[30] = { "" };
	char sistem_operare[30] = { "" };
	char dimensiune_ecran[30] = { "" };
	char rezolutie_ecran[30] = { "" };
	struct procesor
	{
		char producator[30] = { "" };
		char tip[30] = { "" };
	} procesor;
	char culoare[30] = { "" };
	int capacitate_RAM;
	char tip_stocare[30] = { "" };
	int capacitate_stocare;
	float greutate;
	char tastatura_iluminata[30] = { "" };
	char unitate_optica[30] = { "" };
public:
	Laptop() :produse()
	{



		this->capacitate_RAM = 0;
		this->greutate = 0;
		this->capacitate_stocare = 0;


	}
	Laptop(int id, char denumire[100], double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categorie, char tip[30], char sistem_operare[30],
		char dimensiune_ecran[30], char rezolutie_ecran[30], char culoare[30], char tip_procesor[30], char produc_procesor[30], int capacitate_RAM, char tip_stocare[30],
		int capacitate_stocare, float greutate, char tastatura_ilum[30], char unit_optica[30]) :produse(id, denumire, pret, cantitate, descriereProdus, firma, categorie)
	{

		strcpy_s(this->tip, tip);


		strcpy_s(this->sistem_operare, sistem_operare);


		strcpy_s(this->dimensiune_ecran, dimensiune_ecran);


		strcpy_s(this->rezolutie_ecran, rezolutie_ecran);


		strcpy_s(this->culoare, tip);


		strcpy_s(this->procesor.tip, tip_procesor);


		strcpy_s(this->procesor.producator, produc_procesor);

		if (capacitate_stocare > 0)
			this->capacitate_stocare = capacitate_stocare;
		else
			this->capacitate_stocare = 0;

		strcpy_s(this->tip_stocare, tip_stocare);

		if (capacitate_RAM > 0)
			this->capacitate_RAM = capacitate_RAM;
		else
			this->capacitate_RAM = 0;
		if (greutate > 0)
			this->greutate = greutate;
		else
			this->greutate = 0;

		strcpy_s(this->tastatura_iluminata, tastatura_ilum);
		strcpy_s(this->unitate_optica, unit_optica);
	}
	Laptop(Laptop& l) :produse(l)
	{
		strcpy_s(this->tip, l.tip);
		strcpy_s(this->sistem_operare, l.sistem_operare);
		strcpy_s(this->dimensiune_ecran, l.dimensiune_ecran);
		strcpy_s(this->rezolutie_ecran, l.rezolutie_ecran);
		strcpy_s(this->procesor.producator, l.procesor.producator);
		strcpy_s(this->procesor.tip, l.procesor.tip);
		strcpy_s(this->culoare, l.culoare);
		strcpy_s(this->tip_stocare, l.tip_stocare);
		this->capacitate_RAM = l.capacitate_RAM;
		this->greutate = l.greutate;
		this->capacitate_stocare = l.capacitate_stocare;
		strcpy_s(this->tastatura_iluminata, l.tastatura_iluminata);
		strcpy_s(this->unitate_optica, l.unitate_optica);
	}
	Laptop& operator=(Laptop l)
	{
		this->produse::operator=(l);
		strcpy_s(this->tip, l.tip);
		strcpy_s(this->sistem_operare, l.sistem_operare);
		strcpy_s(this->dimensiune_ecran, l.dimensiune_ecran);
		strcpy_s(this->rezolutie_ecran, l.rezolutie_ecran);
		strcpy_s(this->procesor.producator, l.procesor.producator);
		strcpy_s(this->procesor.tip, l.procesor.tip);
		strcpy_s(this->culoare, l.culoare);
		strcpy_s(this->tip_stocare, l.tip_stocare);
		this->capacitate_RAM = l.capacitate_RAM;

		this->greutate = l.greutate;
		this->capacitate_stocare = l.capacitate_stocare;
		strcpy_s(this->tastatura_iluminata, l.tastatura_iluminata);
		strcpy_s(this->unitate_optica, l.unitate_optica);
		return *this;
	}
	void adauga_laptop()
	{
		this->adauga_produse();
		cout << endl << "Tipul laptopului:   (2in1 ,business,home etc.) ";
		cin.getline(this->tip, 30);
		cout << endl << "Sistem de operare:";
		cin.getline(this->sistem_operare, 30);
		cout << endl << "Dimensiunea Ecranului:";
		cin.getline(this->dimensiune_ecran, 30);
		cout << endl << "Rezolutia Ecranului:";
		cin.getline(this->rezolutie_ecran, 30);
		cout << endl << "Producatorul Procesorului: ";
		cin.getline(this->procesor.producator, 30);
		cout << endl << "Tipul Procesorului: ";
		cin.getline(this->procesor.tip, 30);
		cout << endl << "Culoarea Laptopului: ";
		cin.getline(this->culoare, 30);
		cout << endl << "Capacitate RAM: ";
		cin >> this->capacitate_RAM;
		getchar();
		cout << endl << "Tip stocare ";
		cin.getline(this->tip_stocare, 30);
		cout << endl << "Capacitate Stocare: ";
		cin >> this->capacitate_stocare;
		cout << endl << "Greutatea Laptopului: ";
		cin >> this->greutate;
		cout << endl << "Dispune de Unitate Optica?   1=DA/0=NU";
		char unit;
		cin >> unit;
		int ok;
		if (unit == '0' || unit == '1')
			ok = 1;
		else
		{
			ok = 0;
			while (ok == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "Dispune de unitate optica? 1=DA/0=NU";
				cin >> unit;
				if (unit == '0' || unit == '1')
					ok = 1;
				else
					ok = 0;
			}
		}
		if (unit == '1')
			strcpy_s(this->unitate_optica, "DA");
		else
			strcpy_s(this->unitate_optica, "NU");
		cout << endl << "Dispune de Tastatura Iluminata?    1=DA/0=NU ";
		char tast;
		cin >> tast;
		if (tast == '0' || tast == '1')
			ok = 1;
		else
		{
			ok = 0;
			while (ok == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "Dispune de Tastatura Iluminata? 1=DA/0=NU";
				cin >> tast;
				if (tast == '0' || tast == '1')
					ok = 1;
				else
					ok = 0;
			}
		}
		if (tast == '1')
			strcpy_s(this->tastatura_iluminata, "DA");
		else
			strcpy_s(this->tastatura_iluminata, "NU");


	}
	std::ostream& print(std::ostream& output) const {
		return produse::print(output) << "Tip: " << this->tip << endl << "Sistem operare: " << this->sistem_operare << endl << "Dimensiune Ecran: " << this->dimensiune_ecran << endl << "Rezolutie Ecran: " << this->rezolutie_ecran << endl << "Producator Procesor: " << this->procesor.producator << endl << "Tip Procesor: " << this->procesor.tip << endl << "Culoare: " << this->culoare << endl << "Capacitate RAM: " << this->capacitate_RAM << endl << "Tip_stocare: " << this->tip_stocare << endl << "Capacitate Stocare: " << this->capacitate_stocare << endl << "Greutate: " << this->greutate << endl << "Unitate Optica: " << this->unitate_optica << endl << "Tastatura Iluminata: " << this->tastatura_iluminata << endl;
	};
	void operator+=(int cantitate)
	{
		if (cantitate > 0)
			this->cantitate += cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
	void operator-=(int cantitate)
	{
		if (cantitate > 0 && this->cantitate - cantitate > 0)
			this->cantitate -= cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}

};


class monitor :
	public produse
{
protected:
	int rata_refresh;
	char tip_ecran[30] = { "" };
	char touchscreen[30] = { "" };
	int diagonala;
	char rezolutie[30] = { "" };
	char interfata[30] = { "" };
	char boxe_integrate[30] = { "" };
	char culoare[30] = { "" };
	char tip_panou[30] = { "" };
public:
	monitor() :produse()
	{
		this->rata_refresh = 0;

		this->diagonala = 0;



	}
	monitor(int id, char denumire[100], double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categorie, int rata_refresh,
		char touchscreen[30], char ecran[30], int diagonala, char rezolutie[30],
		char interfata[30], char boxe[30], char culoare[30], char tip_panou[30]) :produse(id, denumire, pret, cantitate, descriereProdus, firma, categorie)
	{
		if (rata_refresh > 0)
			this->rata_refresh = rata_refresh;
		else
			rata_refresh = 0;
		if (strcmp("DA", touchscreen) == 0 || strcmp("NU", touchscreen) == 0)
			strcpy_s(this->touchscreen, touchscreen);
		else
			strcpy_s(this->touchscreen, "NU");
		strcpy_s(this->tip_ecran, ecran);
		if (diagonala > 0)
			this->diagonala = diagonala;
		else
			this->diagonala = 0;

		strcpy_s(this->rezolutie, rezolutie);


		strcpy_s(this->interfata, interfata);
		if (strcmp("DA", boxe) == 0 || strcmp("NU", boxe) == 0)
			strcpy_s(this->boxe_integrate, boxe);
		else
			strcpy_s(this->boxe_integrate, "NU");

		strcpy_s(this->culoare, culoare);

		strcpy_s(this->tip_panou, tip_panou);

	}
	monitor(monitor& m)
	{
		this->rata_refresh = m.rata_refresh;
		strcpy_s(this->tip_ecran, m.tip_ecran);
		strcpy_s(this->touchscreen, m.touchscreen);
		this->diagonala = m.diagonala;
		strcpy_s(this->rezolutie, m.rezolutie);
		strcpy_s(this->interfata, m.interfata);
		strcpy_s(this->boxe_integrate, m.boxe_integrate);
		strcpy_s(this->culoare, m.culoare);
		strcpy_s(this->tip_panou, m.tip_panou);
	}
	monitor& operator=(monitor m)
	{
		this->produse::operator=(m);
		this->rata_refresh = m.rata_refresh;
		strcpy_s(this->tip_ecran, m.tip_ecran);
		strcpy_s(this->touchscreen, m.touchscreen);
		this->diagonala = m.diagonala;
		strcpy_s(this->rezolutie, m.rezolutie);
		strcpy_s(this->interfata, m.interfata);
		strcpy_s(this->boxe_integrate, m.boxe_integrate);
		strcpy_s(this->culoare, m.culoare);
		strcpy_s(this->tip_panou, m.tip_panou);
		return *this;
	}
	void adauga_monitor()
	{

		this->adauga_produse();
		cout << "Rata refresh: ";
		cin >> this->rata_refresh;
		getchar();
		cout << endl;
		cout << "Tipul Ecranului:";
		cout << endl;
		cout << "Ecran plat (p)";
		cout << endl;
		cout << "Ecran Curbat (c)";
		char a;
		cin >> a;
		if (a != 'c' && a != 'p')
			while (a != 'c' && a != 'p')
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
				cout << endl << "Ecran plat (p)";
				cout << endl;
				cout << "Ecran Curbat (c)";
				cout << endl;
				cin >> a;
			}
		if (a == 'p')
			strcpy_s(this->tip_ecran, "PLAT");
		if (a == 'c')
			strcpy_s(this->tip_ecran, "CURBAT");

		cout << "Are touchscreen? 1=DA/0=NU";
		char unit;
		cin >> unit;
		int ok;
		if (unit == '0' || unit == '1')
			ok = 1;
		else
		{
			ok = 0;
			while (ok == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "Are touchscreen? 1=DA/0=NU";
				cin >> unit;
				if (unit == '0' || unit == '1')
					ok = 1;
				else
					ok = 0;
			}
		}
		if (unit == '1')
			strcpy_s(this->touchscreen, "DA");
		else
			strcpy_s(this->touchscreen, "NU");
		cout << endl << "Diagonala Ecranului: ";
		cin >> this->diagonala;
		getchar();
		cout << endl << "Rezolutia Ecranului:";
		cin.getline(this->rezolutie, 30);
		cout << endl << "Tipul Interfetei: ";
		cin.getline(this->interfata, 30);
		cout << endl << "Culoarea Monitorului: ";
		cin.getline(this->culoare, 30);
		cout << endl << "Tip Panou  ";
		cin.getline(this->tip_panou, 30);
		cout << endl << "Are boxe integrate? 1=DA/0=NU ";
		char boxe;
		cin >> boxe;
		if (boxe == '0' || boxe == '1')
			ok = 1;
		else
		{
			ok = 0;
			while (ok == 0)
			{
				cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!" << endl;
				cout << "Are boxe integrate? 1=DA/0=NU  ";
				cin >> boxe;
				if (boxe == '0' || boxe == '1')
					ok = 1;
				else
					ok = 0;
			}
		}
		if (boxe == '1')
			strcpy_s(this->boxe_integrate, "DA");
		else
			strcpy_s(this->boxe_integrate, "NU");


	}
	std::ostream& print(std::ostream& output) const {
		return produse::print(output) << "Rata Refresh: " << this->rata_refresh << endl << "Tip Ecran: " << this->tip_ecran << endl << "Touchscreen:  " << this->touchscreen << endl << "Diagonala:  " << this->diagonala << endl << "Rezolutie: " << this->rezolutie << endl << "Interfata: " << this->interfata << endl << "Culoare: " << this->culoare << endl << "Tip Panou: " << this->tip_panou << endl << "Boxe Integrate " << this->boxe_integrate << endl;
	};
	void operator+=(int cantitate)
	{
		if (cantitate > 0)
			this->cantitate += cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
	void operator-=(int cantitate)
	{
		if (cantitate > 0 && this->cantitate - cantitate > 0)
			this->cantitate -= cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}

};




class Aparat :
	public audio_video
{
protected:
	char tip[30] = { "" };
	char format_filmare[30] = { "" };
	float dimensiune_ecran;
public:
	Aparat() :audio_video()
	{
		this->dimensiune_ecran = 0;
	}
	Aparat(
		char tip[30], char format_filmare[30], float dimensiune_ecran, int id, char denumire[100], char waterproof[30], char bluetooth[30], float rezolutie_senzor, char culoare[30],
		double pret, int cantitate, char descriereProdus[200], char firma[50], categorie_produs categorie) :audio_video(id, denumire, pret, cantitate, descriereProdus, firma, categorie, waterproof, bluetooth, rezolutie_senzor, culoare)
	{
		strcpy_s(this->tip, tip);
		strcpy_s(this->format_filmare, format_filmare);
		if (dimensiune_ecran > 0)
			this->dimensiune_ecran = dimensiune_ecran;
		else
			this->dimensiune_ecran = 0;

	}
	Aparat(Aparat& a) :audio_video(a)
	{
		strcpy_s(this->tip, a.tip);
		strcpy_s(this->format_filmare, a.format_filmare);
		this->dimensiune_ecran = a.dimensiune_ecran;
	}
	Aparat& operator=(Aparat a)
	{
		this->audio_video::operator=(a);
		strcpy_s(this->tip, a.tip);
		strcpy_s(this->format_filmare, a.format_filmare);
		this->dimensiune_ecran = a.dimensiune_ecran;
		return *this;
	}
	void adauga_aparat()
	{
		this->adauga_audio_video();
		cout << endl << "Tipul Aparatului:";
		cin.getline(this->tip, 30);
		cout << endl << "Format Filmare:";
		cin.getline(this->format_filmare, 30);
		cout << endl << "Dimensiune Ecran:";
		cin >> this->dimensiune_ecran;
		getchar();

	}
	std::ostream& print(std::ostream& output) const {
		return audio_video::print(output) << "Tipul Aparatului: " << this->tip << endl << "Format Filmare: " << this->format_filmare << endl << "Dimensiune Ecran:  " << this->dimensiune_ecran << endl;
	};
	void operator+=(int cantitate)
	{
		if (cantitate > 0)
			this->cantitate += cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}
	void operator-=(int cantitate)
	{
		if (cantitate > 0 && this->cantitate - cantitate > 0)
			this->cantitate -= cantitate;
		else
			cout << endl << "Nu ati introdus o valoare corecta";
	}

};

void clrscr()
{
	fprintf(stdout, "\033[2J"); 
	fprintf(stdout, "\033[1;1H"); 
	
}

void afisareCos(CosCumparaturi& cos)
{
	clrscr();
	cout << "Output cos de cumparaturi: " << endl;
	cos.VizualizareCos();
}

void adaugaPersoanaFizica(dateF& f)
{
	char numeNou[50];
	char emailNou[50];
	char numarTelefonNou[50];
	char adresaFacturaNou[50];

	persoanaFizica pers;


	clrscr();
	cout << "----Adauga client in baza de date a magazinului----" << endl;
	cout << "Scrieti numele clientului" << endl;
	cin.getline(numeNou, 50);
	pers.setNume(numeNou);

	cout << "  Scrieti emailul clientului" << endl;
	cin.ignore();
	cin.getline(emailNou, 50);
	pers.setEmail(emailNou);

	cout << "  Introduceti numarul de telefon" << endl;
	cin.ignore();
	cin.getline(numarTelefonNou, 50);
	pers.setNumarTelefon(numarTelefonNou);

	cout << "  Introduceti adresa de facturare" << endl;
	cin.ignore();
	cin.getline(adresaFacturaNou, 50);
	pers.setAdresaFactura(adresaFacturaNou);


	f.adaugaPersoanaFizica(pers);

	return;
}


void adaugaInCos(CosCumparaturi& cos)
{
	produse prod;
	int produsIdNou;
	double pretProdusNou;
	int cantitateProdusNou;



	char ch = 'Y';

	clrscr();
	cin.clear();
	cin.ignore();
	do
	{
		cout << "Adauga produs in cos" << endl;
		cout << "Scrie id ul produsului" << endl;
		cin >> produsIdNou;
		prod.setProdusID(produsIdNou);
		cout << "Introdu pretul produsului" << endl;
		cin >> pretProdusNou;
		prod.setPret(pretProdusNou);

		cout << "Introdu cantitatea produsului" << endl;
		cin >> cantitateProdusNou;
		prod.setCantitate(cantitateProdusNou);

		cout << "\t\t Doriti sa mai adaugati un produs in cos ? (y/n)";
		cin >> ch;
		cos.adaugaInCos(prod);
	} while (ch == 'y' || ch == 'Y');
	return;

}
void adaugaPersoanaJuridica(dateJ& j)
{
	char telefonCompanieNou[50];
	char numeFirmaNou[50];
	char CUINou[50];
	char codRegistruComertNou[50];
	char contBancarNou[50];
	char adresaFirmaNou[50];
	persoanaJuridica persJur;


	clrscr();
	cout << "\t Adauga client in baza de date a companiei" << endl;
	cout << "Introduceti telefonul companiei" << endl;
	cin.getline(telefonCompanieNou, 50);
	getchar();
	persJur.setTelefonCompanie(telefonCompanieNou);

	cout << "Adaugati numele firmei d-voastra" << endl;
	cin.getline(numeFirmaNou, 50);
	getchar();
	persJur.setNumeFirma(numeFirmaNou);

	cout << "Introduceti codul de inregistrare unic" << endl;
	cin.getline(CUINou, 50);
	getchar();
	persJur.setCUI(CUINou);

	cout << "Introduceti cod de la registru comert" << endl;
	cin.getline(codRegistruComertNou, 50);
	getchar();
	persJur.setCodRegistruComert(codRegistruComertNou);

	cout << "Introduceti contul bancar de unde sa se realizeze plata" << endl;
	cin.getline(contBancarNou, 50);
	getchar();
	persJur.setContBancar(contBancarNou);
	

	cout << "Introduceti adresa firmei(sediul)" << endl;
	cin.getline(adresaFirmaNou, 50);
	getchar();
	persJur.setAdresaFirma(adresaFirmaNou);

	j.adaugaPersoanaJuridica(persJur);

	return;
}

void adaugaDateClient()
{
	dateF f;
	dateJ j;
	cout << "\t\t f - Daca sunteti persoana fizica" << endl;
	cout << "\t\t j - Daca sunteti persoana juridica" << endl;
	cout << "\t\t quit pentru a iesi" << endl;
	char userChoise;
	cin >> userChoise;
	switch (userChoise)
	{
	case 'quit':
		return;
	case 'f':
		adaugaPersoanaFizica(f);
		break;
	case 'j':
		adaugaPersoanaJuridica(j);
		break;
	}
	return;
}
void stergeDinCos(CosCumparaturi& cos)
{
	clrscr();
	int id;
	char ch = 'Y';

	clrscr();
	cin.clear();
	cin.ignore();
	do
	{
		cout << "\t\t\t Stergere obiect din cos" << endl;
		cout << "\t\t\t Introduceti id-ul produsului pe care-l doriti sters din cos" << endl;
		cin >> id;
		cout << "\t\t Doriti sa mai stergeti un produs din cos ? (y/n)";
		cin >> ch;
		cos.stergeDinCos(id);
	} while (ch == 'y' || ch == 'Y');
	return;
}

void vizualizare_produse()
{
	int y = alegere_categorie();
	if (y == 1)
	{
		system("CLS");
		Laptop l;
		citeste_fis(l, "laptop.dat");

	}
	else
		if (y == 2)
		{
			system("CLS");
			cout << "Doriti sa vizualizati unitati sau monitoare PC?";
			cout << endl << endl;
			cout << "Pentru Unitate apasati tasta u";
			cout << endl;
			cout << "Pentru Monitor apasati tasta m";
			char x;
			cin >> x;
			if (x != 'u' && x != 'm')
				while (x != 'u' && x != 'm')
				{
					cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
					cout << endl << " Pentru Unitate apasati tasta u";
					cout << endl;
					cout << "Pentru Monitor apasati tasta m";
					cout << endl;
					cin >> x;
				}
			if (x == 'm')
			{
				system("CLS");
				monitor m;
				citeste_fis(m, "monitor.dat");
			}
			else
			{
				system("CLS");
				Unitate u;
				citeste_fis(u, "unitate.dat");
			}
		}
		else
			if (y == 3)
			{
				system("CLS");
				telefon t;
				citeste_fis(t, "telefon.dat");

			}
			else
				if (y == 4)
				{
					system("CLS");
					tableta t;
					citeste_fis(t, "tableta.dat");

				}
				else
					if (y == 5)
					{
						system("CLS");
						cout << "Doriti sa vizualizati aparate sau camere video?";
						cout << endl << endl;
						cout << "Pentru Aparate apasati tasta a";
						cout << endl;
						cout << "Pentru Camere apasati tasta c";
						char x;
						cin >> x;
						if (x != 'a' && x != 'c')
							while (x != 'a' && x != 'c')
							{
								cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
								cout << endl << " Pentru Aparate apasati tasta a";
								cout << endl;
								cout << "Pentru Camere apasati tasta c";
								cout << endl;
								cin >> x;
							}
						if (x == 'a')
						{
							system("CLS");
							Aparat a;
							citeste_fis(a, "aparat.dat");

						}
						else
						{
							system("CLS");
							Camera c;
							citeste_fis(c, "camera.dat");
						}

					}
	cout << endl;


}


void TrimiteComanda(string nume_fisier, CosCumparaturi cos, persoanaFizica fizic)
{
	 
	ofstream f(nume_fisier, ios::out | ios::app);
	if (f.is_open())
	{
		for (unsigned i = 0; i < cos.produseCos.size(); i++)
		{
			f <<endl<< "ID Produs: " << cos.produseCos[i].getProdusID() << endl << "Cantitate: " << cos.produseCos[i].getCantitate() << endl;
		}
		double pret = cos.getPretulCosului();
		f << endl;
		f << "Valoarea Totala a comenzii: " << pret << " RON" << endl;
		f <<"Nume: "<< fizic.nume << endl <<"Email:"<< fizic.email << endl <<"Adresa:"<< fizic.adresaFactura << endl <<"Numar:"<< fizic.numarTelefon;
		f.close();

	}
	else
	{
		cout << "Unable to open file" << endl;
	}
	
	
	return;
}
void TrimiteComanda(string nume_fisier, CosCumparaturi cos, persoanaJuridica jur)
{
	ofstream f(nume_fisier, ios::out | ios::app);
	if (f.is_open())
	{
		for (unsigned i = 0; i < cos.produseCos.size(); i++)
		{
			f <<endl<< "ID Produs: " << cos.produseCos[i].getProdusID() << endl << "Cantitate: " << cos.produseCos[i].getCantitate() << endl;
		}
		double pret = cos.getPretulCosului();
		f << endl;
		f << "Valoarea Totala a comenzii: " << pret << " RON" << endl;
		f <<"Adresa Firmei: "<< jur.getAdresaFirma()<< endl <<"Cod Registru Comert"<< jur.getCodRegistruComert() << endl <<"Contul Bancar: "<< jur.getContBancar() << endl <<"CUI firma: "<< jur.getCUI()<<endl<<"Nume Firma: "<<jur.getNumeFirma()<<endl<<"Telefon Companie:"<<jur.getTelefonCompanie();
		f.close();

	}
	else
	{
		cout << "Unable to open file" << endl;
	}


	return;
}

void AfiseazaMeniu()
{
	char userChoise;
	CosCumparaturi cos;
	persoanaFizica persFizica;
	persoanaJuridica persJuridica;
	produse prod;
	dateF f;
	dateJ j;
	do
	{
		cout << "\t\t\t---------------------------MENIU CLIENT---------------------------" << endl;
		cout << "\t\t\t a - Vizualizarea produselor din magazin " << endl;
		cout << "\t\t\t b - Vizualizarea elementelor din cos" << endl;
		cout << "\t\t\t c - Adaugarea produselor in cos " << endl;
		cout << "\t\t\t d - Scoaterea produselor din cosul electronic " << endl;
		cout << "\t\t\t e - Completarea datelor clientului " << endl;
		cout << "\t\t\t f - Trimiterea comenzii cu produsele din cos " << endl;
		cout << "\t\t\t q - Pentru a iesi " << endl;

		do
		{
			cout << "\t\t\t Alegeti o optiune din cele prezentare anterior: " << endl;
			cin >> userChoise;
			if (cin.fail())
			{
				cin.ignore();
				cin.clear();
				return;
			}


		} while (userChoise != 'a' && userChoise != 'b' && userChoise != 'c' && userChoise != 'd' && userChoise != 'e' && userChoise != 'f' && userChoise != 'q');
		switch (userChoise)
		{
		case 'q':
			return;
		case 'a':
			vizualizare_produse();
			break;
		case 'b':
			afisareCos(cos);
			break;
		case 'c':
			adaugaInCos(cos);
			break;
		case 'd':
			stergeDinCos(cos);
			break;
		case 'e':
			adaugaDateClient();
			break;
		case 'f':
		{
			cout << endl << "Sunteti persoana fizica sau juridica?"<<endl;
			cout << "Persoana fizica (f)";
			cout << endl;
			cout << "Persoana Juridica (j)";
			char a;
			cin >> a;
			getchar();
			if (a == 'f')
			{
				persFizica.adauga_fizic();
				TrimiteComanda("Comandafiz1.txt", cos, persFizica);
			}
			else
			if (a == 'j')
			{
				persJuridica.adauga_jur();
				TrimiteComanda("Comandajur1.txt", cos, persJuridica);
			}
		}
			break;
		
		}
	} while (userChoise != 'q');
	return;
}

int main()
{
	
	bun_venit();
	cout << endl << "APASATI ENTER PENTRU A CONTINUA" << endl;
	getchar();
	int y = alegere_utilizator();
	if (y == 1)
	{
		AfiseazaMeniu();

	}
	if (y == 2)
	{
		cout << setw(20) << "********** Bine ati venit,domnule administrator!**********" << endl;
		Sleep(20);
		int ok = 1;
		while (ok == 1)
		{
			int optiune = alegere_operatie();
			if (optiune == 1)
			{
				produse p;
				int alegere = alegere_categorie();
				categorie_produs categ;
				switch (alegere)
				{
				case 1:
				{
					categ = categorie_produs::LAPTOP;
					p.setCategorieProdus(categ);
					int o1 = nou_sau_vechi();
					if (o1 == 1)
					{

						Laptop l;
						l.adauga_laptop();
						adauga_fisier(l, "laptop.dat");

					}
					else
					{
						cout << endl << "Dati id-ul dupa care doriti sa modificati" << endl;
						int idd;
						cin >> idd;
						Laptop l;
						Repository<Laptop> r("laptop.dat");
						if (r.read(idd).getProdusID() == 0)
							cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";

						cin >> idd;
						while (r.read(idd).getProdusID() == 0)
						{
							cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";
							cin >> idd;
						}
						int ads = adaug_scad();
						if (ads == 1)
						{
							int cant;
							cout << endl << "Dati cantititatea de adaugat: ";
							cin >> cant;
							Laptop l;
							Repository<Laptop> r("laptop.dat");
							r.read(idd) += cant;

						}
						else
						{
							int cant;
							cout << endl << "Dati cantititatea de scazut: ";
							cin >> cant;
							Laptop l;
							Repository<Laptop> r("laptop.dat");
							r.read(idd) -= cant;
						}


					}

				}
				break;
				case 2:
				{
					categ = categorie_produs::DESKTOP;
					p.setCategorieProdus(categ);
					system("CLS");
					cout << "Doriti sa introduceti o unitate sau un monitor PC?";
					cout << endl << endl;
					cout << "Pentru Unitate apasati tasta u";
					cout << endl;
					cout << "Pentru Monitor apasati tasta m";
					char x;
					cin >> x;
					if (x != 'u' && x != 'm')
						while (x != 'u' && x != 'm')
						{
							cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
							cout << endl << " Pentru Unitate apasati tasta u";
							cout << endl;
							cout << "Pentru Monitor apasati tasta m";
							cout << endl;
							cin >> x;
						}
					if (x == 'u')
					{
						int o1 = nou_sau_vechi();
						if (o1 == 1)
						{
							Unitate u;
							u.adauga_unitate();
							adauga_fisier(u, "unitate.dat");
						}
						else
						{
							cout << endl << "Dati id-ul dupa care doriti sa modificati" << endl;
							int idd;
							cin >> idd;
							Unitate u;
							Repository<Unitate> r("unitate.dat");
							if (r.read(idd).getProdusID() == 0)
								cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";

							cin >> idd;
							while (r.read(idd).getProdusID() == 0)
							{
								cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";
								cin >> idd;
							}
							int ads = adaug_scad();
							if (ads == 1)
							{
								int cant;
								cout << endl << "Dati cantititatea de adaugat: ";
								cin >> cant;
								Unitate l;
								Repository<Unitate> r("unitate.dat");
								r.read(idd) += cant;

							}
							else
							{
								int cant;
								cout << endl << "Dati cantititatea de scazut: ";
								cin >> cant;
								Unitate l;
								Repository<Unitate> r("unitate.dat");
								r.read(idd) -= cant;
							}


						}
					}
					else
						if (x == 'm')
						{
							int o1 = nou_sau_vechi();
							if (o1 == 1)
							{
								monitor m;
								m.adauga_monitor();
								adauga_fisier(m, "monitor.dat");
							}
							else
							{
								cout << endl << "Dati id-ul dupa care doriti sa modificati" << endl;
								int idd;
								cin >> idd;
								monitor l;
								Repository<monitor> r("monitor.dat");
								if (r.read(idd).getProdusID() == 0)
									cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";

								cin >> idd;
								while (r.read(idd).getProdusID() == 0)
								{
									cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";
									cin >> idd;
								}
								int ads = adaug_scad();
								if (ads == 1)
								{
									int cant;
									cout << endl << "Dati cantititatea de adaugat: ";
									cin >> cant;
									monitor l;
									Repository<monitor> r("monitor.dat");
									r.read(idd) += cant;

								}
								else
								{
									int cant;
									cout << endl << "Dati cantititatea de scazut: ";
									cin >> cant;
									monitor l;
									Repository<monitor> r("monitor.dat");
									r.read(idd) -= cant;
								}


							}
						}

				}
				break;
				case 3:
				{
					categ = categorie_produs::TELEFON;
					p.setCategorieProdus(categ);
					system("CLS");
					int o1 = nou_sau_vechi();
					if (o1 == 1)
					{
						telefon t;
						t.adauga_telefon();
						adauga_fisier(t, "telefon.dat");
					}
					else
					{
						cout << endl << "Dati id-ul dupa care doriti sa modificati" << endl;
						int idd;
						cin >> idd;
						telefon l;
						Repository<telefon> r("telefon.dat");
						if (r.read(idd).getProdusID() == 0)
							cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";

						cin >> idd;
						while (r.read(idd).getProdusID() == 0)
						{
							cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";
							cin >> idd;
						}
						int ads = adaug_scad();
						if (ads == 1)
						{
							int cant;
							cout << endl << "Dati cantititatea de adaugat: ";
							cin >> cant;
							telefon l;
							Repository<telefon> r("telefon.dat");
							r.read(idd) += cant;

						}
						else
						{
							int cant;
							cout << endl << "Dati cantititatea de scazut: ";
							cin >> cant;
							telefon l;
							Repository<telefon> r("telefon.dat");
							r.read(idd) -= cant;
						}


					}
				}
				break;
				case 4:
				{
					categ = categorie_produs::TABLETA;
					p.setCategorieProdus(categ);
					system("CLS");
					int o1 = nou_sau_vechi();
					if (o1 == 1)
					{
						tableta ta;
						ta.adauga_tableta();
						adauga_fisier(ta, "tableta.dat");
					}
					else
					{
						cout << endl << "Dati id-ul dupa care doriti sa modificati" << endl;
						int idd;
						cin >> idd;
						tableta l;
						Repository<tableta> r("tableta.dat");
						if (r.read(idd).getProdusID() == 0)
							cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";

						cin >> idd;
						while (r.read(idd).getProdusID() == 0)
						{
							cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";
							cin >> idd;
						}
						int ads = adaug_scad();
						if (ads == 1)
						{
							int cant;
							cout << endl << "Dati cantititatea de adaugat: ";
							cin >> cant;
							tableta l;
							Repository<tableta> r("tableta.dat");
							r.read(idd) += cant;

						}
						else
						{
							int cant;
							cout << endl << "Dati cantititatea de scazut: ";
							cin >> cant;
							tableta l;
							Repository<tableta> r("tableta.dat");
							r.read(idd) -= cant;
						}


					}
				}
				break;
				case 5:
				{
					categ = categorie_produs::AUDIO_VIDEO;
					p.setCategorieProdus(categ);
					system("CLS");
					cout << "Doriti sa introduceti o Camera Video sau un Aparat?";
					cout << endl << endl;
					cout << "Pentru Camera apasati tasta c";
					cout << endl;
					cout << "Pentru Aparat apasati tasta a";
					char x;
					cin >> x;
					if (x != 'c' && x != 'a')
						while (x != 'c' && x != 'a')
						{
							cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
							cout << endl << "Pentru Camera apasati tasta c";
							cout << endl;
							cout << "Pentru Aparat apasati tasta a";
							cout << endl;
							cin >> x;
						}
					if (x == 'c')
					{
						int o1 = nou_sau_vechi();
						if (o1 == 1)
						{
							Camera c;
							c.adauga_camera();
							adauga_fisier(c, "camera.dat");
						}
						else
						{
							cout << endl << "Dati id-ul dupa care doriti sa modificati" << endl;
							int idd;
							cin >> idd;
							Camera l;
							Repository<Camera> r("camera.dat");
							if (r.read(idd).getProdusID() == 0)
								cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";

							cin >> idd;
							while (r.read(idd).getProdusID() == 0)
							{
								cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";
								cin >> idd;
							}
							int ads = adaug_scad();
							if (ads == 1)
							{
								int cant;
								cout << endl << "Dati cantititatea de adaugat: ";
								cin >> cant;
								Camera l;
								Repository<Camera> r("camera.dat");
								r.read(idd) += cant;

							}
							else
							{
								int cant;
								cout << endl << "Dati cantititatea de scazut: ";
								cin >> cant;
								Camera l;
								Repository<Camera> r("camera.dat");
								r.read(idd) -= cant;
							}


						}
					}
					else
						if (x == 'a')
						{
							int o1 = nou_sau_vechi();
							if (o1 == 1)
							{
								Aparat a;
								a.adauga_aparat();
								adauga_fisier(a, "aparat.dat");
							}
							else
							{
								cout << endl << "Dati id-ul dupa care doriti sa modificati" << endl;
								int idd;
								cin >> idd;
								Aparat l;
								Repository<Aparat> r("aparat.dat");
								if (r.read(idd).getProdusID() == 0)
									cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";

								cin >> idd;
								while (r.read(idd).getProdusID() == 0)
								{
									cout << endl << "Nu exista produs cu acest id!" << "Incercati din nou!";
									cin >> idd;
								}
								int ads = adaug_scad();
								if (ads == 1)
								{
									int cant;
									cout << endl << "Dati cantititatea de adaugat: ";
									cin >> cant;
									Aparat l;
									Repository<Aparat> r("aparat.dat");
									r.read(idd) += cant;

								}
								else
								{
									int cant;
									cout << endl << "Dati cantititatea de scazut: ";
									cin >> cant;
									Aparat l;
									Repository<Aparat> r("aparat.dat");
									r.read(idd) -= cant;
								}


							}
						}

				}
				break;
				}
			}

			if (optiune == 2) {
				//stergere produs
				produse p;
				int alegere = alegere_categorie();
				categorie_produs categ;

				switch (alegere)
				{
				case 1:
				{
					categ = categorie_produs::LAPTOP;

					cout << "Introduceti id-ul laptopului pe care doriti sa il stergeti: ";
					int id;
					cin >> id;
					Repository<Laptop> r("laptop.dat");
					r.stergere_produs(id);

					cout << "Laptopul a fost sters de pe stoc cu succes!" << endl;
				}
				break;

				case 2:
				{
					categ = categorie_produs::DESKTOP;

					cout << "Doriti sa editati o unitate sau un monitor PC?";
					cout << endl << endl;
					cout << "Pentru Unitate apasati tasta u";
					cout << endl;
					cout << "Pentru Monitor apasati tasta m";
					char x;
					cin >> x;
					if (x != 'u' && x != 'm')
						while (x != 'u' && x != 'm')
						{
							cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
							cout << endl << " Pentru Unitate apasati tasta u";
							cout << endl;
							cout << "Pentru Monitor apasati tasta m";
							cout << endl;
							cin >> x;
						}
					if (x == 'u')
					{
						cout << "Introduceti id-ul unitatii pe care doriti sa o stergeti: ";
						int id;
						cin >> id;
						Repository<Unitate> r("unitate.dat");
						r.stergere_produs(id);

						cout << "Unitatea a fost stearsa de pe stoc cu succes!" << endl;
					}
					else
						if (x == 'm')
						{
							cout << "Introduceti id-ul monitorului pe care doriti sa il stergeti: ";
							int id;
							cin >> id;
							Repository<monitor> r("monitor.dat");
							r.stergere_produs(id);

							cout << "Monitorul a fost sters de pe stoc cu succes!" << endl;
						}
				}
				break;

				case 3:
				{
					categ = categorie_produs::TELEFON;

					cout << "Introduceti id-ul telefonului pe care doriti sa il stergeti: ";
					int id;
					cin >> id;
					Repository<telefon> r("telefon.dat");
					r.stergere_produs(id);

					cout << "Telefonul a fost sters de pe stoc cu succes!" << endl;
				}
				break;

				case 4:
				{
					categ = categorie_produs::TABLETA;

					cout << "Introduceti id-ul tabletei pe care doriti sa o stergeti: ";
					int id;
					cin >> id;
					Repository<tableta> r("telefon.dat");
					r.stergere_produs(id);

					cout << "Tableta a fost stearsa de pe stoc cu succes!" << endl;
				}
				break;

				case 5:
				{
					categ = categorie_produs::AUDIO_VIDEO;

					cout << "Doriti sa introduceti o Camera Video sau un Aparat?";
					cout << endl << endl;
					cout << "Pentru Camera apasati tasta c";
					cout << endl;
					cout << "Pentru Aparat apasati tasta a";
					char x;
					cin >> x;
					if (x != 'c' && x != 'a')
						while (x != 'c' && x != 'a')
						{
							cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
							cout << endl << "Pentru Camera apasati tasta c";
							cout << endl;
							cout << "Pentru Aparat apasati tasta a";
							cout << endl;
							cin >> x;
						}
					if (x == 'c')
					{
						cout << "Introduceti id-ul camerei pe care doriti sa o stergeti: ";
						int id;
						cin >> id;
						Repository<Camera> r("camera.dat");
						r.stergere_produs(id);

						cout << "Camera a fost stearsa de pe stoc cu succes!" << endl;
					}
					else
						if (x == 'a')
						{
							cout << "Introduceti id-ul aparatului pe care doriti sa il stergeti: ";
							int id;
							cin >> id;
							Repository<Aparat> r("aparat.dat");
							r.stergere_produs(id);

							cout << "Aparatul a fost sters de pe stoc cu succes!" << endl;
						}
				}
				break;
				}
			}

			if (optiune == 3) {
				//modificare produs
				produse p;
				int alegere = alegere_categorie();
				categorie_produs categ;

				switch (alegere)
				{
				case 1:
				{
					categ = categorie_produs::LAPTOP;

					cout << "Introduceti id-ul laptopului pe care doriti sa il editati: " << endl;

					
					int id;
					cin >> id;
					
					Repository<Laptop> r("laptop.dat");

					if (r.read(id).getProdusID() == 0)
						cout << "Nu exista produs cu acest id!" << "Incercati din nou!" << endl;
					else
					{
						Laptop l;
						l.adauga_laptop();
						r.editare_produs(l);
						cout << "Laptopul a fost editat cu succes!" << endl;
					}
				}
				break;

				case 2:
				{
					categ = categorie_produs::DESKTOP;

					cout << "Doriti sa editati o unitate sau un monitor PC?";
					cout << endl << endl;
					cout << "Pentru Unitate apasati tasta u";
					cout << endl;
					cout << "Pentru Monitor apasati tasta m";
					char x;
					cin >> x;
					if (x != 'u' && x != 'm')
						while (x != 'u' && x != 'm')
						{
							cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
							cout << endl << " Pentru Unitate apasati tasta u";
							cout << endl;
							cout << "Pentru Monitor apasati tasta m";
							cout << endl;
							cin >> x;
						}
					if (x == 'u')
					{
						cout << "Introduceti id-ul unitatii pe care doriti sa o editati: " << endl;

						
						int id;
						cin >> id;
						Repository<Unitate> r("unitate.dat");

						if (r.read(id).getProdusID() == 0)
							cout << "Nu exista produs cu acest id!" << "Incercati din nou!" << endl;
						else
						{
							Unitate u;
							u.adauga_unitate();
							r.editare_produs(u);
							cout << "Unitatea a fost editata cu succes!" << endl;
						}
					}
					else
						if (x == 'm')
						{
							cout << "Introduceti id-ul monitorului pe care doriti sa il editati: " << endl;

							
							int id;
							cin >> id;
							Repository<monitor> r("monitor.dat");

							if (r.read(id).getProdusID() == 0)
								cout << "Nu exista produs cu acest id!" << "Incercati din nou!" << endl;
							else
							{
								monitor m;
								m.adauga_monitor();
								r.editare_produs(m);
								cout << "Monitorul a fost editat cu succes!" << endl;
							}
						}
				}
				break;

				case 3:
				{
					categ = categorie_produs::TELEFON;

					cout << "Introduceti id-ul telefonului pe care doriti sa il editati: " << endl;
					int id;
					cin >> id;
					
					Repository<telefon> r("telefon.dat");

					if (r.read(id).getProdusID() == 0)
						cout << "Nu exista produs cu acest id!" << "Incercati din nou!" << endl;
					else
					{
						telefon t;
						t.adauga_telefon();
						r.editare_produs(t);

						cout << "Telefonul a fost editat cu succes!" << endl;
					}
				}
				break;

				case 4:
				{
					categ = categorie_produs::TABLETA;

					cout << "Introduceti id-ul tabletei pe care doriti sa o editati: " << endl;

					
					int id;
					cin >> id;
					Repository<tableta> r("telefon.dat");

					if (r.read(id).getProdusID() == 0)
						cout << "Nu exista produs cu acest id!" << "Incercati din nou!" << endl;
					else
					{
						tableta tab;
						tab.adauga_tableta();
						r.editare_produs(tab);

						cout << "Tableta a fost editata cu succes!" << endl;
					}
				}
				break;

				case 5:
				{
					categ = categorie_produs::AUDIO_VIDEO;

					cout << "Doriti sa introduceti o Camera Video sau un Aparat?";
					cout << endl << endl;
					cout << "Pentru Camera apasati tasta c";
					cout << endl;
					cout << "Pentru Aparat apasati tasta a";
					char x;
					cin >> x;
					if (x != 'c' && x != 'a')
						while (x != 'c' && x != 'a')
						{
							cout << "\t \t Ati introdus o valoare gresita!\t\t Incercati din nou!";
							cout << endl << "Pentru Camera apasati tasta c";
							cout << endl;
							cout << "Pentru Aparat apasati tasta a";
							cout << endl;
							cin >> x;
						}
					if (x == 'c')
					{
						cout << "Introduceti id-ul camerei pe care doriti sa o editati: " << endl;

						
						int id;
						cin >> id;
						Repository<Camera> r("camera.dat");

						if (r.read(id).getProdusID() == 0)
							cout << "Nu exista produs cu acest id!" << "Incercati din nou!" << endl;
						else
						{
							Camera c;
							c.adauga_camera();
							r.editare_produs(c);

							cout << "Camera a fost editata cu succes!" << endl;
						}
					}
					else
						if (x == 'a')
						{
							cout << "Introduceti id-ul aparatului pe care doriti sa il editati: " << endl;

							
							int id;
							cin >> id;
							Repository<Aparat> r("aparat.dat");

							if (r.read(id).getProdusID() == 0)
								cout << "Nu exista produs cu acest id!" << "Incercati din nou!" << endl;
							else
							{
								Aparat a;
								a.adauga_aparat();
								r.editare_produs(a);

								cout << "Aparatul a fost editat cu succes!" << endl;
							}
						}
				}
				break;
				}

				
			}
			if (optiune == 4) {

				cout << endl << "Sunteti persoana fizica sau juridica?" << endl;
				cout << "Persoana fizica (f)";
				cout << endl;
				cout << "Persoana Juridica (j)";
				char a;
				cin >> a;
				if (a == 'f')
				{
					
					ifstream infile("Comandafiz1.txt");
					ofstream outfile("Comandafizica.txt");
					string content = "";
					int i;

					for (i = 0; infile.eof() != true; i++) 
						content += infile.get();

					i--;
					content.erase(content.end() - 1);     

					infile.close();

					outfile << content;                 
					outfile.close();
					cout << endl<<"Raportul a fost realizat in fisierul Comandafizica.txt"<<endl;

				}
				else
					if (a == 'j')
					{
						ifstream infile("Comandajur1.txt");
						ofstream outfile("ComandaJuridica.txt");
						string content = "";
						int i;

						for (i = 0; infile.eof() != true; i++)
							content += infile.get();

						i--;
						content.erase(content.end() - 1);

						infile.close();

						outfile << content;
						outfile.close();
						cout << endl << "Raportul a fost realizat in fisierul ComandaJuridica.txt" << endl;
						
					}	

			}

			if (optiune == 5) {
				break;
			}

		}
	}
	

	return 0;
}