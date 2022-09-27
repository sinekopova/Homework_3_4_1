#include <fstream>
#include <iostream>
#include <string>

struct Addr
{
    std::string city = "Город";
    std::string street = "Улица";
    unsigned short house = 0;
    unsigned short flat = 0;
};

class Address {
public:
    Address() {};
    Address(std::string city, std::string street, unsigned short house, unsigned short flat) {
        Addr adr{ city, street, house, flat };
        setAdress(adr);
    };

    bool setAdress(Addr addr) {
        m_addr.city = addr.city;
        m_addr.street = addr.street;
        m_addr.house = addr.house;
        m_addr.flat = addr.flat;
        return true;
    };

    std::string getAddressString() {
        return m_addr.city + ", " + m_addr.street + ", " + std::to_string( m_addr.house ) + ", " + std::to_string( m_addr.flat );
    };

private:
    Addr m_addr;
};

Address* readFile(std::ifstream& inFile, int& size);
void writeFile(std::ofstream& outFile, int size, Address* addresses);

int main()
{
    setlocale(LC_ALL, "Russian");


    std::ifstream inFile("in.txt");
    if (inFile.is_open()) {

        std::ofstream outFile("out.txt");
        if (!outFile.is_open()) {
            std::cout << "Не удалось открыть файл на запись!" << std::endl;
            return 0;
        }

        int size = 0;
        Address* addresses = readFile(inFile, size);
        writeFile(outFile, size, addresses);


        delete[] addresses;
        addresses = nullptr;

        inFile.close();
        outFile.close();

        std::cout << "Копирование данных закончено." << std::endl;
    }
    else {
        std::cout << "Не удалось открыть файл на чтение!" << std::endl;
    }

    return 0;
}

Address* readFile(std::ifstream& inFile, int& size) {

    size = 0;
    inFile >> size;

    Address* addresses = new Address[size]();

    for (int i = 0; i < size; ++i) {
        if (!inFile.eof()) {
            Addr addr;
            inFile >> addr.city;
            inFile >> addr.street;
            inFile >> addr.house;
            inFile >> addr.flat;
                
            addresses[i].setAdress( addr );
        }
    }
    return addresses;
};

void writeFile(std::ofstream& outFile, int size, Address* addresses) {
    outFile << size << std::endl;
    for (int i = size; i > 0; --i) {
        outFile << addresses[i-1].getAddressString() << std::endl;
    }
    outFile << std::endl;
};