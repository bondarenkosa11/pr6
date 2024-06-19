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
class RealFile : public File {
private:
    std::string filename;
public:
    RealFile(const std::string& filename) : filename(filename) {}

    void open(const std::string& filename) override {
        std::cout << "Opening file: " << filename << std::endl;
    }

    void edit() override {
        std::cout << "Editing file: " << filename << std::endl;
    }

    void print() override {
        std::cout << "Printing file: " << filename << std::endl;
    }
};

// Заместитель (Proxy) для файлов
class ProxyFile : public File {
private:
    RealFile* realFile;
    std::string filename;
public:
    ProxyFile(const std::string& filename) : filename(filename), realFile(nullptr) {}

    void open(const std::string& filename) override {
        if (!realFile) {
            realFile = new RealFile(filename);
        }
        realFile->open(filename);
    }

    void edit() override {
        if (!realFile) {
            realFile = new RealFile(filename);
        }
        realFile->edit();
    }

    void print() override {
        if (!realFile) {
            realFile = new RealFile(filename);
        }
        realFile->print();
    }

    ~ProxyFile() {
        if (realFile) {
            delete realFile;
        }
    }
};

// Интерфейс для подсветки текста
class Highlighter {
public:
    virtual void highlight(const std::string& text) {
        std::cout << "Highlighting text: " << text << std::endl;
    }
    virtual ~Highlighter() {}
};

// Заместитель (Proxy) для подсветки текста
class ProxyHighlighter : public Highlighter {
private:
    Highlighter* realHighlighter;
public:
    ProxyHighlighter() : realHighlighter(nullptr) {}

    void highlight(const std::string& text) override {
        if (!realHighlighter) {
            realHighlighter = new Highlighter();
        }
        realHighlighter->highlight(text);
    }

    ~ProxyHighlighter() {
        if (realHighlighter) {
            delete realHighlighter;
        }
    }
};

// Класс TextEditor, который использует заместителя для подсветки текста
class TextEditor {
private:
    Highlighter* highlighter;

public:
    TextEditor(Highlighter* h) : highlighter(h) {}

    void highlightText(const std::string& text) {
        highlighter->highlight(text);
    }

    ~TextEditor() {
        delete highlighter;
    }
};

// Главная функция, демонстрирующая использование паттерна "Заместитель"
int main() {
    // Создаем заместителя для подсветки текста
    Highlighter* proxyHighlighter = new ProxyHighlighter();

    // Создаем текстовый редактор с использованием заместителя
    TextEditor editor(proxyHighlighter);

    // Используем текстовый редактор через заместителя
    editor.highlightText("This is a text to highlight.");

    // Освобождаем ресурсы
    delete proxyHighlighter;

    return 0;
}
