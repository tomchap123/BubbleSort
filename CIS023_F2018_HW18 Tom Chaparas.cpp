//Project:  CIS023_F2018_HW18 Tom Chaparas
//Module:   CIS023_F2018_HW18 Tom Chaparas.cpp
//Author:   Tom Chaparas
//Date:     November 10, 2018
//Purpose:  Review interfacing with a linked list.
//          Perform a bubble sort.

#include "stdafx.h"
#include "CIS023_F2018_HW18 Tom Chaparas.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

char szFileName[] = "CIS023_F2018_HW18_Data.txt";	// file that contains data for linked list
HWND hWnd_BTN_Sort;							// Sort button
HWND hWnd_BTN_Close;						// Close button
HWND hWnd_Listbox;							// List box
HWND hWnd_STC_Start;						// start time static control
HWND hWnd_STC_End;							// end time static control
HWND hWnd_STC_Comps;						// # of comparisons static control

LinkedListClass* list;						//pointer to linked list
                                            //NodeClass* node;							//create node

                                            // Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void CreateMainWindowLayout(HWND);			// place controls on main window
BOOL LoadList();							// read input file and create linked list
void FillListBox();							// send linked list to listbox
int InsertionSort();						// perform insertion sort
int BubbleSort();                           //perform bubble sort
int SortBubble();
int SortBubble2();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, (IDC_CIS023_F2018_HW18TOMCHAPARAS), szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS023_F2018_HW18TOMCHAPARAS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS023_F2018_HW18TOMCHAPARAS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CIS023_F2018_HW18TOMCHAPARAS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 375, 350, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case BN_CLICKED:	// capture button click
            if (LOWORD(lParam) == (WORD)hWnd_BTN_Sort)
            {
                EnableWindow(hWnd_BTN_Sort, false);	// disable sort button during sort operation

                SYSTEMTIME sysTime;
                TCHAR szOutput[MAX_LOADSTRING];

                // get and display start time
                GetSystemTime(&sysTime);
                _stprintf_s(szOutput, TEXT("%d:%d.%d"), sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
                SetWindowText(hWnd_STC_Start, szOutput);
                EnableWindow(hWnd_STC_Start, true); // Search start time static control

                //int iComps = InsertionSort();		// perform the sort operation
                int iComps = BubbleSort();          //performs bubble Sort operation
                //int iComps = SortBubble2();
                //SortBubble();
                                                    // get and display end time
                GetSystemTime(&sysTime);
                _stprintf_s(szOutput, TEXT("%d:%d.%d"), sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
                SetWindowText(hWnd_STC_End, szOutput);
                EnableWindow(hWnd_STC_End, true);	// Search end time static control

                                                    // message, how many comparisons in sort
                _stprintf_s(szOutput, TEXT("Number of comparisons:   %i"), iComps);
                SetWindowText(hWnd_STC_Comps, szOutput);
                EnableWindow(hWnd_STC_Comps, true);	// enable static control

                FillListBox();						// reload list box with sorted list
                EnableWindow(hWnd_BTN_Sort, true);	// enable sort button

                break;
            }
            else if (LOWORD(lParam) == (WORD)hWnd_BTN_Close)
            {
                DestroyWindow(hWnd);
            }
            break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_CREATE:
        CreateMainWindowLayout(hWnd);				// layout
        if (LoadList())								// automatically load the list when the program loads
        {
            FillListBox();							// load unordered list into list box
            EnableWindow(hWnd_BTN_Sort, true);		// enable sort button
        }
        break;

    case WM_DESTROY:

        if (list)						//if linked list was fillled
            delete list;				//		delete it

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// layout the controls on the main window
void CreateMainWindowLayout(HWND hWnd)
{
    // buttons
    hWnd_BTN_Sort = CreateWindow(TEXT("BUTTON"), TEXT("Sort"),
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        20, 70, 80, 30, hWnd, NULL, NULL, NULL);

    hWnd_BTN_Close = CreateWindow(TEXT("BUTTON"), TEXT("Close"),
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        20, 120, 80, 30, hWnd, NULL, NULL, NULL);

    hWnd_Listbox = CreateWindow(TEXT("LISTBOX"), NULL,
        WS_VISIBLE | WS_CHILD | LBS_NOTIFY |
        WS_VSCROLL | WS_BORDER | LBS_HASSTRINGS,
        140, 50, 200, 200, hWnd, NULL, NULL, NULL);

    hWnd_STC_Start = CreateWindow(TEXT("STATIC"),
        TEXT("88:88.888"),
        WS_VISIBLE | WS_CHILD, 60, 200, 70, 20, hWnd, NULL, NULL, NULL);

    hWnd_STC_End = CreateWindow(TEXT("STATIC"),
        TEXT("88:88.888"),
        WS_VISIBLE | WS_CHILD, 60, 225, 70, 20, hWnd, NULL, NULL, NULL);

    hWnd_STC_Comps = CreateWindow(TEXT("STATIC"),
        TEXT(""),
        WS_VISIBLE | WS_CHILD, 20, 250, 300, 20, hWnd, NULL, NULL, NULL);

    // static text - labels
    CreateWindow(TEXT("STATIC"),
        TEXT("INSERTION SORT"),
        WS_VISIBLE | WS_CHILD, 100, 20, 260, 20, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"),
        TEXT("Start:"),
        WS_VISIBLE | WS_CHILD, 20, 200, 40, 20, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"),
        TEXT("End:"),
        WS_VISIBLE | WS_CHILD, 20, 225, 40, 20, hWnd, NULL, NULL, NULL);


    EnableWindow(hWnd_BTN_Sort, false);		// disable sort button
    EnableWindow(hWnd_STC_Start, false);	// disable start time
    EnableWindow(hWnd_STC_End, false);		// disable end time
    EnableWindow(hWnd_STC_Comps, false);	// disable # of inserts

}

// opens the file and loads the linked list
BOOL LoadList()
{
    ifstream inFile;							// file handle
    string strLine;								// a line in the file

    try
    {
        inFile.open(szFileName);				// open the file

        if (!inFile.is_open())
            throw 0;

        list = new LinkedListClass;				//create linkled list object

        getline(inFile, strLine);
        while (inFile.good())					// if more to read
        {
            list->Append(strLine);				//add a node to the list

            getline(inFile, strLine);			// get the next line from the file

        }

        inFile.close();							// close the file
    }
    catch (int)
    {
        MessageBox(NULL,
            TEXT("File did not open correctly"),
            TEXT("File error"),
            MB_ICONEXCLAMATION);

        return false;
    }

    return true;
}

// fill list box
void FillListBox()
{
    TCHAR szOutput[TCHAR_SIZE];					//output TCHAR
    string strData;								//data from node
    NodeClass* tempNode;						//temp node for traversing

    SendMessage(hWnd_Listbox,					//send message to listbox
        LB_RESETCONTENT,						//reset, empty the listbox
        0, 0);									//WPARAM, LPARAM not used

    list->SetCurrentNode(list->GetFirstNode());	//start at first node in the list
    tempNode = list->GetCurrentNode();			//grab the current node

    while (tempNode != nullptr)					//traverse to the end of list
    {
        strData = tempNode->GetString();		//get the string from the node

        StringtoTCHAR(&strData, szOutput);		//convert string to TCHAR

        SendMessage(hWnd_Listbox,				//send message to listbox
            LB_ADDSTRING,						//append string
            0,									//WPARAM not used
            LPARAM(szOutput));					//TCHAR to add to the listbox

        list->Next();							//move to next node in the list
        tempNode = list->GetCurrentNode();		//grab the current node
    }

}
// Perform an Insertion Sort
int InsertionSort()
{
    NodeClass* tempNode;						//temp node for holding position
    string strData;								//node data for comparison and insertion
    int iCompareCount = 0;						//return no. of comparisons
    bool bMove;									//if a move needs to happen
    int iNodeCount;								//number of nodes in the list


    list->SetCurrentNode(list->GetFirstNode());	//start at first node in the list
    iNodeCount = 1;								//1st node
    while (list->GetCurrentNode() != list->GetLastNode())
    {
        list->Next();							//advance to the next node
        iNodeCount++;							//count the node
    }

    list->SetCurrentNode(list->GetFirstNode());	//move to first node in the list
    list->Next();								//sort starts at the 2nd node

    for (int i = 1; i < iNodeCount; i++)
    {
        tempNode = list->GetCurrentNode();		//save current position in the list
        strData = tempNode->GetString();		//get data to compare
        bMove = false;							//true if a node needs to be moved


        do										//run backwards until at beginning of list
        {
            iCompareCount++;					//about to do a comparison

            if (list->GetCurrentNode() == list->GetFirstNode())		//special treatment of 1st node
                bMove = true;
            else if (list->GetCurrentNode()->GetPrevNode()->GetString() < strData) //move
                bMove = true;

            if (bMove)
            {
                list->Insert(strData);				//inser here using node's data
                list->SetCurrentNode(tempNode);		//reset location
                list->Delete();						//delete the old node
                tempNode = list->GetCurrentNode();	//resave temp location
                break;								//jump out of Do loop
            }

            list->Previous();						//go back one node if bMove did not happen

        } while (list->GetCurrentNode() != nullptr);	//loop until before 1st node
    }
    //major loop

    list->SetCurrentNode(list->GetFirstNode());

    return iCompareCount;
}
int BubbleSort()
{
    NodeClass* tempNode;
    int iNodeCount;
    int i = 1;
    string strData1;
    string strData2;
    string strTemp;

    list->SetCurrentNode(list->GetFirstNode());	//start at first node in the list
    iNodeCount = 1;

    while (list->GetCurrentNode() != list->GetLastNode())
    {
        list->Next();							//advance to the next node
        iNodeCount++;							//count the node
    }
    list->SetCurrentNode(list->GetFirstNode());	//move to first node in the list

    while (i < iNodeCount)
    {
        for (int j = 0; j < iNodeCount - i; j++)
        {
            strData1 = list->GetCurrentNode()->GetString();
            list->Next();
            strData2 = list->GetCurrentNode()->GetString();

            if (strData1.compare(strData2) > 0)
            {
                strTemp = strData1;
                strData1 = strData2;
                strData2 = strTemp;
            }
            else if (strData1.compare(strData2) > 0)
            {
                strTemp = strData2;
                strData2 = strData1;
                strData1 = strTemp;
            }
        }
        i++;
    }


    return iNodeCount;
}
//perform Bubble Sort
/*int BubbleSort()
{
    NodeClass* tempNode1 = nullptr;                 //for comaprison
    NodeClass* tempNode2 = nullptr;                 //.
    NodeClass* tempNode3 = nullptr;                 //.
    int iCompareCount = 0;                          //track num of camparisons
    int iNodeCount;                                 //num of nodes in the list
    string str1;                                    //use to compare node data
    string str2;                                    //use to compare node data

    list->SetCurrentNode(list->GetFirstNode());	    //start at first node in the list
    iNodeCount = 1;

    while (list->GetCurrentNode() != list->GetLastNode())
    {

        list->Next();                               //move to next node in linked list
        iNodeCount++;                               //count the node
    }

    list->SetCurrentNode(list->GetFirstNode());	    //move to first node in the list
    //list->Next();								    //sort starts at the 2nd node
        
    for (int i = 1; i < iNodeCount; i++)
    {
        tempNode1 = list->GetFirstNode();		//save current position in the list
        str1 = tempNode1->GetString();		    //get data to compare
        list->Next();                           //advance to next node
        tempNode2 = list->GetCurrentNode();
        str2 = tempNode2->GetString();

        if (str1 < str2)
        {

            list->SetCurrentNode(tempNode1);
            list->

        }
        else
        {
            list->SetCurrentNode(tempNode1);
        }

    }
    
    
    
    
    
    /*
    str1 = tempNode1->GetString();		        //get data to compare
         
        tempNode1 = list->GetFirstNode();	        //save current position in the list                            
        tempNode2 = list->GetCurrentNode();         
        str2 = tempNode2->GetString();              //get data for comparison
        tempNode1->SetString(str1);
        tempNode2->SetString(str2);

        if (str1 < str2)                 //if str1 < str2
        {
           
            list->SetCurrentNode(tempNode2);
            tempNode2 = tempNode2->GetNextNode();
            //firstNode = tempNode1;
            list->SetCurrentNode(tempNode1);
        }
        else if (str1.compare(str2) > 0)             //if str1 > str2
        {
            list->SetCurrentNode(tempNode1);
        }
        else (str1.compare(str2) == 0)              //if strings are the same
            ;

       

        iNodeCount++;                               //increment counter
    
    return iCompareCount;
}*/
void swap(NodeClass* a, NodeClass* b)
{
    b = a;
    a = b;
}
int SortBubble2()
{
    return 0;
}
/*int SortBubble()
{
    NodeClass* tempNode;						//temp node for holding position
    NodeClass* tempNode2;
    string strData;								//node data for comparison and insertion
    string strData2;
    string strTemp;
    int iCompareCount = 0;						//return no. of comparisons
    bool bMove = false;									//if a move needs to happen
    int iNodeCount;								//number of nodes in the list


    list->SetCurrentNode(list->GetFirstNode());	//start at first node in the list
    iNodeCount = 1;								//1st node
    while (list->GetCurrentNode() != list->GetLastNode())   //get Node count
    {
        list->Next();							//advance to the next node
        iNodeCount++;							//count the node
    }

    list->SetCurrentNode(list->GetFirstNode());	//move to first node in the list
    //list->Next();								//sort starts at the 2nd node

    for (int i = 1; i < iNodeCount; i++)
    {
        tempNode = list->GetFirstNode();		//save current position in the list
        strData = tempNode->GetString();		//get data to compare
        list->Next();
        tempNode2 = list->GetCurrentNode();
        strData2 = tempNode2->GetString();
        //bMove = false;							//true if a node needs to be moved


        do										//run backwards until at beginning of list
        {
            iCompareCount++;					//about to do a comparison

            if (tempNode->GetString() > tempNode2->GetString())		
            {
                strTemp = tempNode->GetString();
                tempNode->GetString() = tempNode2->GetString();
                tempNode2->GetString() = strTemp;
            }
                //bMove = true;
            
            else if (list->GetCurrentNode()->GetPrevNode()->GetString() < strData) //move
                //bMove = true;

            if (bMove)
            {
                list->Insert(strData);				//insert here using node's data
                list->SetCurrentNode(tempNode);		//reset location
                list->Delete();						//delete the old node
                tempNode = list->GetCurrentNode();	//resave temp location
                break;								//jump out of Do loop
            }

            list->Previous();						//go back one node if bMove did not happen

        } while (list->GetCurrentNode() != nullptr);	//loop until before 1st node
    }
    //major loop

    list->SetCurrentNode(list->GetFirstNode());

    return iCompareCount;
}
    /*****
    NodeClass* tempNode;						//temp node for holding position
    string strData;								//node data for comparison and insertion
    int iCompareCount = 0;						//return no. of comparisons
    bool bMove;									//if a move needs to happen
    int iNodeCount;								//number of nodes in the list
   /* NodeClass* topNode = nullptr;                 //for comaprison
    NodeClass* nextNode = nullptr;                //.
    NodeClass* tempNode = nullptr;                //.
    int iCompareCount = 0;                          //track num of camparisons
    int iNodeCount = 0;                                 //num of nodes in the list
    string str1;                                    //use to compare node data
    string str2; */                                   //use to compare node data


   // list->SetCurrentNode(list->GetFirstNode());	    //start at first node in the list
//iNodeCount = 1;

//while (list->GetFirstNode() != list->GetLastNode())
//{
 //       list->Next();                               //move to next node in linked list
//iNodeCount++;                               //count the node
//}

    //list->SetCurrentNode(list->GetFirstNode());	//move to first node in the list
    //list->Next();								//sort starts at the 2nd node

//for (int i = 1; i < iNodeCount - 1; i++)
//{
       /* for (int j = 1; j < iNodeCount -i - 1; j++)
        {  
            topNode = list->GetFirstNode();
            nextNode = topNode->GetNextNode();
            str1 = topNode->GetString();
            str2 = nextNode->GetString();
                if (str1 < str2)
                {

                    nextNode = topNode->GetNextNode();
                    topNode = tempNode->GetNextNode();
                    tempNode = topNode; 
            
                }
        }*/
 //   }
   
  /* topNode = list->GetFirstNode();
         nextNode = topNode->GetNextNode();
         str1 = topNode->GetString();
         str2 = nextNode->GetString();*/     

    
    



   /* while (list->GetCurrentNode() != list->GetLastNode())
    {
        list->Next();                               //move to next node in linked list
        iNodeCount++;                               //count the nodes for later use
    }
        tempNode1 = list->GetFirstNode();		//save current position in the list
        str1 = tempNode1->GetString();		    //get data to compare
        //->Next();                               //advance to next node
        str2 = tempNode2->GetString();
        list->Insert(str2);
        

        for (int i = 1; i < iNodeCount; i++)
        {

            

             if (str1.compare(str2) < 0)
            {
                tempNode1->SetNextNode(tempNode2);
            }
            else
            {
                tempNode2->SetNextNode(tempNode1);
            }
         }
        

        return iNodeCount;
    }*/
    
 

   
