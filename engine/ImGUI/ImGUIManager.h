#pragma once

#include <functional>
#include <string>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <cassert>


namespace MyImGUI
{
    using Callback = std::function<void()>;
    template<typename T>
    using Getter = std::function<T()>;
    template<typename T>
    using Setter = std::function<void(T)>;


    class IImGUIInput
    {
    public:
        virtual ~IImGUIInput() = default;
        virtual void update() = 0;
        virtual void render() = 0;
    };

    class ImguiButton : public IImGUIInput
    {
    public:
        ImguiButton(std::string& text, Callback& callback)
            : m_text(text)
            , m_callback(callback)
        {}
        void update() override
        {
            if (ImGui::Button(m_text.c_str())) {
                m_callback();
            }
        }

        void render() override
        {
            update();
        }

    protected:
        std::string m_text;
        Callback m_callback;
    };


    class ImguiWindow
    {
    public:
        ImguiWindow(std::string title)
            : m_title(title)
        {}

        void update()
        {
            ImGui::Begin(m_title.c_str());
            for (auto& input : m_inputs) {
                input->update();
            }
            ImGui::End();
        }

        void render()
        {
            update();
        }

        void addInput(std::unique_ptr<IImGUIInput> input)
        {
            m_inputs.push_back(std::move(input));
        }

    private:
        std::string m_title;
        std::vector<std::unique_ptr<IImGUIInput>> m_inputs;
    };

}
