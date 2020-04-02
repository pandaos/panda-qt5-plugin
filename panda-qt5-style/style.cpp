#include "style.h"
#include "styleanimation.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <QWidget>
#include <QWindow>
#include <QAbstractItemView>

#include <QPainter>

Style::Style() 
    : QProxyStyle("fusion")
{
    // QStyleFactory::create("panda")
    // Code reference qfusionstyle.cpp
}

void Style::polish(QWidget *w)
{
    QProxyStyle::polish(w);

    if (w->inherits("QPushButton") || w->inherits("QCheckBox")
     || w->inherits("QComboBox") || w->inherits("QRadioButton")
     || w->inherits("QScrollBar") || w->inherits("QToolButton")
     || w->inherits("QAbstractSpinBox") || w->inherits("QAbstractSpinBox")
     || w->inherits("QTabBar"))
        w->setAttribute(Qt::WA_Hover, true);

    if (w->inherits("QScrollBar"))
        w->setAttribute(Qt::WA_OpaquePaintEvent, false);

    // transparent tooltips
    if (w->inherits("QTipLabel")) {
        w->setAttribute(Qt::WA_TranslucentBackground);
    }
}

void Style::unpolish(QWidget *w)
{
    QProxyStyle::unpolish(w);

    if (w->inherits("QPushButton") || w->inherits("QCheckBox")
     || w->inherits("QComboBox") || w->inherits("QRadioButton")
     || w->inherits("QScrollBar") || w->inherits("QToolButton")
     || w->inherits("QAbstractSpinBox") || w->inherits("QAbstractSpinBox")
     || w->inherits("QTabBar"))
        w->setAttribute(Qt::WA_Hover, false);
}

void Style::polish(QApplication *app)
{
    QFont font("Ubuntu");
    font.setPixelSize(15);
    app->setFont(font);
}

void Style::polish(QPalette &palette)
{
    QColor windowBg(255, 255, 255);
    palette.setBrush(QPalette::Window, windowBg);
}

void Style::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {

    case PE_Frame: {
        break;
    }

    case PE_FrameTabWidget: {
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::transparent);
        painter->drawRect(option->rect);
        break;
    }

    case PE_PanelMenu:
    case PE_FrameMenu: {
        QColor color(255, 255, 255, 30);
        painter->fillRect(option->rect, color);
        break;
    }

    case PE_PanelLineEdit: {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        if (const QStyleOptionFrame *panel = qstyleoption_cast<const QStyleOptionFrame *>(option)) {
            painter->setPen(Qt::NoPen);
            painter->setBrush(QColor(255, 255, 255, 80));
            painter->drawRoundedRect(panel->rect, 6, 6);
        }
        painter->restore();
        break;
    }

    case PE_FrameLineEdit: {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        QRectF frameRect(option->rect);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(242, 242, 242));
        painter->drawRoundedRect(frameRect.adjusted(0.5, 0.5, -0.5, -0.5), 6, 6);
        painter->restore();
        break;
    }

    case PE_PanelButtonCommand: {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(242, 242, 242));

        if (option->state & State_MouseOver) {
            // press
            if (option->state & State_Sunken) {
                painter->setBrush(QColor(204, 204, 204));
            } else {
            // hover
                painter->setBrush(QColor(224, 224, 224));
            }
        }
        painter->drawRoundedRect(option->rect,6, 6);
        painter->restore();
        break;
    }

    default:
        QProxyStyle::drawPrimitive(element, option, painter, widget);
        break;
    }
}

void Style::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case CE_TabBarTabShape:
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
            if (drawTabBar(painter, tab, widget))
                return;
        }
        break;
    case CE_TabBarTabLabel:
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
            if (drawTabBarLabel(painter, tab, widget))
                return;
        }
        break;
    default:
        QProxyStyle::drawControl(element, option, painter, widget);
        break;
    }
}

QRect Style::subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex *option, QStyle::SubControl sc, const QWidget *widget) const
{
    switch (cc) {
    case CC_ScrollBar: {
        auto rect = QProxyStyle::subControlRect(cc, option, sc, widget);
        if (sc == SC_ScrollBarSlider) {
            rect.adjust(1, 1, -1, -1);
            if (option->state.testFlag(QStyle::State_Horizontal)) {
                rect.adjust(1, 0, -1, 0);
            } else {
                rect.adjust(0, 1, 0, -1);
            }
            return rect;
        }
        return rect;
    }
    }

    return QProxyStyle::subControlRect(cc, option, sc, widget);
}

void Style::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option,
                                      QPainter *painter, const QWidget *widget) const
{
    switch (control) {
    default:
        QProxyStyle::drawComplexControl(control, option, painter, widget);
        break;
    }
}

int Style::styleHint(QStyle::StyleHint sh, const QStyleOption *opt, const QWidget *w, QStyleHintReturn *shret) const
{
    switch (sh) {
    default:
        break;
    }

    return QProxyStyle::styleHint(sh, opt, w, shret);
}

int Style::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch (metric) {
    case PM_ScrollBarExtent: return 11;
    case PM_ScrollBarSliderMin: return 40;
    default:
        break;
    }

    return QProxyStyle::pixelMetric(metric, option, widget);
}