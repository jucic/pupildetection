
// PupilDetectionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PupilDetection.h"
#include "PupilDetectionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPupilDetectionDlg 对话框



CPupilDetectionDlg::CPupilDetectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PUPILDETECTION_DIALOG, pParent)
	, numbofcir(0)
	, xvalue(0)
	, yvalue(0)
	, radius(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPupilDetectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, numbofcir);
	DDX_Text(pDX, IDC_EDIT2, xvalue);
	DDX_Text(pDX, IDC_EDIT3, yvalue);
	DDX_Text(pDX, IDC_EDIT4, radius);
}

BEGIN_MESSAGE_MAP(CPupilDetectionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPupilDetectionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPupilDetectionDlg::OnBnClickedButton2)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CPupilDetectionDlg 消息处理程序

BOOL CPupilDetectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//CPupilDetectionDlg* A=this;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPupilDetectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPupilDetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPupilDetectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CPupilDetectionDlg::thread01(LPVOID pParam)//pupilcamera
{
	//VideoCapture capture0(0);
	Mat initframe0, frame0;

	//CPupilDetectionDlg* A = new CPupilDetectionDlg;
	CPupilDetectionDlg* A = (CPupilDetectionDlg*)pParam;

	//AfxGetMainWnd()->m_hWnd;
	//HWND m_hWnd = (HWND)cvGetWindowHandle("PupoldetectionDlg");
	//HWND m_hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();

	CRect rect0;
	A->GetDlgItem( IDC_CAMERA2)->GetClientRect(rect0);
	//GetDlgItem(m_hWnd,IDC_CAMERA2)->GetClientRect(rect0);

	//::GetClientRect(::GetDlgItem(m_hWnd, IDC_CAMERA2), rect0);

	cv::namedWindow("myshowWnd2", WINDOW_NORMAL);
	cv::resizeWindow("myshowWnd2", rect0.Width(), rect0.Height());

	HWND hWnd0 = (HWND)cvGetWindowHandle("myshowWnd2");
	HWND hParent0 = ::GetParent(hWnd0);
	//::SetParent(hWnd0, GetDlgItem(m_hWnd, IDC_CAMERA2)->m_hWnd);
	::SetParent(hWnd0, A->GetDlgItem(IDC_CAMERA2)->m_hWnd);
	::ShowWindow(hParent0, SW_HIDE);

	string filename = "C:\\Users\\jucic\\Desktop\\研究生\\机器视觉\\pupilGlintVideo\\eye005.avi";//打开的视频文件  
	VideoCapture videocapture;
	videocapture.open(filename);

	double rate0 = videocapture.get(CV_CAP_PROP_FPS);//获取视频文件的帧率  
	int delay = cvRound(1000.000 / rate0);

	double fps;
	char string[10];  // 用于存放帧率的字符串
	double t = 0;

	while (true)
	{
		t = (double)cv::getTickCount();
		videocapture >> initframe0;//视频文件
	    //capture0 >> initframe0;//摄像头

		if (initframe0.empty()) break;

		cvtColor(initframe0, frame0, CV_RGB2GRAY);//C++风格接口

		//Mat element = getStructuringElement(MORPH_DILATE, Size(5, 5));//定义核  
		//morphologyEx(frame, frame, MORPH_OPEN, element);		//进行形态学操作  
		//morphologyEx(frame, frame, MORPH_CLOSE, element);		//进行形态学操作 

		GaussianBlur(frame0, frame0, Size(9, 9), 2, 2);

		//【4】进行霍夫圆变换
		vector<Vec3f> circles;
		HoughCircles(frame0, circles, CV_HOUGH_GRADIENT, 1.5, 10, 40, 40, 10, 30);//1.5, 10, 200, 100, 0, 0

		A->UpdateData(true);
		A->numbofcir = circles.size();
		//framerate0 = rate0;

		//【5】依次在图中绘制出圆  
		if (circles.size() > 0)
		{
			for (size_t i = 0; i < circles.size(); i++)
			{
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int Radius = cvRound(circles[i][2]);
				if (i == 0)
				{
					A->xvalue = cvRound(circles[i][0]);
					A->yvalue = cvRound(circles[i][1]);
					A->radius = cvRound(circles[i][2]);
				}
				//绘制圆心  
				circle(initframe0, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				//绘制圆轮廓  
				circle(initframe0, center, Radius, Scalar(155, 50, 255), 3, 8, 0);
			}
		}
		A->UpdateData(false);
		t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
		fps = 1.0 / t;
		sprintf_s(string, "%.2f", fps);      // 帧率保留两位小数
		std::string fpsString("FPS:");
		fpsString += string;                    // 在"FPS:"后加入帧率数值字符串
												// 将帧率信息写在输出帧上
		cv::putText(initframe0, // 图像矩阵
			fpsString,                  // string型文字内容
			cv::Point(5, 20),           // 文字坐标，以左上角为原点
			cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
			0.5, // 字体大小
			cv::Scalar(155, 50, 255));       // 字体颜色

		imshow("myshowWnd2", initframe0);
		waitKey(1);
	}
}

void CPupilDetectionDlg::on_mouse(int event, int x, int y, int flags, void *ustc)
//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号      
{
	Mat& image = *(cv::Mat*) ustc;//这样就可以传递Mat信息了，很机智  
	char temp[16];
	switch (event) {
	case CV_EVENT_LBUTTONDOWN://按下左键  
	{
		sprintf_s(temp, "(%d,%d)", x, y);
		putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		A->是否画矩形 = true;
		A->左击顶点 = Point(x, y);
	}   break;
	case CV_EVENT_MOUSEMOVE://移动鼠标  
	{
		A->鼠标位置 = Point(x, y);
		if (A->是否画矩形)
		{
		}
	}break;
	case EVENT_LBUTTONUP:
	{
		//A->鼠标位置 = Point(x, y);
		A->是否画矩形 = false;
		sprintf_s(temp, "(%d,%d)", x, y);
		putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		//调用函数进行绘制  
		cv::rectangle(image, A->左击顶点, A->鼠标位置, cv::Scalar(A->g_rng.uniform(0, 255), A->g_rng.uniform(0, 255), A->g_rng.uniform(0, 255)));//随机颜色    
	}break;
	}
}

void CPupilDetectionDlg::thread0(VideoCapture capture0)
{
	Mat initframe1;
	while (1)
	{
		capture0 >> initframe1;
		imshow("myshowWnd0", initframe1);
	}
}

void CPupilDetectionDlg::thread1(VideoCapture capture1)
{
	Mat initframe0;
	while (1)
	{
		capture1 >> initframe0;
		imshow("myshowWnd1", initframe0);
	}
}

void CPupilDetectionDlg::OnBnClickedButton1()//开始读入图像
{
	AfxBeginThread(thread01, this);

	VideoCapture capture0(0);
	Mat initframe0, frame0;
	capture0.set(CAP_PROP_FRAME_WIDTH, 320);
	capture0.set(CAP_PROP_FRAME_HEIGHT, 240);

	VideoCapture capture1(1);
	Mat initframe1, frame1;
	capture1.set(CAP_PROP_FRAME_WIDTH, 320);
	capture1.set(CAP_PROP_FRAME_HEIGHT, 240);

	CRect rect0;
	this->GetDlgItem(IDC_CAMERA3)->GetClientRect(rect0);
	cv::namedWindow("myshowWnd0", WINDOW_NORMAL);
	cv::resizeWindow("myshowWnd0", rect0.Width(), rect0.Height());
	HWND hWnd0 = (HWND)cvGetWindowHandle("myshowWnd0");
	HWND hParent0 = ::GetParent(hWnd0);
	::SetParent(hWnd0, this->GetDlgItem(IDC_CAMERA3)->m_hWnd);
	::ShowWindow(hParent0, SW_HIDE);

	CRect rect1;
	this->GetDlgItem(IDC_CAMERA4)->GetClientRect(rect1);
	cv::namedWindow("myshowWnd1", WINDOW_NORMAL);
	cv::resizeWindow("myshowWnd1", rect1.Width(), rect1.Height());
	HWND hWnd1 = (HWND)cvGetWindowHandle("myshowWnd1");
	HWND hParent1 = ::GetParent(hWnd1);
	::SetParent(hWnd1, this->GetDlgItem(IDC_CAMERA4)->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);

	capture0.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	capture0.set(CAP_PROP_FRAME_WIDTH, 1280);
	capture0.set(CAP_PROP_FRAME_HEIGHT, 720);

	capture1.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	capture1.set(CAP_PROP_FRAME_WIDTH, 1280);
	capture1.set(CAP_PROP_FRAME_HEIGHT, 720);

	thread task01(thread0, capture0);  //带参数子线程  
	thread task02(thread1, capture1);
	task01.detach();
	task02.detach();
}

void CPupilDetectionDlg::OnBnClickedButton2()
{

}


void CPupilDetectionDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonUp(nFlags, point);
}
//CPupilDetectionDlg* A = nullptr;