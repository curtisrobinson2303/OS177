#!/bin/bash
#Thanks to Daniel Kazarian

make clean

echo "Step A:"
ls -l file?.bin
sleep 2

echo "Step B:"
make
sleep 2

echo "Step C:"
echo "C: Step 4"
time ./Step4 file3.bin 10000
ls -l file?.bin copy*.out
sleep 3
diff file3.bin copy*.out
rm -f copy*.out
sleep 2

echo "C: Step 5"
time ./Step5 file3.bin 10000 4
ls -l file?.bin copy*.out
sleep 3
diff file3.bin copy*.out
rm -f copy*.out
sleep 2

echo "Step D:"
bash step2.sh
sleep 2
bash step3.sh
sleep 2
bash step4.sh
sleep 2
bash step5.sh
sleep 2

echo "Step E:"
make clean

