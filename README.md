# kompilator
Prvi ćirilični kompilator

**- Studentski projekat iz predmeta Konstrukcija kompilatora na Matematickom fakultetu.**

**- Instalacija Clanga:**

    sudo apt-get install clang-3.8
    sudo ln -s /usr/bin/clang++-3.8 /usr/bin/clang++


-Trenutno podrzane naredbe ovim kompilatorom su:

-Dva brojevna tipa, double i int
   

     цео ц;
     дупли д;

-Pisanje funkcija

    @дупли степен(дупли е, цео н){
    
    }


-if then else, if then

    ако а<2{
        1;
    }
    иначе{
        фиб(а-1)+фиб(а-2);
    };
    
    ако (а<2) { 1; }
-while petlja
   

     док а<н{
            а=а+1;
            д=д*е;
        };
    
Pored ovih podrzane su racunske operacije, poredjenje < i >. **Poslednja naredba je i povratna vrednost funkcije**

Komande za kompilaciju test primera:

    make
    ./cirko --compile primer.txt
    clang output.o main.c
    ./a.out

