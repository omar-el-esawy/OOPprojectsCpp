# include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//the base class
class FloatArray {
private:
    int size_;
protected:
    //to be shared to children
    int lastEmptyBac = 0;
    float *array;
public:
    FloatArray(int s) {
        size_ = s;
        array = new float[size_];
    }

    //simply add function
    virtual void add(float value) {
        array[lastEmptyBac] = value;
        lastEmptyBac++;
    }

    //overloading print in the file
    friend ofstream &operator<<(ofstream &out, FloatArray &f) {
        out << f.lastEmptyBac << "| ";
        for (int i = 0; i < f.lastEmptyBac; i++) {
            out << setw(6) << f.array[i] << ' ';
        }
        out << endl;
        return out;
    }

    //overloading read from the file
    friend ifstream &operator>>(ifstream &in, FloatArray &f) {
        float temp;
        in >> temp;
        f.add(temp);
        return in;
    }

    //deleting the array
    ~FloatArray() {
        delete[] array;
    }

};

class SortedArray : public FloatArray {
public:
    SortedArray(int s) : FloatArray(s) {
    }

// add to the right place to sort the array
    virtual void add(float value) {
        if (lastEmptyBac == 0)
            array[0] = value;
        else {
            if (value < array[lastEmptyBac - 1]) {
                for (int j = lastEmptyBac; j >= 0; j--)
                    if (value < array[j - 1] && j != 0) {
                        array[j] = array[j - 1];
                        array[j - 1] = value;
                    }
            } else {
                array[lastEmptyBac] = value;
            }
        }
        lastEmptyBac++;
    }

};

class FrontArray : public FloatArray {
public:
    FrontArray(int s) : FloatArray(s) {
    }
//add function that push from the front
    void add(float value) {
        if (lastEmptyBac == 0)
            array[0] = value;
        else {
            for (int j = lastEmptyBac; j > 0; j--) {
                array[j] = array[j - 1];
                array[j - 1] = value;
            }
        }
        lastEmptyBac++;
    }


};

class PositiveArray : public SortedArray {
public:
    PositiveArray(int s) : SortedArray(s) {

    }
//select positive numbers and add to function sort
    void add(float value) {
        if (value > 0) {
            SortedArray::add(value);
        }

    }

};

class NegativeArray : public SortedArray {
public:
    NegativeArray(int s) : SortedArray(s) {

    }
//select nagative numbers and add to function sort
    void add(float value) {
        if (value < 0) {
            SortedArray::add(value);
        }
    }

};

int main() {
    FloatArray *ptr;
    FloatArray *allArrays[10];
    int counter = 0;
    cout << "Enter the name of the input file: \n";
    string fileToReadFrom, fileToWriteTo;
    cin >> fileToReadFrom;
    ifstream ReadFrom(fileToReadFrom);
    string s;
    while (ReadFrom >> s) {
        int num;
        ReadFrom >> num;
        if (s == "Array") {
            ptr = new FloatArray(num);
        } else if (s == "Sorted") {
            ptr = new SortedArray(num);
        } else if (s == "Front") {
            ptr = new FrontArray(num);
        } else if (s == "Positive") {
            ptr = new PositiveArray(num);
        } else if (s == "Negative") {
            ptr = new NegativeArray(num);
        }
        while (num--) {
            ReadFrom >> *ptr;
        }
        allArrays[counter++] = ptr;
    }
    ReadFrom.close();
    cout << "Enter the name of the output file: \n";
    cin >> fileToWriteTo;
    ofstream WriteTo(fileToWriteTo);
    for (int i = 0; i < 10; i++)
        WriteTo << *allArrays[i];
    WriteTo.close();
    for (int i = 0; i < 10; i++)
        delete allArrays[i];

}
