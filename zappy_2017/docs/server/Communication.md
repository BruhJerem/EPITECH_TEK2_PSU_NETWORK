# Player client connection

~~~
<-- = Le serveur répond
--> = Le client répond
{...} = Valeur / Variable


<-- WELCOME\n
--> {TEAM-NAME}\n
<-- {CLIENT-NUM}\n
<-- {X} {Y}\n


{TEAM-NAME} : Nom de la team que le client veut rejoindre, si la team n'existe
pas sur le serveur, le serveur repond "ko\n" directement sinon le serveur
envoie les {CLIENT-NAME} et {X} {Y} juste après.

{CLIENT-NAME} : Nombre de client autorisé a se connecter sur le serveur par
team, envoyé par le serveur au client.

{X} {Y} : Indique la taille de la map au client.

{X} {Y} et {CLIENT-NUM} sont des int positifs.
~~~

# UI client connection

~~~
<-- = Le serveur répond
--> = Le client graphique répond
{...} = Valeur / Variable


<-- WELCOME\n
--> GRAPHIC\n
<-- ok\n OU ko\n

Quand le client graphique se connecte sur le serveur, il envoie la chaine de
caratère suivante "GRAPHIC\n", le serveur répond ensuite par
les informations sur la map, etc .... si le serveur à accepté la connexion.

Une fois ces étapes de connexion passé, le client peut discuter avec le serveur
librement.
~~~
