#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
cmake --build .

cd ..
type addressdata.txt | _build/Debug/validate_emails.exe
type addressdata.txt | _build/Debug/validate_emails.exe --print-valid
type addressdata.txt | _build/Debug/validate_emails.exe --print-invalid
cd _build