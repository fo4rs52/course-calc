#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QString>
#include "ProductCatalog.h"

namespace Services {

    class StorageManager {
    private:
        QString m_filePath;

    public:
        explicit StorageManager(const QString& filePath = "products.json");

        bool saveCatalog(const ProductCatalog& catalog);
        bool loadCatalog(ProductCatalog& catalog);
    };

} 
#endif