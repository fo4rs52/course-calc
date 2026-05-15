#ifndef PRODUCTCATALOG_H
#define PRODUCTCATALOG_H

#include <vector>
#include <memory>
#include "models/Product.h"

namespace Services {

    class ProductCatalog {
    private:
        std::vector<std::shared_ptr<Models::Product>> m_products;

    public:
        ProductCatalog() = default;

        void addProduct(std::shared_ptr<Models::Product> product);
        std::vector<std::shared_ptr<Models::Product>> getAllProducts() const;
        void clear();
    };

}
#endif