#include <iostream>
#include<fstream>
#include<cstring>
using namespace std;
ifstream f("Date2.txt");

struct arbore_b{
int val;
struct arbore_b *left, *right;

};

void inser_x(int x, struct arbore_b *&a)
{
     if(a!=NULL)
        {
          if(x<a->val)
           inser_x(x,a->left);

          if(x>a->val)
            inser_x(x,a->right);
        }
            else
            { a=new struct arbore_b;
              a->val=x;
              a->left=a->right=NULL;

            }


}

void afisare_sdr ( struct arbore_b *a)
{
    if(a!=NULL)
    {   afisare_sdr(a->left);
        afisare_sdr(a->right);
        cout<<a->val<<" ";

    }
}

void afisare_srd ( struct arbore_b *a)
{
    if(a!=NULL)
    {
        afisare_srd(a->left);
         cout<<a->val<<" ";
        afisare_srd(a->right);


    }
}

void afisare_rsd ( struct arbore_b *a)
{
    if(a!=NULL)
    {
        cout<<a->val<<" ";
        afisare_rsd(a->left);

        afisare_rsd(a->right);
    }
}


void search_x(int x, struct arbore_b *a)
{ struct arbore_b *b=a;
   cout<<"Cautam elementul "<< x<< " in arbore\n";
     while(b!=NULL&&x!=b->val)
        if(x<b->val)
            b=b->left;
          else
            b=b->right;

      if(b==NULL)
        cout<<"Valoarea "<<x<<" nu exista in arbore\n";
         else
        cout<<"Elementul "<<x<<" a fost gasit\n";

}

void delete_x(int x, struct arbore_b *&a)
{
    struct arbore_b *b=a, *aux, *c=a;

cout<<"Stergem elementul "<<x<<" din arbore\n";
   while(a!=NULL&&x!=a->val)
    if(x<a->val)
       a=a->left;
     else
       a=a->right;


       if(a==NULL)
          cout<<"Valoarea nu se afla in arbore\n";
          else
      { int ok=1;

          while((b->left!=NULL||b->right!=NULL)&&ok)
         { if(b->left!=NULL&&b->right!=NULL)
           {
             if(b->left->val!=x&&b->right->val!=x)
              if(x<b->val)
                b=b->left;
               else
                b=b->right;
              else
                ok=0;
           }
           else
        {
         if(b->left!=NULL)
            if(b->left->val!=x)
                b=b->left;
             else
                ok=0;
           else
           if(b->right!=NULL)
            if(b->right->val!=x)
                b=b->right;
             else
                ok=0;
           }
         }



         if( a->right==NULL&&a->left==NULL )
         {
           if(b->left!=NULL&&b->left->val==x)
             b->left=NULL;
             else
             b->right=NULL;

             delete a;
              a=c;
                    }
           else
         {
          if(a->left==NULL)
          {
              aux=a;
               if(b->left!=NULL&&b->left->val==x)
                b->left=a->right;         ///mai trebuie niste conditii pentru null la drp sau stg lui b
               else
                if(b->right!=NULL)
                b->right=a->right;
               delete aux;

          }

           if(a->right==NULL)
          {
              aux=a;
               if(b->left!=NULL&&b->left->val==x)
                b->left=a->left;
               else
                if(b->right!=NULL)
                b->right=a->left;
               delete aux;

          }

         }

         if( a->right!=NULL&&a->left!=NULL )
         {
             while(a->right->right!=NULL)
                   { a->val=a->right->val;
                     a->right->val=x;
                     a=a->right;
                     }
                  a->val=a->right->val;
                  a->right->val=x;
                  aux=a->right;
                  a->right=NULL;
                 delete aux;


         }
        a=c;
         cout<<"Valoare stearsa\n";

      }



}

void find_max ( struct arbore_b *a, int &m)  ///aceasta functie cauta max in tot arborele chiar daca se stie ca in B.S.T. max este cel mai din drp elem
{

    if(a!=NULL&&m<a->val)
        m=a->val;
    if(a!=NULL)
     {
         find_max(a->left,m);

         find_max(a->right,m);
     }
}

void afisare_nr_din_interval(struct arbore_b *a, int k1, int k2)
{
   if(a!=NULL)
   {

       if(k1<a->val&&a->val<k2)
        cout<<a->val<<" ";
        afisare_nr_din_interval(a->left,k1,k2);
        afisare_nr_din_interval(a->right,k1,k2);

   }

}

int main()
{ struct arbore_b *a=NULL;
 int x,k1,k2;
 char s[40];

  while(!f.eof() )
  {
        f.getline(s,41);
        if(strcmp(s,"inser")==0)
        {

            f>>x;
            inser_x(x,a);
        }
        else
            if(strcmp(s,"search")==0)
        {   f>>x;

            search_x(x,a);
        }
         else
            if(strcmp(s,"find_max")==0)
        {
            int m=a->val;
            find_max(a,m);
            cout<<"Maximul este: "<<m<<"\n";
        }
        else
            if(strcmp(s,"delete")==0)
        {
            f>>x;
            delete_x(x,a);

        }




    }



/*cout<<"Afisare SDR: ";
 afisare_sdr(a);
cout<<"\n";

cout<<"Afisare SRD: ";
 afisare_rsd(a);
 cout<<"\n";
*/
  cout<<"Afisare SRD arbore binar de cautare<=>sir sortat: ";
  afisare_srd (a);
  cout<<"\n\n\n";

  cout<<"Intro intervalul din care vrei sa afisezi numere existente in arbore: ";
  cin>>k1>>k2;
  cout<<"Valorile sunt: ";
  afisare_nr_din_interval(a,k1,k2);
  cout<<"\n";
    return 0;
}
