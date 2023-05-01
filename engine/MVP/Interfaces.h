#pragma once

#include "Observable.h"

class IView
{
public:
    virtual ~IView() = default;
    virtual void update() = 0;
    virtual void render() = 0;

private:
    std::map<std::string, Observable> m_observables;
};

class IModel
{
public:
    virtual ~IModel() = default;
};

class IPresenter
{
public:
    virtual ~IPresenter() = default;
    virtual void setView(IView* view) = 0;
    virtual void setModel(IModel* model) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

private:
    IView* m_view;
    IModel* m_model;
};