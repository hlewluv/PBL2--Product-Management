#include "NCC.h"
using namespace std;

NCC::NCC(const string& maNCC, const string& tenNCC, const string& diaChi, const string& sdt)
    : MaNCC(maNCC), TenNCC(tenNCC), DiaChi(diaChi), STD(sdt) {}

NCC::NCC() {}
NCC::~NCC() {}

void NCC::ShowNCC() {
    cout << "Ma NCC: " << GetMaNCC() << endl;
    cout << "Ten NCC: " << GetTenNCC() << endl;
    cout << "Dia Chi: " << GetDiaChi() << endl;
    cout << "So Dien Thoai: " << GetSTD() << endl;
}

void NCC::ReadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Khong the mo file " << filename << " de doc." << endl;
        return;
    }

    file >> MaNCC >> TenNCC >> DiaChi >> STD;

    file.close();
}

