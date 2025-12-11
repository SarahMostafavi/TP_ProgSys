# TP_ProgSys
# Compte Rendu du TP de programmation Système

Par Sarah Mostafavi Gorji et Nada Sbai

## I. Introduction
L'objectif du TP est de réaliser un terminal fonctionnel qui doit afficher les codes de sorties des programmes lancés ainsi que leur durée de fonctionnement.

## II. Projet

On commence par créer le microshell enseash.c qui va permettre de lancer les commandes. 
On va y ajouter les fonctionalités suivantes : 

### 1. Affichage du message d'accueil
L'objectif de cette fonctionalité est de faire apparaître un message d'acueil indiquant qu'on a ouvert le microshell. On doit également ajouter un prompt qui doit permettre de donner l'apparence d'un terminal.
Pour afficher le message, onutilise le programme **write()** à qui on fournit 3 arguments qui dans l'ordre sont :
* **STDOUT_FILENO** : pour indiquer qu'on souhaite écrire le message en sortie, dans le terminal
* **welcome_message** : le message de bienvenu sous forme de chaine de caractère.
* **Le nombre de caractères** du message de bienvenue à afficher.

On écrit également le prompt sous forme de chaine de caractère de la même manière que le message de bienvenue.

On teste ensuite le bon fonctionnement de ce programme. Pour cela, on le compile grâce au programme **gcc** dans le terminal. On indique également en paramètre du gcc que l'on doit entrer **"./enseash"** pour lancer notre microshell.
Après la compilation, on appelle donc le programme en entrant **"./enseash"**. On observe bien le comportement attendu, à savoir le message de bienvenu et le prompt qui s'affichent :
![Capture Question 1](capture_q1.png)

Cpendant à ce point du TP, le microshell ne peut rien faire d'autre. La prochaine étape est donc de lire les commandes entrées par l'utilisateur à la suite du prompt.

### 2. Exécution de la commande saisie et retour au prompt
 

## III. Conclusion
