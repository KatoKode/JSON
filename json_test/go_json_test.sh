#-------------------------------------------------------------------------------
#   Assembly Language Implementation of a B-Tree
#   Copyright (C) 2025  J. McIntosh
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#-------------------------------------------------------------------------------
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
