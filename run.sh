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
    ./data > data.output
    ./ac < data.output > ac.output
    ./wa < data.output > wa.output
    diff ac.output wa.output
done

