#pragma once
#include <iostream>

using namespace std;

class Graf
{
private:
        int** tab_wierzcholkow = nullptr;
        int n_wierzcholkow = 0;
        int* tab_stopni = nullptr;
        int* tab_stopni_copy = nullptr;
        int* tab_odwiedzonych = nullptr;
        int* tab_nowych = nullptr;
        int najw_stop_wierz = 0;
        int ilosc_cykli = 0;
        int* tab_stopni_LF = nullptr;
public:
        Graf(int n);
        void WczytanieGrafu();

        // zad 1
        void merge(int* array, int left, int mid, int right);
        void mergeSort(int* array, int left, int right);
        int getTabStopni(int i);
        // zad 2
        int liczbaSpojnosciGrafu();
        void dfs(int i);
        // zad 3
        void dwudzielnoscGrafu();
        bool dfs_dwudzielnosc(int i);
        // zad 6a
        void koloryWierzcholkow();
        // zad 6b
        void koloryWierzcholkowLF();
        int najwiekszyStopienWierzcholkaLF();
        // zad 6c
        void koloryWierzcholkowSLF();
        bool czyNowyKolorSasiada(int obecny, int kolorNowegoSasiada);
        //zad 6
        int sprawdzKolor(int i);
        //zad 7
        int cyklC4();
        bool dfsC4(int i, int pocz, int sasiad, int size);
        // zad 8
        void dopelnienieGrafu(); 
        // inne
        void zerowanie_tab_odwiedzonych();
        int* Get_tabStopniNowych();
        void check();

        ~Graf();
};