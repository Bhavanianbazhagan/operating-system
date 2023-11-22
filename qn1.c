#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    HANDLE hProcess;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file1> <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Execute 'cat' command on the specified file in the parent process
    if (!CreateProcess(NULL,"cat.exe",argv[1], NULL,FALSE,0,NULL,NULL,&si,&pi))     
    {
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    // Wait for the child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("\nParent Process:\n");
    printf("\n\tParent Process ID: %d\n", GetCurrentProcessId());

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Execute the second command in the child process
    if (!CreateProcess(NULL,   // No module name (use command line)
                       argv[2],  // Command to be executed
                       NULL,     // Command line parameters
                       NULL,     // Process handle not inheritable
                       FALSE,    // Set handle inheritance to FALSE
                       0,        // No creation flags
                       NULL,     // Use parent's environment block
                       NULL,     // Use parent's starting directory
                       &si,      // Pointer to STARTUPINFO structure
                       &pi))     // Pointer to PROCESS_INFORMATION structure
    {
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    // Wait for the child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("\nChild Process:\n");
    printf("\n\tChild Process Parent ID: %d\n", GetCurrentProcessId());
    printf("\n\tChild Process ID: %d\n", pi.dwProcessId);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}



