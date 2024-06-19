#include <iostream>
#include <string>

// ��������� ��� ������ � �������
class File {
public:
    virtual void open(const std::string& filename) = 0;
    virtual void edit() = 0;
    virtual void print() = 0;
    virtual ~File() {}
};

// ���������� ���������� �������� ���������� �����
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

// ��������� ��� ��������� ������
class Highlighter {
public:
    virtual void highlight(const std::string& text) = 0;
    virtual ~Highlighter() {}
};

// ���������� ���������� ��������� ��� �������� ������ (��� ���������)
class PlainTextHighlighter : public Highlighter {
public:
    void highlight(const std::string& text) override {
        std::cout << "Plain text does not support highlighting: " << text << std::endl;
    }
};

// ����� TextEditor, �������������� ��������� �������� � ���������� ������������
class TextEditor {
private:
    File* file;
    Highlighter* highlighter;

public:
    // ����������� � ��������� ������������
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

// ������� �������, ��������������� ������������� Dependency Injection
int main() {
    // ������� ������� ������������
    File* plainTextFile = new PlainTextFile();
    Highlighter* plainTextHighlighter = new PlainTextHighlighter();

    // ������� ��������� �������� � ��������� ������������
    TextEditor editor(plainTextFile, plainTextHighlighter);

    // ���������� ��������� ��������
    editor.openFile("example.txt");
    editor.editFile();
    editor.highlightText("This is a plain text file.");
    editor.printFile();

    // ����������� �������
    delete plainTextFile;
    delete plainTextHighlighter;

    return 0;
}
