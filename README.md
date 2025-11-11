# 🔷 Zależności Grafów

Projekt implementuje analizę grafów — struktur danych używanych w informatyce — w celu obliczenia ich podstawowych i zaawansowanych parametrów.

## 🎯 Cel projektu
Celem projektu jest wczytanie danych o grafach oraz wyznaczenie dla każdego z nich następujących parametrów:

1. **Ciąg stopniowy** wierzchołków  
2. **Liczba składowych spójności**  
3. **Dwudzielność grafu**  
4. **Acentryczność wierzchołków** (w obrębie składowych spójności)  
5. **Planarność grafu**  
6. **Kolorowanie wierzchołków** (liczbami naturalnymi od 1) za pomocą algorytmów:
   - zachłannego (według kolejności numerów wierzchołków),
   - LF (Largest First),
   - SLF (Smallest Last First)
7. **Liczba różnych podgrafów C₄**  
8. **Liczba krawędzi w dopełnieniu grafu**

### ⚙️ Wejście
- Pierwsza linia: liczba `k` — ilość grafów.
- Następnie `k` zestawów danych.
- Każdy zestaw opisuje graf o rzędzie `n` oraz zawiera:
  - dla każdego wierzchołka — liczbę sąsiadów `s` oraz `s` identyfikatorów wierzchołków.

Przykład:
