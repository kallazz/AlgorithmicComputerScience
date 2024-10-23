Algorytmy Optymalizacji Dyskretnej 2024/25
-------------------------------------------
-------------------------------------------

LABORATORIUM 1 - DANE TESTOWE

--------------------------------------------------------------------------------
STRUKTURA ARCHIWUM aod_testy1.zip

|
|-- 2              // testy do ZADANIA 2
|   |
|   |-- g2a-i.txt  (1 <= i <= 6) -> grafy bez skierowanego cyklu (DAG-i)
|   |-- g2b-i.txt  (1 <= i <= 6) -> grafy ze skierowanym cyklem
|
|
|-- 3              // testy do ZADANIA 3
|   |
|   |-- g3-i.txt   (1 <= i <= 6)    
|
|
|-- 4              // testy do ZADANIA 4
|   |
|   |-- u4a-i.txt  (1 <= i <= 6) -> grafy nieskierowane dwudzielne
|   |-- u4b-i.txt  (1 <= i <= 6) -> grafy nieskierowane niedwudzielne
|   |-- d4a-i.txt  (1 <= i <= 6) -> grafy skierowane dwudzielne
|   |-- d4b-i.txt  (1 <= i <= 6) -> grafy skierowane niedwudzielne


--------------------------------------------------------------------------------
DANE TESTOWE - UWAGI

* każdy plik zawiera definicję grafu wg specyfikacji z Listy 1 LAB:
  
        [D|U]
        n
        m
        <m par postaci e1 e2, 1 <= e1, e2 <= n, każda w osobnej linii>
	    <na końcu pusta linia>

  pliki generowane pod Windowsem, kodowanie UTF-8

* graf z pliku *-i.txt ma liczbę wierzchołków i krawędzi rzędu 10^i dla 1 <= i <= 6

* maksymalny rozmiar pojedynczego pliku: ok. 43 MB (dla grafów z 1 000 000 wierzchołków)

* należy dobrać narzędzia (czytaj: język programowania) tak, aby program poradził sobie
  z tak dużymi danymi testowymi

* grafy do ZADANIA 2 to "skierowane kraty z przekątnymi" dla wersji acyklicznej (g2a-i.txt)
                      i "skierowane kraty z przekątnymi z dodatkową krawędzią w środku" tworzącą cykl skierowany (g2b-i.txt)
					  
  coś w stylu:
  
     --- --- ---      --- ---- --- 
	| / | / | / |    | / | /  | / |
	 --- --- ---      --- ---- --- 
	| / | / | / |    | / | // | / |  <- krawędź "w środku" jest dwukierunkowa (2 krawędzie skierowane)
	 --- --- ---      --- ---- --- 
	| / | / | / |    | / | /  | / |
	 --- --- ---      --- ---- --- 

* grafy do ZADANIA 3 składają się z 5 silnie spójnych komponent
  ich struktura jest następująca:
  
           -> G -> P ->
          /            \
        K               t
          \            /
           ---> C ---->
 
  gdzie:
    K to mała klika skierowana
	G to silnie spójna skierowana krata (grid graph)
	P to skierowana "dwukierunkowa" ścieżka (path graph)
    C to cykl skierowany
	t to pojedynczy wierzchołek (ujście / sink)
  
  rozmiary G, P i C się skalują (rosną wraz z rozmiarem grafu)
  
* nieskierowane grafy do ZADANIA 4 to zmodyfikowane pełne drzewa binarne:
    -> u4a-i.txt - liście są połączone z przodkiem "3 poziomy wyżej" (powstają cykle parzystej długości)
	-> u4b-i.txt - liście są połączone z przodkiem "2 poziomy wyżej" (powstają cykle nieparzystej długości)
	
* skierowane grafy do ZADANIA 4 to:
    -> d4a-i.txt - skierowane kraty
	-> d4b-i.txt - skierowane kraty "z przekątną w środkowej komórce"
	
  coś w stylu:
  
     --- --- ---      --- --- --- 
    |   |   |   |    |   |   |   |
     --- --- ---      --- --- --- 
    |   |   |   |    |   | / |   |  <- dodatkowa krawędź skierowana "w środku"
     --- --- ---      --- --- --- 
    |   |   |   |    |   |   |   |
     --- --- ---      --- --- --- 

* problemy natury technicznej związane z danymi testowymi należy zgłaszać wykładowcy
  (to on wymyślał przykłady i generował te pliki)
