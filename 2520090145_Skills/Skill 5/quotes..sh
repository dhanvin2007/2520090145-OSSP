#!/bin/bash

name="Dhanvin Goud"
course="Operating Systems"

echo "======================================"
echo "   SINGLE AND DOUBLE QUOTES IN BASH"
echo "======================================"

echo
echo "----- SINGLE QUOTES -----"

echo 'Hello World'
echo 'Name: $name'
echo 'Course: $course'

single='Hello $name'
echo "Stored single-quoted string: $single"

echo
echo "----- DOUBLE QUOTES -----"

echo "Hello World"
echo "Name: $name"
echo "Course: $course"

double="Hello $name"
echo "Stored double-quoted string: $double"

echo
echo "----- PRESERVING SPACES -----"

message="Operating Systems Lab"
echo "$message"

printf '<%s>\n' "Hello World"

echo
echo "----- SPECIAL CHARACTERS -----"

echo '$HOME'
echo "$HOME"

echo
echo "----- EDGE CASE -----"

empty=''
echo "Length of empty string: ${#empty}"

echo
echo "----- QUOTED COMMAND -----"

command="echo Hello from Ubuntu"
echo "Command stored as: $command"

echo "Executing command:"
eval "$command"

echo
echo "======================================"
echo "             TEST COMPLETED"
echo "======================================"
