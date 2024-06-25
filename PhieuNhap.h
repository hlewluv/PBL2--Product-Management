#ifndef PHIEUNHAP_H
#define PHIEUNHAP_H
#include "NCC.h"
#include "MatHang.h"
#include "Date.h"
#include <map>
#include <string>
#include <iostream>


class PhieuNhap : public NCC, public MatHang, public Date {
private:
    string maPhieu;
    int soLuongNhap;
    string maHang; 
public:
    PhieuNhap();
    PhieuNhap(const string& maPhieu, int soLuongNhap,
             const string& maNCC, const string& tenNCC, const string& diaChiNCC, const string& sdtNCC,
             int day, int month, int year, const string& maHang, const string& tenHang,
            float donGia);
              
    // Các phương thức getter và setter cần thiết
    void setSoLuongNhap(const int& soLuong);
    int getSoLuongNhap() const;
    void setMaPhieu(const string& ma);
    string getMaPhieu() const;

    void SetMaHang(const string& ma);
    string GetMaHang() const;
    void hienThiThongTin() const;
    float Giamgia();
};

class QuanLyPhieuNhap {
private:
    PhieuNhap *danhSachPhieu;
    int soLuongPhieu;
    QuanLyMatHang& quanLyMatHang;
public:
    QuanLyPhieuNhap(int size, QuanLyMatHang& qlMatHang);
    ~QuanLyPhieuNhap();

    void ThemPhieuNhap(const PhieuNhap &phieu);
    void DocDuLieu(const string &filename);
    void XoaPhieuNhap(const string &maPhieu);
    void HienThiDanhSachPhieuNhap() const;
    void LuuDuLieu(const string &filename) const;
    friend class QuanLyMatHang;
    void CapNhatsoluong(const PhieuNhap &phieu);
    int TongSoLuongHangNhap() const;
    float TongGiaTriHangNhap() const;
    map<string, int> ThongKeSoLuongHangNhapTheoNCC() const;
    map<string, float> ThongKeGiaTriHangNhapTheoNCC() const;
};
#endif 
