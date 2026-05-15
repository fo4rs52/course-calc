#include "StorageManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

namespace Services {

    StorageManager::StorageManager(const QString& filePath) : m_filePath(filePath) {}

    bool StorageManager::saveCatalog(const ProductCatalog& catalog) {
        QFile file(m_filePath);
        if (!file.open(QIODevice::WriteOnly)) {
            return false;
        }

        QJsonArray jsonArray;
        for (const auto& product : catalog.getAllProducts()) {
            jsonArray.append(product->toJson());
        }

        QJsonDocument doc(jsonArray);
        file.write(doc.toJson());
        file.close();
        return true;
    }

    bool StorageManager::loadCatalog(ProductCatalog& catalog) {
        QFile file(m_filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            return false;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isArray()) return false;

        catalog.clear();
        QJsonArray jsonArray = doc.array();

        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject obj = jsonArray[i].toObject();
            auto product = std::make_shared<Models::Product>();
            product->fromJson(obj);
            catalog.addProduct(product);
        }
        return true;
    }

}