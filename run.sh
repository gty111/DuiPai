g++ ac.cpp -o ac
g++ wa.cpp -o wa
g++ data.cpp -o data
while [ $? -eq 0 ]
do
    echo "..."
    ./data > data.output
    ./ac < data.output > ac.output
    ./wa < data.output > wa.output
    diff ac.output wa.output
done