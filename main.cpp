#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#define MAX_N 15
#define LICZBA_SAMOCHODOW 1

int liczba_paczek_n_0[LICZBA_SAMOCHODOW];
int waga_paczki_0[LICZBA_SAMOCHODOW][MAX_N];
int cena_paczki_0[LICZBA_SAMOCHODOW][MAX_N];
int zysk_z_paczki_0[LICZBA_SAMOCHODOW][MAX_N];
int waga_dopuszczalna_ladunku_C[LICZBA_SAMOCHODOW];

bool odmowa_przyjecia_paczki[LICZBA_SAMOCHODOW][MAX_N];
bool na_stos = true;

int liczba_paczek_n[LICZBA_SAMOCHODOW];
int waga_paczki[LICZBA_SAMOCHODOW][MAX_N];
int cena_paczki[LICZBA_SAMOCHODOW][MAX_N];
int zysk_z_paczki[LICZBA_SAMOCHODOW][MAX_N];

int zysk_calkowity[LICZBA_SAMOCHODOW];
int cena_calkowita[LICZBA_SAMOCHODOW];
int zestaw_paczek_1[LICZBA_SAMOCHODOW];
int zestaw_paczek_2[LICZBA_SAMOCHODOW];

const int oplata_za_zaladowanie_samochodu = 20;
const int dodatkowa_oplata_za_paczki_100_kg = 5;
const int waga_graniczna = 100;

int czytaj_liczbe_paczek(int i)
{
	int n;

	cout << "Podaj liczbe paczek w zaladunku nr " << (i + 1) << endl;
	cin >> n;
	return n;
}

int czytaj_wagi_paczek(int i,int j)
{
	int n;

    if(na_stos == true)
    {
        cout << "Podaj wage paczki nr " << (j + 1) << " w zaladunku nr " << (i + 1) << endl;
    }

	cin >> n;
	return n;
}

int czytaj_cena_paczek(int i,int j)
{
	int n;

    if(na_stos == true)
    {
        cout << "Podaj cene paczki nr " << (j + 1) << " w zaladunku nr " << (i + 1) << endl;
    }

	cin >> n;
	return n;
}

int czytaj_wage_dopuszczalna_ladunku_C(int i)
{
	int n;

    if(na_stos == true)
    {
        cout << "Podaj wage dopuszczalna samochodu nr " << (i + 1) << endl;
    }

	cin >> n;
	return n;
}

void analiza_zaladunku(int i)
{
	int zysk_maksymalny = 0;
	int waga_minimalna = 0;
	int numer_zestawu_paczek = 0;
	int cena_maksymalna = 0;

	int koncowa_liczba_kontrolna_1 = 0;
	int koncowa_liczba_kontrolna_2 = 0;

	int flaga_paczki_OK[MAX_N];

	for (int liczba_kontrolna = 1;liczba_kontrolna <= pow(2,liczba_paczek_n[i]) - 1;liczba_kontrolna++)
	{
        for (int j = 0;j < liczba_paczek_n[i];j++)
   		{
		    flaga_paczki_OK[j] = liczba_kontrolna & (1 << j);

			if (flaga_paczki_OK[j] > 0)
			{
				flaga_paczki_OK[j] = 1;
			}
			else
			{
				flaga_paczki_OK[j] = 0;
			}
		}

	    cout << endl;

		int waga_paczek = 0;
		int zysk_z_paczek = 0;
		int cena_paczek = 0;

		for (int j = 0;j < liczba_paczek_n[i];j++)
   		{
		    waga_paczek += waga_paczki[i][j] * flaga_paczki_OK[j];
			zysk_z_paczek += zysk_z_paczki[i][j] * flaga_paczki_OK[j];
			cena_paczek += cena_paczki[i][j] * flaga_paczki_OK[j];
	    }

		if (waga_paczek <= waga_dopuszczalna_ladunku_C[i])
		{
			if (zysk_z_paczek > zysk_maksymalny)
			{
				zysk_maksymalny = zysk_z_paczek;
				//koncowa_liczba_kontrolna_1 = liczba_kontrolna;
			}

			if (cena_paczek > cena_maksymalna)
			{
				cena_maksymalna = cena_paczek;
				//koncowa_liczba_kontrolna_2 = liczba_kontrolna;
			}
		}
    }

	zysk_calkowity[i] = zysk_maksymalny - oplata_za_zaladowanie_samochodu;
	cena_calkowita[i] = cena_maksymalna;

if (cena_calkowita[i] == 0)
    {
        zysk_calkowity[i] = 0;
    }
	//zestaw_paczek_1[i] = koncowa_liczba_kontrolna_1;
	//zestaw_paczek_2[i] = koncowa_liczba_kontrolna_2;
}

int main()
{
    /////wczytywanie danych

    for (int i = 0;i < LICZBA_SAMOCHODOW;i++)
	{
		liczba_paczek_n_0[i] = czytaj_liczbe_paczek(i);

	    for (int j = 0;j < liczba_paczek_n_0[i];j++)
	    {
	        waga_paczki_0[i][j] = czytaj_wagi_paczek(i,j);
	    }

	    for (int k = 0;k < liczba_paczek_n_0[i];k++)
	 	{
	   		cena_paczki_0[i][k] = czytaj_cena_paczek(i,k);
		}

		waga_dopuszczalna_ladunku_C[i] = czytaj_wage_dopuszczalna_ladunku_C(i);
    }

    /////analiza

	for (int i = 0;i < LICZBA_SAMOCHODOW;i++)
	{
		for (int j = 0;j < MAX_N;j++)
	    {
	        odmowa_przyjecia_paczki[i][j] = false;
	    }

	    for (int j = 0;j < liczba_paczek_n_0[i];j++)
	    {

            zysk_z_paczki_0[i][j] = cena_paczki_0[i][j];

			if (waga_paczki_0[i][j] > waga_graniczna)
	        {
	        	if (cena_paczki_0[i][j] <= dodatkowa_oplata_za_paczki_100_kg)
	        	{
	        		odmowa_przyjecia_paczki[i][j] = true;
			    }

			    zysk_z_paczki_0[i][j] = cena_paczki_0[i][j] - dodatkowa_oplata_za_paczki_100_kg;
			}
		}
    }

	for (int i = 0;i < LICZBA_SAMOCHODOW;i++)
	{
		int licznik = 0;

		for (int j = 0;j < liczba_paczek_n_0[i];j++)
   		{
			if (odmowa_przyjecia_paczki[i][j] == false)
			{
				waga_paczki[i][licznik] = waga_paczki_0[i][j];
				cena_paczki[i][licznik] = cena_paczki_0[i][j];
				zysk_z_paczki[i][licznik] = zysk_z_paczki_0[i][j];
				licznik++;
			}
		}

		liczba_paczek_n[i] = licznik;

		analiza_zaladunku(i);
	}

	/////wypisywanie wynikow
    if(na_stos == true)
    {
        for (int i = 0;i < LICZBA_SAMOCHODOW; i++)
        {
            cout << "Zysk calkowity za zaladunek samochodu nr " << (i + 1) << " to " << zysk_calkowity[i] << endl;
        }
    }
};


