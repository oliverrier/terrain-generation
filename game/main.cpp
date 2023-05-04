#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include "engine/ImGUI/ImGUIManager.h"
#include "engine/MVP/Interfaces.h"


class MainWindow : public IView, public MyImGUI::ImguiWindow
{

public:
    MainWindow(std::string title) : ImguiWindow(title)
    {
    }
    ~MainWindow();

    void update() override
    {
        ImGui::Begin(ImguiWindow::m_title.c_str());
        slider->render();
        ImGui::End();
    }

    void render() override
    {
        update();
    }

    MyImGUI::ImguiSliderInt* slider;
    //MyImGUI::ImguiLineEdit* lineEdit;
};

class DataModel : public IModel
{
public:
    DataModel() : ageDuCapitaine(42)
    //, nomDuCapitaine(std::string("Jack Sparrow"))
    {
    }
    Observable<int> ageDuCapitaine;
    MyImGUI::Getter<int> getAgeDuCapitaine = [this]() { return ageDuCapitaine; };
    MyImGUI::Setter<int> setAgeDuCapitaine = [this](int value) { ageDuCapitaine = value; };

    //Observable<std::string> nomDuCapitaine;
};

/*
struct Presenter
{
    Presenter(DataModel* dataModel, MainWindow* view) : m_dataModel(dataModel), m_view(view)
    {
        onModelChanged();

        m_dataModel->ageDuCapitaine.connect([this](int){onModelChanged(); });
        //m_dataModel->nomDuCapitaine.connect([this](std::string){onModelChanged();});

        MyImGUI::Callback callback = [this]() {onViewChanged(); };

        m_view->slider->setCallback(callback);
        m_view->slider->setGetter(m_dataModel->getAgeDuCapitaine);
        m_view->slider->setSetter(m_dataModel->setAgeDuCapitaine);
        //QObject::connect(m_view->lineEdit, &QLineEdit::editingFinished, [this](){onViewChanged(); });
    }

    void onViewChanged()
    {
        m_dataModel->ageDuCapitaine = m_view->slider->getValue();
        //m_dataModel->nomDuCapitaine = m_view->lineEdit->text().toStdString();
    }

    void onModelChanged()
    {
        m_view->slider->setValue(m_dataModel->ageDuCapitaine);
        //auto toto = QString::fromStdString(m_dataModel->nomDuCapitaine);
        //m_view->lineEdit->setText(QString::fromStdString(m_dataModel->nomDuCapitaine));
        //emit m_view->lineEdit->editingFinished();
    }

private:
    DataModel* m_dataModel;
    MainWindow* m_view;
};
*/

int main()
{
    DataModel dataModel;
    // MainWindow view("My Window");
    // Presenter presenter(&dataModel, &view);


    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    bool buttonValue = false;
    MyImGUI::Callback callback = [&buttonValue]() {
        buttonValue = !buttonValue;
        std::cout << "Button pressed lolilol" << std::endl;
    };
    std::string buttonText = "My Button";
    // uniq ptr of input
    std::unique_ptr<MyImGUI::ImguiButton> button = std::make_unique<MyImGUI::ImguiButton>(buttonText, callback);
    MyImGUI::ImguiWindow window1("My Window");
    window1.addInput(std::move(button));


    // slider
    int sliderValue = 42;
    MyImGUI::Getter<int> getter = [&sliderValue]() { return sliderValue; };
    MyImGUI::Setter<int> setter = [&sliderValue](int value) { sliderValue = value; };
    std::unique_ptr<MyImGUI::ImguiSliderInt> slider = std::make_unique<MyImGUI::ImguiSliderInt>("My Slider", getter, setter);
    window1.addInput(std::move(slider));



    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        window1.update();

        ImGui::Begin("Debug");
        ImGui::Text("int : %d", getter());
        ImGui::Text("bool : %d", buttonValue);
        ImGui::End();

        // view.render();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
