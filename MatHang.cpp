#include "MatHang.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include <algorithm>
#include <cctype> 
using namespace std;

MatHang::MatHang() : ma_hang(""), don_vi(""), ten_hang(""), so_luong_hang_hoa(0), GiaTien(0.0) {}

MatHang::MatHang(const string& ma_hang, string don_vi, string ten_hang, int so_luong_hang_hoa, float gia_tien)
    : ma_hang(ma_hang), don_vi(don_vi), ten_hang(ten_hang), so_luong_hang_hoa(so_luong_hang_hoa), GiaTien(gia_tien) {}


float MatHang::TinhTien() {
    float ThanhTien = getSoLuongHangHoa() * getGiaTien();
    if (getSoLuongHangHoa() > 200) {
        ThanhTien *= 0.85;
    } else if (getSoLuongHangHoa() > 100) {
        ThanhTien *= 0.9;
    }
    return ThanhTien;
}

float MatHang::TinhTien(int soluong){
        float ThanhTien = soluong * getGiaTien();
    if (soluong > 200) {
        ThanhTien *= 0.85;
    } else if (soluong > 100) {
        ThanhTien *= 0.9;
    }
    return ThanhTien;
}

string MatHang::getMaHang() const {
    return ma_hang;
}

string MatHang::getDonVi() const {
    return don_vi;
}
string MatHang::getTenHang() const {
    return ten_hang;
}
int MatHang::getSoLuongHangHoa() const {
    return so_luong_hang_hoa;
}
float MatHang::getGiaTien() const{
    return GiaTien;
}

void MatHang::setSoLuongHangHoa(int newSoLuong) {
    so_luong_hang_hoa = newSoLuong;
}

void MatHang::ShowHeader() {
    for (int i = 0; i < 75; ++i) {
        cout << "-";
    }
    cout << endl;
    cout << left << setw(15) << "|   Ma Hang";
    cout << left << setw(17) << "|   Don Vi";
    cout << left << setw(17) << "|   Ten Hang";
    cout << left << setw(13) << "|   So luong";
    cout << left << setw(10) << "| Gia Tien " << "|"<< endl;

    for (int i = 0; i < 75; ++i) {
        cout << "-";
    }
    cout << endl;
}

void MatHang::Show() const {
    if (so_luong_hang_hoa <= 0) {
        // Không hiển thị thông báo khi hàng hóa trong kho đã hết
        return;
    } else {
        cout <<"|  " << left << setw(12) <<  ma_hang;
        cout <<"|  " << left << setw(14) <<  don_vi;
        cout <<"|  " << left << setw(14) << ten_hang;
        cout <<"|  " << left << setw(10) << so_luong_hang_hoa;
        cout <<"|  " << left  << setw(8)<< GiaTien << "|" << endl;
   
    }
}
int QuanLyMatHang::TongSoLuongHangHoa() const {
    int tongSoLuong = 0;
    for (int i = 0; i < soLuongMatHang; ++i) {
        tongSoLuong += danh_sach_mat_hang[i].getSoLuongHangHoa();
    }
    return tongSoLuong;
}

QuanLyMatHang::QuanLyMatHang(int soLuongMatHang) : soLuongMatHang(soLuongMatHang) {
    danh_sach_mat_hang = new MatHang[soLuongMatHang];
    this->soLuongMatHang = soLuongMatHang;
    soLuongHienTai = 0;
}

QuanLyMatHang::~QuanLyMatHang() {
    delete[] danh_sach_mat_hang;
}

MatHang* QuanLyMatHang::getDanhSachMatHang() const {
    return danh_sach_mat_hang;
}

int QuanLyMatHang::getSoLuongMatHang() const {
    return soLuongMatHang;
}


void QuanLyMatHang::TimMatHang(const string& ma_hang) {
    // Xóa nội dung file "TimHang.txt" trước khi tìm kiếm và lưu vào
    ofstream clear_tim_hang_file("TimHang.txt", ios::trunc);
    clear_tim_hang_file.close();

    MatHang::ShowHeader();

    for (int i = 0; i < soLuongMatHang; i++) {
        // Kiểm tra xem chuỗi "ma_hang" có là một phần của mã hàng hay không
        if (danh_sach_mat_hang[i].getMaHang().find(ma_hang) != string::npos) {
            danh_sach_mat_hang[i].Show();
            cout << endl;
            // Lưu thông tin hàng vào file "TimHang.txt"
            ofstream tim_hang_file("TimHang.txt", ios::app); // Mở file để ghi (append)
            if (tim_hang_file.is_open()) {    
                tim_hang_file << danh_sach_mat_hang[i].getMaHang() << ", "
                               << danh_sach_mat_hang[i].getDonVi() << ", "
                               << danh_sach_mat_hang[i].getTenHang() << ", "
                               << danh_sach_mat_hang[i].getSoLuongHangHoa() << ", "
                               << danh_sach_mat_hang[i].getGiaTien() << endl;
                tim_hang_file.close();
            } else {
                cout << "Khong mo duoc file TimHang.txt." << endl;
            }
        }
    }

    // Kiểm tra xem đã tìm thấy hay chưa để thông báo
    if (ifstream("TimHang.txt").peek() == ifstream::traits_type::eof()) {
        cout << "Khong tim thay mat hang." << endl;
    }
}

void QuanLyMatHang::ThemMatHang(const MatHang& mat_hang) {
    // Nếu mã hàng không tồn tại, thêm mặt hàng mới
    for (int i = 0; i < soLuongMatHang; i++) {
        if (danh_sach_mat_hang[i].getMaHang().empty()) {
            danh_sach_mat_hang[i] = mat_hang;
            soLuongHienTai++;

            // Lưu danh sách mặt hàng vào file sau khi thêm mặt hàng mới
            LuuDuLieuVaoFile("Hang.txt");
            return;
        }
    }

    cout << "Khong the them mat hang. Danh sach da day." << endl;
}


void QuanLyMatHang::LuuDuLieuVaoFile(const string& ten_file) const {
    ofstream file(ten_file);
    if (!file.is_open()) {
        cout << "Khong mo duoc file." << endl;
        return;
    }

    for (int i = 0; i < soLuongMatHang; ++i) {
        if (!danh_sach_mat_hang[i].getMaHang().empty()) {

        
            file << danh_sach_mat_hang[i].getMaHang() << ","
                 << danh_sach_mat_hang[i].getDonVi() << ","
                 << danh_sach_mat_hang[i].getTenHang() << ","
                 << danh_sach_mat_hang[i].getSoLuongHangHoa() << ","
                 << danh_sach_mat_hang[i].getGiaTien();

            // Xuống dòng sau mỗi thông tin hàng hóa
            file << endl;
        }
    }

    file.close();
}



void QuanLyMatHang::XoaMatHang(const string& ma_hang) {
    for (int i = 0; i < soLuongMatHang; i++) {
        if (danh_sach_mat_hang[i].getMaHang() == ma_hang) {
            for (int j = i + 1; j < soLuongMatHang; j++) {
                danh_sach_mat_hang[j - 1] = danh_sach_mat_hang[j];
            }
            soLuongMatHang--;
            soLuongHienTai++;

            // Lưu danh sách mặt hàng vào file sau khi xóa mặt hàng
            LuuDuLieuVaoFile("Hang.txt");

            return;
        }
    }
    cout << "Khong tim thay mat hang." << endl;
}


void QuanLyMatHang::XoaDonVi(const string& don_vi) {
    for (int i = 0; i < soLuongMatHang; ++i) {
        if (danh_sach_mat_hang[i].getDonVi() == don_vi) {
            for (int j = i + 1; j < soLuongMatHang; ++j) {
                danh_sach_mat_hang[j - 1] = danh_sach_mat_hang[j];
            }
            soLuongMatHang--;
            soLuongHienTai--;

            // Lưu danh sách mặt hàng vào file sau khi xóa mặt hàng
            LuuDuLieuVaoFile("Hang.txt");

            cout << "Da xoa cac mat hang co don vi '" << don_vi << "'." << endl;
            return;
        }
    }

    cout << "Khong tim thay mat hang voi don vi '" << don_vi << "'." << endl;
}

void QuanLyMatHang::DocDuLieuTuFile(const string& ten_file) {
    ifstream file(ten_file);
    if (!file.is_open()) {
        cout << "Khong mo duoc file." << endl;
        return;
    }

    Vector<MatHang> mat_hang_vector;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string ma_hang, don_vi, ten_hang;
        int so_luong_hang_hoa;
        float GiaTien;

        if (getline(iss, ma_hang, ',') && getline(iss, don_vi, ',') &&
            getline(iss, ten_hang, ',') && (iss >> so_luong_hang_hoa) &&
            (iss.ignore(1, ',') && (iss >> GiaTien))) {

            MatHang mat_hang(ma_hang, don_vi, ten_hang, so_luong_hang_hoa, GiaTien);
            mat_hang_vector.push_back(mat_hang);
        } else {
            cout << "Loi dinh dang file." << endl;
            continue;
        }
    }

    file.close();

    for (int i = 0; i < mat_hang_vector.getSize(); ++i) {
        ThemMatHang(mat_hang_vector[i]);
    }
}

void QuanLyMatHang::HienThiDanhSachMatHang() const {
    MatHang::ShowHeader();
    // In ra màn hình và ghi vào file thông tin từng mặt hàng
    for (int i = 0; i < soLuongMatHang; ++i) {
        danh_sach_mat_hang[i].Show();
    }
     for (int i = 0; i < 75; ++i) {
        cout << "-";
    }
    cout << endl << endl;
    // file.close();
}

bool QuanLyMatHang::KiemTraMaHangTonTai(const string& ma_hang) const  {
    for (int i = 0; i < soLuongMatHang; i++) {
        if (danh_sach_mat_hang[i].getMaHang() == ma_hang) {
            int so_luong_moi;
            cout << "Mat hang co ma '" << danh_sach_mat_hang[i].getMaHang() << "' da ton tai. Thong tin cu:" << endl;
            MatHang::ShowHeader();
            danh_sach_mat_hang[i].Show();  
            for (int i = 0; i < 75; ++i) {
                cout << "-";
            }
            cout << endl;          
            cout << "Nhap so luong moi: ";
            cin >> so_luong_moi;

            // Cập nhật số lượng hàng hóa
            danh_sach_mat_hang[i].setSoLuongHangHoa(danh_sach_mat_hang[i].getSoLuongHangHoa() + so_luong_moi);
            cout << "\nMat hang sau khi cap nhat:" << endl;
            MatHang::ShowHeader();
            danh_sach_mat_hang[i].Show();
            for (int i = 0; i < 75; ++i) {
                cout << "-";
            }
            cout << endl;
            // Lưu danh sách mặt hàng vào file sau khi cập nhật số lượng hàng hóa
            LuuDuLieuVaoFile("Hang.txt");

            return true; // Mã hàng tồn tại và đã cập nhật số lượng
        }
    }
    return false; // Mã hàng không tồn tại
}


bool compareBySoLuong(const MatHang& a, const MatHang& b) {
    return a.getSoLuongHangHoa() < b.getSoLuongHangHoa();
}
void QuanLyMatHang::SapXep() {
    int choice;
    cout << "-------------------------------------------------" << endl;
    cout << left << setw(48)<< "|       Nhap kieu ban muon sap xep:" << "|" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << left << setw(48) << "|     1.De sap xep tang dan theo so luong" << "|" << endl;
    cout << left << setw(48) << "|     2.De sap xep giam dan theo so luong: " << "|" << endl;
    cout << left << setw(48) << "|     3.De sap xep hang theo thu tu (a-z): " << "|" << endl;
    cout << left << setw(48) << "|     4.De sap xep hang theo thu tu (z-a): " << "|" << endl;
    cout << left << setw(48) << "|     5.De sap xep tang dan theo gia tien: " << "|" << endl;
    cout << left << setw(48) << "|     6.De sap xep giam dan theo gia tien: " << "|" << endl;
    cout << "-------------------------------------------------" << endl;

    cin >> choice;

    switch (choice) {
        case 1: // Tăng dần
            sort(danh_sach_mat_hang, danh_sach_mat_hang + soLuongMatHang, [](const MatHang& a, const MatHang& b) {
                return a.getSoLuongHangHoa() < b.getSoLuongHangHoa();
            });
            break;
        case 2: // Giảm dần
            sort(danh_sach_mat_hang, danh_sach_mat_hang + soLuongMatHang, [](const MatHang& a, const MatHang& b) {
                return a.getSoLuongHangHoa() > b.getSoLuongHangHoa();
            });
            break;
        case 3: // Sắp xếp theo tên hàng (A-Z)
            sort(danh_sach_mat_hang, danh_sach_mat_hang + soLuongMatHang, [](const MatHang& a, const MatHang& b) {
                return a.getTenHang() < b.getTenHang();
            });
            break;
        case 4: // Sắp xếp theo tên hàng (Z-A)
            sort(danh_sach_mat_hang, danh_sach_mat_hang + soLuongMatHang, [](const MatHang& a, const MatHang& b) {
                return a.getTenHang() > b.getTenHang();
            });
            break;
        case 5: // Sắp xếp theo giá tiền tăng dần
            sort(danh_sach_mat_hang, danh_sach_mat_hang + soLuongMatHang, [](const MatHang& a, const MatHang& b) {
                return a.getGiaTien() < b.getGiaTien();
            });
            break;
        case 6: // Sắp xếp theo giá tiền giảm dần
            sort(danh_sach_mat_hang, danh_sach_mat_hang + soLuongMatHang, [](const MatHang& a, const MatHang& b) {
                return a.getGiaTien() > b.getGiaTien();
            });
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
    }
}

void QuanLyMatHang::CapNhatSoLuong(const string& maHang, int soLuongNhap) {
    for (int i = 0; i < soLuongMatHang; ++i) {
        if (danh_sach_mat_hang[i].getMaHang() == maHang) {
            danh_sach_mat_hang[i].setSoLuongHangHoa(danh_sach_mat_hang[i].getSoLuongHangHoa() + soLuongNhap);
            LuuDuLieuVaoFile("Hang.txt");
            break; 
            
        }
    }
}

float QuanLyMatHang::TrungBinhGiaMatHang() const {
    if (soLuongMatHang == 0) {
        return 0.0f; // Trả về 0 nếu danh sách rỗng
    }

    float tongGia = 0.0f;
    for (int i = 0; i < soLuongMatHang; ++i) {
        tongGia +=  danh_sach_mat_hang[i].getGiaTien();
    }

    return tongGia / SoLuongHienTai(); // Trả về giá trung bình
}
MatHang QuanLyMatHang::MatHangGiaCaoNhat() const {
    MatHang matHangMax = danh_sach_mat_hang[0];
    for (int i = 1; i < soLuongHienTai; ++i) {
        if (danh_sach_mat_hang[i].getGiaTien() > matHangMax.getGiaTien()) {
            matHangMax = danh_sach_mat_hang[i];
        }
    }
    return matHangMax;
}

MatHang QuanLyMatHang::MatHangGiaThapNhat() const {
    MatHang matHangMin = danh_sach_mat_hang[0]; 
    for (int i = 1; i < soLuongHienTai; ++i) {
        if (danh_sach_mat_hang[i].getGiaTien() < matHangMin.getGiaTien()) {
            matHangMin = danh_sach_mat_hang[i];
        }
    }
    return matHangMin;
}


void QuanLyMatHang::ThongKeTongGiaTriHangHoa() const {
    float tongGiaTriTruocGiam = 0.0;
    float tongGiaTriSauGiam = 0.0;

    for (int i = 0; i < soLuongMatHang; ++i) {
        MatHang mat_hang = danh_sach_mat_hang[i];
        int soLuong = mat_hang.getSoLuongHangHoa();
        float giaBanTruocGiam = mat_hang.getGiaTien() * soLuong;
        float giaBanSauGiam = mat_hang.TinhTien();

        tongGiaTriTruocGiam += giaBanTruocGiam;
        tongGiaTriSauGiam += giaBanSauGiam;
    }

    cout << "\nTong gia tri truoc khi giam gia: " << tongGiaTriTruocGiam << endl;
    cout << "Tong gia tri sau khi giam gia: " << tongGiaTriSauGiam << endl;
}


bool QuanLyMatHang::KiemTra(const string& maHang) const {
    for (int i = 0; i < soLuongMatHang; ++i) {
        if (danh_sach_mat_hang[i].getMaHang() == maHang) {
            return true;
        }
    }
    return false;
}

MatHang QuanLyMatHang::LayThongTinMatHang(const string &maHang) const {
    for (int i = 0; i < soLuongMatHang; ++i) {
        if (danh_sach_mat_hang[i].getMaHang() == maHang) {
            return danh_sach_mat_hang[i];
        }
    }
    // Nếu không tìm thấy mã hàng, trả về một mặt hàng trống hoặc có thể xử lý khác tùy theo logic của bạn
    return MatHang();
}