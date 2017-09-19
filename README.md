# kompilator
Prvi ćirilični kompilator

- Studentski projekat iz predmeta Konstrukcija kompilatora na Matematickom fakultetu.

- Instalacija Clanga:
sudo apt-get install clang-3.8
sudo ln -s /usr/bin/clang++-3.8 /usr/bin/clang++


--Trenutno podrzane naredbe ovim kompilatorom su:

-Dva brojevna tipa, double i int
    int c;
    double d;

-Pisanje funkcija
    @double stepen(double e, int n){

    }
-Definisanje eksternih funkcija
    extern double sin(double x);

-if then else, if then
    if a<2{
        1;
    }
    else{
        fib(a-1)+fib(a-2);
    };
    
    if (a<2) { 1; }
-while
    while a<n{
        a=a+1;
        d=d*e;
    };
    
Pored ovih podrzane su racunske operacije, poredjenje < i > 
