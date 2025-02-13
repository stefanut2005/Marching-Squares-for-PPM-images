# Marching_squares
In functia main ne declaram variabilele n, m(dimensiunile imaginii initiale), matricea imaginii initale( **a), matricea gridului( **grid) si matricea de 3 dimensiuni pentru contur(contur[16][4][4]), carora le atasam ulterior valori in functiile in care le folosim ca parametru cu referinta. Tot aici prelucram fiecare comanda in parte astfel: 

    - pentru comanda "READ" eliberam memoria pentru matricele 'a' si 'grid' si apoi apelam functia READ folosind ca parametru &n, &m si &a deoarece acestea vor fi schimbate la citire. In plus, oferim valoarea 1 variabilei 'read' care verifica ulterior pentru fiecare comanda daca inainte de aceasta a fost "READ" pentru a afisa mesajul de citire cu cu succes. Dupa afisarea mesajului, variabile 'read' primeste valoarea 0.

    - pentru comanda "WRITE", apelam functia WRITE

    - pentru comanda "INIT_CONTUR", apelam functia INIT_CONTUR, folosind referinta asupra variabilei 'contur' deoarece o sa fie modificata. Apoi, afisez pattern-urile

    - pentru comanda "GRID", apelam functia GRID, folosind referinta asupra variabilei 'grid' deoarece o sa fie modificata. Apoi, afisez gridul, fara ultima linie si ultima coloana, acestea fiind relevante doar in "MARCH"

    - pentru comanda "MARCH", apelam functia MARCH, folosind referinta asupra variabilelor 'a', 'grid' si 'contur' deoarece toate pot fi modificate (exista teste in care comanda "MARCH" este ceruta fara a fi cerute inainte "GRID" sau "INIT_CONTUR")

    - pentru comanda "RESIZE", apelam functia RESIZE, folosind referinta asupra variabilelor 'n', 'm', 'a' deoarece toate vor fi modificate

    - pentru comanda "EXIT", apelam functia EXIT, folosind referinta asupra variabilelor 'a' si 'grid' deoarece vor fi eliberate de memorie

    - ultimul "if" este pentru cazul in care vor fi cititi mai multi pixeli decat este necesar si astfel, in loc sa citeasca o comanda, programul va citi niste numere. Afisam mesajul de eroare "Eroare: eroare citire pixeli" si eliberam de memorie cele 2 matrice, 'a' si 'grid'

Functia free_a:
    Elibereaza de memorie matricea 'a'

Functia free_grid:
    Elibereaza de memorie matricea 'grid'

Functia READ:
    Aloca dinamic matricea 'a' si o citeste. Verifica daca vreun pixel are valoare invalida si afiseaza mesajul "Eroare: valoare pixel necorespunzatoare" in acest caz. Daca sunt cititi prea putini pixeli, "scanf" va returna valoarea -1 si astfel trebuie sa afisam mesajul "Eroare: eroare citire pixeli". Daca formatul este incorect, afisam mesajul "Eroare: trebuie sa fie P3"

Functia WRITE:
    Afiseaza matricea 'a'

Functia INIT_CONTUR:
    Creeaza pattern-urile in variabila 'c', iar apoi copiaza element cu element in 'contur'

Functia inmat:
    Verifica daca elementul de pe o anumita pozitie se afla in matricea 'a'. Aceasta functie va fi folosita in GRID.

Functia GRID:
    Elibereaza de memorie vechea matrice 'grid', o aloca dinamic din nou, iar apoi calculeaza valorile din ea astfel: elementele din 'grid' sunt din 4 in 4 in matricea initiala, 'a', doar ca modificate. In cazul in care media aritmetica a vecinilor aflati in forma de X este mai mica decat 200, elementul din grid ia valoarea 1, altfel ia valoarea 0

Functia MARCH:
    Elibereaza de memorie vechea matrice 'grid', apeleaza functiile GRID si INIT_CONTUR si construieste noua imagine astfel: transformam din baza 2 in baza 10, numarul format din bitii reprezentati de valorile a cate 4 noduri vecine

Functia RESIZE:
    Mareste de 4 ori matricea initiala astfel: creeaza o noua matrice in care copiaza de 16 ori fiecare element din cea veche, apoi o elibereaza de memorie pe cea veche si ii atribuie valoarea noii matrici.

Functia EXIT:
    Afiseaza mesajul "Gigel a terminat" si elibereaza de memorie cele 2 matrice 'a' si 'grid'