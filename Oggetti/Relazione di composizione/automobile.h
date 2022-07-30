#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include "Motore.h"

class Automobile {
    private:
        Motore motore;
        Serbatoio serbatoio;
    public:
        Automobile(string tipo_motore, string taglia_serbatoio);
        void rifornisci(double);
        void percorri(double);
        double autonomia();
        double chilometri();
};

#endif