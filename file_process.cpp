//
// Created by 黄智忠 on 19/6/2018.
//

#include "file_process.h"

/*********** *********** *********** *********** *********** *********** ***********
* Function Name :printInfo
* Description :输出文件信息
*********** *********** *********** *********** *********** *********** ***********/
void printInfo(BITMAPFILEHEADER fileHeader,BITMAPINFOHEADER infoHeader)
{
    printf("\n\n\tThe information of your map:\n");
    printf("\t----------------------------------------------\n");

    printf("\tbfOffBits:\t%d\n",fileHeader.bfOffBits);
    printf("\tbfSize:\t\t%d\n\n",fileHeader.bfSize);

    printf("\tbiBitCount:\t%d\n",infoHeader.biBitCount);
    printf("\tbiHeight:\t%d\n",infoHeader.biHeight);
    printf("\tbiWidth:\t%d\n",infoHeader.biWidth);
    printf("\tbiSize:\t\t%d\n",infoHeader.biSize);
    printf("\tbiClrUsed:\t%d\n\n\n",infoHeader.biClrUsed);
}
/*********** *********** *********** *********** *********** *********** ***********
* Function Name :printInfo
* Description :输出画板信息
*********** *********** *********** *********** *********** *********** ***********/
void printPalette(RGBQUAD *rgbPalette,int sizeOfPalette)
{
    int i;

    printf("\tThe Palette of your map:\n");
    printf("\t----------------------------------------------\n");
    for(i=0;i<sizeOfPalette;i++)
    {
        printf("\t%d/%d:",i+1,sizeOfPalette);
        printf("\trgbBlue=%d\t",(rgbPalette+i)->rgbBlue);
        printf("\trgbGreen=%d\t",(rgbPalette+i)->rgbGreen);
        printf("\trgbRed=%d\n",(rgbPalette+i)->rgbRed);
    }
    printf("\n\n\n");
}

//unsigned char *pBmpBuf;//读入图像的数据指针
//int bmpWidth;//图像的宽
//int bmpHeight;//图像的高
//RGBQUAD *pColorTable;//颜色表指针
//int biBitCount;//图像类型，每像素的位数

bool readBmp(char *bmpName, unsigned char*& pBmpBuf, int& bmpWidth, int& bmpHeight, RGBQUAD*& pColorTable, int& biBitCount)
{

    //二进制方式打开
    FILE *fp=fopen(bmpName,"rb");
    if(fp==0)
        return 0;
    //跳过位图文件头结构BITMAPFILEHEADER
    fseek(fp,sizeof(BITMAPFILEHEADER),0);
    //定义位图头结构变量，读取位图信息头进内存放在变量head中
    BITMAPINFOHEADER head;
    fread(&head,sizeof(BITMAPINFOHEADER),1,fp);
    bmpWidth=head.biWidth;
    bmpHeight=head.biHeight;
    biBitCount=head.biBitCount;
    //定义变量计算图像每行像素所占的字节数
    int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
    //灰度图像有颜色表，且颜色表表项为256
    if(biBitCount==8){
        //申请颜色表所需的空间，读颜色表进内存
        pColorTable=new RGBQUAD[256];
        fread(pColorTable,sizeof(RGBQUAD),256,fp);
    }
    //申请位图数据所需的空间，读位图数据进内存
    pBmpBuf=new unsigned char[lineByte * bmpHeight];
    fread(pBmpBuf,lineByte * bmpHeight,1,fp);
    //关闭文件
    fclose(fp);
    return 1;
}


bool saveBmp(char *bmpName,unsigned char *imgBuf,int width,
             int height,int biBitCount,RGBQUAD *pColorTable)
{
    //如果位图数据指针为0，则没有数据传入，函数返回
    if(!imgBuf)
        return 0;
    //颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
    int colorTablesize=0;
    if(biBitCount==8)
        colorTablesize=1024;
    //待存储图像每行字节数为4的倍数
    int lineByte=(width * biBitCount/8+3)/4*4;
    //以二进制写的方式打开文件
    FILE *fp=fopen(bmpName,"wb");
    if(fp==0)
        return 0;
    //申请位图头文件结构变量，填写文件头信息
    BITMAPFILEHEADER fileHead;
    fileHead.bfType=0x4D42;//bmp类型
    //bfSize是图像文件四个组成部分之和
    fileHead.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
                    +colorTablesize+lineByte*height;
    fileHead.bfReserved1=0;
    fileHead.bfReserved2=0;
    //bfOffBits是图像文件前三个部分所需空间之和
    fileHead.bfOffBits=54+colorTablesize;
    //写文件头进文件
    fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
    //申请位图信息头结构变量，填写信息头信息
    BITMAPINFOHEADER head;
    head.biBitCount=biBitCount;
    head.biClrImportant=0;
    head.biClrUsed=0;
    head.biCompression=0;
    head.biHeight=height;
    head.biPlanes=1;
    head.biSize=40;
    head.biSizeImage=lineByte*height;
    head.biWidth=width;
    head.biXPelsPerMeter=0;
    head.biYPelsPerMeter=0;
    //写位图信息头进内存
    fwrite(&head,sizeof(BITMAPINFOHEADER),1,fp);
    //如果是灰度图像，有颜色表，写入文件
    if(biBitCount==8)
        fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
    //写位图数据进文件
    fwrite(imgBuf,height*lineByte,1,fp);
    //关闭文件
    fclose(fp);
    return 1;
}


bool proportion(unsigned char *bmpBuf,int width,int height)
{   //直方图均衡化
    //统计各个灰度的个数
    int DegreeCount[256]={0};
    BYTE DegreeMap[256]={0};//灰度映射表
    int i,j;
    unsigned char *num;
    for(i=0;i<height;i++)
        for(j=0;j<width;j++)
        {
            num=(unsigned char *)(bmpBuf+width*i+j);
            DegreeCount[(*num)]++;//该灰度值加一
        }

    for(i=0;i<256;i++)
    {
        int temp=0;
        for(j=0;j<=i;j++)
            temp+=DegreeCount[j];
        DegreeMap[i]=(BYTE)(temp*255/width/height);//此公式的由来？归一化后的复原
    }
    //处理每个象素
    for(i=0;i<height;i++)
        for(j=0;j<width;j++)
        {
            num=(unsigned char *)(bmpBuf+i*width+j);
            *num=DegreeMap[*num];//根据映射表计算新的灰度值
        }
    return 1;
}

