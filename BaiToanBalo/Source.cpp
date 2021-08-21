#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
void fill_line(char c, int dodai)
{
	cout << setfill(c);
	cout << setw(dodai) << c << endl;
	cout << setfill(' ');
}
struct DanhSachDoVat {
	char Ten[10];
	float trongLuong, giaTri, donGia;
	int SoLuong = 0;
	int SoLuongLay = 0;
};
typedef DanhSachDoVat DSDV;
float TinhDonGia(float GT, float TL)
{
	return GT / TL;
}
void DocFile_DSDV(ifstream* f, DSDV* a, int n)
{
	string s;
	*f >> s;
	*f >> s;
	*f >> s;
	*f >> s;
	for (int i = 0; i < n; i++)
	{
		*f >> a[i].Ten;
		*f >> a[i].trongLuong;
		*f >> a[i].giaTri;
		*f >> a[i].SoLuong;
		a[i].donGia = TinhDonGia(a[i].giaTri, a[i].trongLuong);
	}
}
void Xuat_DSDV(DSDV* a, int n)
{

	fill_line(196, 79);
	cout << setw(15) << left << "| Ten do vat" << "|" << setw(15) << left << "Trong Luong" << "|" << setw(15) << left << "Gia Tri" << "|" << setw(15) << left << "So Luong" << "|" << setw(15) << right << "Don Gia(GT/TL) |\n";
	fill_line(196, 79);

	for (int i = 0; i < n; i++)
	{

		cout << "| " << setw(13) << left << a[i].Ten << "|" << setw(15) << left << a[i].trongLuong << "|" << setw(15) << left << a[i].giaTri << "|" << setw(15) << left << a[i].SoLuong << "|" << setw(14) << right << a[i].donGia << " |" << endl;
	}
	fill_line(196, 79);
}
void SapXep_GiamDanTheoDonGia(DSDV* a, int left, int right)
{

	int i = left, j = right, mid = (left + right) / 2;
	DSDV x = a[mid];
	do {
		while (a[i].donGia > x.donGia) i++;
		while (a[j].donGia < x.donGia) j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (left < j)
		SapXep_GiamDanTheoDonGia(a, left, j);
	if (right > i)
		SapXep_GiamDanTheoDonGia(a, i, right);
}
int chon(int soluong, float trongluong, int balo)
{
	int count(0), temp(0);
	while (soluong != 0 && temp < balo)
	{
		++count;
		temp = count * trongluong;
		--soluong;
	}
	if (temp > balo)
		return --count;
	else
		return count;
}
void LaySoLuong_DoVat(DSDV* a, int n, int balo)
{
	for (int i = 0; i < n; i++)
	{
		a[i].SoLuongLay = chon(a[i].SoLuong, a[i].trongLuong, balo);
		balo = balo - (int)(a[i].SoLuongLay * a[i].trongLuong);
	}
}

void Xuat_SoLuongLay(DSDV* a, int n)
{
	cout << setfill('*');
	cout << setw(31) << left << "\n******* So luong da lay " << '*' << endl << endl;
	cout << setfill(' ');
	fill_line(196, 31);
	cout << setw(15) << left << "| Ten do vat" << "|" << setw(16) << right << "So luong lay |\n";
	fill_line(196, 31);
	for (int i = 0; i < n; i++)
	{
		if (a[i].SoLuong != 0)
			cout << "| " << setw(13) << left << a[i].Ten << "|" << setw(13) << right << a[i].SoLuongLay << " |" << endl;
	}
	fill_line(196, 34);
}

void KetLuan(DSDV* a, int n)
{
	cout << setfill('*');
	cout << setw(75) << left << "\n********************************** Ket Luan " << '*' << endl << endl;
	cout << setfill(' ');
	float TongTrongLuong(0), TongGiaTri(0), TongDonGia(0);
	string s = "";
	for (int i = 0; i < n; i++)
	{

		if (a[i].SoLuongLay != 0)
		{
			if (i == 0)
				s = s + a[i].Ten + "(" + to_string(a[i].SoLuongLay) + ")";
			else
				s = s + ',' + a[i].Ten + "(" + to_string(a[i].SoLuongLay) + ")";
			TongTrongLuong += a[i].SoLuongLay * a[i].trongLuong;
			TongGiaTri += a[i].SoLuongLay * a[i].giaTri;
			TongDonGia += a[i].SoLuongLay * a[i].donGia;
		}
	}
	fill_line(196, 75);
	cout << setw(15) << left << "| Ten do vat" << "|" << setw(20) << left << "Tong Trong Luong" << "|" << setw(16) << left << "Tong Gia Tri" << "|" << setw(22) << right << "Tong Don Gia |\n";
	fill_line(196, 75);
	cout << "| " << setw(13) << left << s << "|" << setw(20) << left << TongTrongLuong << "|" << setw(16) << left << TongGiaTri << "|" << setw(19) << right << TongDonGia << " |" << endl;
	fill_line(196, 75);
}
int main()
{
	// nhập bằng file txt
	system("input.txt");
	DSDV* a;
	int n, balo;
	cout << "Khoi luong balo co the dung duoc: ";
	cin >> balo;
	ifstream f("input.txt", ios_base::in);
	// dịch sang phải 4 byte từ vị trí đầu tiên
	f.seekg(4, ios::beg);
	f >> n;
	a = new DSDV[n];
	DocFile_DSDV(&f, a, n);
	Xuat_DSDV(a, n);
	cout << setfill('*');
	cout << setw(64) << left << "\n************* Sau khi sap xep giam dan theo don gia " << '*' << endl << endl;
	cout << setfill(' ');
	SapXep_GiamDanTheoDonGia(a, 0, n - 1);
	Xuat_DSDV(a, n);
	LaySoLuong_DoVat(a, n, balo);
	KetLuan(a, n);
	system("pause");
	return 0;
}