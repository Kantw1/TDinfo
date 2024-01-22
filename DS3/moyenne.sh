#!/bin/bash
#1 a)
nb_argument=$#
for (( i=1 ; i<= $nb_argument ; i++)); do
	if (( ${!i} >= 0 && ${!i} <= 20 )); then
		echo " l'argument $i correspondant à ${!i} est vérifié"
	else
		echo " argument $i incorrecte "
		exit 1
	fi
done

#1 b)
moyenne=0
 for (( i=1; i<=$nb_argument ; i++ )) ; do
 	moyenne=$((moyenne + ${!i}))
 done
 moyenne=$(( moyenne / nb_argument))
 echo " la moyenne est $moyenne"
 
 #1 c)
 
if (( $moyenne < 7)); then
	echo " $moyenne veut dire redoublement"
elif (( $moyenne >= 7 && $moyenne <= 10)); then
	echo "$moyene veut dire rattrapage"
elif (( $moyenne > 10 && $moyenne <= 16)); then
	echo "$moyene veut dire passage"
 else
 	echo " $moyenne veut dire félicitation !!"
 fi
