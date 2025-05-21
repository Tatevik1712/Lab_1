#include <iostream>
#include <cstring>
#include <cstdarg>
#include <cstdlib>

class String {
private:

    char* str;  // Указатель на динамически выделенную строку
    int size;   // Размер строки (без нулевого символа)

    // Функция сообщения об ошибке
    void Error(int errorType, int badIndex = 0) const {
        cerr << "String error [" << errorType << "] at index " << badIndex << endl;
    }

    // Вспомогательная функция: возвращает длину строки
    static int StrLen(const char* s) {
        int len = 0;
        while (s[len] != '\0') ++len;
        return len;
    }

    // Вспомогательная функция: копирует строку src в dest
    static void StrCpy(char* dest, const char* src) {
        while ((*dest++ = *src++));
    }

    // Вспомогательная функция: добавляет строку src к dest
    static void StrCat(char* dest, const char* src) {
        while (*dest) dest++;
        while ((*dest++ = *src++));
    }

    // Вспомогательная функция: сравнивает две строки
    static int StrCmp(const char* s1, const char* s2) {
        while (*s1 && (*s1 == *s2)) { s1++; s2++; }
        return *(unsigned char*)s1 - *(unsigned char*)s2;
    }

    // Вспомогательная функция: находит подстроку needle в haystack
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
    // Конструктор: инициализация строкой C-типа (по умолчанию пустой)
    String(char* s = "") {
        size = StrLen(s);
        str = new char[size + 1];
        StrCpy(str, s);
    }

    // Конструктор копирования
    String(const String& s) {
        size = s.size;
        str = new char[size + 1];
        StrCpy(str, s.str);
    }

    // Деструктор: освобождение памяти
    ~String() {
        delete[] str;
    }

    // Оператор присваивания для объекта String
    String& operator= (const String& s) {
        if (this != &s) {
            delete[] str;
            size = s.size;
            str = new char[size + 1];
            StrCpy(str, s.str);
        }
        return *this;
    }

    // Оператор присваивания для C-строки
    String& operator= (char* s) {
        delete[] str;
        size = StrLen(s);
        str = new char[size + 1];
        StrCpy(str, s);
        return *this;
    }

    // Возвращает длину строки
    int Length() const {
        return size;
    }

    // Проверяет, пуста ли строка
    int IsEmpty() const {
        return size == 0;
    }

    // Очищает строку (делает её пустой)
    void Clear() {
        delete[] str;
        str = new char[1];
        str[0] = '\0';
        size = 0;
    }

    // Сравнивает текущую строку с другой строкой
    int Compare(const String& other) const {
        return StrCmp(str, other.str);
    }

    // Ищет подстроку внутри строки
    char* Find(const char* needle) const {
        return StrStr(str, needle);
    }

    // Форматирует строку аналогично sprintf
    void Format(const char* format, ...) {
        char buffer[1024];  // Временный буфер
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        va_end(args);
        *this = buffer; // Используем перегруженный оператор =
    }

    // Преобразует строку в целое число
    int ToInt() const {
        return atoi(str);
    }

    // Печатает строку в консоль
    void Print() const {
        cout << str << endl;
    }

    // Возвращает C-строку (char*)
    const char* CStr() const {
        return str;
    }
};
