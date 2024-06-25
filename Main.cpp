#include "MatHang.h"
#include "PhieuNhap.h"
#include <iostream>
#include <fstream>
using namespace std;
// them phieu nhap thi chi in ra những gia tri key
// chinh sua lai thong ke phieu nhap
// them nhieu mat hang vao phieu nhap
int main() {
    QuanLyMatHang quan_ly_mat_hang(20);
    quan_ly_mat_hang.DocDuLieuTuFile("Hang.txt");

    QuanLyPhieuNhap quan_ly_nhap(20, quan_ly_mat_hang);
    quan_ly_nhap.DocDuLieu("PhieuNhap.txt");
    
    int choice;
    do {
        cout << setw(20) << left << "=====================" << "MENU" << setw(20) << right << "=====================" << endl;
        cout << setw(44) << left << "||    1. Hien thi danh sach mat hang" << "||" << endl;
        cout << setw(44) << left << "||    2. Tim mat hang theo ma" << "||" << endl;
        cout << setw(44) << left << "||    3. Them mat hang moi" << "||" << endl;
        cout << setw(44) << left << "||    4. Xoa mat hang" << "||" << endl;
        cout << setw(44) << left << "||    5. Sap xep mat hang theo so luong" << "||" << endl;
        cout << setw(44) << left << "||    6. Hien thi danh sach phieu nhap" << "||" << endl;
        cout << setw(44) << left << "||    7. Them phieu nhap" << "||" << endl;
        cout << setw(44) << left << "||    8. Xoa phieu nhap " << "||" << endl;
        cout << setw(44) << left << "||    9. Thong ke mat hang" << "||" << endl;
        cout << setw(44) << left << "||    10. Thong ke phieu nhap" << "||" << endl;
        cout << setw(44) << left << "||    0. Thoat chuong trinh" << "||" << endl;
        cout << "----------------------------------------------" << endl;
        cout <<setw(44) << left << "||      NHAP LUA CHON DE THAO TAC      "<< "||" << endl;
        cout << "----------------------------------------------" << endl;
        cin >> choice;

        switch (choice) {
            case 1:{
                cout << "\nDanh sach mat hang:" << endl;
                quan_ly_mat_hang.HienThiDanhSachMatHang();
                cout << endl ;
                break;
            }
           case 2: {
                string ma_hang_can_tim;
                cout << "---------------------------------------" << endl;
                cout << left << setw(38) << "|      Nhap ma mat hang can tim: " << "|"<< endl;
                cout << "---------------------------------------" << endl;
                cin >> ma_hang_can_tim;
                cout << endl ;                
                cout << "---------------------------------------" << endl;
                cout << left << setw(20) << "|    Tim mat hang co ma' "  << ma_hang_can_tim << "':      |" << endl;
                cout << "---------------------------------------" << endl;
                quan_ly_mat_hang.TimMatHang(ma_hang_can_tim);
                break;
            }

            // Nếu đưa mã hàng vào mặt hàng chưa tồn tại thì cout ra mặt hàng chưa tồn tại, yêu cầu tạo 1 cái mặt hàng chứa mã hàng đó r mới add dô đc

            case 3: {
                string ma_hang_moi;
                cout << "---------------------------------------" << endl;
                cout << left << setw(38) << "|           Nhap ma hang moi:    " << "|" << endl;
                cout << "---------------------------------------" << endl;                cin >> ma_hang_moi;

                if (quan_ly_mat_hang.KiemTraMaHangTonTai(ma_hang_moi)) {
                    cout << "Cap nhat so luong thanh cong!" << endl;
                } else {

                string don_vi, ten_hang;
                int so_luong_hang_hoa;
                float gia_tien;
                cout << "Mat Hang khong co san. Vui long nhap mat hang moi." << endl;
                
                cout << "Nhap don vi: ";
                cin >> don_vi;
                cout << "Nhap ten hang: ";
                cin >> ten_hang;
                cout << "Nhap so luong hang hoa: ";
                cin >> so_luong_hang_hoa;
                cout << "Nhap gia tien: ";
                cin >> gia_tien;

                MatHang mat_hang_moi(ma_hang_moi, don_vi, ten_hang, so_luong_hang_hoa, gia_tien);

                // Thêm mặt hàng mới vào danh sách
                quan_ly_mat_hang.ThemMatHang(mat_hang_moi);
                cout << "Them mat hang moi thanh cong!" << endl;
                quan_ly_mat_hang.HienThiDanhSachMatHang();
                cout << endl ;
            }
            break;
        }

            case 4: {
                int c;
                cout << "---------------------------------------" << endl;
                cout << left << setw(38) << "|     Chon kieu xoa: " << "|" << endl;
                cout << "---------------------------------------" << endl;
                cout << left << setw(38) << "|     1.Xoa mat hang theo ma " << "|" << endl;
                cout << left << setw(38) << "|     2.Xoa mat hang theo don vi " << "|" << endl;
                cout << "---------------------------------------" << endl;
                cin >> c;
                if (c == 1 )
                {
                string ma_hang_can_xoa;
                cout << "Nhap ma hang can xoa: ";
                cin >> ma_hang_can_xoa;
                cout << "\nXoa mat hang co ma '" << ma_hang_can_xoa << "':" << endl;
                quan_ly_mat_hang.XoaMatHang(ma_hang_can_xoa);
                cout << endl ;
                break;
            }

            else if (c == 2) {
                string don_vi_can_xoa;
                cout << "Nhap don vi hang can xoa: ";
                cin >> don_vi_can_xoa;
                cout << "\nXoa mat hang co ma '" << don_vi_can_xoa << "':" << endl;
                quan_ly_mat_hang.XoaDonVi(don_vi_can_xoa);
                cout << endl ;
                break;
            } 
            else {
                cout << "Nhap khong dung kieu. Vui long thao tac lai." << endl;
            }
            }

            case 5: {
                quan_ly_mat_hang.SapXep();
                quan_ly_mat_hang.HienThiDanhSachMatHang();
                cout << endl ;
                break;
            }

            case 6: {
                cout << "\nDanh sach phieu nhap:" << endl;
                quan_ly_nhap.HienThiDanhSachPhieuNhap();
                cout << endl ;
                break;
            }
            case 7: {
                string maPhieu, maNCC, tenNCC, diaChiNCC, sdtNCC, maHang, tenHang;
                int soLuongNhap, day, month, year;
                float donGia;

                cout << "Nhap ma phieu : " << endl;
                cin >> maPhieu;
                cout << "Nhap ma hang : " << endl;
                cin >> maHang;
                // if (quan_ly_mat_hang.KiemTra(maHang))
                // {
                cout << "Nhap so luonng hang hoa nhap: " << endl;
                cin >> soLuongNhap;
                cout << "Nhap ma nha cung cap : " << endl;
                cin >> maNCC;
                cout << "Nhap ten nha cung cap : " << endl;
                cin >> tenNCC;
                cout << "Nhap dia chi nha cung cap : " << endl;
                cin >> diaChiNCC;
                cout << "Nhap so dien thoai : " << endl;
                cin >> sdtNCC;
                cout << "Nhap ten hang : " << endl;
                cin >> tenHang;
                cout << "Nhap ngay nhap hang : " << endl;
                cin >> day;
                cout << "Nhap thang nhap hang : " << endl;
                cin >> month;
                cout << "Nhap nam nhap hang : " << endl;
                cin >> year;
                cout << "Nhap don gia: " << endl;
                cin >> donGia;
                PhieuNhap phieu_nhap_moi(maPhieu,soLuongNhap,maNCC, tenNCC, diaChiNCC, sdtNCC, day, month, year, maHang, tenHang, donGia);     
                quan_ly_nhap.ThemPhieuNhap(phieu_nhap_moi);
                // } else {
                //     cout << "Vui long nhap ma hang truoc khi them phieu nhap." << endl;
                // }
                cout << endl ;
                break;
            }

            case 8: {
                string maPhieuCanXoa;
                cout << "Nhap ma phieu nhap can xoa: ";
                cin >> maPhieuCanXoa;
                cout << "Xoa phieu nhap co ma: " << maPhieuCanXoa << endl;
                quan_ly_nhap.XoaPhieuNhap(maPhieuCanXoa);
                cout << endl ;
                break;
            }

            case 9: {
                cout << "----------------------------------------------------------------" << endl;
                int tong_so_luong = quan_ly_mat_hang.TongSoLuongHangHoa();
                cout << left << setw(35) << "|     Tong so luong mat hang: " << left << setw(28) << tong_so_luong << "|" << endl;
                cout << "----------------------------------------------------------------" << endl;

                MatHang mat_hang_cao_nhat = quan_ly_mat_hang.MatHangGiaCaoNhat();
                cout << left << setw(35) <<"|     Mat hang co gia cao nhat: " << left << setw(7) << mat_hang_cao_nhat.getTenHang() << left << setw(7) << " - Gia: " << mat_hang_cao_nhat.getGiaTien() << endl;
                cout << "----------------------------------------------------------------" << endl;

                MatHang mat_hang_thap_nhat = quan_ly_mat_hang.MatHangGiaThapNhat();
                cout << left << setw(35) <<"|     Mat hang co gia thap nhat: " << left << setw(7) << mat_hang_thap_nhat.getTenHang() << left << setw(7) << " - Gia: " << mat_hang_thap_nhat.getGiaTien() << endl;
                cout << "----------------------------------------------------------------" << endl;

                float trung_binh_gia = quan_ly_mat_hang.TrungBinhGiaMatHang();
                cout << left << setw(35) << "|     Trung binh gia mat hang: " << left << setw(28) << trung_binh_gia << "|" << endl;
                cout << "----------------------------------------------------------------" << endl;

                int soLuongHienTai = quan_ly_mat_hang.SoLuongHienTai();
                cout << left << setw(35) <<"|     So luong ma hang: " << left << setw(28) << soLuongHienTai << "|" << endl;
                cout << "----------------------------------------------------------------" << endl;

                quan_ly_mat_hang.ThongKeTongGiaTriHangHoa();
                cout << "----------------------------------------------------------------" << endl;
                cout << endl ;
                break;
            }

            case 10: {
                    int totalQuantity = quan_ly_nhap.TongSoLuongHangNhap();
                    float totalValue = quan_ly_nhap.TongGiaTriHangNhap();

                    cout << "Tong so luong hang nhap: " << totalQuantity << endl;
                    cout << "Tong gia tri hang nhap: " << totalValue << endl;

                    cout << "Thong ke so luong hang nhap theo NCC:" << endl;
                    map<string, int> quantityBySupplier = quan_ly_nhap.ThongKeSoLuongHangNhapTheoNCC();
                    for (const auto& pair : quantityBySupplier) {
                        cout << "NCC: " << pair.first << " - So luong: " << pair.second << endl;
                    }

                    cout << "Thong ke gia tri hang nhap theo NCC:" << endl;
                    map<string, float> valueBySupplier = quan_ly_nhap.ThongKeGiaTriHangNhapTheoNCC();
                    for (const auto& pair : valueBySupplier) {
                        cout << "NCC: " << pair.first << " - Gia tri: " << pair.second << endl;
                    }
                    break;
                
            }

            case 0:
                cout << "---------------------------------------" << endl;            
                cout << left << setw(38) << "|    Thoat chuong trinh." << "|" << endl;
                cout << "---------------------------------------" << endl;
                break;

            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }

    } while (choice != 0);

    return 0;
}
