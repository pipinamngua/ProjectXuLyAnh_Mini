#include<iostream>
#include<fstream>
#include<Windows.h>
#include<stdlib.h>
#include<string>
#include"BaiLam.h"
using namespace std;

bool Read_File_BitMap(ifstream &file_in,string filename)
{
	file_in.open(filename,ios::binary);
	if(file_in.fail())
	{
		return false;
	}
	return true;

}

void Read_Data_BitMap(ifstream &file_in,Image2D &image)
{
	file_in.seekg(0,file_in.beg);
	file_in.read((char*)&image.fileHeader,sizeof(BITMAPFILEHEADER));
	file_in.read((char*)&image.infoHeader,sizeof(BITMAPINFOHEADER));

	

	//cap phat bo nho cho data
	image.data = new Pixels*[image.infoHeader.biHeight];
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		image.data[i] = new Pixels[image.infoHeader.biWidth];
	}
	
	//doc pixel data

	int vitri = image.fileHeader.bfOffBits;
	int padding = image.infoHeader.biWidth%4;


	file_in.seekg(image.fileHeader.bfOffBits,file_in.beg);
	
	for(int i=image.infoHeader.biHeight-1;i>=0;i--)
	{
		file_in.seekg(vitri,file_in.beg);

		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			Pixels temp;
			file_in.read((char*)&image.data[i][j],sizeof(Pixels));

		}
		vitri = vitri + image.infoHeader.biWidth*3+padding;

	}




}

void Write_Data_BitMap(ofstream &file_out,Image2D &image)
{
	string filename;
	cout<<"Moi ban nhap ten file out:";
	fflush(stdin);
	getline(cin,filename);

	file_out.open(filename,ios::binary);
	if(file_out.fail())
	{
		cout<<"Khong mo duoc file_out "<<filename<<" de ghi"<<endl;
	}

	file_out.seekp(0);
	file_out.write((char*)&image.fileHeader,sizeof(BITMAPFILEHEADER));
	file_out.write((char*)&image.infoHeader,sizeof(BITMAPINFOHEADER));
	
	file_out.seekp(image.fileHeader.bfOffBits);
	int vitri = image.fileHeader.bfOffBits;
	char kitu = '\0';
	for(int i=image.infoHeader.biHeight-1;i>=0;i--)
	{
		int padding =0;
		file_out.seekp(vitri);
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			file_out.write((char*)&image.data[i][j],sizeof(Pixels));

		}
		//Chen them cac byte rac 
		while((image.infoHeader.biWidth*3+padding)%4!=0)
		{
			padding++;
			file_out.write((char*)&kitu,sizeof(char));
		}
		vitri = vitri+image.infoHeader.biWidth*3 +padding;



	}

}


void grayscale(Image2D &image)
{
	Hien_Thi_Anh_Ra_Console(image);
	for(int i=image.infoHeader.biHeight-1;i>=0;i--)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			int val = (image.data[i][j].r +image.data[i][j].g+image.data[i][j].b)/3;
			image.data[i][j].r=image.data[i][j].g=image.data[i][j].b=val;
		}

	}
	Hien_Thi_Anh_Ra_Console_Result(image);

}
void brighten(Image2D &image)
{
	Hien_Thi_Anh_Ra_Console(image);
	int k=20;
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			Pixels temp=image.data[i][j];
			temp.r = (int)temp.r +k <255 ?temp.r+k:255;
			temp.g = (int)temp.g +k <255 ?temp.g+k:255;
			temp.b = (int)temp.b +k <255 ?temp.b+k:255;

			image.data[i][j] = temp;
		}

	}
	Hien_Thi_Anh_Ra_Console_Result(image);

}

void darken(Image2D &image)
{
	Hien_Thi_Anh_Ra_Console(image);
	int k=30;
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			Pixels temp = image.data[i][j];
			temp.r = temp.r-k>0?temp.r-k:0;
			temp.g = temp.g-k>0?temp.g-k:0;
			temp.b = temp.b-k>0?temp.b-k:0;

			image.data[i][j] = temp;
		}

		
	}
	Hien_Thi_Anh_Ra_Console_Result(image);
}

void Hot(Image2D &image)
{
	Hien_Thi_Anh_Ra_Console(image);
	int k=30;
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			Pixels temp = image.data[i][j];
			
			temp.b = temp.b+k<256?temp.b+k:255;
			image.data[i][j] = temp;
		}

	}
	Hien_Thi_Anh_Ra_Console_Result(image);
}

void Cold(Image2D &image)
{
	Hien_Thi_Anh_Ra_Console(image);
	int k=30;
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			Pixels temp = image.data[i][j];
			
			temp.r = temp.r+k<256?temp.r+k:255;
			image.data[i][j] = temp;
		}

	}
	Hien_Thi_Anh_Ra_Console_Result(image);
}

void Swap(Pixels &a,Pixels &b)
{
	Pixels temp;
	temp = a;
	a=b;
	b=temp;
}

void Lat_Anh_Theo_Chieu_Doc(Image2D &image)
{
	Hien_Thi_Anh_Ra_Console(image);
	int dem=0;
	int flag=image.infoHeader.biHeight/2;
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			Swap(image.data[i][j],image.data[image.infoHeader.biHeight-(i+1)][j]);
		}
		dem++;
		if(dem==flag)
		{
			break;
		}

	}
	Hien_Thi_Anh_Ra_Console_Result(image);
}

void Lat_Anh_Theo_Chieu_Ngang(Image2D &image)
{
	Hien_Thi_Anh_Ra_Console(image);
	int width = image.infoHeader.biWidth/2;
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<width;j++)
		{
			Swap(image.data[i][j],image.data[i][image.infoHeader.biWidth-(j+1)]);
		}
		


	}
	Hien_Thi_Anh_Ra_Console_Result(image);
}

void Tao_Vien(Image2D &image)
{
	Hien_Thi_Anh_Ra_Console(image);
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			if(i<4||j<4||i>image.infoHeader.biHeight-4||j>image.infoHeader.biWidth-4)
			{
				image.data[i][j].b=255;
				image.data[i][j].g=0;
				image.data[i][j].r=0;
			}

		}

	}
	Hien_Thi_Anh_Ra_Console_Result(image);
}

void Hien_Thi_Anh_Ra_Console(Image2D &image)
{
	if(image.infoHeader.biHeight>=1000 || image.infoHeader.biWidth>=1000)
	{
		cout<<"Kich thuoc anh qua to khong hien thi tren man hinh console duoc"<<endl;
		return ;
	}

	 //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

	//Draw pixels
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			Pixels temp= image.data[i][j];
			COLORREF color = RGB(temp.b,temp.g,temp.r);
			SetPixel(mydc,j+50,i+50,color);
		}

	}


    ReleaseDC(myconsole, mydc);

}

void Hien_Thi_Anh_Ra_Console_Result(Image2D &image)
{
	if(image.infoHeader.biHeight>=1000 || image.infoHeader.biWidth>=1000)
	{
		cout<<"Kich thuoc anh qua to khong hien thi tren man hinh console duoc"<<endl;
		return ;
	}

	 //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

	//Draw pixels
	for(int i=0;i<image.infoHeader.biHeight;i++)
	{
		for(int j=0;j<image.infoHeader.biWidth;j++)
		{
			Pixels temp= image.data[i][j];
			COLORREF color = RGB(temp.b,temp.g,temp.r);
			SetPixel(mydc,j+100+image.infoHeader.biWidth,i+50,color);
		}

	}


    ReleaseDC(myconsole, mydc);

}




void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}


void Menu()
{
	while(true)
	{
		ifstream file_in;
		ofstream file_out;
		Image2D image;
		string filename;
		cout<<"Moi ban nhap ten file input:";
		fflush(stdin);
		getline(cin,filename);
		if(Read_File_BitMap(file_in,filename))
		{
			Read_Data_BitMap(file_in,image);
		}
		else
		{
			cout<<"Khong mo duoc file "<<filename<<" de doc"<<endl;
			return;
		}
		cout<<"====================MENU================"<<endl;
		cout<<"|1.Lam sang anh                        |"<<endl;
		cout<<"|2.Lam toi anh                         |"<<endl;
		cout<<"|3.Lam nong anh                        |"<<endl;
		cout<<"|4.Lam mat anh                         |"<<endl;
		cout<<"|5.Lam anh den trang                   |"<<endl;
		cout<<"|6.Lat anh theo chieu doc              |"<<endl;
		cout<<"|7.Lat anh theo chieu ngang            |"<<endl;
		cout<<"|8.Tao vien cho anh                    |"<<endl;
		cout<<"|9.Hien thi anh ra man hinh            |"<<endl;
		cout<<"|10.Thoat chuong trinh                 |"<<endl;
		cout<<"========================================"<<endl;
		cout<<"Moi ban nhap tuy chon:";
		string chon;
		fflush(stdin);
		getline(cin,chon);
		
		clrscr();
		

		if(chon=="1")
		{
			brighten(image);
			Write_Data_BitMap(file_out,image);
		}else if(chon=="2")
		{
			darken(image);
			Write_Data_BitMap(file_out,image);
		}else if(chon=="3")
		{
			Hot(image);
			Write_Data_BitMap(file_out,image);
		}else if(chon=="4")
		{
			Cold(image);
			Write_Data_BitMap(file_out,image);
		}else if(chon=="5")
		{
			grayscale(image);
			Write_Data_BitMap(file_out,image);
		}else if(chon=="6")
		{
			Lat_Anh_Theo_Chieu_Doc(image);
			Write_Data_BitMap(file_out,image);
		}else if(chon=="7")
		{
			Lat_Anh_Theo_Chieu_Ngang(image);
			Write_Data_BitMap(file_out,image);
		}else if(chon=="8")
		{
			Tao_Vien(image);
			Write_Data_BitMap(file_out,image);
		}else if(chon=="9")
		{
			Hien_Thi_Anh_Ra_Console(image);
		}else if(chon=="10")
		{
			break;
		}else
		{
			cout<<"Ban nhap yeu cau khong hop le!!!!"<<endl;
			continue;
		}






		cout<<"Ban co muon chinh anh nua khong?? Neu co an phim 1, neu khong an cac phim con lai"<<endl;
		string tuychon;
		fflush(stdin);
		getline(cin,tuychon);

		if(tuychon=="1")
		{
			for(int i=0;i<image.infoHeader.biHeight;i++)
			{
				delete[] image.data[i];
			}
			delete[] image.data;
			clrscr();
			continue;
		}
		else
		{
			
			file_in.close();
			file_out.close();
			for(int i=0;i<image.infoHeader.biHeight;i++)
			{
				delete[] image.data[i];
			}
			delete[] image.data;
			break;
		}
		
		





	}
	
	
}
