returnStatus=0

# Only show colours on local "Git Bash" terminal
passFormat="if [ $TERM = "xterm" ]; then tput sgr0 && tput setaf 2; fi"
failFormat="if [ $TERM = "xterm" ]; then tput sgr0 && tput setaf 1; fi"
normalFormat="if [ $TERM = "xterm" ]; then tput sgr0; fi"

# If not on Linux set output to .exe
unameValue="$(uname -s)"
echo "Testing OS Platform: $unameValue"
fileExtension=".exe"
if [  $unameValue = "Linux" ] || [  $unameValue = "Darwin" ] ; then
    fileExtension=".out"
fi

echo "Running tests..."
echo

./a$fileExtension > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_1=$(./a$fileExtension 2>&1)

# don't worry about extra whitespace in the output
newOutput_1=""
while read line
do
  newOutput_1=$newOutput_1$(echo "$line" | xargs)
done <<< "$output_1"

expected_output_1="Invalid number of command line arguments."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_1" <<< "$newOutput_1"; then
  eval "$passFormat"
  echo "Test #1 - No Args - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #1 - No Args - Expected '$expected_output_1' but got: $newOutput_1"
  returnStatus=1
fi

echo

./a$fileExtension apple banana cucumber donut egg  > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_2=$(./a$fileExtension apple banana cucumber donut egg 2>&1)

# don't worry about extra whitespace in the output
newOutput_2=""
while read line
do
  newOutput_2=$newOutput_2$(echo "$line" | xargs)
done <<< "$output_2"

expected_output_2="Invalid number of command line arguments."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_2" <<< "$newOutput_2"; then
  eval "$passFormat"
  echo "Test #2 - Wrong Args Count - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #2 - Wrong Args Count - Expected '$expected_output_2' but got: $newOutput_2"
  returnStatus=1
fi

echo

./a$fileExtension apple banana cucumber donut > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_3=$(./a$fileExtension apple banana cucumber donut 2>&1)

# don't worry about extra whitespace in the output
newOutput_3=""
while read line
do
  newOutput_3=$newOutput_3$(echo "$line" | xargs)
done <<< "$output_3"

expected_output_3="Invalid command line argument usage."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_3" <<< "$newOutput_3"; then
  eval "$passFormat"
  echo "Test #3 - Wrong Args Format #1 - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #3 - Wrong Args Format #1 - Expected '$expected_output_3' but got: $newOutput_3"
  returnStatus=1
fi

echo

./a$fileExtension -i banana cucumber donut > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_4=$(./a$fileExtension -i banana cucumber donut 2>&1)

# don't worry about extra whitespace in the output
newOutput_4=""
while read line
do
  newOutput_4=$newOutput_4$(echo "$line" | xargs)
done <<< "$output_4"

expected_output_4="Invalid command line argument usage."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_4" <<< "$newOutput_4"; then
  eval "$passFormat"
  echo "Test #4 - Wrong Args Format #2 - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #4 - Wrong Args Format #2 - Expected '$expected_output_4' but got: $newOutput_4"
  returnStatus=1
fi

echo

./a$fileExtension -i banana -o donut > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_5=$(./a$fileExtension -i banana -o donut 2>&1)

# don't worry about extra whitespace in the output
newOutput_5=""
while read line
do
  newOutput_5=$newOutput_5$(echo "$line" | xargs)
done <<< "$output_5"

expected_output_5="Cannot open banana for reading."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_5" <<< "$newOutput_5"; then
  eval "$passFormat"
  echo "Test #5 - Bad Input File - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #5 - Bad Input File - Expected '$expected_output_5' but got: $newOutput_5"
  returnStatus=1
fi

echo

./a$fileExtension -i ./test-files/matrix1.txt -o ./nonfolder/out1.txt > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_6=$(./a$fileExtension -i ./test-files/matrix1.txt -o ./nonfolder/out1.txt 2>&1)

# don't worry about extra whitespace in the output
newOutput_6=""
while read line
do
  newOutput_6=$newOutput_6$(echo "$line" | xargs)
done <<< "$output_6"

expected_output_6="Cannot open ./nonfolder/out1.txt for writing."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_6" <<< "$newOutput_6"; then
  eval "$passFormat"
  echo "Test #6 - Bad Output File - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #6 - Bad Output File - Expected '$expected_output_6' but got: $newOutput_6"
  returnStatus=1
fi

echo

./a$fileExtension -i ./test-files/matrix1.txt -o ./test-files/out1.txt > /dev/null 2>&1

if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_7=$(cat ./test-files/out1.txt)

# don't worry about extra whitespace in the output
newOutput_7=""
while read line
do
  newOutput_7=$newOutput_7$(echo "$line" | xargs)
done <<< "$output_7"

expected_output_7="Is not a magic square"

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_7" <<< "$newOutput_7"; then
  eval "$passFormat"
  echo "Test #7 - Matrix #1 File - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #7 - Matrix #1 File - Expected '$expected_output_7' but got: $newOutput_7"
  returnStatus=1
fi

echo

./a$fileExtension -o ./test-files/out2.txt -i ./test-files/matrix2.txt > /dev/null 2>&1

if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_8=$(cat ./test-files/out2.txt)

# don't worry about extra whitespace in the output
newOutput_8=""
while read line
do
  newOutput_8=$newOutput_8$(echo "$line" | xargs)
done <<< "$output_8"

expected_output_8="Is a magic square (the sums are all 15)"

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_8" <<< "$newOutput_8"; then
  eval "$passFormat"
  echo "Test #8 - Matrix #2 File - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #8 - Matrix #2 File - Expected '$expected_output_8' but got: $newOutput_8"
  returnStatus=1
fi

echo

./a$fileExtension -i ./test-files/matrix3.txt -o ./test-files/out3.txt > /dev/null 2>&1

if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_9=$(cat ./test-files/out3.txt)

# don't worry about extra whitespace in the output
newOutput_9=""
while read line
do
  newOutput_9=$newOutput_9$(echo "$line" | xargs)
done <<< "$output_9"

expected_output_9="Is a magic square (the sums are all 34)"

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_9" <<< "$newOutput_9"; then
  eval "$passFormat"
  echo "Test #9 - Matrix #3 File - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #9 - Matrix #3 File - Expected '$expected_output_9' but got: $newOutput_9"
  returnStatus=1
fi

echo

./a$fileExtension -o ./test-files/out4.txt -i ./test-files/matrix4.txt > /dev/null 2>&1

if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_10=$(cat ./test-files/out4.txt)

# don't worry about extra whitespace in the output
newOutput_10=""
while read line
do
  newOutput_10=$newOutput_10$(echo "$line" | xargs)
done <<< "$output_10"

expected_output_10="Is not a magic square"

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_10" <<< "$newOutput_10"; then
  eval "$passFormat"
  echo "Test #10 - Matrix #4 File - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #10 - Matrix #4 File - Expected '$expected_output_10' but got: $newOutput_10"
  returnStatus=1
fi

echo

rm ./test-files/out*

if [ $returnStatus -eq 0 ] ; then
    eval "$passFormat"
    echo "All tests passed."
else
    eval "$failFormat"
    echo "One or more tests failed."
fi

eval "$normalFormat"

echo
exit $returnStatus