[ ! -d log ] && mkdir log
g++ ac.cpp -o ac
if [ $? -ne 0 ] ; then
    return
fi
g++ wa.cpp -o wa
if [ $? -ne 0 ] ; then
    return
fi
g++ data.cpp -o data
while [ $? -eq 0 ]
do
    echo "..."
    ./data > log/data.output
    ./ac < log/data.output > log/ac.output
    ./wa < log/data.output > log/wa.output
    diff log/ac.output log/wa.output
done

