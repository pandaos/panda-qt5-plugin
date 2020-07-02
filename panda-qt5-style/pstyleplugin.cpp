#include "pstyleplugin.h"
#include "modernstyle.h"

#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

QStringList ProxyStylePlugin::keys() const
{
    return {"panda"};
}

QStyle *ProxyStylePlugin::create(const QString &key)
{
    if (key != QStringLiteral("panda")) {
        return nullptr;
    }

    return new ModernStyle;
}
