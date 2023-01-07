
#ifndef persoanaJuridica_h
#define persoanaJuridica_h
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
class persoanaJuridica 
{
protected:
	char telefonCompanie[50]= { "" };
	char numeFirma[50]= { "" };
	char CUI[50]= { "" };
	char codRegistruComert[50]= { "" };
	char contBancar[50]= { "" };
	char adresaFirma[50]= { "" };

public:
	vector<persoanaJuridica>j;
	persoanaJuridica();
	persoanaJuridica(char telefonCompanie[50], char numeFirma[50], char CUI[50], char codRegistruComert[50], char contBancar[50], char adresaFirma[50]);
	persoanaJuridica(const persoanaJuridica& pj);

	~persoanaJuridica();

	void operator=(persoanaJuridica pj);

	char* getTelefonCompanie();
	void setTelefonCompanie(const char* telefonCompanie);
	char* getNumeFirma();
	void setNumeFirma(const char* numeFirma);
	char* getCUI();
	void setCUI(const char* CUI);
	char* getCodRegistruComert();
	void setCodRegistruComert(const char* codRegistruComert);
	char* getContBancar();
	void setContBancar(const char* contBancar);
	char* getAdresaFirma();
	void setAdresaFirma(const char* adresaFirma);

	void adauga_jur()
	{
		cout << "Introduceti telefonul companiei" << endl;
		cin.getline(telefonCompanie, 50);
		fflush(stdin);
		
		//persJur.setTelefonCompanie(telefonCompanie);

		cout << "Adaugati numele firmei d-voastra" << endl;
		cin.getline(numeFirma, 50);
		fflush(stdin);
		//persJur.setNumeFirma(numeFirmaNou);

		cout << "Introduceti codul de inregistrare unic" << endl;
		cin.getline(CUI, 50);
		fflush(stdin);
		//persJur.setCUI(CUINou);

		cout << "Introduceti cod de la registru comert" << endl;
		cin.getline(codRegistruComert, 50);
		fflush(stdin);
		//persJur.setCodRegistruComert(codRegistruComertNou);

		cout << "Introduceti contul bancar de unde sa se realizeze plata" << endl;
		cin.getline(contBancar, 50);
		fflush(stdin);
		//persJur.setContBancar(contBancarNou);


		cout << "Introduceti adresa firmei(sediul)" << endl;
		cin.getline(adresaFirma, 50);
		fflush(stdin);
		//persJur.setAdresaFirma(adresaFirmaNou);

		//j.adaugaPersoanaJuridica(persJur);
		return;
	}
	void afis()
	{
		
	}

};
#endif /*persoanaJuridica_h*/
