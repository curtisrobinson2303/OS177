#!/bin/sh

# Name: Curtis 
# Date: Jan 8th 2024
# Title: Lab1 -
# Description: This is lab 1 where we computer the area of a rectangle and demonstrate how to use a bash script

echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$="$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "curtisrobinson" ] #Replace with your own username!
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
exit 1
fi
response="Yes"
while [ $response != "No" ]
do
    echo "Enter radius of circle: "
    read radius
    area=$(echo "3.14 * $radius * $radius" | bc -l)
    echo "The area of the circle is $area"
    echo "Would you like to repeat for another circle [Yes/No]?"
    read response
done