# json_make.sh
sep="--------------------------------------------------------------------------------"

echo -e "${sep}"

builtin cd ./util/ || exit -1

make clean; make

test -e ./libutil.so || exit -1

echo -e "${sep}"

builtin cd ../json/ || exit -1

make clean; make

test -e ./libjson.so || exit -1

echo -e "${sep}"

builtin cd ../json_test || exit -1

make clean; make

test -e ./json_test || exit -1

chmod 744 ./go_json_test.sh || exit -1

echo -e "${sep}"

echo -e "alls well that ends well.\n"
