#include <iostream>
#include <cstring>
#include <cstdarg>
#include <cstdlib>

class String {
private:

    char* str;  // ��������� �� ����������� ���������� ������
    int size;   // ������ ������ (��� �������� �������)

    // ������� ��������� �� ������
    void Error(int errorType, int badIndex = 0) const {
        cerr << "String error [" << errorType << "] at index " << badIndex << endl;
    }

    // ��������������� �������: ���������� ����� ������
    static int StrLen(const char* s) {
        int len = 0;
        while (s[len] != '\0') ++len;
        return len;
    }

    // ��������������� �������: �������� ������ src � dest
    static void StrCpy(char* dest, const char* src) {
        while ((*dest++ = *src++));
    }

    // ��������������� �������: ��������� ������ src � dest
    static void StrCat(char* dest, const char* src) {
        while (*dest) dest++;
        while ((*dest++ = *src++));
    }

    // ��������������� �������: ���������� ��� ������
    static int StrCmp(const char* s1, const char* s2) {
        while (*s1 && (*s1 == *s2)) { s1++; s2++; }
        return *(unsigned char*)s1 - *(unsigned char*)s2;
    }

    // ��������������� �������: ������� ��������� needle � haystack
    static char* StrStr(char* haystack, const char* needle) {
        if (!*needle) return haystack;
        for (; *haystack; ++haystack) {
            if (*haystack == *needle) {
                const char* h = haystack;
                const char* n = needle;
                while (*h && *n && *h == *n) { h++; n++; }
                if (!*n) return haystack;
            }
        }
        return nullptr;
    }

public:
    // �����������: ������������� ������� C-���� (�� ��������� ������)
    String(char* s = "") {
        size = StrLen(s);
        str = new char[size + 1];
        StrCpy(str, s);
    }

    // ����������� �����������
    String(const String& s) {
        size = s.size;
        str = new char[size + 1];
        StrCpy(str, s.str);
    }

    // ����������: ������������ ������
    ~String() {
        delete[] str;
    }

    // �������� ������������ ��� ������� String
    String& operator= (const String& s) {
        if (this != &s) {
            delete[] str;
            size = s.size;
            str = new char[size + 1];
            StrCpy(str, s.str);
        }
        return *this;
    }

    // �������� ������������ ��� C-������
    String& operator= (char* s) {
        delete[] str;
        size = StrLen(s);
        str = new char[size + 1];
        StrCpy(str, s);
        return *this;
    }

    // ���������� ����� ������
    int Length() const {
        return size;
    }

    // ���������, ����� �� ������
    int IsEmpty() const {
        return size == 0;
    }

    // ������� ������ (������ � ������)
    void Clear() {
        delete[] str;
        str = new char[1];
        str[0] = '\0';
        size = 0;
    }

    // ���������� ������� ������ � ������ �������
    int Compare(const String& other) const {
        return StrCmp(str, other.str);
    }

    // ���� ��������� ������ ������
    char* Find(const char* needle) const {
        return StrStr(str, needle);
    }

    // ����������� ������ ���������� sprintf
    void Format(const char* format, ...) {
        char buffer[1024];  // ��������� �����
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        va_end(args);
        *this = buffer; // ���������� ������������� �������� =
    }

    // ����������� ������ � ����� �����
    int ToInt() const {
        return atoi(str);
    }

    // �������� ������ � �������
    void Print() const {
        cout << str << endl;
    }

    // ���������� C-������ (char*)
    const char* CStr() const {
        return str;
    }
};
