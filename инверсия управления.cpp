#include <iostream>
#include <string>

// Интерфейс для работы с файлами
class File {
public:
    virtual void open(const std::string& filename) = 0;
    virtual void edit() = 0;
    virtual void print() = 0;
    virtual ~File() {}
};

// Конкретная реализация обычного текстового файла
class PlainTextFile : public File {
public:
    void open(const std::string& filename) override {
        std::cout << "Opening plain text file: " << filename << std::endl;
    }

    void edit() override {
        std::cout << "Editing plain text file" << std::endl;
    }

    void print() override {
        std::cout << "Printing plain text file" << std::endl;
    }
};

// Интерфейс для подсветки текста
class Highlighter {
public:
    virtual void highlight(const std::string& text) = 0;
    virtual ~Highlighter() {}
};

// Конкретная реализация подсветки для обычного текста (без подсветки)
class PlainTextHighlighter : public Highlighter {
public:
    void highlight(const std::string& text) override {
        std::cout << "Plain text does not support highlighting: " << text << std::endl;
    }
};

// Класс TextEditor, представляющий текстовый редактор с внедрением зависимостей
class TextEditor {
private:
    File* file;
    Highlighter* highlighter;

public:
    // Конструктор с инъекцией зависимостей
    TextEditor(File* file, Highlighter* highlighter)
        : file(file), highlighter(highlighter) {}

    void openFile(const std::string& filename) {
        file->open(filename);
    }

    void editFile() {
        file->edit();
    }

    void printFile() {
        file->print();
    }

    void highlightText(const std::string& text) {
        highlighter->highlight(text);
    }

    ~TextEditor() {
        delete file;
        delete highlighter;
    }
};

// Главная функция, демонстрирующая использование Dependency Injection
int main() {
    // Создаем объекты зависимостей
    File* plainTextFile = new PlainTextFile();
    Highlighter* plainTextHighlighter = new PlainTextHighlighter();

    // Создаем текстовый редактор с инъекцией зависимостей
    TextEditor editor(plainTextFile, plainTextHighlighter);

    // Используем текстовый редактор
    editor.openFile("example.txt");
    editor.editFile();
    editor.highlightText("This is a plain text file.");
    editor.printFile();

    // Освобождаем ресурсы
    delete plainTextFile;
    delete plainTextHighlighter;

    return 0;
}
