#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
cmake --build .

cat ../addressdata.txt | ./validate_emails
cat ../addressdata.txt | ./validate_emails --print-valid
cat ../addressdata.txt | ./validate_emails --print-invalid
