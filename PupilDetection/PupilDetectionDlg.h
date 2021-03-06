#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include "afxcmn.h"  
// PupilDetectionDlg.h: 头文件
//
#include "afxwin.h"
#include "Resource.h"
#include<string>  

#include <opencv.hpp>
#include <iostream>
#include <thread>
#include <Windows.h>  
using namespace std;

using namespace cv;
#pragma once


// CPupilDetectionDlg 对话框
class CPupilDetectionDlg : public CDialog
{
	// 构造
public:
	CPupilDetectionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUPILDETECTION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:

	static UINT thread01(LPVOID pParam);
	static UINT thread022(LPVOID pParam);
	static UINT thread02(LPVOID pParam);
	static UINT thread03(LPVOID pParam);
	static void on_mouse(int event, int x, int y, int flags, void *ustc);

	static void thread0(VideoCapture capture0);
	static void thread1(VideoCapture capture1);

	//void thread02();
	afx_msg void OnBnClickedButton1();
	int numbofcir;
	double xvalue;
	double yvalue;
	double radius;

	//VideoCapture capture0;
	//VideoCapture capture1;

	RNG& g_rng = theRNG();
	//RNG g_rng(12345);//毛大大的博客里看到的生成随机数，用于生成随机颜色  
	bool 是否画矩形 = false;//不可避免地还是要定义几个全局变量，伤心  
	Point 左击顶点 = Point(-1, -1);
	Point 鼠标位置 = Point(-1, -1);

	afx_msg void OnBnClickedButton2();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);


};
//static Mat initframe2, frame2;
static CPupilDetectionDlg* A=new CPupilDetectionDlg;
//void on_mouse(int event, int x, int y, int flags, void *ustc);

//extern CPupilDetectionDlg A;
//extern CPupilDetectionDlg B;
//extern CPupilDetectionDlg C;