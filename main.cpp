#include<iostream>
#include<string>
#include <pthread.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
// on définit une structure que l'on va utiliser pour passer les paramètre de nos fonctions en arguments dans la fonction pthread_create
struct values{
    
    string name; // non fichier
    string rep; // repertoire de travail
    int nbr;
} ;

// la fonction de cryptage
void * encrypt(void * args)

{
    values *ptr = static_cast<values*>(args); // conversion de void * en values type
    string reper(ptr->rep);
    
    string file_base = reper+"/"+ptr->name;

    
    string file_encrypted =reper+"/encrypted"+ptr->name;
    int key=ptr->nbr; // la clé de cryptage
    fstream fin, fout;
    char c;

    // overture des deux fichiers

    fin.open(file_base, fstream::in);
    fout.open(file_encrypted , fstream::out);

    // lecture du fichier jusqu'à la fin

    while (fin >> noskipws >> c) {
        int temp = (c + key);

    //  temp comme char
        
        fout << (char)temp;
    }

    // on ferme les deux fichiers
    fin.close();
    fout.close();
    pthread_exit(NULL); // pour quitter le processus proprement
    
};
// on définit la fonctions de decryptage
void * decrypt( void * args)
{
    
    values *ptr = static_cast<values*>(args); // conversion de void * args
    string file_encrypted = ptr->rep+"/"+ptr->name;  // chemin de notre fichier qu'on veut decrypter
    string file_base =ptr->rep+"/org"+ptr->name; // chemin du nouveau fihier criée après le decryptage
    int key;
    key=ptr->nbr; // la clé de cryptage
    char c;
    fstream fin;
    fstream fout;
    fin.open(file_encrypted, fstream::in);
    fout.open(file_base, fstream::out);

    while (fin >> noskipws >> c)
    {
        int temp = (c - key);
        fout << (char)temp;
    }

    fin.close();
    fout.close();
   pthread_exit(NULL);
};


int main()
    {
        cout<<"entrez le répertoire de travail \n ";
        string repertoire;
        cin>>repertoire;
        
        int n;
        cout<<"le nombre des fichiers"<<endl;
        cin>>n;
        
        
        char c;
       // string name1;
            cout << "\n";
        cout << "Quel est votre choix ? \n";
        cout << "1 : encrypt \n";
        cout << "2 : decrypt \n";
        cin >> c;
        
        // on définie les composantes de la fonction pthread_creat()
        
        int id[n]; // création de n valeur de retour pour la fonction pthread_create()
        pthread_t p[n]; //// création de n id pour la fonction pthread_create()
        struct values vals[n] ; // création de n structure
        
        struct values *tab[n] ;//création de n pointeur de type struct valeurs
        
        // dans cette boucle on remplit les structures
       for (int i =0; i<n ; i++)
       {
                    cout << "entez le clé de cryptage "<<i+1<<endl;
                    cin>>vals[i].nbr;
                    cout<<"entrez le nom du fichier ? \n";
           
                    cin>>vals[i].name;
           vals[i].rep=repertoire;
       }
    
  
    
        
        //pointer les n pointeurs vers les structures
        for(int i=0 ; i<n; i++){
        tab[i]=&vals[i];
        }
        switch (c) {
            case '1':
            {

                    for (int i =0 ; i<n; i++)
                    {
                                id[i] = pthread_create(&p[i] , NULL , encrypt ,  (void*)tab[i]); //création du thread
                                  pthread_join(p[i], NULL);

                    }
                
                    break;
            }
            case '2':
            {
                
                    for (int i =0 ; i<n; i++)
                    {
                        
                        id[i] = pthread_create(&p[i] , NULL , decrypt ,  (void*)tab[i]); //création de thread
                         pthread_join(p[i], NULL);

                }



            break;
        }
    }
        
        
        
        return 0;
}
