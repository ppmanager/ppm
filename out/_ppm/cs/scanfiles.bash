#!/bin/bash

rm -f _objs

echo -e "OBJSX = \\" >> _objs
find src -name "*.cs" -printf "	\$(SOURCE_DIR)/%P \<newLine>" | sed 's/<newLine>/\'$'\n/g' >> _objs
echo -e "\n\n" >> _objs

