#-------------------------------------------------------------------------------
#   JSON (JSON) Library Implementation in C with Assembly Language Support
#   Libraries
#
#   Copyright (C) 2025  J. McIntosh
#
#   JSON is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   JSON is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with JSON; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#-------------------------------------------------------------------------------
# !/bin/sh
#
clear;

sep=" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"

echo -e "${sep}\n"

if [ -e ./demo_1.json ];
then
  rm -f ./demo_1.json
fi

if [ -e ./demo_2.json ];
then
  rm -f ./demo_2.json
fi

./demo

if [ -e ./demo_1.json ] && [ -e ./demo_2.json ];
then
  echo -e "Dump of file: demo_1.json\n"

  cat ./demo_1.json

  echo -e "\n\nDump of file: demo_2.json\n"

  cat ./demo_2.json

  echo -e "\n\nDiff of JSON files:\n"

  diff -a -s ./demo_1.json ./demo_2.json

  echo;

echo -e "${sep}\n"

else
  echo -e "./demo FAILED!\n"
fi
