# go_json_test.sh
#
clear;

sep=" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"

echo -e "${sep}\n"

if [ -e ./json_test_1.json ];
then
  rm -f ./json_test_1.json
fi

if [ -e ./json_test_2.json ];
then
  rm -f ./json_test_2.json
fi

./json_test

if [ -e ./json_test_1.json ] && [ -e ./json_test_2.json ];
then
  echo -e "Dump of file: json_test_1.json\n"

  cat ./json_test_1.json

  echo -e "\n\nDump of file: json_test_2.json\n"

  cat ./json_test_2.json

  echo -e "\n\nDiff of JSON files:\n"

  diff -a -s ./json_test_1.json ./json_test_2.json

  echo;

echo -e "${sep}\n"

else
  echo -e "./json_test FAILED!\n"
fi
