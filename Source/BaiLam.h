#ifndef BaiLam_HEADER
#define BaiLam_HEADER

#include<fstream>
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;
struct Pixels{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct Image2D
{
	Pixels **data;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
};


bool Read_File_BitMap(ifstream &file_in,string filename);
void Read_Data_BitMap(ifstream &file_in,Image2D &image);
void Write_Data_BitMap(ofstream &file_out,Image2D &image);
void grayscale(Image2D &image);
void brighten(Image2D &image);
void darken(Image2D &image);
void Hot(Image2D &image);
void Cold(Image2D &image);
void Swap(Pixels &a,Pixels &b);
void Lat_Anh_Theo_Chieu_Doc(Image2D &image);
void Lat_Anh_Theo_Chieu_Ngang(Image2D &image);
void Tao_Vien(Image2D &image);
void Hien_Thi_Anh_Ra_Console(Image2D &image);
void Menu();
void clrscr();
void Hien_Thi_Anh_Ra_Console_Result(Image2D &image);

#endif