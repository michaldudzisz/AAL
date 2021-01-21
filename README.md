## Budowanie projektu
W celu zbudowania programu zawierającego algorytm należy wykonać:
1. `cd algo`
2. `make`

W celu uruchomienia programu bez pomiaru czasu działania: \
`./prog -0 nazwa_pliku_do_ktorego_zapisac_wynik -i nazwa_pliki_z_ktorego_odczytac_dane`
-0 oznacza wybranie algorytmu brute force, aby wybrać algorytm programowania dynamicznego należy użyć opcji -1. Można użyć obu algorytmów jednocześnie, przykład: \
`./prog -0 plik1 -1 plik2 -i plik3`

W celu uruchomienia programu z pomiarem czasu działania: \
`./prog -t -0 nazwa_pliku_do_ktorego_zapisac_wynik nazwa_pliku_do_ktrego_zapisac_wyniki_czasu -i nazwa_pliku_z_ktorego_odczytac_dane`


