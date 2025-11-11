#include <iostream>
#include "Graf.h"
using namespace std;

int main()
{
        Graf* graf;
        int k_grafow = 0, n_wierzch = 0;
        cin >> k_grafow;
        for (int i = 0; i < k_grafow; i++)
        {
                cin >> n_wierzch;
                graf = new Graf(n_wierzch);
                graf->WczytanieGrafu();

                // zadanie 1
                graf->mergeSort(graf->Get_tabStopniNowych(), 0, n_wierzch - 1);
                for (int j = 0; j < n_wierzch; j++)
                        cout << graf->getTabStopni(j) << " ";
                cout << endl;
                // zadanie 2
                cout << graf->liczbaSpojnosciGrafu() << endl;
                // zadanie 3
                graf->dwudzielnoscGrafu();
                // zadanie 4
                cout << "?" << endl;
                // zadanie 5
                cout << "?" << endl;
                // zadanie 6a
                graf->koloryWierzcholkow();
                cout << endl;
                // zadanie 6b
                graf->koloryWierzcholkowLF();
                cout << endl;
                //zadanie 6c
                graf->koloryWierzcholkowSLF();
                // zadanie 7
                cout<<"?"<<endl;
                //cout << graf->cyklC4() << endl;
                // zadanie 8
                graf->dopelnienieGrafu();
                //graf->check();
                delete graf;
        }

}