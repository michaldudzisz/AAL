Projekt - Analiza Algorytmów \
Michał Dudzisz, Michał Kruk

# Zadanie
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

### Wygenerowanie wykresu
Potrzebne jest posiadanie biblioteki do Pythona matplotlib.
Mając plik z danymi wyjściowymi pracy algorytmu, można wywołać skrypt rysujący wykres tych danych (czasu rozpatrywania danej pary napisów od długości napisu a lub b).
Wywołanie:
`python3 plot.py <filename> <-a lub -b>`

gdzie `filename` to nazwa pliku z danymi wygenerowanym przez algorytmy, a opcje `-a` lub `-b` oznaczają, która z długości (napisu a lub b) będzie brana pod uwagę przy generowaniu wykresu czasu wykonania od długości napisu. Skrypt jednocześnie sumuje czasy wykonywania wszystkich operacji w `filename`, co również może zostać użyte.

## Konwencja danych w plikach

Plik wejściowy zawiera w każdej lini dwa rozdzielone spacją stringi, które są traktowane jako pojedyncze dane wejściowe algorytmu.
Przykład \
`string1 string2`

Plik wyjściowy z wynikami algorytmu zawiera w jednej lini dwa stringi rozdzielone spacją, a następnie rozwiązanie zadania. 0 - oznacza fałsz, 1 - oznacza prawdę.
Przykład: \
`string1 string2 0`

Plik wyjściowy z pomiarem czasu zawiera, rozdzielone spacją, długość pierwszego stringu, długość drugiego stringu, czas wykonania algorytmu w sekundach. Przykład: \
`liczba1 liczba2 czas_trwania_obliczen`

Puste stringi w pliku oznaczamy jako gwiazdkę.

## Stuktura plików w folderze algo
* algo.h - plik nagłówkowy algorytmów
* algo.cpp - plik źródłowy algorytmów
* solver.h - plik nagłówkowy klasy Solver - obudowującej rozwiązywanie. Odpowiada m.in za wczytywanie danych, pomiar czasu, zapis do plików.
* solver.cpp - plik źródłowy klasy Solver
* main.cpp - plik źródłowy zawierający funkcję main
* plot.py - skrypt Pythona rysujący wykres z danych wygenerowanych przez algorytmy

# Generator

Dostarczony został automatyczny generator danych (par napisów a i b) opisany poniżej. 

### Zależności

Przed przystąpieniem do budowania samego generatora należy pobrać bibliotekę `yaml-cpp` (https://github.com/jbeder/yaml-cpp), rozpakować jej folder w folderze `gen` projektu tak, aby bezpośrednio z poziomu `gen` widoczny był folder `yaml-cpp-master`. Wejść w ten folder, wywołać:
1. `mkdir build && cd build`
2. `cmake ..`
3. `make`

## Budowanie generatora danych wejściowych
W celu zbudowania programu zawierającego generator należy wykonać:
1. `cd gen`
2. `make`

## Uruchomienie generatora
Uruchomić można go komendą:
`./test-generator <-f filename> <-n number> <-a, -b lub -p>`
 
Dostępne opcje:
* `-f filename` - przekierowanie wyjścia generatora do pliku `filename`. Jeśli opcja nie jest użyta, dane wypisywane są na standardowe wyjście.
* `-n number` - liczba par napisów do wygenerowania. Jeśli niesprecyzowane, to domyślnie 1. Może zostawać przysłoniona przez opcje `-a`, `-b` i `-p`.
* `-a` - ustalenie długości napisu b, zmienia się tylko a.
* `-b` - ustalenie długości napisu a, zmienia się tylko b.
* `-p` - zmienia się zarówno a i b - w tym samym tempie, tzn. długość a zawsze jest taka sama jak długość b.

Bardzo ważnym plikiem dla generatora jest `test-gen-config.yaml`, który przechowuje informacje o takich parametrach jak startowa długość b, maksymalne długości napisów a i b, prawdopodobieństwach wystąpienia małych lub wielkich liter w określonych miejscach napisów a i b, liczbę przypadków do wygenerowania (jeśli nie podano w wierszu poleceń) i inne (ich dokładniejszy opis znajduje się w tym pliku).

Generator tworzy pary napisów a i b tak, jak w konwencjach opisanych wyżej, a zatem: <napis a><spacja><napis b><nowa linia>.
  
## Stuktura plików w folderze gen
* test-generator.h - plik nagłówkowy generatora
* test-generator.cpp - plik źródłowy generatora
* makefile - plik budowania generatora
* test-gen-config.yaml - plik konfiguracyjny generatora w formacie yaml
* ./lib/ - folder z biblioteką libyaml do odczytania pliku konfiguracyjnego
  
## Ogólny opis rozwiązania.
W programie zaimplementowane są dwa algorytmy. \
1. Siłowy - polega na generacji permutacji stringu a, możliwych do otrzymania przy pomocy operacji.  Dla każdej permutacji porównania jej ze stringiem b. Jeśli permutacja stringu a będzie taka sama jak string b, algorytm zwraca prawdę. Jeśli nie znajdzie się żadna odpowiednia permutacja, algorytm zwraca fałsz. 
2. Algorytm oporty o istotę programowania dynamicznego, o złożoności O(n\*m), gdzie n - długość stringu a, m - długość stringu b. Algorytm rozwiązuje zadanie dla podproblemów, rozszerzając badany podproblem w kolejnych iteracjach, aż do rozwiązania całego problemu. Do rozwiązania użyto struktury vector ze standardowej biblioteki c++.







