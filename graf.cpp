#include "Graf.h"

Graf::Graf(int n) : n_wierzcholkow(n)
{
        tab_wierzcholkow = new int* [n];
        tab_odwiedzonych = new int[n]();
        tab_stopni = new int[n];
        tab_stopni_LF = new int[n];
        tab_stopni_copy = new int[n];
        tab_nowych = new int[n];
        for (int i = 0; i < n; ++i) {
                tab_nowych[i] = i;
        }
}
void Graf::WczytanieGrafu()
{
        int ilosc_polaczen = 0;
        for (int j = 0; j < n_wierzcholkow; j++)
        {
                cin >> ilosc_polaczen;
                tab_stopni[j] = ilosc_polaczen;
                tab_stopni_LF[j] = ilosc_polaczen;
                tab_stopni_copy[j] = ilosc_polaczen;
                tab_wierzcholkow[j] = new int[ilosc_polaczen]; // inicjacja tablic 
                for (int k = 0; k < ilosc_polaczen; k++)
                {
                        cin >> tab_wierzcholkow[j][k];
                        tab_wierzcholkow[j][k] -= 1;
                        // wpisujemy wartosci polaczen
                }
        }
}

// Zadanie 1
void Graf::merge(int* array, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Tworzymy tymczasowe tablice
        int* L = new int[n1];
        int* R = new int[n2];

        // Kopiujemy dane do tymczasowych tablic L[] i R[]
        for (int i = 0; i < n1; ++i)
                L[i] = array[left + i];
        for (int j = 0; j < n2; ++j)
                R[j] = array[mid + 1 + j];

        int i = 0; 
        int j = 0;
        int k = left; 

        while (i < n1 && j < n2) {
                if (L[i] >= R[j]) 
                { 
                        array[k] = L[i];
                        i++;
                }
                else {
                        array[k] = R[j];
                        j++;
                }
                k++;
        }

        while (i < n1) {
                array[k] = L[i];
                i++;
                k++;
        }

        while (j < n2) {
                array[k] = R[j];
                j++;
                k++;
        }

        delete[] L;
        delete[] R;
}
void Graf::mergeSort(int* array, int left, int right) {
        if (left < right) {
                int mid = left + (right - left) / 2;

                // Sortujemy pierwszą i drugą połowę
                mergeSort(array, left, mid);
                mergeSort(array, mid + 1, right);

                // Łączymy posortowane połówki
                merge(array, left, mid, right);
        }
}
int Graf::getTabStopni(int i)
{
        return tab_stopni_copy[i];
}

// Zadanie 2
int Graf::liczbaSpojnosciGrafu()
{
        zerowanie_tab_odwiedzonych();
        int liczba_spojnosci = 0;

        for (int i = 0; i < n_wierzcholkow; ++i)  // puszczamy dfs z kazdego nie odwiedzonego wierzchołka
        {
                if (!tab_odwiedzonych[i]) 
                {
                        ++liczba_spojnosci;
                        dfs(i); 
                }
        }

        return liczba_spojnosci;
}
void Graf::dfs(int i)
{
        tab_odwiedzonych[i] = 1;

        for (int neighbor = 0; neighbor < tab_stopni[i]; neighbor++) {
                if (!tab_odwiedzonych[tab_wierzcholkow[i][neighbor]]) {
                        dfs(tab_wierzcholkow[i][neighbor]);
                }
        }
}

// Zadanie 3
void Graf::dwudzielnoscGrafu()
{
        zerowanie_tab_odwiedzonych();

        for (int i = 0; i < n_wierzcholkow; i++)
        {
                if (!tab_odwiedzonych[i])
                {
                        tab_odwiedzonych[i] = 1;
                        if (dfs_dwudzielnosc(i) == false) // puszczamy dfs dzielacego na grupy
                        {
                                cout << "F" << endl;
                                return;
                        }
                }
        }
        cout << "T" << endl;
}
bool Graf::dfs_dwudzielnosc(int i)
{
        int temp = tab_odwiedzonych[i];

        for (int j = 0; j < tab_stopni[i]; j++) {
                if (tab_odwiedzonych[tab_wierzcholkow[i][j]] == 0) // jesli nie jest jeszcze przypisany o grupy
                {
                        tab_odwiedzonych[tab_wierzcholkow[i][j]] = (temp) % 2 + 1; //robi znak inny niz ten pierwsz
                        if (dfs_dwudzielnosc(tab_wierzcholkow[i][j]) == false)
                                return false;
                }
                else if (tab_odwiedzonych[tab_wierzcholkow[i][j]] != temp) //jesli jest inny to git
                {
                        continue;
                }
                else //jesli taki sam to kicha
                {
                        return false;
                }
        }
        return true;
}

// Zadanie 6a
void Graf::koloryWierzcholkow()
{
        zerowanie_tab_odwiedzonych();
        for (int i = 0; i < n_wierzcholkow; i++) 
        {
                tab_odwiedzonych[i] = sprawdzKolor(i); // wyznaczanie kolorów dla wierzcholkow w kolejnosc od 1 do n
                cout << tab_odwiedzonych[i] << " ";
        }
}

// Zadanie 6b
void Graf::koloryWierzcholkowLF()
{
        zerowanie_tab_odwiedzonych();
        int licznik = 0;

        while (licznik != n_wierzcholkow)
        {
                najw_stop_wierz = najwiekszyStopienWierzcholkaLF(); // wyznaczamy najw stop aktualnego wierzcholka 
                tab_odwiedzonych[najw_stop_wierz] = sprawdzKolor(najw_stop_wierz); // robi jemu wybor koloru
                licznik++;
        }
         for (int i = 0; i < n_wierzcholkow; i++) {
                 cout << tab_odwiedzonych[i] << " ";
         }
}
int Graf::najwiekszyStopienWierzcholkaLF()
{
        int najw_stop = -1;
        int id = 0;
        for (int i = 0; i < n_wierzcholkow; i++)
        {
                if (najw_stop < tab_stopni_LF[i])
                {
                        najw_stop = tab_stopni_LF[i];
                        id = i;
                }
        }
        tab_stopni_LF[id] = -1; // jesli tab juz oznaczony to -1

        // for (int i = 0; i < n_wierzcholkow; i++) {
        //      cout << tab_stopni_LF[i] << " ";
        // }
        // cout << endl;
        return id;
}

// Zadanie 6c
void Graf::koloryWierzcholkowSLF()
{
        zerowanie_tab_odwiedzonych();
        int* tab_kolorow = new int[n_wierzcholkow]();
        int* pom_tab_odwiedzonych = new int[n_wierzcholkow]();
        int licznik = 0;
        int liczba_odwiedzonych = 0;
        int najwieciej_kolorow_sasiadow = -1;
        int id_max = -1;

        while (liczba_odwiedzonych < n_wierzcholkow)
        {
                //szukamy najwiekszej ilosci kolorow sasiadow
                najwieciej_kolorow_sasiadow = -1;
                id_max = -1;
                for (int i = 0; i < n_wierzcholkow; i++)
                {
                        if (tab_kolorow[i] == -2)
                                continue;
                        if (najwieciej_kolorow_sasiadow < tab_kolorow[i] ||
                                (najwieciej_kolorow_sasiadow == tab_kolorow[i] && tab_stopni[id_max] < tab_stopni[i]))
                        {
                                najwieciej_kolorow_sasiadow = tab_kolorow[i];
                                id_max = i;
                        }
                }

                //TYLKO WYZNACZENIE nowego koloru
                int nowyKolor = sprawdzKolor(id_max);

                //zwiekszanie ilosci kolorow dla sasiadow
                for (int i = 0; i < tab_stopni[id_max]; i++)
                {
                        int obecny = tab_wierzcholkow[id_max][i];
                        if (pom_tab_odwiedzonych[obecny] != 1)
                                tab_kolorow[obecny] += czyNowyKolorSasiada(obecny, nowyKolor);
                }
                tab_kolorow[id_max] = -2;
                //kolorowanie wierzcholka 
                tab_odwiedzonych[id_max] = nowyKolor;
                pom_tab_odwiedzonych[id_max] = 1;
                liczba_odwiedzonych++;
        }
        delete[] tab_kolorow;
        delete[] pom_tab_odwiedzonych;

        for (int i = 0; i < n_wierzcholkow; i++) {
                cout << tab_odwiedzonych[i] << " ";
        }
}
bool Graf::czyNowyKolorSasiada(int obecny, int kolorNowegoSasiada)
{
        for (int i = 0; i < tab_stopni[obecny]; i++)
        {
                if (tab_odwiedzonych[tab_wierzcholkow[obecny][i]] == kolorNowegoSasiada)
                        return false;
        }
        return true;
}

// Do wszystkich 6
int Graf::sprawdzKolor(int i)
{
        bool* used_colors = new bool[n_wierzcholkow + 1]();

        for (int j = 0; j < tab_stopni[i]; j++)
        {
                if (tab_odwiedzonych[tab_wierzcholkow[i][j]] != 0)
                {
                        used_colors[tab_odwiedzonych[tab_wierzcholkow[i][j]]] = true;
                }
        }

        // Znajdujemy pierwszy niewykorzystany kolor
        int kolor = 1;
        while (used_colors[kolor])
        {
                kolor++;
        }

        delete[] used_colors;
        return kolor;
}

// Zadanie 7 (brute force)
int Graf::cyklC4()
{
        for (int i = 0; i < n_wierzcholkow; i++)
        {
                dfsC4(i, i, -1, 1); // dany wierzcholek, pocz wierzhołek , jaki sasiad, wielkosc
        }
        return ilosc_cykli / 8;
}
bool Graf::dfsC4(int i, int pocz, int sasiad, int size)
{
        if (size == 5)
        {
                if (i == pocz)
                {
                        ilosc_cykli++;
                        return true;
                }
                else
                        return false;
        }
        for (int a = 0; a < tab_stopni[i]; a++)
        {
                if (sasiad != tab_wierzcholkow[i][a])
                {
                        dfsC4(tab_wierzcholkow[i][a], pocz, i,size+1);
                }
        }
        return false;
}

// Zadanie 8
void Graf::dopelnienieGrafu()
{
        // Liczba krawedzi grafu pelnego n(n-1)/2
        long long n = n_wierzcholkow;
        long long int pelnyGraf =n * (n - 1) / 2;
        long long int liczba_krawedzi = 0;
        for (int i = 0; i < n_wierzcholkow; i++)
        {
                liczba_krawedzi += tab_stopni[i];
        }
        liczba_krawedzi /= 2;
        pelnyGraf -= liczba_krawedzi;
        cout << pelnyGraf << endl;
}

// Inne
void Graf::zerowanie_tab_odwiedzonych()
{
        for (int i = 0; i < n_wierzcholkow; i++)
                tab_odwiedzonych[i] = 0;
}
int* Graf::Get_tabStopniNowych()
{
        return tab_stopni_copy;
}
void Graf::check()
{
        for (int i = 0; i < n_wierzcholkow; i++)
        {
                //spacje(i);
                for (int j = 0; j < tab_stopni[i]; j++)
                {
                        cout << tab_wierzcholkow[i][j] << " ";
                }
                cout << endl;
        }
}

Graf::~Graf()
{
        for (int i = 0; i < n_wierzcholkow; ++i)
        {
                delete[] tab_wierzcholkow[i];
        }
        delete[] tab_wierzcholkow;
        delete[] tab_stopni;
};