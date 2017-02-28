#!/bin/bash
# Updates the tree directories in the repo readmes

echo "Root dir:"
echo ~~~~ > README.md
tree -d -L 2 >> README.md
cat README.md
echo " "

echo "1000-Level-Courses/"
cd 1000-Level-Courses/
echo ~~~~ > README.md
tree -d -L 2 >> README.md
cat README.md
echo " "

echo "2000-Level-Courses/"
cd ../2000-Level-Courses/
echo ~~~~ > README.md
tree -d -L 2 >> README.md
cat README.md
echo " "

echo "3000-Level-Courses/"
cd ../3000-Level-Courses/
echo ~~~~ > README.md
tree -d -L 2 >> README.md
cat README.md
echo " "


