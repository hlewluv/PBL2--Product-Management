#pragma once
#ifndef MATHANG_H
#define MATHANG_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Vector.h"

using namespace std;
class MatHang {
private:
    string ma_hang;
    string don_vi;
    string ten_hang;
    int so_luong_hang_hoa;
    float GiaTien;
    
public:
    MatHang();
    MatHang(const string& ma_hang, string don_vi, string ten_hang, int so_luong_hang_hoa, float gia_tien);
    
    string getMaHang() const;
    string getDonVi() const;
    string getTenHang() const;
    int getSoLuongHangHoa() const;
    float getGiaTien() const;
    void setSoLuongHangHoa(int newSoLuong);
    
    float TinhTien();
    float TinhTien(int soluong);
    static void ShowHeader();
    void Show() const;
    
};

class QuanLyMatHang {
private:
    MatHang* danh_sach_mat_hang;
    int soLuongMatHang;
    int soLuongHienTai;

public:
    QuanLyMatHang(int soLuongMatHang);
    ~QuanLyMatHang();
    int SoLuongHienTai() const {
        return soLuongHienTai;
    }
    bool KiemTra(const string& maHang) const;
    MatHang LayThongTinMatHang(const string &maHang) const;

    MatHang* getDanhSachMatHang() const;
    int getSoLuongMatHang() const;

    int TongSoLuongHangHoa() const ;
    MatHang MatHangGiaCaoNhat() const;
    MatHang MatHangGiaThapNhat() const;
    float TrungBinhGiaMatHang() const;
    static void ShowHeader();
    void TimMatHang(const string& ten_hang);
    void ThemMatHang(const MatHang& mat_hang);
    void XoaMatHang(const string& ma_hang);
    void XoaDonVi(const string& don_vi);
    void DocDuLieuTuFile(const string& ten_file);
    void LuuDuLieuVaoFile(const string& ten_file) const;
    void HienThiDanhSachMatHang() const;
    bool KiemTraMaHangTonTai(const string& ma_hang) const;
    void SapXep();
    void CapNhatSoLuong(const string& maHang, int soLuongNhap);
    void ThongKeGiaTriHangHoa() const;
    void ThongKeTongGiaTriHangHoa() const;
    float TongGiaTriHangNhapTuNCC(const string& maNCC) const;
};

#endif // MATHANG_H
