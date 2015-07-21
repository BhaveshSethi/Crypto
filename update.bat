cp ../blowfish.cpp BF.cpp
cp ../Des.cpp Des.cpp
cp ../AES.cpp AES.cpp
cp ../RSA.cpp RSA.cpp
cp ../RC6.cpp RC6.cpp
cp ../../include/AEStable.h AEStable.h
cp ../../include/BFtable.h BFtable.h
cp ../../include/DEStable.h DEStable.h
cp ../All.cpp ALL/All.cpp
cp ../../include/AES.h 		ALL/AES.h
cp ../../include/BLOWFISH.h 	ALL/BF.h
cp ../../include/DES.h 		ALL/DES.h
cp ../../include/RC6.h		ALL/RC6.h
cp ../../include/RSA.h		ALL/RSA.h
git add .
git commit -m "$1"
git push -u origin master
