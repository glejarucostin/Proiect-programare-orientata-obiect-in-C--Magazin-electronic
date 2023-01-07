
#ifndef persoanaFizica_h
#define persoanaFizica_h
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
class persoanaFizica 
{
public:
	vector<persoanaFizica>f;
	char nume[50]= { "" };
	char email[50]= { "" };
	char numarTelefon[50]= { "" };
	char adresaFactura[50]= { "" };

	persoanaFizica();
	persoanaFizica(char nume[50], char email[50], char numarTelefon[50], char adresaFactura[50]);
	persoanaFizica(const persoanaFizica& p);

	~persoanaFizica();

	void operator=(persoanaFizica pf);


	char* getNume();
	void setNume(const char* nume);
	char* getEmail();
	void setEmail(const char* email);
	char* getNumarTelefon();
	void setNumarTelefon(const char* numarTelefon);
	char* getAdresa();
	void setAdresaFactura(const char* adresaFactura);
	void adauga_fizic()
	{


		cout << "Scrieti numele clientului" << endl;
		cin.getline(this->nume, 50);
		fflush(stdin);

		cout << "  Scrieti emailul clientului" << endl;
		cin.getline(this->email, 50);
		fflush(stdin);

		cout << "  Introduceti numarul de telefon" << endl;
		cin.getline(this->numarTelefon, 50);
		fflush(stdin);

		cout << "  Introduceti adresa de facturare" << endl;
		cin.getline(this->adresaFactura, 50);
		fflush(stdin);

	}

	void afis()
	{
		cout << this->email;
		cout << this->nume;
	}
};
#endif /*persoanaFizica*/
