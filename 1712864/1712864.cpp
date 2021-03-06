#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include <conio.h>
#include<wchar.h>
#include<stdlib.h>
#include <fcntl.h> 
#include <io.h> 

struct sinhvien
{
	wchar_t* mssv;
	wchar_t* ten;
	wchar_t* KHOA;
	wchar_t* khoahoc;
	wchar_t* ngaysinh;
	wchar_t* hinhanh;
	wchar_t* email;
	wchar_t* motabanthan;
	wchar_t* sothich;
};

int token(FILE* f, wchar_t x)
{
	wchar_t ch;
	int i = 0;
	while (!feof(f))
	{
		ch = fgetwc(f);
		if (ch != x)
		{
			i++;
		}
		else
			return i + 1;
	}
	return i;
}
void getInfo(FILE* f, sinhvien &x, int &begin)
{
	fseek(f, begin, SEEK_SET);
	int a = token(f, L',');
	x.mssv = (wchar_t*)malloc(sizeof(wchar_t)*a);
	fseek(f, begin, SEEK_SET);
	fgetws(x.mssv, a, f);
	int b = ftell(f);
	wprintf(L"Mã số sinh viên: %ls\n", x.mssv);



	fseek(f, b + 1, SEEK_SET);
	a = token(f, L',');
	x.ten = (wchar_t*)malloc(sizeof(wchar_t)*a);
	fseek(f, b + 1, SEEK_SET);
	fgetws(x.ten, a, f);
	b = ftell(f);
	wprintf(L"Tên: %ls\n", x.ten);


	fseek(f, b + 1, SEEK_SET);
	a = token(f, L',');
	x.KHOA = (wchar_t*)malloc(sizeof(wchar_t)*a);
	fseek(f, b + 1, SEEK_SET);
	fgetws(x.KHOA, a, f);
	b = ftell(f);
	wprintf(L"Khoa: %ls\n", x.KHOA);


	fseek(f, b + 1, SEEK_SET);
	a = token(f, L',');
	x.khoahoc = (wchar_t*)malloc(sizeof(wchar_t)*a);
	fseek(f, b + 1, SEEK_SET);
	fgetws(x.khoahoc, a, f);
	b = ftell(f);
	wprintf(L"Khóa: %ls\n", x.khoahoc);

	fseek(f, b + 1, SEEK_SET);
	a = token(f, L',');
	x.ngaysinh = (wchar_t*)malloc(sizeof(wchar_t)*a);
	fseek(f, b + 1, SEEK_SET);
	fgetws(x.ngaysinh, a, f);
	b = ftell(f);
	wprintf(L"Ngày sinh: %ls\n", x.ngaysinh);

	fseek(f, b + 1, SEEK_SET);
	a = token(f, L',');
	x.email = (wchar_t*)malloc(sizeof(wchar_t)*a);
	fseek(f, b + 1, SEEK_SET);
	fgetws(x.email, a, f);
	b = ftell(f);
	wprintf(L"Email: %ls\n", x.email);

	fseek(f, b + 1, SEEK_SET);
	a = token(f, L',');
	x.hinhanh = (wchar_t*)malloc(sizeof(wchar_t)*a);
	fseek(f, b + 1, SEEK_SET);
	fgetws(x.hinhanh, a, f);
	b = ftell(f);
	wprintf(L"File hình ảnh cá nhân: %ls\n", x.hinhanh);

	fseek(f, b + 1, SEEK_SET);
	if (fgetwc(f) != L'"') {
		fseek(f, b + 1, SEEK_SET);
		a = token(f, L',');
		x.motabanthan = (wchar_t*)malloc(sizeof(wchar_t)*a);
		fseek(f, b + 1, SEEK_SET);
		fgetws(x.motabanthan, a, f);
		b = ftell(f);
	}
	else {
		fseek(f, b + 2, SEEK_SET);
		a = token(f, L'"');
		x.motabanthan = (wchar_t*)malloc(sizeof(wchar_t)*a);
		fseek(f, b + 2, SEEK_SET);
		fgetws(x.motabanthan, a, f);
		b = ftell(f) + 1;
	}
	wprintf(L"Mô tả bản thân: %ls\n", x.motabanthan);

	fseek(f, b, SEEK_SET);
	if (fgetwc(f) == L',') {
		if (fgetwc(f) != L'"') {
			fseek(f, b + 1, SEEK_SET);
			a = token(f, '\n');
			x.sothich = (wchar_t*)malloc(sizeof(wchar_t)*a);
			fseek(f, b + 1, SEEK_SET);
			fgetws(x.sothich, a, f);
			b = ftell(f);
			begin = b;
		}
		else {
			fseek(f, b + 2, SEEK_SET);
			a = token(f, '"');
			x.sothich = (wchar_t*)malloc(sizeof(wchar_t)*a);
			fseek(f, b + 2, SEEK_SET);
			fgetws(x.sothich, a, f);
			b = ftell(f) + 1;
			fgetwc(f);
			fgetwc(f);
		}
		wprintf(L"Sở thích: %ls\n", x.sothich);
		begin = b + 2;
	}
	else
	{
		begin = b;
	}
}
void xuatfile(sinhvien s)
{
	wchar_t filename[60], path[60];
	wcscpy_s(filename, s.mssv);
	wcscpy_s(path, L"WEBSITES/");
	wcscat_s(filename, L".html");
	wcscat_s(path,filename);
	FILE* fo;
	_wfopen_s(&fo, path, L"w, ccs=UTF-8");
	if (fo == NULL)
	{
		wprintf(L"Không thể tạo file %ls!!!\n");
	}
	else
	{
		fwprintf(fo, L"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n");
		fwprintf(fo, L"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
		fwprintf(fo, L"	<head>\n");
		fwprintf(fo, L"		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
		fwprintf(fo, L"		<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\n");
		fwprintf(fo, L"		<title>HCMUS - %ls</title>\n", s.mssv);
		fwprintf(fo, L"	</head>\n");
		fwprintf(fo, L"	<body>\n");
		fwprintf(fo, L"		<div class=\"Layout_container\">\n");
		fwprintf(fo, L"			<!-- Begin Layout Banner Region -->\n");
		fwprintf(fo, L"			<div class=\"Layout_Banner\" >\n");
		fwprintf(fo, L"				<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\n");
		fwprintf(fo, L"				<div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN</div>\n");
		fwprintf(fo, L"			</div>\n");
		fwprintf(fo, L"			<!-- End Layout Banner Region -->\n");
		fwprintf(fo, L"			<!-- Begin Layout MainContents Region -->\n");
		fwprintf(fo, L"			<div class=\"Layout_MainContents\">\n");
		fwprintf(fo, L"				<!-- Begin Below Banner Region -->\n");
		fwprintf(fo, L"				<div class=\"Personal_Main_Information\">\n");
		fwprintf(fo, L"					<!-- Begin Thông tin cá nhân của sinh viên ------------------------------------------------------------------------------------------->\n");
		fwprintf(fo, L"					<div class=\"Personal_Location\"> \n");
		fwprintf(fo, L"						<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\n");
		fwprintf(fo, L"						<span class=\"Personal_FullName\">%ls - %ls</span>\n", s.ten, s.mssv);
		fwprintf(fo, L"						<div class=\"Personal_Department\">KHOA CÔNG NGHỆ THÔNG TIN</div>\n");
		fwprintf(fo, L"						<br />\n");
		fwprintf(fo, L"						<div class=\"Personal_Phone\">\n");
		fwprintf(fo, L"						</div>\n");
		fwprintf(fo, L"						<br />\n");
		fwprintf(fo, L"						<br />\n");
		fwprintf(fo, L"					</div>\n");
		fwprintf(fo, L"					<!-- End Thông tin cá nhân của sinh viên ------------------------------------------------------------------------------------------->\n");
		fwprintf(fo, L"					<div class=\"Personal_HinhcanhanKhung\">\n");
		fwprintf(fo, L"						<img src=\"Images/%ls\" class=\"Personal_Hinhcanhan\" />\n", s.hinhanh);
		fwprintf(fo, L"					</div>\n");
		fwprintf(fo, L"				</div>\n");
		fwprintf(fo, L"				<!-- End Below Banner Region -->\n");
		fwprintf(fo, L"				<!-- Begin MainContents Region -->\n");
		fwprintf(fo, L"				<div class=\"MainContain\">\n");
		fwprintf(fo, L"\n");
		fwprintf(fo, L"					<!-- Begin Top Region -->\n");
		fwprintf(fo, L"					<div class=\"MainContain_Top\">\n");
		fwprintf(fo, L"\n");
		fwprintf(fo, L"						<div class=\"InfoGroup\">Thông tin cá nhân</div>\n");
		fwprintf(fo, L"                       <div>\n");
		fwprintf(fo, L"                            <ul class=\"TextInList\">\n");
		fwprintf(fo, L"                              <li>Họ và tên: %ls </li>\n", s.ten);
		fwprintf(fo, L"								 <li>MSSV: %ls </li>\n", s.mssv);
		fwprintf(fo, L"								 <li>Sinh viên khoa %ls </li>\n", s.KHOA);
		fwprintf(fo, L"								 <li>Ngày sinh: %ls </li>\n", s.ngaysinh);
		fwprintf(fo, L"								 <li>Email: %ls </li>\n", s.email);
		fwprintf(fo, L"							 </ul>\n");
		fwprintf(fo, L"						</div>\n");
		fwprintf(fo, L"                       <div class=\"InfoGroup\">Sở thích</div>\n");
		fwprintf(fo, L"                       <div>\n");
		fwprintf(fo, L"                            <ul class=\"TextInList\">\n");
		fwprintf(fo, L"                              <li>%ls</li>\n", s.sothich);
		fwprintf(fo, L"							 </ul>\n");
		fwprintf(fo, L"						</div>\n");
		fwprintf(fo, L"						<div class=\"InfoGroup\">Mô tả</div>\n");
		fwprintf(fo, L"						<div>\n");
		fwprintf(fo, L"							<ul class=\"Description\">\n");
		fwprintf(fo, L"                            <li>%ls</li>\n", s.motabanthan);
		fwprintf(fo, L"							</ul>\n");
		fwprintf(fo, L"						</div>\n");
		fwprintf(fo, L"\n");
		fwprintf(fo, L"					</div>\n");
		fwprintf(fo, L"				</div>\n");
		fwprintf(fo, L"			</div>\n");
		fwprintf(fo, L"\n");
		fwprintf(fo, L"			<!-- Begin Layout Footer -->\n");
		fwprintf(fo, L"			<div class=\"Layout_Footer\">\n");
		fwprintf(fo, L"				<div class=\"divCopyright\">\n");
		fwprintf(fo, L"					<br />\n");
		fwprintf(fo, L"					<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n");
		fwprintf(fo, L"					<br />\n");
		fwprintf(fo, L"				@2018</br>\n");
		fwprintf(fo, L"				Đồ án giữa kì</br>\n");
		fwprintf(fo, L"				Kỹ thuật lâp trình</br>\n");
		fwprintf(fo, L"				TH2018/04</br>\n");
		fwprintf(fo, L"				1712864 - Huỳnh Lâm Tứ</br>\n");
		fwprintf(fo, L"				</div>\n");
		fwprintf(fo, L"			</div>\n");
		fwprintf(fo, L"			<!-- End Layout Footer -->\n");
		fwprintf(fo, L"		</div>\n");
		fwprintf(fo, L"	</body>\n");
		fwprintf(fo, L"</html>");
		wprintf(L"=> Phát sinh file html thành công!!\n\n");
		fclose(fo);
	}
}
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	FILE* f;
	_wfopen_s(&f, L"thongtinsv.csv", L"r, ccs=UTF-8");
	if (f == NULL)
	{
		wprintf(L"Không mở được FILE!!!\n");
	}
	else
	{
		int i = 0, begin = 3;
		sinhvien x;
		while (!feof(f))
		{
			i++;
			wprintf(L"- Xử lí thông tin sinh viên thứ %d:\n", i);
			getInfo(f, x, begin);
			xuatfile(x);
		}
		fclose(f);
	}
	_getch();
	return 0;
}