using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <vector>

typedef struct Cvor
{
	int mat[3][3];
    struct Cvor* rod;
}cvor;

void mat_copy(cvor* cv, int mat[][3])
{
	for(int i=0; i<3; i++)
	   for(int j=0; j<3; j++)
			cv->mat[i][j] = mat[i][j];
}

bool uporedi(cvor* cv, int mat[][3])
{
	for(int i=0; i<3; i++)
	   for(int j=0; j<3; j++)
			if (cv->mat[i][j] != mat[i][j])
				return false;

	return true;
}

void nadji_potomke(cvor* cv, vector<cvor*>& potomci)
{
	int ind_i, ind_j;

	//nalazimo poziciju 0
	for(int i=0; i<3; i++)
	   for(int j=0; j<3; j++)
		if (cv->mat[i][j] == 0)
        {
			ind_i = i; ind_j = j;
		}

	//pravimo 4 moguca potomka
	if (ind_i - 1 >= 0)
    {
		cvor* sled = (cvor*)malloc(sizeof(cvor));
		sled->rod = cv;
    	mat_copy(sled, cv->mat);
		sled->mat[ind_i][ind_j] = sled->mat[ind_i - 1][ind_j];
        sled->mat[ind_i - 1][ind_j] = 0;
		potomci.push_back(sled);
    }

	if (ind_j - 1 >= 0)
    {
		cvor* sled = (cvor*)malloc(sizeof(cvor));
		sled->rod = cv;
    	mat_copy(sled, cv->mat);
		sled->mat[ind_i][ind_j] = sled->mat[ind_i][ind_j - 1];
        sled->mat[ind_i][ind_j - 1] = 0;
		potomci.push_back(sled);
    }

	if (ind_j + 1 < 3)
    {
		cvor* sled = (cvor*)malloc(sizeof(cvor));
		sled->rod = cv;
    	mat_copy(sled, cv->mat);
		sled->mat[ind_i][ind_j] = sled->mat[ind_i][ind_j + 1];
        sled->mat[ind_i][ind_j + 1] = 0;
		potomci.push_back(sled);
    }

	if (ind_i + 1 < 3)
    {
		cvor* sled = (cvor*)malloc(sizeof(cvor));
		sled->rod = cv;
    	mat_copy(sled, cv->mat);
		sled->mat[ind_i][ind_j] = sled->mat[ind_i+1][ind_j];
        sled->mat[ind_i+1][ind_j] = 0;
		potomci.push_back(sled);
    }
}

bool jednake(int mat1[][3], int mat2[][3])
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			if (mat1[i][j] != mat2[i][j])
				return false;

	return true;
}

bool ne_postoji_u_posecenima(vector<cvor*>& poseceni, cvor* cv)
{
	for(int i=0; i<poseceni.size(); i++)
		if (jednake(poseceni[i]->mat, cv->mat))
			return false;

	return true;
}

bool nadji_neposecen_medju_potomcima(vector<cvor*>& poseceni, vector<cvor*>& potomci, int& potomak)
{
	for(int i=0; i<potomci.size(); i++)
		if (ne_postoji_u_posecenima(poseceni, potomci[i]))
		{
			potomak = i;
			return true;
		}

	return false;
}

void stampaj(cvor* cv)
{
	for(int i=0; i<3; i++)
	{
	   for(int j=0; j<3; j++)
			printf("%d ", cv->mat[i][j]);

		printf("\n");
	}

}

void stampaj_potomke(vector<cvor*>& potomci)
{
	for(int i=0; i<potomci.size(); i++)
		stampaj(potomci[i]);
}

bool dfs(cvor* polazni, int cilj[][3])
{
	vector<cvor*> poseceni;
    vector<cvor*> put; //ovo nam je stek; tj. koristimo ga kao stek -- last in first out
	vector<cvor*> potomci;
	int potomak;
	cvor* trenutni;
	int i=0;

	poseceni.push_back(polazni);
    put.push_back(polazni);

	bool nadjen_put = false;

	while(put.size() != 0)
	{
		trenutni = put[put.size()-1]; //uzimamo prvi sa steka
		//stampaj(trenutni);
		//printf("\n");

		if (uporedi(trenutni, cilj))
		{
			nadjen_put = true;
            break;
		}

		nadji_potomke(trenutni, potomci);
		

		if (nadji_neposecen_medju_potomcima(poseceni, potomci, potomak))
        {
			//printf("%d\n", potomak);
			put.push_back(potomci[potomak]);
			poseceni.push_back(potomci[potomak]);
        }
		else
			put.pop_back();

		potomci.clear();
		i++;
	}

	printf("Broj iteracija %d\n", i);

	if (nadjen_put)
	{
		printf("Nadjen put, stamamo unazad\n");
		while(trenutni != NULL)
        {
			stampaj(trenutni);
			printf("\n");
			trenutni = trenutni->rod;
		}
	}

	return nadjen_put;
}

int main()
{
	int mat[][3] = {{0,3,1}, {7,5,4}, {8,6,2}};
	int cilj[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	cvor* polazni = (cvor*)malloc(sizeof(cvor));
	polazni->rod = NULL;
    mat_copy(polazni, mat);
	
	if (!dfs(polazni, cilj))
		printf("nema puta\n");

	return 0;
}
