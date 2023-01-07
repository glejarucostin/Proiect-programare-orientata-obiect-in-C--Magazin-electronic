#include "persoanaFizica.h"

persoanaFizica::persoanaFizica()
{

	
}

persoanaFizica::persoanaFizica(char nume[50], char email[50], char numarTelefon[50], char adresaFactura[50])
{
	if (nume != " ")
		strcpy_s(this->nume,nume);
	
	if (email != " ")
		strcpy_s(this->email,email);
	

	if (numarTelefon != " ")
		strcpy_s(this->numarTelefon,numarTelefon);


	if (adresaFactura != " ")
		strcpy_s(this->adresaFactura,adresaFactura);
	


}

persoanaFizica::persoanaFizica(const persoanaFizica& p)
{
	
	strcpy_s(this->nume, p.nume);
	strcpy_s(this->email,p.email);
	strcpy_s(this->numarTelefon,p.numarTelefon);
	strcpy_s(this->adresaFactura,p.adresaFactura);
}

persoanaFizica::~persoanaFizica()
{

}

void persoanaFizica::operator=(persoanaFizica pf)
{
	strcpy_s(this->nume, pf.nume);
	strcpy_s(this->email, pf.email);
	strcpy_s(this->numarTelefon ,pf.numarTelefon);
	strcpy_s(this->adresaFactura ,pf.adresaFactura);
}


char * persoanaFizica::getNume()
{
	return nume;
}

void persoanaFizica::setNume(const char* nume)
{
	if (nume != " ")
		strcpy_s(this->nume,nume);
}

char* persoanaFizica::getEmail()
{
	return email;
}

void persoanaFizica::setEmail(const char* email)
{
	if (email != " ")
		strcpy_s(this->email ,email);
}

char* persoanaFizica::getNumarTelefon()
{
	return numarTelefon;
}

void persoanaFizica::setNumarTelefon(const char* numarTelefon)
{
	if (numarTelefon != " ")
		strcpy_s(this->numarTelefon,numarTelefon);
}

char* persoanaFizica::getAdresa()
{
	return adresaFactura;
}

void persoanaFizica::setAdresaFactura(const char* adresaFactura)
{
	if (adresaFactura != " ")
		strcpy_s(this->adresaFactura ,adresaFactura);

}




