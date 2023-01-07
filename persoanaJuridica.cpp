#include "persoanaJuridica.h"
#include "persoanaJuridica.h"

persoanaJuridica::persoanaJuridica()
{

}

persoanaJuridica::persoanaJuridica(char telefonCompanie[50], char numeFirma[50], char CUI[50], char codRegistruComert[50], char contBancar[50], char adresaFirma[50])
{
	if (telefonCompanie != " ")
		strcpy_s(this->telefonCompanie, telefonCompanie);


	if (numeFirma != " ")
		strcpy_s(this->numeFirma, numeFirma);


	if (CUI != " ")
		strcpy_s(this->CUI, CUI);

	if (codRegistruComert != " ")
		strcpy_s(this->codRegistruComert, codRegistruComert);


	if (contBancar != " ")
		strcpy_s(this->contBancar, contBancar);


	if (adresaFirma != " ")
		strcpy_s(this->adresaFirma, adresaFirma);

}

persoanaJuridica::persoanaJuridica(const persoanaJuridica& pj)
{
	strcpy_s(telefonCompanie, pj.telefonCompanie);
	strcpy_s(numeFirma, pj.numeFirma);
	strcpy_s(CUI, pj.CUI);
	strcpy_s(codRegistruComert, pj.codRegistruComert);
	strcpy_s(contBancar, pj.contBancar);
	strcpy_s(adresaFirma, pj.adresaFirma);
}


persoanaJuridica::~persoanaJuridica()
{

}

void persoanaJuridica::operator=(persoanaJuridica pj)
{
	strcpy_s(this->telefonCompanie, pj.telefonCompanie);
	strcpy_s(this->numeFirma, pj.numeFirma);
	strcpy_s(this->CUI, pj.CUI);
	strcpy_s(this->codRegistruComert, pj.codRegistruComert);
	strcpy_s(this->contBancar, pj.contBancar);
	strcpy_s(this->adresaFirma, pj.adresaFirma);
}

char* persoanaJuridica::getTelefonCompanie()
{
	return telefonCompanie;
}

void persoanaJuridica::setTelefonCompanie(const char* telefonCompanie)
{
	if (telefonCompanie != " ")
		strcpy_s(this->telefonCompanie, telefonCompanie);
}

char* persoanaJuridica::getNumeFirma()
{
	return numeFirma;
}

void persoanaJuridica::setNumeFirma(const char* numeFirma)
{
	if (numeFirma != " ")
		strcpy_s(this->numeFirma, numeFirma);
}
char* persoanaJuridica::getCUI()
{
	return CUI;
}

void persoanaJuridica::setCUI(const char* CUI)
{
	if (CUI != " ")
		strcpy_s(this->CUI, CUI);
}

char* persoanaJuridica::getCodRegistruComert()
{
	return codRegistruComert;
}

void persoanaJuridica::setCodRegistruComert(const char* codRegistruComert)
{
	if (codRegistruComert != " ")
		strcpy_s(this->codRegistruComert, codRegistruComert);
}

char* persoanaJuridica::getContBancar()
{
	return contBancar;
}

void persoanaJuridica::setContBancar(const char* contBancar)
{
	if (contBancar != " ")
		strcpy_s(this->contBancar, contBancar);
}

char* persoanaJuridica::getAdresaFirma()
{
	return adresaFirma;
}

void persoanaJuridica::setAdresaFirma(const char* adresaFirma)
{
	if (adresaFirma != " ")
		strcpy_s(this->adresaFirma, adresaFirma);
}






