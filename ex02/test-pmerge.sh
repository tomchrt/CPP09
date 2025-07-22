#!/bin/bash

echo "=== TESTS VALIDES ==="

echo -e "\nTest 1 : Mélangé simple"
./PmergeMe 5 2 9 1 7

echo -e "\nTest 2 : Décroissant"
./PmergeMe 10 9 8 7 6 5 4 3 2 1

echo -e "\nTest 3 : Doublons"
./PmergeMe 4 2 4 3 2 1 4 2

echo -e "\nTest 4 : Un seul élément"
./PmergeMe 42

echo -e "\nTest 5 : Deux éléments"
./PmergeMe 99 11

echo -e "\nTest 6 : Tous identiques"
./PmergeMe 7 7 7 7 7 7 7

echo -e "\nTest 7 : Alterné haut/bas"
./PmergeMe 1 100 2 99 3 98 4 97 5 96

echo -e "\nTest 8 : Aléatoire petite"
./PmergeMe 8 3 5 1 9 6 2 7 4

echo -e "\nTest 9 : Impair"
./PmergeMe 13 7 2 8 5

echo -e "\nTest 10 : 20 mélangés"
./PmergeMe $(shuf -i 1-20 -n 20)

echo -e "\nTest 11 : 3000 mélangés"
./PmergeMe $(shuf -i 1-3000 -n 3000)

echo "=== TESTS D'ERREUR ==="

echo -e "\nErreur 1 : Négatif"
./PmergeMe 1 2 -3 4 5 2>&1

echo -e "\nErreur 2 : Non numérique"
./PmergeMe 1 2 a 4 5 2>&1

echo -e "\nErreur 3 : Flottant"
./PmergeMe 1 2 3.5 4 5 2>&1

echo -e "\nErreur 4 : Vide"
./PmergeMe 2>&1

echo -e "\nErreur 5 : Zéro"
./PmergeMe 0 1 2 3 2>&1

echo -e "\nErreur 6 : Très grand nombre"
./PmergeMe 1 2 9999999999999999999999999 4 5 2>&1

echo -e "\nErreur 7 : Espace vide"
./PmergeMe \" \" 2>&1

echo -e "\nErreur 8 : Doublons (si tu veux les interdire, à activer)"
# ./PmergeMe 1 2 2 3 4 2>&1

echo -e "\nTous les tests sont terminés."
