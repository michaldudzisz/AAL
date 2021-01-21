Projekt - Analiza Algorytmów
Michał Dudzisz, Michał Kruk

## Zadanie
Dozwolona jest jedna operacja na zmiennej typu string:
1. Zmiana liter na wskazanych indeksach z małej na dużą,
2. Skasowanie wszystkich pozostałych małych liter

Mając na wejściu dwie zmienne typu string a i b zaproponuj algorytm, który oceni czy przy użyciu powyższej operacji można przekształcić zmienną a w zmienną b.


## Budowanie projektu
W celu zbudowania programu zawierającego algorytm należy wykonać:
1. `cd algo`
2. `make`

## Uruchomienie projektu
W celu uruchomienia programu bez pomiaru czasu działania: \
`./prog -0 plik_wyjsciowy -i plik_wejsciowy`
-0 oznacza wybranie algorytmu brute force, aby wybrać algorytm programowania dynamicznego należy użyć opcji -1. Można użyć obu algorytmów jednocześnie, przykład: \
`./prog -0 plik_wyjsciowy1 -1 plik_wyjsciowy2 -i plik_wejsciowy`

W celu uruchomienia programu z pomiarem czasu działania: \
`./prog -t -1 plik_wyjsciowy plik_wyjsciowy_dla_pomiaru_czasu -i plik_wejsciowy`
W tym przypadku też można wybierać algorytm opcją -0 lub/i -1.

## Konwencja danych w plikach

Plik wejściowy zawiera w każdej lini dwa rozdzielone spacją stringi, które są traktowane jakoś pojedyncze dane wejściowe algorytmu.
Przykład \
`string1 string2`

Plik wyjściowy z wynikami algorytmu zawiera w jednej lini dwa stringi rozdzielone spacją, a następnie rozwiązanie zadania. 0 - oznacza fałsz, 1 - oznacza prawdę.
Przykład: \
`string1 string2 0`

Plik wyjściowy z pomiarem czasu zawiera, rozdzielone spacją, długość pierwszego stringu, długość drugiego stringu, czas wykonania algorytmu w sekundach. Przykład: \
`liczba1 liczba2 czas_trwania_obliczen`






