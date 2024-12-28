# Minishell
## Description
Minishell est un projet visant à recréer une version simplifiée de Bash. Ce shell interactif permet l'exécution de commandes de base, la gestion des redirections, des pipes, et l'interprétation des variables d'environnement tout en respectant un comportement proche de celui de Bash.

Ce projet est conçu pour améliorer la compréhension des mécanismes internes des shells Unix/Linux et de leur interaction avec le système d'exploitation.

## Fonctionnalités principales
### Fonctionnalités de base
- Prompt interactif : Affiche un prompt en attente de commandes utilisateur.
- Historique : Conserve les commandes précédentes pour un rappel facile.
- Exécution des commandes :
  - Basé sur la variable PATH ou via un chemin relatif/absolu.
  - Supporte les commandes externes et internes.

### Gestion des métacaractères
- Gestion des quotes simples (') : Empêche l'interprétation des métacaractères.
- Gestion des quotes doubles (") : Empêche l'interprétation sauf pour le caractère $.

### Redirections
-   < : Redirection de l'entrée standard.
-   \> : Redirection de la sortie standard.
-   << : Mode "heredoc" avec un délimiteur.
-   \>> : Redirection de la sortie en mode append.

### Pipes
- Support complet des pipes (|) pour chaîner plusieurs commandes :
- L'entrée de chaque commande est connectée à la sortie de la commande précédente.

### Variables d'environnement
- Expansion des variables : Interprétation de $variable en utilisant les valeurs de l'environnement.
- $? : Affiche le code de retour de la dernière commande exécutée.

### Gestion des signaux
- Ctrl+C : Interrompt la commande en cours et affiche un nouveau prompt.
- Ctrl+D : Quitte le shell.
- Ctrl+\ : Ne fait rien.

### Builtins
- echo : Affiche un message avec prise en charge de l'option -n.
- cd : Change de répertoire avec un chemin relatif ou absolu.
- pwd : Affiche le répertoire courant.
- export : Ajoute ou modifie des variables d'environnement.
- unset : Supprime des variables d'environnement.
- env : Affiche toutes les variables d'environnement.
- exit : Quitte le shell proprement.

### contributor
- [sycourbi](https://github.com/Sycourbi)
- [vetudenoir](https://github.com/vetuedenoir)
