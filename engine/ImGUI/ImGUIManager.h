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


    template<typename T>
    class IImGUIInput
    {
    public:
        virtual ~IImGUIInput() = default;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual T getValue() const = 0;
        virtual void setValue(const T& value) = 0;
    };

    class ImguiButton : public IImGUIInput<bool>
    {
    public:
        ImguiButton(std::string& text, Callback& callback)
            : m_text(text)
            , m_callback(callback)
        {}
        void update() override
        {
            if (ImGui::Button(m_text.c_str()))
                m_callback();
        }

        void render() override
        {
            update();
        }

        bool getValue() const override
        {
            assert(false);
            return false;
        }

        void setValue(const bool& value) override
        {
            assert(false);
        }

    protected:
        std::string m_text;
        Callback m_callback;
    };

    class ImguiButtonOnOff : public IImGUIInput<bool>
    {
    public:
        ImguiButtonOnOff(std::string& text) : m_text(text)
        {}

        ImguiButtonOnOff(std::string& text, Getter<bool>& getter, Setter<bool>& setter)
            : m_text(text)
            , m_getter(getter)
            , m_setter(setter)
        {}
        void update() override
        {

            // concat text with value
            m_text += " : ";
            m_text += m_getter() ? "On" : "Off";
            if (ImGui::Button(m_text.c_str()))
                m_setter(!m_getter());
        }

        void render() override
        {
            update();
        }

        bool getValue() const override
        {
            return m_getter();
        }

        void setValue(const bool& value) override
        {
            m_setter(value);
        }

    protected:
        std::string m_text;
        Getter<bool> m_getter;
        Setter<bool> m_setter;
    };

}
