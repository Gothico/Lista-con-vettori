/**
*Quest'opera è stata rilasciata con licenza Creative Commons Attribuzione - Non commerciale - 
*Condividi allo stesso modo 3.0 Italia. 
*Per leggere una copia della licenza visita il sito web http://creativecommons.org/licenses/by-nc-sa/3.0/it/
*o spedisci una lettera a Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/
/**************************************************************************
REALIZZAZIONE TEMPLATE DI LISTA IMPLEMENTATA CON VETTORE
              La realizzzazione è molto elementare: è basata sul semplice
              accesso sequenziale del vettore lineare.

Autore: Riccardo Monterisi  http://riccardomonterisi.altervista.org/

**************************************************************************/

#ifndef _LISTA
#define _LISTA

   #include <iostream>
   #include <assert.h>
    using namespace std;

    typedef int posizione;

    template <class T>
    class Lista
    {
          public:
                 Lista();   //costruttore 1
                 Lista(int );
                 ~Lista(); //distruttore

                 typedef T tipoelem;
                 void creaLista(); // implementato
                 bool listaVuota() const; // implementato
                 T leggiLista(posizione); //implementato
                 void scriviLista(tipoelem, posizione); //implementato
                 posizione primoLista() const; // implementato
                 bool fineLista(posizione) const; //implementato
                 posizione succLista(posizione) const; // implementato
                 posizione predLista(posizione) const; //implementato
                 void insLista(tipoelem, posizione); // implementato
                 void cancLista(posizione); //implementato
                 void stampaLista();
         private:
                 int lunghezza;
                 int primo_lista; //posizione del primo nella lista
                 tipoelem *VETTORE;
                 int MAX_DIM;
       };


//----------------------Implementazione-----------------------
template <class T>
Lista<T>::Lista()
{
    VETTORE = new tipoelem[100]; // dimensione standard della lista
    MAX_DIM = 100;
    Lista<T>::creaLista();
}

template <class T>
Lista<T>::Lista(int N)
{
   VETTORE = new tipoelem[N]; // dimensione N della lista
   MAX_DIM = N;
   creaLista();
}

template <class T>
Lista<T>::~Lista() {delete[] VETTORE;};

template <class T>
void Lista<T>::creaLista()
{

   lunghezza = 0;
   primo_lista = -1;
}

template <class T>
bool Lista<T>::listaVuota() const
{
    /*specifica sintattica:
                LISTAVUOTA:( LISTA) --> BOOLEAN
     specifica semantica:
               LISTAVUOTALISTAVUOTA(L)= b
               POST:b = TRUE SE L= <> ALTRIMENTI b = FALSE
      N.B. per comodità si assume che il parametro L sia semplicemente
      la lista corrente, quindi nella realizzazione corrente non la funzione
      è priva di parametri.
    */

    bool output = false;

    if (lunghezza == 0 && primo_lista == -1)
       output = true;
    else
       output = false;

    return  output;
}

template <class T>
T Lista<T>::leggiLista(posizione p)
{
/*specifica sintattica:  LEGGILISA:(POSIZIONE) --> TIPOELEM
  specifica semantica:
  LEGGILISTALEGGILISTA(p)= a
                PRE: p = pos(i)  inizio_lista <= i <= n
                POST: a = ai */

    tipoelem out;

     assert((primo_lista <= p) && (p<= MAX_DIM));
     out = VETTORE[p];
     
     return out;
}

template <class T>
void Lista<T>::scriviLista(tipoelem add, posizione pos)
{
   assert((primo_lista <= pos) && (pos <= MAX_DIM));
   
   VETTORE[pos] = add;  
}

template <class T>
bool Lista<T>::fineLista(posizione pos) const
{
   bool risp = false;

   if ((pos+1) == lunghezza)
      risp = true;

   return risp;
}

template <class T>
posizione Lista<T>::primoLista() const
{
	return primo_lista;
}

template <class T>
posizione Lista<T>::succLista(posizione pos) const
{
    posizione succ;

    assert((primo_lista<= pos) && (pos <= (primo_lista + lunghezza)));
    succ = pos + 1;

    return succ;
}

template <class T>
posizione Lista<T>::predLista(posizione pos) const
{
   posizione pred;

    assert(((primo_lista+1) <= pos) && (pos<= (primo_lista + lunghezza)));
    pred = pos - 1;
    
    return pred;
}

template <class T>
void Lista<T>::insLista(tipoelem add, posizione pos)
{
   bool ques;
   tipoelem prov;
   int i;

    if (primo_lista < 0)
    {
       primo_lista = pos;
	   VETTORE[pos] = add;
       lunghezza++;
    }
    else
    {
       if ((primo_lista <= pos) && (pos<= MAX_DIM))
       {
          ques = fineLista(pos+1);
          if (ques == true)
          {
             VETTORE[pos] = add;
             lunghezza++;
          }
          else
          {
             prov = VETTORE[pos];
             VETTORE[pos] = add;

             for (i=pos+1; i<lunghezza; i++)
             {
                VETTORE[i] = prov;
                prov = VETTORE[i+1];
             }
             lunghezza++;
          }
       }
        else
        {
           if ((0<= pos) && (pos<= primo_lista))
           {
              primo_lista = pos;
              VETTORE[pos] = add;
           }
           else
            cout << "Impossibile aggiungere l'elemento: la posizione e` minore di 0.\n";
        }
     }
}

template <class T>
void Lista<T>::cancLista(posizione pos)
{
   tipoelem prov;
   int i;

   if (pos == primo_lista)
   {
      primo_lista = Lista::succLista(primo_lista);
      lunghezza--;
   }
   else
   {
      assert((primo_lista + 1 <= pos)&& (pos <= (primo_lista + lunghezza)));
       
     for (i=pos; i<lunghezza; i++)
     {
        prov = VETTORE[i+1];
        VETTORE[i] = prov;
     }
     lunghezza--;
      
    }
}

template <class T>
void Lista<T>::stampaLista()
{
  int i;

    cout << "|----Elementi presenti nella lista----|" << endl;
    for (i=0; i<lunghezza; i++)
      cout << "Elemento " << i+1 <<  ": " << VETTORE[i] << endl;

}


#endif //_LISTA
