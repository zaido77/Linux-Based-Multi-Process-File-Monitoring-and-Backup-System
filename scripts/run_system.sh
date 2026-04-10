#!/bin/bash

folderToScan="./filesToScan"
exeFile="./monitor"
logFile="logs/report.txt"
makeFile="makefile.mk"


echo "---System Build Started---"

if make -f "$makeFile"; then
    echo "[SUCCESS] Compilation completed"
else
    echo "[ERROR] Compilation failed"
    exit 1
fi

echo "---Running Monitor System on $folderToScan---"

$exeFile $folderToScan >> $logFile


if [ $? -eq 0 ]; then
    echo "------------------------------------------------"
    echo "SUCCESS | System done and logged to $logFile"
    echo "------------------------------------------------"
else
    echo "------------------------------------------------"
    echo "FAILURE | System exited with error"
    echo "------------------------------------------------"
fi
