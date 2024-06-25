#include "PhieuNhap.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

PhieuNhap::PhieuNhap() : NCC(), MatHang(), Date(), maPhieu(""), soLuongNhap(0) {}

PhieuNhap::PhieuNhap(const string& maPhieu, int soLuongNhap,
                     const string& maNCC, const string& tenNCC, const string& diaChi, const string& sdt,
                     int day, int month, int year,
                     const string& maHang, const string& tenHang, float donGia)
    : NCC(maNCC, tenNCC, diaChi, sdt),
      MatHang(maHang, "", tenHang, 0, donGia),
      Date(day, month, year),
      maPhieu(maPhieu),
      soLuongNhap(soLuongNhap) {}

void PhieuNhap::setSoLuongNhap(const int& soLuong) {
    soLuongNhap = soLuong;
}

int PhieuNhap::getSoLuongNhap() const {
    return soLuongNhap;
}

void PhieuNhap::setMaPhieu(const string& ma) {
    maPhieu = ma;
}

string PhieuNhap::getMaPhieu() const {
    return maPhieu;
}

 void PhieuNhap::SetMaHang(const string& ma) {
     maHang = ma;
 }

 string PhieuNhap::GetMaHang() const {
     return maHang;
 }

float PhieuNhap::Giamgia() {
    float ThanhTien =  getSoLuongNhap() * getGiaTien();
    if (getSoLuongNhap() > 200) {
        ThanhTien *= 0.85;
    } else if (getSoLuongNhap() > 100) {
        ThanhTien *= 0.9;
    }
    return ThanhTien;
}
void PhieuNhap::hienThiThongTin() const {
    cout << "=============== THONG TIN CHI TIET CUA PHIEU NHAP ===============" << endl;
    cout << "_________________________________________________________________" << endl;
    cout << left << setw(9) << "| Ma Phieu: " << left << setw(14) << maPhieu;
    cout << left << setw(9) << " Ngay Nhap: ";
    HienThiNgayThang();
    cout << left << setw(20) <<"| So Luong Nhap :" << left << setw(44) << soLuongNhap << "|" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << left << setw(64) << "| Thong tin NCC: " << "|" << endl;
    cout << left << setw(14) << "| Ma NCC:     " << left << setw(12) << GetMaNCC();
    cout << left << setw(10) << " Ten NCC:    " << left << setw(12) << GetTenNCC() << "\t\t|"<< endl;
    cout << left << setw(14) << "| Dia Chi:   " << left << setw(12) << GetDiaChi();
    cout << left << setw(14) << " SDT:       " << left << setw(12) << GetSTD() << "\t\t|"<< endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << left << setw(64) << "| Thong tin Mat Hang: " << "|" << endl;
    cout << left << setw(14) << "| Ma Hang:    " << left << setw(12) << getMaHang();
    cout << left << setw(14) << " Ten Hang:   " << left << setw(12) << getTenHang() << "\t\t|"<< endl;
    cout << left << setw(14) << "| Don Gia:    " << left << setw(50) << getGiaTien() << "|" << endl;
    cout << left << setw(14) << "| Tong tien:   " << left << setw(49) << getGiaTien() * soLuongNhap << "|" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    PhieuNhap phieuNhap = *this;
    cout << left << setw(54) << "| Sau khi su dung giam gia: " << left << setw(10) << phieuNhap.Giamgia() << "|" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << endl;
    }


QuanLyPhieuNhap::QuanLyPhieuNhap(int size, QuanLyMatHang& qlMatHang) : quanLyMatHang(qlMatHang) {
    danhSachPhieu = new PhieuNhap[size];
    soLuongPhieu = 0;
}
QuanLyPhieuNhap::~QuanLyPhieuNhap() {
    delete[] danhSachPhieu;
}
void QuanLyPhieuNhap::DocDuLieu(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong mo duoc file " << filename << " de doc." << endl;
        return;
    }
    while (!file.eof()) {
        string maPhieu, maNCC, tenNCC, diaChiNCC, sdtNCC, ngay, maHang, tenHang;
        int soLuongNhap, day, month, year;
        float donGia;

        getline(file, maPhieu, ',');
        if (maPhieu.empty()) {
            break; // Đọc hết file
        }
        file >> soLuongNhap;
        file.ignore();

        getline(file, maNCC, ',');
        getline(file, tenNCC, ',');
        getline(file, diaChiNCC, ',');
        getline(file, sdtNCC, ',');

        file >> day;
        file.ignore();
        file >> month;
        file.ignore(); 
        file >> year;
        file.ignore(); 
    
        getline(file, maHang, ',');
        getline(file, tenHang, ',');
        file >> donGia;
        file.ignore();


        // Tạo đối tượng PhieuNhap từ dữ liệu đọc được và thêm vào danh sách
        PhieuNhap phieu(maPhieu, soLuongNhap, maNCC, tenNCC, diaChiNCC, sdtNCC, day, month, year, maHang, tenHang, donGia);        
        ThemPhieuNhap(phieu);
    }

    file.close();
}

void QuanLyPhieuNhap::ThemPhieuNhap(const PhieuNhap& phieu) {
    // Tạo mảng tạm thời lớn hơn để chứa dữ liệu mới
    PhieuNhap* temp = new PhieuNhap[soLuongPhieu + 1];
    // Copy dữ liệu từ danh sách cũ sang danh sách mới
    for (int i = 0; i < soLuongPhieu; ++i) {
        temp[i] = danhSachPhieu[i];
    }
    // Thêm phiếu mới vào cuối danh sách
    temp[soLuongPhieu] = phieu;
    soLuongPhieu++; // Tăng số lượng phiếu sau khi thêm mới thành công
    // Xóa danh sách cũ
    delete[] danhSachPhieu;
    // Cập nhật con trỏ danh sách mới
    danhSachPhieu = temp;

    // Lưu dữ liệu vào file
    LuuDuLieu("PhieuNhap.txt");

    // Cập nhật số lượng mặt hàng trong danh sách mặt hàng của QuanLyMatHang
    quanLyMatHang.CapNhatSoLuong(phieu.getMaHang(), phieu.getSoLuongNhap());

}

void QuanLyPhieuNhap::LuuDuLieu(const string &filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << filename << " de ghi." << endl;
        return;
    }

    for (int i = 0; i < soLuongPhieu; ++i) {
        file << danhSachPhieu[i].getMaPhieu() << ",";
        file << danhSachPhieu[i].getSoLuongNhap() << ",";
        // Ghi thông tin NCC
        file << danhSachPhieu[i].GetMaNCC() << ",";
        file << danhSachPhieu[i].GetTenNCC() << ",";
        file << danhSachPhieu[i].GetDiaChi() << ",";
        file << danhSachPhieu[i].GetSTD() << ",";
        // Ghi thông tin ngày
        file << danhSachPhieu[i].getDay() << "/" << danhSachPhieu[i].getMonth() << "/" << danhSachPhieu[i].getYear() << ",";
        // Ghi thông tin mặt hàng
        file << danhSachPhieu[i].getMaHang() << ",";
        file << danhSachPhieu[i].getTenHang() << ",";
        file << danhSachPhieu[i].getGiaTien() << endl;
    }

    file.close();
}

void QuanLyPhieuNhap::HienThiDanhSachPhieuNhap() const {
    cout << "=========================================================" << endl;
    cout << "||" << "\t\tTOM TAT PHIEU NHAP:\t\t\t||"  << endl;
    cout << "=========================================================" << endl;

    for (int i = 0; i < soLuongPhieu; ++i) {
        cout << "||  phieu: " << left << setw(6) << danhSachPhieu[i].getMaPhieu() << ", ";
        cout << "Ma NCC: " << left << setw(7) << danhSachPhieu[i].GetMaNCC() << ", ";
        cout << "So luong nhap: " << left << setw(5) << danhSachPhieu[i].getSoLuongNhap()  << "||" << endl;
        cout << "||" << "______________________________________________________" << "||" << endl;
        // Lựa chọn xem chi tiết phiếu nhập
        // cout << "Nhap " << i + 1 << " de xem chi tiet Phieu Nhap " << i + 1 << endl;
    }

    cout << "||" << "\tNhap STT de xem chi tiet Phieu Nhap\t\t" << "||" << endl;
    cout << "=========================================================" << endl << endl;

    // Xử lý việc xem chi tiết
    string maPhieu;
    cout << "Nhap Ma Phieu: ";
    cin >> maPhieu;

    bool found = false;
    for (int i = 0; i < soLuongPhieu; ++i) {
        if (danhSachPhieu[i].getMaPhieu() == maPhieu) {
            danhSachPhieu[i].hienThiThongTin(); // Hiển thị chi tiết phiếu nhập tương ứng với mã nhập
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay phieu nhap co ma: " << maPhieu << endl;
    }
}



void QuanLyPhieuNhap::XoaPhieuNhap(const string &maPhieu) {
    bool found = false;
    for (int i = 0; i < soLuongPhieu; ++i) {
        if (danhSachPhieu[i].getMaPhieu() == maPhieu) {
            found = true;
            // Di chuyển các phần tử sau về phía trước để ghi đè lên phần tử cần xóa
            for (int j = i; j < soLuongPhieu - 1; ++j) {
                danhSachPhieu[j] = danhSachPhieu[j + 1];
            }
            break;
        }
    }

    if (found) {
        soLuongPhieu--;
        PhieuNhap *newDanhSachPhieu = new PhieuNhap[soLuongPhieu];
        for (int i = 0; i < soLuongPhieu; ++i) {
            newDanhSachPhieu[i] = danhSachPhieu[i];
        }
        delete[] danhSachPhieu;
        danhSachPhieu = newDanhSachPhieu;
        cout << "Da xoa phieu nhap co ma: " << maPhieu << endl;
    } else {
        cout << "Khong tim thay phieu nhap co ma: " << maPhieu << endl;
    }
    LuuDuLieu("PhieuNhap.txt");
}

void QuanLyPhieuNhap::CapNhatsoluong(const PhieuNhap &phieu)
{
    quanLyMatHang.CapNhatSoLuong(phieu.getMaHang(), phieu.getSoLuongNhap());
}

int QuanLyPhieuNhap::TongSoLuongHangNhap() const {
    int tong = 0;
    for (int i = 0; i < soLuongPhieu; ++i) {
        tong += danhSachPhieu[i].getSoLuongNhap();
    }
    return tong;
}
float QuanLyPhieuNhap::TongGiaTriHangNhap() const {
    float tong = 0.0f;
    for (int i = 0; i < soLuongPhieu; ++i) {
        tong += danhSachPhieu[i].getSoLuongNhap() * danhSachPhieu[i].getGiaTien();
    }
    return tong;
}

map<string, int> QuanLyPhieuNhap::ThongKeSoLuongHangNhapTheoNCC() const {
    map<string, int> quantityBySupplier;
    for (int i = 0; i < soLuongPhieu; ++i) {
        string maNCC = danhSachPhieu[i].GetMaNCC();
        quantityBySupplier[maNCC] += danhSachPhieu[i].getSoLuongNhap();
    }
    return quantityBySupplier;
}

map<string, float> QuanLyPhieuNhap::ThongKeGiaTriHangNhapTheoNCC() const {
    map<string, float> valueBySupplier;
    for (int i = 0; i < soLuongPhieu; ++i) {
        string maNCC = danhSachPhieu[i].GetMaNCC();
        valueBySupplier[maNCC] += danhSachPhieu[i].getSoLuongNhap() * danhSachPhieu[i].getGiaTien();
    }
    return valueBySupplier;
}
