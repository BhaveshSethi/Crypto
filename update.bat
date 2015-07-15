cp ../blowfish.cpp blowfish.cpp
cp ../Des.cpp Des.cpp
cp ../AES.cpp AES.cpp
cp ../RSA.cpp RSA.cpp
cp ../RC6.cpp RC6.cpp
git add .
git commit -m "$1"
git push -u origin master
