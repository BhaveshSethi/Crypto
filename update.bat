cp ../blowfish.cpp blowfish.cpp
cp ../Des.cpp Des.cpp
cp ../AES.cpp AES.cpp
cp ../RSA.cpp RSA.cpp
cp ../twofish.cpp  twofish.cpp
git add .
git commit -m "$1"
git push -u origin master
