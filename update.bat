cp ../blowfish.cpp BF.cpp
cp ../Des.cpp Des.cpp
cp ../AES.cpp AES.cpp
cp ../RSA.cpp RSA.cpp
cp ../RC6.cpp RC6.cpp
cp ../../include/AEStable.h AEStable.h
cp ../../include/BFtable.h BFtable.h
cp ../../include/DEStable.h DEStable.h
git add .
git commit -m "$1"
git push -u origin master
