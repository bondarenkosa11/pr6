#include <iostream>
#include <string>
#include <vector>

// Интерфейс компонента
class Component {
public:
    virtual void open() = 0;
    virtual void edit() = 0;
    virtual void print() = 0;
    virtual ~Component() {}
};

// Конкретная реализация файла
class File : public Component {
private:
    std::string name;
public:
    File(const std::string& name) : name(name) {}

    void open() override {
        std::cout << "Opening file: " << name << std::endl;
    }

    void edit() override {
        std::cout << "Editing file: " << name << std::endl;
    }

    void print() override {
        std::cout << "Printing file: " << name << std::endl;
    }
};

// Конкретная реализация папки
class Folder : public Component {
private:
    std::string name;
    std::vector<Component*> children;
public:
    Folder(const std::string& name) : name(name) {}

    void add(Component* component) {
        children.push_back(component);
    }

    void open() override {
        std::cout << "Opening folder: " << name << std::endl;
        for (auto child : children) {
            child->open();
        }
    }

    void edit() override {
        std::cout << "Editing folder: " << name << std::endl;
        for (auto child : children) {
            child->edit();
        }
    }

    void print() override {
        std::cout << "Printing folder: " << name << std::endl;
        for (auto child : children) {
            child->print();
        }
    }

    ~Folder() {
        for (auto child : children) {
            delete child;
        }
    }
};

// Класс TextEditor, который использует компоновщик для работы с файлами и папками
class TextEditor {
private:
    Component* root;

public:
    TextEditor(Component* r) : root(r) {}

    void openAll() {
        root->open();
    }

    void editAll() {
        root->edit();
    }

    void printAll() {
        root->print();
    }

    ~TextEditor() {
        delete root;
    }
};

// Главная функция, демонстрирующая использование паттерна Компоновщик
int main() {
    // Создаем компоненты: файлы и папки
    Component* file1 = new File("file1.txt");
    Component* file2 = new File("file2.txt");
    Component* folder1 = new Folder("Folder 1");

    // Добавляем файлы в папку
    dynamic_cast<Folder*>(folder1)->add(file1);
    dynamic_cast<Folder*>(folder1)->add(file2);

    // Создаем текстовый редактор с корневым компонентом
    TextEditor editor(folder1);

    // Используем текстовый редактор через компоновщик
    editor.openAll();
    editor.editAll();
    editor.printAll();

    return 0;
}
