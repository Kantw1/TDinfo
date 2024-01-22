#!/bin/bash
#2 a)
if [ "$#" -ne 2 ] ; then
	echo "Erreur! syntaxe d'appel $0 f1 f2"
	exit 1
fi
#2 b)
fichier1=$1
fichier2=$2

if [ -e $fichier1 ]; then
	echo "le fichier $fichier1 existe"
fi

nombre_ligne=$(find . -iname "$fichier1" -exec wc -l {} \;)
echo "$nombre_ligne"

#2 c)
find . -iname "$fihcher2" -exec rm -f {} \;



