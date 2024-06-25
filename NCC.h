#ifndef NCC_H
#define NCC_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class NCC {

private:
    string MaNCC;
    string TenNCC;
    string DiaChi;
    string STD;

public:
    NCC(const string& maNCC, const string& tenNCC, const string& diaChi, const string& sdt);
    NCC();
    ~NCC();
    void ShowNCC();
    void ReadFromFile(const string& filename);

    string GetMaNCC() const { return MaNCC; }
    string GetTenNCC() const { return TenNCC; }
    string GetDiaChi() const { return DiaChi; }
    string GetSTD() const { return STD; }
};

#endif // NCC_H

