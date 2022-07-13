Notre programme prend en entrée n fichiers de n'importe quelle extension et fait le cryptage ou le décryptage.
L'utilisateur choisit une clé pour chaque fichier, cette clé sera nécessaire dans le décryptage donc il faut le préserver.
Ce qui caractérise notre programme c'est le processus de cryptage parallèle de tous les fichiers. 
En fait chaque fichier est crypté ou décrypte, selon le choix de l'utilisateur, par un Thread indépendant, ce qui donne l'impression, à l'utilisateur, que le l'opération sur les n fichiers se fait simultanément.
Pour une raison de flexibilité le programme demande à l'utilisateur d'entrer le répertoire du travail. Ce répertoire doit contenir les fichiers qu'on souhait crypter ou décrypter.
La sortie du programme est un fichier crée dans le répertoire du travail. Les fichiers crées préservent l'extension originale.
