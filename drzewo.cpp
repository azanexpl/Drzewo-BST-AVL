#include <iostream>
#include <string>
#include <malloc.h>
#include <fstream>

using namespace std;

fstream plikwe,plikwy;

struct wzl
{
  int klucz;
  int waga;
  struct wzl *lewo;
  struct wzl *prawo;
  struct wzl *ojciec;
};

struct wzl *krz=NULL, *x=NULL, *temp = NULL;

struct wzl *tworz_krz(int nr)
{
  struct wzl *krz_rl = NULL;
  krz_rl = (struct wzl *)malloc(sizeof(struct wzl));
  krz_rl -> klucz = nr;
  krz_rl -> lewo = NULL;
  krz_rl -> prawo = NULL;
  krz_rl -> ojciec = NULL;
  krz_rl -> waga = 0;
  return krz_rl;
}

int lacz(struct wzl *krz, struct wzl *wzl)
{
 if((wzl -> klucz) < (krz -> klucz))
  {

    if(krz -> lewo == NULL)
    {

      krz -> lewo = wzl;
      wzl -> ojciec = krz;
    }

    else
    {
        return lacz(krz -> lewo, wzl);
    }

  }

  else if((wzl -> klucz) > (krz -> klucz))
  {

    if(krz -> prawo == NULL)
    {
      krz -> prawo = wzl;
      wzl -> ojciec = krz;
    }

    else
    {
        return lacz(krz -> prawo, wzl);
    }

  }
}

void zrobwzl(struct wzl *krz, int nr)
{

  struct wzl *wzl = NULL;
  wzl = (struct wzl *)malloc(sizeof(struct wzl));
  wzl -> klucz = nr;
  wzl -> lewo = NULL;
  wzl -> prawo = NULL;
  wzl -> ojciec = krz;
  wzl -> waga = 0;
  lacz(krz, wzl);

}

void preorder(struct wzl *krz)
{
  plikwy << endl << endl;
  plikwy << "Wierzcholek:" << krz -> klucz << endl;
  plikwy << "Waga:" << krz -> waga << endl;

  if(krz -> ojciec != NULL)
  {
      plikwy << "Ojciec:" << krz -> ojciec -> klucz << endl;
  }

  else
  {
      plikwy << "Ojciec:" << "Brak" << endl;
  }

  if(krz -> lewo != NULL)
  {
      plikwy << "Lewy Syn:" << krz -> lewo -> klucz << endl;
  }

  else
  {
      plikwy << "Lewy Syn:" << "Brak" << endl;
  }

  if(krz -> prawo != NULL)
  {
      plikwy << "Prawy Syn:" << krz -> prawo -> klucz << endl;
  }

  else
  {
      plikwy << "Prawy Syn:" << "Brak" << endl;
  }

  if(krz -> lewo)
  {
      preorder(krz -> lewo);
  }

  if(krz -> prawo)
  {
      preorder(krz -> prawo);
  }

}

void postorder(struct wzl *krz)
{
  if(krz -> lewo)
  {
      preorder(krz -> lewo);
  }

  if(krz -> prawo)
  {
      preorder(krz -> prawo);
  }

  plikwy << endl << endl;
  plikwy << "Wierzcholek:" << krz -> klucz << endl;
  plikwy << "Waga:" << krz -> waga << endl;

  if(krz -> ojciec != NULL)
  {
      plikwy << "Ojciec:" << krz -> ojciec -> klucz << endl;
  }

  else
  {
      plikwy << "Ojciec:" << "Brak" << endl;
  }


  if(krz -> lewo != NULL)
  {
      plikwy << "Lewy Syn:" << krz -> lewo -> klucz << endl;
  }

  else
  {
      plikwy << "Lewy Syn:" << "Brak" << endl;
  }

  if(krz -> prawo != NULL)
  {
      plikwy << "Prawy Syn:" << krz -> prawo -> klucz << endl;
  }

  else
  {
      plikwy << "Prawy Syn:" << "Brak" << endl;
  }
  plikwy << endl << endl;
}

void inorder(struct wzl *krz)
{
  if(krz -> lewo)
  {
      preorder(krz -> lewo);
  }

  plikwy << endl << endl;
  plikwy << "Wierzcholek:" << krz -> klucz << endl;
  plikwy << "Waga:" << krz -> waga << endl;

  if(krz -> ojciec != NULL)
  {
      plikwy << "Ojciec:" << krz -> ojciec -> klucz << endl;
  }

  else
  {
      plikwy << "Ojciec:" << "Brak" << endl;
  }

  if(krz -> lewo != NULL)
  {
      plikwy << "Lewy Syn:" << krz -> lewo -> klucz << endl;
  }

  else
  {
      plikwy << "Lewy Syn:" << "Brak" << endl;
  }

  if(krz -> prawo != NULL)
  {
      plikwy << "Prawy Syn:" << krz -> prawo -> klucz << endl;
  }

  else
  {
      plikwy << "Prawy Syn:" << "Brak" << endl;
  }

  plikwy << endl << endl;

  if(krz -> prawo)
  {
      preorder(krz -> prawo);
  }

}

void usundrzw(struct wzl *krz)
{
  if(krz -> lewo)
  {
      usundrzw(krz -> lewo);
  }

  if(krz -> prawo)
  {
      usundrzw(krz -> prawo);
  }

  cout << "Skasowano wezel:" << krz -> klucz << endl;
  free(krz);
}

int main()
{
  struct wzl *krz_rl = NULL;
  struct wzl *krzold = NULL;

  int nr = 1;
  int menu = 0;

  char tn;

  string nazwapliku = "";

  cout << "Program tworzacy drzewa BST-AVL" << endl;
  cout << "Wybierz co chcesz robic:" << endl;
  cout << "0 - Wczytaj dane z pliku" << endl;
  cout << "1 - Podaj dane z klawiatury(drzewo przestaje byc tworzone, gdy poda sie 0 jako wartosc wezla)" << endl;
  cin >> menu;

    if(menu == 0)
    {
        cout << "Podaj nazwe pliku z danymi:";
        cin >> nazwapliku;

        plikwe.open(nazwapliku.c_str(), ios::in);

        if(!plikwe.good())
        {
            cout << "Niepoprawna nazwa pliku" << endl;
            return 1;
        }


        plikwe >> nr;
        krz_rl = tworz_krz(nr);
        krzold = krz_rl;

        while(plikwe >> nr)
        {

            if(nr != 0)
            {
                zrobwzl(krz_rl,nr);
            }

        }

    }

    else if(menu == 1)
    {
        cout << "Podaj wartosc korzenia:" << endl;
        cin >> nr;
        krz_rl = tworz_krz(nr);
        krzold = krz_rl;
        cout << "Utworzono korzen drzewa" << endl;
        cout << "Wprowadz wartosci kolejnych wezlow:" << endl;

        while(nr != 0)
        {
            cin >> nr;

            if(nr != 0)
            {
                zrobwzl(krz_rl,nr);
            }
        }
    }


    else
    {
        cout << "Blad przy wyborze trybu pracy" << endl;
        return 1;
    }

    menu = 0;

  cout << "Utworzono drzewo BST-AVL" << endl;
  cout << "Jak zapisac drzewo:" << endl;
  cout << "1-PREORDER" << endl;
  cout << "2-INORDER" << endl;
  cout << "3-POSTORDER" << endl;
  cin >> menu;

  cout << "Zapisywanie drzewa" << endl << endl;
  plikwy.open("drzewo.txt", ios::out);

  if(menu == 1)
  {
      preorder(krz_rl);
  }

  else if(menu == 2)
  {
      inorder(krz_rl);
  }

  else if(menu == 3)
  {
      postorder(krz_rl);
  }

  else
  {
    cout << "Blad przy wyborze trybu pracy" << endl;
    return 1;
  }

 plikwy.close();

 cout << "Czy usunac drzewo?    T-tak   N-nie" << endl;
 cin >> tn;

 if(tn == 'T' || tn == 't')
 {
     usundrzw(krz_rl);
 }

 cout << "Koniec programu" << endl;


return 0;
}
