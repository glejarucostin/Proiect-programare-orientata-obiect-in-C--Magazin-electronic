
#include<iostream>
#include"persoanaFizica.h"
#include<vector>
#ifndef dateF_h
#define dateF_h

class dateF :persoanaFizica
{	
	vector<persoanaFizica>fizica;
public:
		void adaugaPersoanaFizica(persoanaFizica fiz);
	~dateF();
};

#endif /*dateF_h*/